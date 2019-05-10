lessThan(QT_MAJOR_VERSION, 5) {
error("Qt 4 is no longer supported. In order to compile cryptoBT you need update to Qt5 http://qt.io/download-open-source/");
}

TARGET   = cryptoBT
TEMPLATE = app

CONFIG += c++11
QT     += core gui widgets

LIBS += -lcryptopp -llibtorrent

INCLUDEPATH += \
            src \
            src/gui \
            src/ui

HEADERS += \
        src/gui/mainwindow.h

SOURCES += \
        src/main.cpp \
        src/gui/mainwindow.cpp

FORMS += \
        src/ui/mainwindow.ui

