#ifndef LEARNPHONETICALPHABET_H
#define LEARNPHONETICALPHABET_H

#include <QWidget>

namespace Ui {
class LearnPhoneticAlphabet;
}

class LearnPhoneticAlphabet : public QWidget
{
    Q_OBJECT

public:
    explicit LearnPhoneticAlphabet(QWidget *parent = nullptr);
    ~LearnPhoneticAlphabet();

private slots:
    void on_btn_shortVowel_start_toggled(bool checked);
    void on_btn_longVowel_start_toggled(bool checked);
    void on_btn_diphthongs_start_toggled(bool checked);
    void on_btn_voicelessConsonant_start_toggled(bool checked);
    void on_btn_voicedConsonant_start_toggled(bool checked);
    void on_btn_otherConsonant_start_toggled(bool checked);
    void on_btn_shortVowel_last_clicked();
    void on_btn_shortVowel_next_clicked();
    void on_btn_longVowel_last_clicked();
    void on_btn_longVowel_next_clicked();
    void on_btn_diphthongs_last_clicked();
    void on_btn_diphthongs_next_clicked();
    void on_btn_voicelessConsonant_last_clicked();
    void on_btn_voicelessConsonant_next_clicked();
    void on_btn_voicedConsonant_last_clicked();
    void on_btn_voicedConsonant_next_clicked();
    void on_btn_otherConsonant_last_clicked();
    void on_btn_otherConsonant_next_clicked();

private:
    QVector<QString> m_shortVowels = {"[æ]", "[ɛ]", "[ɪ]", "[ɒ]", "[ʌ]", "[ʊ]"}; // 短元音
    QVector<QString> m_longVowels = {"[iː]", "[eɪ]", "[aɪ]", "[oʊ]", "[uː]"};  // 长元音
    QVector<QString> m_diphthongs = {"[aɪ]", "[eɪ]", "[ɔɪ]", "[aʊ]"};  // 双元音
    QVector<QString> m_voicelessConsonants = {"[p]", "[t]", "[k]", "[s]", "[ʃ]", "[f]"}; // 清辅音
    QVector<QString> m_voicedConsonants = {"[b]", "[d]", "[g]", "[z]", "[ʒ]", "[v]"};    // 浊辅音
    QVector<QString> m_otherConsonants = {"[m]", "[n]", "[ŋ]", "[l]", "[w]", "[j]"};     // 其他辅音

    int m_cursVIndex = 0;
    int m_curlVIndex = 0;
    int m_curdtIndex = 0;
    int m_vlCIndex = 0;
    int m_vdCIndex = 0;
    int m_oCIndex = 0;

private:
    Ui::LearnPhoneticAlphabet *ui;
};

#endif // LEARNPHONETICALPHABET_H
