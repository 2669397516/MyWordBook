#include "mainwindow.h"

#include <QIcon>
#include <QMenu>
#include <QApplication>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    QIcon icon(":/WordBook.ico");
    a.setWindowIcon(icon);

    // 创建托盘图标
    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":/WordBook.ico"));  // 设置托盘图标

    // 创建菜单
    QMenu* trayMenu = new QMenu();
    QAction* restoreAction = trayMenu->addAction("Restore");
    QAction* quitAction = trayMenu->addAction("Quit");

    // 连接菜单动作的信号槽
    QObject::connect(restoreAction, &QAction::triggered, [&]() {
        m.showNormal();
    });
    QObject::connect(quitAction, &QAction::triggered, [&]() {
        // 点击"Quit"菜单时，退出程序
        QApplication::quit();
    });
    QObject::connect(&trayIcon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::DoubleClick) // 只有双击才触发该事件
            m.showNormal();
    });

    trayIcon.setContextMenu(trayMenu);  // 设置托盘菜单

    trayIcon.show();  // 显示托盘图标

    return a.exec();
}
