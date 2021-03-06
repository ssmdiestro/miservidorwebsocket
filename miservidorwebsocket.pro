#-------------------------------------------------
#
# Project created by QtCreator 2019-11-27T14:23:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miservidorwebsocket
TEMPLATE = app

TRANSLATIONS += traductor_es_ES.ts
TRANSLATIONS += traductor_en_US.ts

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    usuarios.cpp \
    registro.cpp \
    server.cpp

HEADERS += \
    mainwindow.h \
    usuarios.h \
    json.hpp \
    registro.h \
    server.h

FORMS += \
        mainwindow.ui


LIBS += -pthread -lz


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/websocket/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/websocket/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/websocket/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/websocket/include
DEPENDPATH += $$PWD/websocket/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/websocket/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/websocket/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/websocket/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/websocket/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/websocket/lib/libixwebsocket.a
