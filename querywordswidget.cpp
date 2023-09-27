#include "querywordswidget.h"
#include "ui_querywordswidget.h"

#include <regex>
#include <QFile>
#include <QDebug>
#include <string>
#include <QKeyEvent>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>

QueryWordsWidget::QueryWordsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWordsWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("查单词界面"));
    // 初始化时间种子
    qsrand(QDateTime::currentMSecsSinceEpoch());

    m_translator = new Translator;

    ui->lineEdit_word->installEventFilter(this);
    ui->lineEdit_word_baidu->installEventFilter(this);
//    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
//    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
}

QueryWordsWidget::~QueryWordsWidget()
{
    delete ui;
}

QString QueryWordsWidget::unicodeToUtf8(QString str)
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

QString QueryWordsWidget::myregex(const QString &qstr)
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

void QueryWordsWidget::recvMap(QMap<QString, QString> wordMap)
{
    m_wordMap = wordMap;
}

void QueryWordsWidget::dealAddWord(QPair<QString, QString> newWord)
{
    m_wordMap.insert(newWord.first, newWord.second);
}

void QueryWordsWidget::dealDelWord(QPair<QString, QString> delWord)
{
    m_wordMap.remove(delWord.first);
}

void QueryWordsWidget::parsingJson(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {   //判断是否请求成功
        QString all = reply->readAll();   //读出返回数据
//        qDebug() << all ;   //打印出来会发现中文和一些外文是Unicode编码的转义字符，如\\u187d
        QString re = myregex(all);   //解析出翻译结果，即取出dst字段
//        qDebug()<<re;
        QString res = unicodeToUtf8(re);    //unicode转utf8
//        qDebug()<<res ;
        ui->plainTextEdit_baidu->setPlainText(res);  //更新控件上的内容
    }
    else{
        qDebug() << reply->errorString() << " error " << reply->error();
    }
}

bool QueryWordsWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress && watched == ui->lineEdit_word)
    {
        QKeyEvent *ke = dynamic_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
        {
            on_pushButton_queryWord_clicked();
            return true;
        }
    }

    if(event->type() == QEvent::KeyPress && watched == ui->lineEdit_word_baidu)
    {
        QKeyEvent *ke = dynamic_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
        {
            on_pushButton_queryWord_baidu_clicked();
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void QueryWordsWidget::on_pushButton_queryWord_clicked()
{
    if(ui->lineEdit_word->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入单词！"), QMessageBox::Ok);
        ui->lineEdit_word->clear();
        ui->plainTextEdit_show->clear();
        return;
    }

    QString word = ui->lineEdit_word->text();

    if(m_wordMap.contains(word))
    {
        ui->plainTextEdit_show->clear();
        ui->plainTextEdit_show->setPlainText(m_wordMap.value(word));
    }
    else
    {
        QMessageBox::information(this, tr("提示"), tr("当前单词未收录"), QMessageBox::Ok);
        ui->lineEdit_word->clear();
        ui->plainTextEdit_show->clear();
    }
}

void QueryWordsWidget::on_lineEdit_word_textChanged(const QString &arg1)
{
    if(ui->lineEdit_word->text().isEmpty())
        ui->plainTextEdit_show->clear();
}

void QueryWordsWidget::on_lineEdit_word_baidu_textEdited(const QString &arg1)
{
    if(ui->lineEdit_word_baidu->text().isEmpty())
        ui->plainTextEdit_baidu->clear();
}

void QueryWordsWidget::on_pushButton_queryWord_baidu_clicked()
{
    int index;
    QString str = ui->lineEdit_word_baidu->text();   //获取输入框中的内容
    if(isChinese(str))
        index = 0;  // 输入的是中文，转换成英文
    else
        index = 1;  // 输入的是英文，转换成中文
    m_translator->SetQstr(str);     //传入需要翻译
    m_translator->SetIndex(index);  //传入下标
    QString url = m_translator->GetUrl();     //获取url
    //1. 创建一个请求
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    //2. 创建一个管理器
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
   // 3. 连接请求结束信号
    connect(manager, &QNetworkAccessManager::finished, this, &QueryWordsWidget::parsingJson);
    //4. 发送GET请求
    manager->get(request);
}

bool QueryWordsWidget::isChinese(const QString &str)
{
    for (const QChar& ch : str) {
        ushort unicode = ch.unicode();
        if (unicode >= 0x4E00 && unicode <= 0x9FFF) {
            return true;  // 包含中文字符
        }
    }
    return false;  // 不包含中文字符
}
