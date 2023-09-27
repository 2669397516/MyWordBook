#ifndef QUERYWORDSWIDGET_H
#define QUERYWORDSWIDGET_H

#include <QMap>
#include <QWidget>
#include <QNetworkReply>

#include "translator.h"

namespace Ui {
class QueryWordsWidget;
}

class QueryWordsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWordsWidget(string &appid, string &secret_key, QWidget *parent = nullptr);
    ~QueryWordsWidget();
    QString unicodeToUtf8(QString);  //unicode转utf-8,用于处理返回数据
    QString myregex(const QString &str);   //正则处理函数，用于解析返回数据，这里也可以使用json解析数据

public slots:
    void recvMap(QMap<QString, QString> wordMap);
    void dealAddWord(QPair<QString, QString> newWord);
    void dealDelWord(QPair<QString, QString> delWord);
    void parsingJson(QNetworkReply * reply);   //get请求完成后触发槽函数

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_pushButton_queryWord_clicked();
    void on_lineEdit_word_textChanged(const QString &arg1);
    void on_pushButton_queryWord_baidu_clicked();
    void on_lineEdit_word_baidu_textEdited(const QString &arg1);

private:
    bool isChinese(const QString& str);

private:
    Ui::QueryWordsWidget *ui;
    QMap<QString, QString> m_wordMap;
    Translator *m_translator;

    string m_appid;
    string m_secret_key;
};

#endif // QUERYWORDSWIDGET_H
