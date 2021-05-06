#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app

INCLUDEPATH = G:/1204_Advanced_Programming/P20

SOURCES += main.cpp\
        queue.cpp \
        receivecanvas.cpp \
        receivewindow.cpp \
        sendcanvas.cpp \
        sendwindow.cpp \
        sendthread.cpp \
        receivethread.cpp

HEADERS  +=\
        drawinformation.h \
        queue.h \
        receivecanvas.h \
        receivewindow.h \
        sendcanvas.h \
        sendwindow.h \
        serialstruct.h \
        wiringPi.h \
        sendthread.h \
        receivethread.h

FORMS    +=

RESOURCES += \
    Icons.qrc
