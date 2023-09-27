#ifndef SETAPPIDSECRETKEY_H
#define SETAPPIDSECRETKEY_H

#include <string>
#include <QString>
#include <QDialog>

namespace Ui {
class setAppidSecretkey;
}

class setAppidSecretkey : public QDialog
{
    Q_OBJECT

public:
    explicit setAppidSecretkey(QWidget *parent = nullptr);
    ~setAppidSecretkey();

signals:
    void sendMessage(std::string appid, std::string secret_key);

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::setAppidSecretkey *ui;
    std::string m_appid;
    std::string m_secret_key;
};

#endif // SETAPPIDSECRETKEY_H
