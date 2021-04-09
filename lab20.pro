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
        recievewindow.cpp \
        sendwindow.cpp \
        window.cpp

HEADERS  +=\
        recievewindow.h \
        sendwindow.h \
        window.h \
        wiringPi.h

FORMS    += window.ui
