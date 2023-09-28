#include "setappidsecretkey.h"
#include "ui_setappidsecretkey.h"

#include <QMessageBox>

setAppidSecretkey::setAppidSecretkey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setAppidSecretkey)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("设置ID和密钥"));
    this->setWindowIcon(QIcon(":/MyWordBook.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowModality(Qt::ApplicationModal);
}

setAppidSecretkey::~setAppidSecretkey()
{
    delete ui;
}

void setAppidSecretkey::on_pushButton_confirm_clicked()
{
    if(ui->lineEdit_ID->text() == "" || ui->lineEdit_key->text() == "")
    {
        QMessageBox::information(this, tr("提示"), tr("请输入完整ID和Key！"), QMessageBox::Ok);
        return;
    }

    m_appid = ui->lineEdit_ID->text().toStdString();
    m_secret_key = ui->lineEdit_key->text().toStdString();

    emit sendMessage(m_appid, m_secret_key);

    this->close();
}

void setAppidSecretkey::on_pushButton_cancel_clicked()
{
    this->close();
}
