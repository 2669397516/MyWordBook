QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWordBook
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    mainwindow.ui \
    querywordswidget.ui \
    recitewordswidget.ui \
    wordlistwidget.ui \
    addword.ui \
    learnipa.ui \
    showtranslators.ui

HEADERS += \
    mainwindow.h \
    querywordswidget.h \
    recitewordswidget.h \
    wordlistwidget.h \
    addword.h \
    translator.h \
    md5.h \
    learnipa.h \
    showtranslators.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    main.cpp \
    querywordswidget.cpp \
    recitewordswidget.cpp \
    wordlistwidget.cpp \
    addword.cpp \
    translator.cpp \
    md5.cpp \
    learnipa.cpp \
    showtranslators.cpp

include(QHotKey/qhotkey.pri)
