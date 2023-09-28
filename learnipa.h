#ifndef LEARNIPA_H
#define LEARNIPA_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    Ui::LearnIPA *ui;
    QMediaPlayer *m_mediaPlayer;
    QMediaPlaylist *m_mediaPlaylist;
    QList<QMediaContent> m_mediaContentlist;
};

#endif // LEARNIPA_H
