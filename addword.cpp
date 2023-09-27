#include "addword.h"
#include "ui_addword.h"

#include <QDebug>
#include <QMessageBox>
#include <QTemporaryFile>

AddWord::AddWord(QString fileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWord),
    m_fileName(fileName)
{
    ui->setupUi(this);

    m_file.setFileName(fileName);
}

AddWord::~AddWord()
{
    delete ui;
}

void AddWord::recvMap(QMap<QString, QString> wordMap)
{
    m_wordMap = wordMap;
}

void AddWord::on_pushButton_add_clicked()
{
    if(ui->plainTextEdit_chinese->toPlainText().isEmpty() || ui->plainTextEdit_english->toPlainText().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入完整的中英文！"), QMessageBox::Ok);
        ui->plainTextEdit_chinese->clear();
        ui->plainTextEdit_english->clear();
        return;
    }

    QString english = ui->plainTextEdit_english->toPlainText();
    english.remove(QChar(' '), Qt::CaseInsensitive);
    english.remove(QChar('\t'), Qt::CaseInsensitive);
    english.remove(QChar('\n'), Qt::CaseInsensitive);
    // 如果当前单词已经收录
    if(m_wordMap.find(english) != m_wordMap.end())
    {
        QMessageBox::information(this, tr("提示"), tr("当前单词已经收录"), QMessageBox::Ok);
        ui->plainTextEdit_english->clear();
        ui->plainTextEdit_chinese->clear();
        return;
    }

    QString chinese = ui->plainTextEdit_chinese->toPlainText();
    chinese.remove(QChar(' '), Qt::CaseInsensitive);
    chinese.remove(QChar('\t'), Qt::CaseInsensitive);
    chinese.remove(QChar('\n'), Qt::CaseInsensitive);

    m_wordMap.insert(english, chinese); // 会自动按照字母序来插入数据

    // 将新单词加入word.txt文件中
    if(!m_file.open(QIODevice::Append | QIODevice::Text))
        QMessageBox::information(this, tr("提示"), tr("文件打开失败！"), QMessageBox::Ok);
    QTextStream in(&m_file);
    in.setCodec("UTF-8");
    in << endl << english << endl << chinese;

    QMessageBox::information(this, tr("提示"), tr("单词添加成功！"), QMessageBox::Ok);
    ui->plainTextEdit_chinese->clear();
    ui->plainTextEdit_english->clear();

    m_file.close();

    emit addWord(QPair<QString, QString>(english, chinese));
}

void AddWord::on_pushButton_del_clicked()
{
    if(ui->plainTextEdit_english->toPlainText().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入你想要删除的单词！"), QMessageBox::Ok);
        return;
    }

    QString str = ui->plainTextEdit_english->toPlainText();
    QString delWordEnglish;
    for(auto x : str)
    {
        if(x == ' ' || x == '\t')   // 输入的空格和'\t'全部删除
            continue;
        delWordEnglish.push_back(x);
    }

    if(m_wordMap.value(delWordEnglish) == "")
    {
        QMessageBox::information(this, tr("提示"), tr("当前单词未收录！"), QMessageBox::Ok);
        ui->plainTextEdit_english->clear();
        ui->plainTextEdit_chinese->clear();
        return;
    }

    // 获取要删除对象的中文
    QString delWordChinese = m_wordMap.value(delWordEnglish);

    switch (QMessageBox::information(this, tr("删除单词"), tr("是否删除:") + delWordEnglish, QMessageBox::Yes | QMessageBox::No)) {
    case QMessageBox::Yes:
        m_wordMap.remove(delWordEnglish);  // 在容器中删除当前对象
        if(m_file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // 在.txt文件中删除当前对象
            QTextStream stream(&m_file);
            stream.setCodec("UTF-8"); // 根据文本编码进行设置

            QString line;
            QStringList lines;
            while (!stream.atEnd())
            {
                line = stream.readLine();
                if (line != delWordEnglish && line != delWordChinese)
                {
                    lines.append(line);
                }
            }

            m_file.resize(0);

            for (const QString& line : lines) {
                stream << line << endl;
            }

            QMessageBox::information(this, tr("提示"), tr("单词删除成功！"), QMessageBox::Ok);

            ui->plainTextEdit_chinese->clear();
            ui->plainTextEdit_english->clear();

            // 需要通知查单词窗口，删除的单词不能查阅了
            emit delWord(QPair<QString, QString> (delWordEnglish, delWordChinese));
        }
        else
        {
            // m_file打开失败
            QMessageBox::warning(this, tr("提示"), tr("文件打开失败"), QMessageBox::Ok);
        }

        m_file.close();
        break;
    case::QMessageBox::No:
        break;
    default:
        break;
    }
}

void AddWord::on_pushButton_clear_clicked()
{
    ui->plainTextEdit_chinese->clear();
    ui->plainTextEdit_english->clear();
}
