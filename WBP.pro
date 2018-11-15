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
    widgetselection.cpp \
    formwindow.cpp \
    basewidget.cpp

HEADERS  += mainwindow.h \
    widget.h \
    common.h \
    leftwidget.h \
    widgetselection.h \
    formwindow.h \
    basewidget.h

RESOURCES += \
    application.qrc
