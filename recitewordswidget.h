#ifndef RECITEWORDSWIDGET_H
#define RECITEWORDSWIDGET_H

#include <QMap>
#include <QWidget>

namespace Ui {
class ReciteWordsWidget;
}

class ReciteWordsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReciteWordsWidget(QWidget *parent = nullptr);
    ~ReciteWordsWidget();

public slots:
    void recvMap(QMap<QString, QString> wordMap);
    void dealAddWord(QPair<QString, QString> newWord);
    void dealDelWord(QPair<QString, QString> delWord);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_pushButton_next_clicked();
    void on_pushButton_last_clicked();
    void on_pushButton_look_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_hidden_clicked();
    void on_pushButton_reciteASC_clicked();
    void on_pushButton_reciteRand_clicked();

private:
    Ui::ReciteWordsWidget *ui;
    QMap<QString, QString> m_wordMap;
    QVector<QString> m_wordVector;
    bool m_isReciteASC = false;
    bool m_isReciteRand = true;
    int curNum;
};

#endif // RECITEWORDSWIDGET_H
