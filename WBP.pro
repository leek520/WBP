#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T13:40:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WBP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    leftwidget.cpp \
    ewindow.cpp \
    widgethandle.cpp

HEADERS  += mainwindow.h \
    widget.h \
    common.h \
    leftwidget.h \
    ewindow.h \
    widgethandle.h

RESOURCES += \
    application.qrc
