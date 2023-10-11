#include "wordlistwidget.h"
#include "ui_wordlistwidget.h"

#include <QDebug>
#include <QScrollBar>

WordListWidget::WordListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordListWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("单词表"));
}

WordListWidget::~WordListWidget()
{
    delete ui;
}

void WordListWidget::recvMap(QMap<QString, QString> wordMap)
{
    m_wordMap = wordMap;
    showWordList();
}

void WordListWidget::dealAddWord(QPair<QString, QString> addWord)
{
    m_wordMap.insert(addWord.first, addWord.second);
    showWordList();
}

void WordListWidget::dealDelWord(QPair<QString, QString> delWord)
{
    m_wordMap.remove(delWord.first);
    showWordList();
}

void WordListWidget::showWordList()
{
    ui->plainTextEdit_show->clear();
    for(auto itr = m_wordMap.begin(); itr != m_wordMap.end(); ++itr)
    {
        QString key = itr.key();
        QString value = itr.value();

        while(key.size() < 30)
        {
            key += ' ';
        }

        QString content = key + value;
        ui->plainTextEdit_show->appendPlainText(content);
    }

    ui->plainTextEdit_show->verticalScrollBar()->setValue(0);   // 设置文本从最上方开始
}

void WordListWidget::on_pushButton_refresh_clicked()
{
    showWordList();
}
