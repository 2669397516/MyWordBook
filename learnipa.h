#ifndef LEARNIPA_H
#define LEARNIPA_H

#include <QUrl>
#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class LearnIPA;
}

class LearnIPA : public QWidget
{
    Q_OBJECT

public:
    explicit LearnIPA(QWidget *parent = nullptr);
    ~LearnIPA();

private:
    void playMusic(QPoint flag, const QString musicPath);

private slots:
    void on_setVolume_sliderMoved(int position);

private:
    Ui::LearnIPA *ui;
    QMediaPlayer *m_mediaPlayer;
    QPoint m_flag;
};

#endif // LEARNIPA_H
