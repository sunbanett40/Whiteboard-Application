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
        drawarea.cpp \
        queue.cpp \
        receivearea.cpp \
        receivewindow.cpp \
        sendwindow.cpp \
        sendthread.cpp \
        receivethread.cpp

HEADERS  +=\
        drawarea.h \
        queue.h \
        receivearea.h \
        receivewindow.h \
        sendwindow.h \
        serialstruct.h \
        wiringPi.h \
        sendthread.h \
        receivethread.h

FORMS    +=

RESOURCES += \
    Icons.qrc
