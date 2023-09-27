#include "learnphoneticalphabet.h"
#include "ui_learnphoneticalphabet.h"

#include <QDebug>qDebug() << m_cursVIndex;

LearnPhoneticAlphabet::LearnPhoneticAlphabet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LearnPhoneticAlphabet)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("学音标"));

    ui->label_shortVowel->setText(m_shortVowels[m_cursVIndex]);
    ui->label_longVowel->setText(m_longVowels[m_curlVIndex]);
    ui->label_diphthong->setText(m_diphthongs[m_curdtIndex]);
    ui->label_voicelessConsonant->setText(m_voicelessConsonants[m_vlCIndex]);
    ui->label_voicedConsonant->setText(m_voicedConsonants[m_vdCIndex]);
    ui->label_otherConsonant->setText(m_otherConsonants[m_oCIndex]);
}

LearnPhoneticAlphabet::~LearnPhoneticAlphabet()
{
    delete ui;
}

void LearnPhoneticAlphabet::on_btn_shortVowel_start_toggled(bool checked)
{
    if(checked)
        ui->btn_shortVowel_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_shortVowel_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_longVowel_start_toggled(bool checked)
{
    if(checked)
        ui->btn_longVowel_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_longVowel_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_diphthongs_start_toggled(bool checked)
{
    if(checked)
        ui->btn_diphthongs_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_diphthongs_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_voicelessConsonant_start_toggled(bool checked)
{
    if(checked)
        ui->btn_voicelessConsonant_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_voicelessConsonant_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_voicedConsonant_start_toggled(bool checked)
{
    if(checked)
        ui->btn_voicedConsonant_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_voicedConsonant_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_otherConsonant_start_toggled(bool checked)
{
    if(checked)
        ui->btn_otherConsonant_start->setIcon(QIcon(":/images/暂停.svg"));
    else
        ui->btn_otherConsonant_start->setIcon(QIcon(":/images/播放.svg"));
}

void LearnPhoneticAlphabet::on_btn_shortVowel_last_clicked()
{
    if(--m_cursVIndex < 0)
        m_cursVIndex = 5;

    ui->label_shortVowel->setText(m_shortVowels[m_cursVIndex]);
}

void LearnPhoneticAlphabet::on_btn_shortVowel_next_clicked()
{
    if(++m_cursVIndex > 5)  // 先进行计算再进行比较
        m_cursVIndex = 0;

    ui->label_shortVowel->setText(m_shortVowels[m_cursVIndex]);
}

void LearnPhoneticAlphabet::on_btn_longVowel_last_clicked()
{
    if(--m_curlVIndex < 0)
        m_curlVIndex = 4;

    ui->label_longVowel->setText(m_longVowels[m_curlVIndex]);
}

void LearnPhoneticAlphabet::on_btn_longVowel_next_clicked()
{
    if(++m_curlVIndex > 4)
        m_curlVIndex = 0;

    ui->label_longVowel->setText(m_longVowels[m_curlVIndex]);
}

void LearnPhoneticAlphabet::on_btn_diphthongs_last_clicked()
{
    if(--m_curdtIndex < 0)
        m_curdtIndex = 3;

    ui->label_diphthong->setText(m_diphthongs[m_curdtIndex]);
}

void LearnPhoneticAlphabet::on_btn_diphthongs_next_clicked()
{
    if(++m_curdtIndex > 3)
        m_curdtIndex = 0;

    ui->label_diphthong->setText(m_diphthongs[m_curdtIndex]);
}

void LearnPhoneticAlphabet::on_btn_voicelessConsonant_last_clicked()
{
    if(--m_vlCIndex < 0)
        m_vlCIndex = 5;

    ui->label_voicelessConsonant->setText(m_voicelessConsonants[m_vlCIndex]);
}

void LearnPhoneticAlphabet::on_btn_voicelessConsonant_next_clicked()
{
    if(++m_vlCIndex > 5)
        m_vlCIndex = 0;

    ui->label_voicelessConsonant->setText(m_voicelessConsonants[m_vlCIndex]);
}

void LearnPhoneticAlphabet::on_btn_voicedConsonant_last_clicked()
{
    if(--m_vdCIndex < 0)
        m_vdCIndex = 5;

    ui->label_voicedConsonant->setText(m_voicedConsonants[m_vdCIndex]);
}

void LearnPhoneticAlphabet::on_btn_voicedConsonant_next_clicked()
{
    if(++m_vdCIndex > 5)
        m_vdCIndex = 0;

    ui->label_voicedConsonant->setText(m_voicedConsonants[m_vdCIndex]);
}

void LearnPhoneticAlphabet::on_btn_otherConsonant_last_clicked()
{
    if(--m_oCIndex < 0)
        m_oCIndex = 5;

    ui->label_otherConsonant->setText(m_otherConsonants[m_oCIndex]);
}

void LearnPhoneticAlphabet::on_btn_otherConsonant_next_clicked()
{
    if(++m_oCIndex > 5)
        m_oCIndex = 0;

    ui->label_otherConsonant->setText(m_otherConsonants[m_oCIndex]);
}
