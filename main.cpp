#include "mainwindow.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    QIcon icon(":/images/记单词.svg");
    a.setWindowIcon(icon);

    return a.exec();
}
