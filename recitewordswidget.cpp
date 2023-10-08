#include "recitewordswidget.h"
#include "ui_recitewordswidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

ReciteWordsWidget::ReciteWordsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReciteWordsWidget)
{
    ui->setupUi(this);
//    ui->lineEdit_translate->installEventFilter(this);
    ui->pushButton_hidden->setEnabled(false);
}

ReciteWordsWidget::~ReciteWordsWidget()
{
    delete ui;
}

void ReciteWordsWidget::recvMap(QMap<QString, QString> wordMap)
{
    m_wordMap = wordMap;
    m_wordVector.clear();
    for(auto itr = m_wordMap.begin(); itr != m_wordMap.end(); ++itr)
    {
        m_wordVector.push_back(itr.key());
    }

    if(m_wordVector.isEmpty())
    {
        ui->plainTextEdit_word->clear();
        return;
    }
    int count = m_wordVector.size();
    int num = rand() % count;
    QString key = m_wordVector[num];
    ui->plainTextEdit_word->setPlainText(key);
}

void ReciteWordsWidget::dealAddWord(QPair<QString, QString> newWord)
{
    m_wordMap.insert(newWord.first, newWord.second);
    m_wordVector.clear();
    for(auto itr = m_wordMap.begin(); itr != m_wordMap.end(); ++itr)
    {
        m_wordVector.push_back(itr.key());
    }
}

void ReciteWordsWidget::dealDelWord(QPair<QString, QString> delWord)
{
    m_wordMap.remove(delWord.first);
    m_wordVector.clear();
    for(auto itr = m_wordMap.begin(); itr != m_wordMap.end(); ++itr)
    {
        m_wordVector.push_back(itr.key());
    }
}

bool ReciteWordsWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress && watched == ui->lineEdit_translate)
    {
        QKeyEvent *ke = dynamic_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
        {
            on_pushButton_ok_clicked();
            return true;
        }
    }
}

void ReciteWordsWidget::on_pushButton_next_clicked()
{
    // 默认是随机背诵
    if(m_wordVector.isEmpty())
        return;
    ui->plainTextEdit_translate->clear();
    int count = m_wordVector.size();
    int num;
    if (m_isReciteRand)
        num = rand() % count;
    else if (m_isReciteASC)
    {
        if (curNum == count)
        {
            curNum = 0;
            num = curNum;
        }
        else
            num = ++curNum;
//        qDebug() << num;
    }
    QString key = m_wordVector[num];
    ui->plainTextEdit_word->setPlainText(key);

    ui->pushButton_look->setEnabled(true);
    ui->pushButton_hidden->setEnabled(false);
}

void ReciteWordsWidget::on_pushButton_last_clicked()
{
    // 默认是随机背诵
    if(m_wordVector.isEmpty())
        return;
    ui->plainTextEdit_translate->clear();
    int count = m_wordVector.size();
    int num;
    if (m_isReciteRand)
        num = rand() % count;
    else if (m_isReciteASC)
    {
        if (curNum == 0)
        {
            curNum = count;
            num = curNum;
        }
        else
            num = --curNum;
    }
    QString key = m_wordVector[num];
    ui->plainTextEdit_word->setPlainText(key);

    ui->pushButton_look->setEnabled(true);
    ui->pushButton_hidden->setEnabled(false);
}

void ReciteWordsWidget::on_pushButton_look_clicked()
{
    QString key = ui->plainTextEdit_word->toPlainText();
    QString value = m_wordMap.value(key);
    ui->plainTextEdit_translate->setPlainText(value);

    ui->pushButton_look->setEnabled(false);
    ui->pushButton_hidden->setEnabled(true);
}

void ReciteWordsWidget::on_pushButton_ok_clicked()
{
    if(ui->lineEdit_translate->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入翻译！"), QMessageBox::Ok);
        return;
    }

    QString translate = ui->lineEdit_translate->text();

    QString key = ui->plainTextEdit_word->toPlainText();

    QString value = m_wordMap.value(key);

    if(value.contains(translate))
    {
        QMessageBox::information(this, tr("提示"), tr("翻译正确！"), QMessageBox::Ok);
        on_pushButton_next_clicked();

        ui->pushButton_look->setEnabled(true);
        ui->pushButton_hidden->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this, tr("提示"), tr("翻译错误"), QMessageBox::Ok);
    }
    ui->lineEdit_translate->clear();
}

void ReciteWordsWidget::on_pushButton_hidden_clicked()
{
    ui->plainTextEdit_translate->clear();

    ui->pushButton_look->setEnabled(true);
    ui->pushButton_hidden->setEnabled(false);
}

// 顺序背诵
void ReciteWordsWidget::on_pushButton_reciteASC_clicked()
{
    m_isReciteASC = true;
    m_isReciteRand = false;
    ui->plainTextEdit_word->clear();
    ui->plainTextEdit_translate->clear();
    ui->plainTextEdit_word->setPlainText(m_wordVector[0]);
    ui->pushButton_hidden->setEnabled(false);
    ui->pushButton_look->setEnabled(true);
}

// 随机背诵
void ReciteWordsWidget::on_pushButton_reciteRand_clicked()
{
    m_isReciteRand = true;
    m_isReciteASC = false;
    ui->plainTextEdit_word->clear();
    ui->plainTextEdit_translate->clear();
    int count = m_wordVector.size();
    ui->plainTextEdit_word->setPlainText(m_wordVector[rand() % count]);
    ui->pushButton_hidden->setEnabled(false);
    ui->pushButton_look->setEnabled(true);
}
