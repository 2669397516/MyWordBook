#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include <QMap>
#include <QWidget>

namespace Ui {
class WordListWidget;
}

class WordListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordListWidget(QWidget *parent = nullptr);
    ~WordListWidget();

public slots:
    void recvMap(QMap<QString, QString> wordMap);
    void dealAddWord(QPair<QString, QString> addWord);
    void dealDelWord(QPair<QString, QString> delWord);

private:
    void showWordList();

private:
    Ui::WordListWidget *ui;
    QMap<QString, QString> m_wordMap;

};

#endif // WORDLISTWIDGET_H
