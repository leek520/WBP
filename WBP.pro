#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T13:40:10
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WBP
TEMPLATE = app


include(./qtpropertybrowser/src/qtpropertybrowser.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    leftwidget.cpp \
    widgetselection.cpp \
    formwindow.cpp \
    basewidget.cpp \
    comobject.cpp

HEADERS  += mainwindow.h \
    widget.h \
    common.h \
    leftwidget.h \
    widgetselection.h \
    formwindow.h \
    basewidget.h \
    comobject.h

RESOURCES += \
    application.qrc
