#include "learnipa.h"
#include "ui_learnipa.h"

#include <QDebug>

LearnIPA::LearnIPA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LearnIPA)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("学音标"));

    m_mediaPlayer = new QMediaPlayer;

    // 设置水平滑动栏
    ui->setVolume->setMaximum(100);
    ui->setVolume->setValue(0);
    m_mediaPlayer->setVolume(ui->setVolume->value());

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 105);
    ui->tableWidget->setColumnWidth(3, 80);
    ui->tableWidget->setColumnWidth(4, 80);
    ui->tableWidget->setColumnWidth(5, 80);
    ui->tableWidget->setColumnWidth(6, 80);
    ui->tableWidget->setColumnWidth(7, 80);

    ui->tableWidget->setSpan(0, 0, 5, 1);
    ui->tableWidget->setSpan(5, 0, 9, 1);
    ui->tableWidget->setSpan(0, 1, 3, 1);
    ui->tableWidget->setSpan(3, 1, 2, 1);
    ui->tableWidget->setSpan(5, 1, 2, 1);
    ui->tableWidget->setSpan(7, 1, 2, 1);
    ui->tableWidget->setSpan(9, 1, 2, 1);

    // 设置所有单元格不可编辑
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }

    connect(ui->tableWidget, &QTableWidget::cellClicked, [&](int row, int column){
        if (row == 0 && column == 3) // /i:/
            playMusic(QPoint(0, 3), "qrc:/mp3/i-sound2.mp3");
        if(row == 0 && column == 4) // /I/
            playMusic(QPoint(0, 4), "qrc:/mp3/i-sound.mp3");
        if(row == 0 && column == 5) // /e/
            playMusic(QPoint(0, 4), "qrc:/mp3/e-sound.mp3");
        if(row == 0 && column == 6) // /æ/
            playMusic(QPoint(0 , 6), "qrc:/mp3/an-sound.mp3");

        if(row == 1 && column == 4) // /ɜː/
            playMusic(QPoint(1, 4), "qrc:/mp3/er-sound.mp3");
        if(row == 1 && column == 5) // /ə/
            playMusic(QPoint(1, 5), "qrc:/mp3/e^-sound.mp3");
        if(row == 1 && column == 6) // /ʌ/
            playMusic(QPoint(1, 6), "qrc:/mp3/^-sound.mp3");

        if(row == 2 && column == 3) // /uː/
            playMusic(QPoint(2, 3), "qrc:/mp3/u-sound2.mp3");
        if(row == 2 && column == 4) // /ʊ/
            playMusic(QPoint(2, 4), "qrc:/mp3/u-sound.mp3");
        if(row == 2 && column == 5) // /ɔː/
            playMusic(QPoint(2, 5), "qrc:/mp3/o-sound2.mp3");
        if(row == 2 && column == 6) // /ɒ/
            playMusic(QPoint(2, 6), "qrc:/mp3/o-sound.mp3");
        if(row == 2 && column == 7) // /ɑː/
            playMusic(QPoint(2, 7), "qrc:/mp3/a-sound2.mp3");

        if(row == 3 && column == 3) // /eɪ/
            playMusic(QPoint(3, 3), "qrc:/mp3/ei.mp3");
        if(row == 3 && column == 4) // /aɪ/
            playMusic(QPoint(3, 4), "qrc:/mp3/ai.mp3");
        if(row == 3 && column == 5) // /ɔɪ/
            playMusic(QPoint(3, 5), "qrc:/mp3/oi.mp3");
        if(row == 3 && column == 6) // /aʊ/
            playMusic(QPoint(3, 6), "qrc:/mp3/ao.mp3");
        if(row == 3 && column == 7) // /əʊ/
            playMusic(QPoint(3, 7), "qrc:/mp3/eu.mp3");

        if(row == 4 && column == 3) // /ɪə/
            playMusic(QPoint(4, 3), "qrc:/mp3/ir.mp3");
        if(row == 4 && column == 4) // /eə/
            playMusic(QPoint(4, 4), "qrc:/mp3/er-sound.mp3");
        if(row == 4 && column == 5) // /ʊə/
            playMusic(QPoint(4, 5), "qrc:/mp3/uer.mp3");

        if(row == 5 && column == 3) // /p/
            playMusic(QPoint(5, 3), "qrc:/mp3/p.mp3");
        if(row == 5 && column == 4) // /t/
            playMusic(QPoint(5, 4), "qrc:/mp3/t.mp3");
        if(row == 5 && column == 5) // /k/
            playMusic(QPoint(5, 5), "qrc:/mp3/k.mp3");

        if(row == 6 && column == 3) // /b/
            playMusic(QPoint(6, 3), "qrc:/mp3/b.mp3");
        if(row == 6 && column == 4) // /d/
            playMusic(QPoint(6, 4), "qrc:/mp3/d.mp3");
        if(row == 6 && column == 5) // /g/
            playMusic(QPoint(6, 5), "qrc:/mp3/g.mp3");

        if(row == 7 && column == 3) // /f/
            playMusic(QPoint(7, 3), "qrc:/mp3/f.mp3");
        if(row == 7 && column == 4) // /s/
            playMusic(QPoint(7, 4), "qrc:/mp3/s.mp3");
        if(row == 7 && column == 5) // /ʃ/
            playMusic(QPoint(7, 5), "qrc:/mp3/ss.mp3");
        if(row == 7 && column == 6) // /θ/
            playMusic(QPoint(7, 6), "qrc:/mp3/si.mp3");
        if(row == 7 && column == 7) // /h/
            playMusic(QPoint(7, 7), "qrc:/mp3/h.mp3");

        if(row == 8 && column == 3) // /v/
            playMusic(QPoint(8, 3), "qrc:/mp3/v.mp3");
        if(row == 8 && column == 4) // /z/
            playMusic(QPoint(8, 4), "qrc:/mp3/z.mp3");
        if(row == 8 && column == 5) // /ʒ/
            playMusic(QPoint(8, 5), "qrc:/mp3/n3.mp3");
        if(row == 8 && column == 6) // /ð/
            playMusic(QPoint(8, 6), "qrc:/mp3/qq.mp3");
        if(row == 8 && column == 7) // /r/
            playMusic(QPoint(8, 7), "qrc:/mp3/r.mp3");

        if(row == 9 && column == 3) // /tʃ/
            playMusic(QPoint(9, 3), "qrc:/mp3/tss.mp3");
        if(row == 9 && column == 4) // /tr/
            playMusic(QPoint(9, 4), "qrc:/mp3/tr.mp3");
        if(row == 9 && column == 5) // /ts/
            playMusic(QPoint(9, 5), "qrc:/mp3/ts.mp3");

        if(row == 10 && column == 3) // /dʒ/
            playMusic(QPoint(10, 3), "qrc:/mp3/d3.mp3");
        if(row == 10 && column == 4) // /dr/
            playMusic(QPoint(10, 4), "qrc:/mp3/dr.mp3");
        if(row == 10 && column == 5) // /dz/
            playMusic(QPoint(10, 5), "qrc:/mp3/dz.mp3");

        if(row == 11 && column == 3) // /m/
            playMusic(QPoint(11, 3), "qrc:/mp3/m.mp3");
        if(row == 11 && column == 4) // /n/
            playMusic(QPoint(11, 4), "qrc:/mp3/n.mp3");
        if(row == 11 && column == 5) // /ŋ/
            playMusic(QPoint(11, 5), "qrc:/mp3/ng.mp3");

        if(row == 12 && column == 3) // /l/
            playMusic(QPoint(12, 3), "qrc:/mp3/l.mp3");

        if(row == 13 && column == 3) // /j/
            playMusic(QPoint(13, 3), "qrc:/mp3/j.mp3");
        if(row == 13 && column == 4) // /w/
            playMusic(QPoint(13, 4), "qrc:/mp3/w.mp3");
    });
}

LearnIPA::~LearnIPA()
{
    delete ui;
}

void LearnIPA::playMusic(QPoint flag, const QString musicPath)
{
    if (m_flag == flag)
    {
        m_mediaPlayer->setPosition(0);
        m_mediaPlayer->play();
    }
    else
    {
        m_mediaPlayer->setMedia(QUrl(musicPath));  // 使用相对路径的
        m_mediaPlayer->play();  // 播放指定的音频文件
        m_flag = flag;
    }

    return;
}

void LearnIPA::on_setVolume_sliderMoved(int position)
{
    m_mediaPlayer->setVolume(position);
}
