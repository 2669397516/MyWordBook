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
    m_mediaPlaylist = new QMediaPlaylist;

    m_mediaContentlist.push_back(QUrl::fromLocalFile(":/mp3/^-sound.mp3"));
    m_mediaContentlist.push_back(QUrl::fromLocalFile(":/mp3/a-sound2.mp3"));

    m_mediaPlaylist->addMedia(m_mediaContentlist);

    m_mediaPlayer->setPlaylist(m_mediaPlaylist);

    m_mediaPlaylist->setCurrentIndex(1);

    m_mediaPlayer->play();  // 播放指定的音频文件

//    ui->tableWidget->setRowCount(14);
//    ui->tableWidget->setColumnCount(8);

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

//    QTableWidgetItem *yuanyin = new QTableWidgetItem("元音");
//    ui->tableWidget->setItem(0, 0, yuanyin);
//    QTableWidgetItem *fuyin = new QTableWidgetItem("辅音");

//    ui->tableWidget->setItem(5, 0, fuyin);
//    QTableWidgetItem *danyuanyin = new QTableWidgetItem("单元音");
//    ui->tableWidget->setItem(0, 1, danyuanyin);
//    QTableWidgetItem *shuangyuanyin = new QTableWidgetItem("双元音");
//    ui->tableWidget->setItem(3, 1, shuangyuanyin);
//    QTableWidgetItem *baopoyin = new QTableWidgetItem("爆破音");
//    ui->tableWidget->setItem(5, 1, baopoyin);
//    QTableWidgetItem *mocayin = new QTableWidgetItem("摩擦音");
//    ui->tableWidget->setItem(7, 1, mocayin);
//    QTableWidgetItem *pocayin = new QTableWidgetItem("破擦音");
//    ui->tableWidget->setItem(9, 1, pocayin);
//    QTableWidgetItem *sheyin = new QTableWidgetItem("舌音");
//    ui->tableWidget->setItem(11, 1, sheyin);
//    QTableWidgetItem *sheceyin = new QTableWidgetItem("舌侧音");
//    ui->tableWidget->setItem(12, 1, sheceyin);
//    QTableWidgetItem *banyuanyin = new QTableWidgetItem("半元音");
//    ui->tableWidget->setItem(13, 1, banyuanyin);

//    QTableWidgetItem *qianyuanyin = new QTableWidgetItem("前元音");
//    ui->tableWidget->setItem(0, 2, qianyuanyin);
//    QTableWidgetItem *zhongyuanyin = new QTableWidgetItem("中元音");
//    ui->tableWidget->setItem(1, 2, zhongyuanyin);
//    QTableWidgetItem *houyuanyin = new QTableWidgetItem("后元音");
//    ui->tableWidget->setItem(2, 2, houyuanyin);
//    QTableWidgetItem *kaiheshuangyuanyin = new QTableWidgetItem("开合双元音");
//    ui->tableWidget->setItem(3, 2, kaiheshuangyuanyin);
//    QTableWidgetItem *jizhongshuangyuanyin = new QTableWidgetItem("集中双元音");
//    ui->tableWidget->setItem(4, 2, jizhongshuangyuanyin);
//    QTableWidgetItem *qingfuyin1 = new QTableWidgetItem("清辅音");
//    ui->tableWidget->setItem(5, 2, qingfuyin1);
//    QTableWidgetItem *zhuofuyin1 = new QTableWidgetItem("浊辅音");
//    ui->tableWidget->setItem(6, 2, zhuofuyin1);
//    QTableWidgetItem *qingfuyin2 = new QTableWidgetItem("清辅音");
//    ui->tableWidget->setItem(7, 2, qingfuyin2);
//    QTableWidgetItem *zhuofuyin2 = new QTableWidgetItem("浊辅音");
//    ui->tableWidget->setItem(8, 2, zhuofuyin2);
//    QTableWidgetItem *qingfuyin3 = new QTableWidgetItem("清辅音");
//    ui->tableWidget->setItem(9, 2, qingfuyin3);
//    QTableWidgetItem *zhuofuyin3 = new QTableWidgetItem("浊辅音");
//    ui->tableWidget->setItem(10, 2, zhuofuyin3);
//    QTableWidgetItem *zhuofuyin4 = new QTableWidgetItem("(浊辅音)");
//    ui->tableWidget->setItem(11, 2, zhuofuyin4);
//    QTableWidgetItem *zhuofuyin5 = new QTableWidgetItem("(浊辅音)");
//    ui->tableWidget->setItem(12, 2, zhuofuyin5);
//    QTableWidgetItem *zhuofuyin6 = new QTableWidgetItem("(浊辅音)");
//    ui->tableWidget->setItem(13, 2, zhuofuyin6);

    // 设置所有单元格不可编辑
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }

//    connect(ui->tableWidget, &QTableWidget::cellEntered, [&](int row, int column){
//        this->setCursor(Qt::PointingHandCursor);
//    });

    connect(ui->tableWidget, &QTableWidget::cellClicked, [&](int row, int column){
        if(row == 0 && column == 3) // /iː/
            qDebug() << "/iː/";
        if(row == 0 && column == 4)
            qDebug() << "/I/";
        if(row == 0 && column == 5)
            qDebug() << "/e/";
        if(row == 0 && column == 6)
            qDebug() << "/æ/";

        if(row == 1 && column == 4)
            qDebug() << "/ɜː/";
        if(row == 1 && column == 5)
            qDebug() << "/ə/";
        if(row == 1 && column == 6)
            qDebug() << "/ʌ/";

        if(row == 2 && column == 3)
            qDebug() << "/uː/";
        if(row == 2 && column == 4)
            qDebug() << "/ʊ/";
        if(row == 2 && column == 5)
            qDebug() << "/ɔː/";
        if(row == 2 && column == 6)
            qDebug() << "/ɒ/";
        if(row == 2 && column == 7)
            qDebug() << "/ɑː/";

        if(row == 3 && column == 3)
            qDebug() << "/eɪ/";
        if(row == 3 && column == 4)
            qDebug() << "/aɪ/";
        if(row == 3 && column == 5)
            qDebug() << "/ɔɪ/";
        if(row == 3 && column == 6)
            qDebug() << "/aʊ/";
        if(row == 3 && column == 7)
            qDebug() << "/əʊ/";

        if(row == 4 && column == 3)
            qDebug() << "/ɪə/";
        if(row == 4 && column == 4)
            qDebug() << "/eə/";
        if(row == 4 && column == 5)
            qDebug() << "/ʊə/";

        if(row == 5 && column == 3)
            qDebug() << "/p/";
        if(row == 5 && column == 4)
            qDebug() << "/t/";
        if(row == 5 && column == 5)
            qDebug() << "/k/";

        if(row == 6 && column == 3)
            qDebug() << "/b/";
        if(row == 6 && column == 4)
            qDebug() << "/d/";
        if(row == 6 && column == 5)
            qDebug() << "/g/";

        if(row == 7 && column == 3)
            qDebug() << "/f/";
        if(row == 7 && column == 4)
            qDebug() << "/s/";
        if(row == 7 && column == 5)
            qDebug() << "/ʃ/";
        if(row == 7 && column == 6)
            qDebug() << "/θ/";
        if(row == 7 && column == 7)
            qDebug() << "/h/";

        if(row == 8 && column == 3)
            qDebug() << "/v/";
        if(row == 8 && column == 4)
            qDebug() << "/z/";
        if(row == 8 && column == 5)
            qDebug() << "/ʒ/";
        if(row == 8 && column == 6)
            qDebug() << "/ð/";
        if(row == 8 && column == 7)
            qDebug() << "/r/";

        if(row == 9 && column == 3)
            qDebug() << "/tʃ/";
        if(row == 9 && column == 4)
            qDebug() << "/tr/";
        if(row == 9 && column == 5)
            qDebug() << "/ts/";

        if(row == 10 && column == 3)
            qDebug() << "/dʒ/";
        if(row == 10 && column == 4)
            qDebug() << "/dr/";
        if(row == 10 && column == 5)
            qDebug() << "/dz/";

        if(row == 11 && column == 3)
            qDebug() << "/m/";
        if(row == 11 && column == 4)
            qDebug() << "/n/";
        if(row == 11 && column == 5)
            qDebug() << "/ŋ/";

        if(row == 12 && column == 3)
            qDebug() << "/l/";

        if(row == 13 && column == 3)
            qDebug() << "/j/";
        if(row == 13 && column == 4)
            qDebug() << "/w/";
    });
}

LearnIPA::~LearnIPA()
{
    delete ui;
}
