#ifndef ADDWORD_H
#define ADDWORD_H

#include <QMap>
#include <QFile>
#include <QWidget>

namespace Ui {
class AddWord;
}

class AddWord : public QWidget
{
    Q_OBJECT

public:
    explicit AddWord(QString fileName, QWidget *parent = nullptr);
    ~AddWord();

signals:
    void addWord(QPair<QString, QString> newWord);
    void delWord(QPair<QString, QString> delWord);

public slots:
    void recvMap(QMap<QString, QString> wordMap);

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_clear_clicked();

private:
    Ui::AddWord *ui;
    QMap<QString, QString> m_wordMap;
    QString m_fileName;
    QFile m_file;
};

#endif // ADDWORD_H
