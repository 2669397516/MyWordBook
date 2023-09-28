#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <regex>
#include <QDebug>
#include <string>
#include <QMimeData>
#include <QClipboard>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("我的单词本"));
    this->setWindowIcon(QIcon(":/MyWordBook.ico"));

    init();
}

MainWindow::~MainWindow()
{
    if(!m_showTranslators->isHidden())
        m_showTranslators->close();
    delete ui;
}

void MainWindow::init()
{
    m_file.setFileName(m_fileName);

    m_translator = new Translator;

    m_setAppidSecretKey = new setAppidSecretkey;
    m_setAppidSecretKey->show();
    connect(m_setAppidSecretKey, &setAppidSecretkey::sendMessage, this, &MainWindow::dealMessage);

    m_showTranslators = new ShowTranslators();

    m_hotKey = new QHotkey(QKeySequence(Qt::CTRL + Qt::Key_F9), true, this);
    connect(m_hotKey, &QHotkey::activated, this, &MainWindow::handleHotkeyActivated);

    m_queryWordWidget = new QueryWordsWidget(m_appid, m_secret_key);
    m_addWord = new AddWord(m_fileName);
    m_reciteWordsWidget = new ReciteWordsWidget;
    m_wordListWidget = new WordListWidget;
    m_learnIPA = new LearnIPA;

    ui->stackedWidget->addWidget(m_queryWordWidget);
    ui->stackedWidget->addWidget(m_addWord);
    ui->stackedWidget->addWidget(m_reciteWordsWidget);
    ui->stackedWidget->addWidget(m_wordListWidget);
    ui->stackedWidget->addWidget(m_learnIPA);

    ui->stackedWidget->setCurrentWidget(m_queryWordWidget);

    connect(ui->toolButton_queryWords, &QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_queryWordWidget);
    });
    connect(ui->toolButton_addWord, &QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_addWord);
    });
    connect(ui->toolButton_reciteWords, &QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_reciteWordsWidget);
    });
    connect(ui->toolButton_wordList, &QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_wordListWidget);
    });
    connect(ui->toolButton_learnIPA, &QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_learnIPA);
    });

    // 初始化容器
    if(!m_file.open(QIODevice::ReadOnly))
        QMessageBox::information(this, tr("提示"), tr("文件存放路径错误！"), QMessageBox::Ok);

    QTextStream in(&m_file);
    in.setCodec("UTF-8");   // 设置编码

    bool isKey = true;
    QString key;
    QString value;

    while (!in.atEnd())
    {
        if(isKey)
        {
            key = in.readLine();
        }
        else
        {
            value = in.readLine();
            m_wordMap.insert(key, value);
        }

        isKey = !isKey;
    }

    m_file.close();

    // 将容器发送给子对象
    connect(this, &MainWindow::sendMap, m_addWord, &AddWord::recvMap);
    connect(this, &MainWindow::sendMap, m_queryWordWidget, &QueryWordsWidget::recvMap);
    connect(this, &MainWindow::sendMap, m_reciteWordsWidget, &ReciteWordsWidget::recvMap);
    connect(this, &MainWindow::sendMap, m_wordListWidget, &WordListWidget::recvMap);
    emit sendMap(m_wordMap);

    connect(m_addWord, &AddWord::addWord, this, &MainWindow::dealAddWord);
    connect(m_addWord, &AddWord::addWord, m_queryWordWidget, &QueryWordsWidget::dealAddWord);
    connect(m_addWord, &AddWord::addWord, m_reciteWordsWidget, &ReciteWordsWidget::dealAddWord);
    connect(m_addWord, &AddWord::addWord, m_wordListWidget, &WordListWidget::dealAddWord);

    connect(m_addWord, &AddWord::delWord, this, &MainWindow::dealDelWord);
    connect(m_addWord, &AddWord::delWord, m_queryWordWidget, &QueryWordsWidget::dealDelWord);
    connect(m_addWord, &AddWord::delWord, m_reciteWordsWidget, &ReciteWordsWidget::dealDelWord);
    connect(m_addWord, &AddWord::delWord, m_wordListWidget, &WordListWidget::dealDelWord);
}

QFile &MainWindow::getFile()
{
    return m_file;
}

QString MainWindow::unicodeToUtf8(QString str)
{
    QString result;
    int index = str.indexOf("\\u");
//    qDebug()<<index;
    //判断是否存在为转移字符，实践表明只有英文字母是可以正常显示不需要转码的
    if(index!=-1){
        /* 判断字符串是否全为转义字符，实践表明中文和韩文等全是转移
         * 法语和德语只有个别特殊符号是转义字符
         *  */
        if(index==0){   //全为转义
            while (index != -1){
                QString s1 = str.mid(index + 2, 4);
                result.append(s1.toUShort(0, 16));
                index = str.indexOf("\\u", index+5);
            }
            return result.toUtf8().constData();
        }
        else{   //部分转义
            while (index != -1){
                QString s1 = str.mid(index + 2, 4);
                result=s1.toUShort(0, 16);
                str.replace(index-1,7,result.toUtf8().constData());
                index = str.indexOf("\\u", index+5);
            }
            return str;
        }
    }
    return str;
//    return result.toUtf8().constData();
}

QString MainWindow::myregex(const QString &qstr)
{
    std::string ans;
    std::string str = qstr.toStdString();
    std::string pattern = "\"(.+?)\"";
    regex e("\\[(.*)\\]");
    regex r(pattern);
    smatch m;
    regex_search(str, m, e);

    std::string temp = m[1];
    auto res = vector<std::string>(9);

    sregex_iterator pos(temp.cbegin(), temp.cend(), r), end;
    for (; pos != end; ++pos) {
        res.push_back(pos->str(1));
    }
    for (auto temp : res)
        ans = temp;

    return QString::fromStdString(ans);
}

void MainWindow::dealAddWord(QPair<QString, QString> newWord)
{
    m_wordMap.insert(newWord.first, newWord.second);
}

void MainWindow::dealDelWord(QPair<QString, QString> delWord)
{
    m_wordMap.remove(delWord.first);
}

void MainWindow::parsingJson(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {   //判断是否请求成功
        QString all = reply->readAll();   //读出返回数据
//        qDebug() << all ;   //打印出来会发现中文和一些外文是Unicode编码的转义字符，如\\u187d
        QString re = myregex(all);   //解析出翻译结果，即取出dst字段
//        qDebug()<<re;
        QString res = unicodeToUtf8(re);    //unicode转utf8
//        qDebug() << res;
        // 弹出一个对话框输出翻译
        m_showTranslators->setText(res);

        m_showTranslators->show();
    }
    else{
        qDebug() << reply->errorString() << " error " << reply->error();
    }
}

void MainWindow::dealMessage(string appid, string secret_key)
{
    m_appid = appid;
    m_secret_key = secret_key;
}

void MainWindow::on_toolButton_setPath_clicked()
{
    QString newFileName = QFileDialog::getOpenFileName(NULL, tr("选择文件"),"D:/","*.txt");

    if(newFileName == "")
        newFileName = m_fileName;

    m_file.setFileName(newFileName);

    // 更新容器
    m_wordMap.clear();
    if(!m_file.open(QIODevice::ReadOnly))
        QMessageBox::information(this, tr("提示"), tr("文件存放路径错误！"), QMessageBox::Ok);

    QTextStream in(&m_file);
    in.setCodec("UTF-8");   // 设置编码

    bool isKey = true;
    QString key;
    QString value;

    while (!in.atEnd())
    {
        if(isKey)
        {
            key = in.readLine();
        }
        else
        {
            value = in.readLine();
            m_wordMap.insert(key, value);
        }

        isKey = !isKey;
    }

    m_file.close();

    emit sendMap(m_wordMap);
}

void MainWindow::handleHotkeyActivated()
{
    int index;
    QString str = getClipboardText();   //获取剪切板上的文本
    // 去掉剪切板中的'' '\n' '\t'
    str.remove(QChar(' '), Qt::CaseInsensitive);
    str.remove(QChar('\n'), Qt::CaseInsensitive);
    str.remove(QChar('\t'), Qt::CaseInsensitive);
    str.remove(QChar('~'), Qt::CaseInsensitive);
    str.remove(QChar('-'), Qt::CaseInsensitive);
    str.remove(QChar('_'), Qt::CaseInsensitive);
    str.remove(QChar('='), Qt::CaseInsensitive);
    str.remove(QChar('+'), Qt::CaseInsensitive);
    if(isChinese(str))
        index = 0;  // 输入的是中文，转换成英文
    else
        index = 1;  // 输入的是英文，转换成中文
    m_translator->SetQstr(str);     //传入需要翻译
    m_translator->SetIndex(index);  //传入下标
    QString url = m_translator->GetUrl(m_appid, m_secret_key);     //获取url
    //1. 创建一个请求
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    //2. 创建一个管理器
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
   // 3. 连接请求结束信号
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::parsingJson);
    //4. 发送GET请求
    manager->get(request);
}

QString MainWindow::getClipboardText()
{
    QString clipboardText;

    const QClipboard *clipboard = QGuiApplication::clipboard();
    if (clipboard->mimeData()->hasText()) {
        clipboardText = clipboard->text();
    }

    return clipboardText;
}

bool MainWindow::isChinese(const QString& str)
{
    for (const QChar& ch : str) {
        ushort unicode = ch.unicode();
        if (unicode >= 0x4E00 && unicode <= 0x9FFF) {
            return true;  // 包含中文字符
        }
    }
    return false;  // 不包含中文字符
}
