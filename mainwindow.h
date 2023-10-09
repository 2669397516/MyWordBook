#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QFile>
#include <QWidget>
#include <QHotkey>
#include <QNetworkReply>

#include "addword.h"
#include "learnipa.h"
#include "wordlistwidget.h"
#include "querywordswidget.h"
#include "recitewordswidget.h"
//#include "learnphoneticalphabet.h"
#include "showtranslators.h"
#include "translator.h"
#include "setappidsecretkey.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QFile& getFile();
    QString unicodeToUtf8(QString);  //unicode转utf-8,用于处理返回数据
    QString myregex(const QString &str);   //正则处理函数，用于解析返回数据，这里也可以使用json解析数据


public slots:
    void dealAddWord(QPair<QString, QString> newWord);
    void dealDelWord(QPair<QString, QString> delWord);
    void parsingJson(QNetworkReply * reply);   //get请求完成后触发槽函数
    void dealMessage(string appid, string secret_key);

signals:
    void sendMap(QMap<QString, QString> wordMap);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_toolButton_setPath_clicked();
    void handleHotkeyActivated();

private:
    void init();
    QString getClipboardText();
    bool isChinese(const QString& str);

private:
    Ui::MainWindow *ui;

    AddWord *m_addWord;
    LearnIPA *m_learnIPA;
    WordListWidget *m_wordListWidget;
    QueryWordsWidget *m_queryWordWidget;
    ReciteWordsWidget *m_reciteWordsWidget;

    QFile m_file;
    QMap<QString, QString> m_wordMap;
    QString m_fileName = "D:/word.txt";

    QHotkey *m_hotKey;
    Translator *m_translator;

    ShowTranslators *m_showTranslators;
    setAppidSecretkey *m_setAppidSecretKey;

    string m_appid = "20230925001829083";
    string m_secret_key = "nDiRo9JNqRAG2KYvl81M";
};

#endif // MAINWINDOW_H
