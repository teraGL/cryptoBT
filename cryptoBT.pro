lessThan(QT_MAJOR_VERSION, 5) {
  error("Qt 4 is no longer supported. In order to compile cryptoBT you need update to Qt5 http://qt.io/download-open-source/");
}

TARGET   = cryptoBT
TEMPLATE = app

CONFIG += c++11
QT     += core gui widgets
LIBS   += -lcryptopp

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

INCLUDEPATH += \
            src \
            src/gui \
            src/ui

HEADERS += \
        src/crypto/aescipher.h \
        src/crypto/blockcipher.h \
        src/crypto/blockcryptor.h \
        src/crypto/camelliacipher.h \
        src/crypto/serpentcipher.h \
        src/crypto/twofishcipher.h \
        src/gui/mainwindow.h \
        src/gui/torrentcreatordialog.h \
        src/gui/torrentview.h

SOURCES += \
        src/crypto/aescipher.cpp \
        src/crypto/blockcipher.cpp \
        src/crypto/blockcryptor.cpp \
        src/crypto/camelliacipher.cpp \
        src/crypto/serpentcipher.cpp \
        src/crypto/twofishcipher.cpp \
        src/gui/torrentcreatordialog.cpp \
        src/gui/torrentview.cpp \
        src/main.cpp \
        src/gui/mainwindow.cpp

FORMS += \
        src/ui/mainwindow.ui \
        src/ui/torrentcreatordialog.ui

RESOURCES += \
    img/icons.qrc

