#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T13:40:10
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WBP
TEMPLATE = app

INCLUDEPATH += \
               ./com
               ./window
include(./qtpropertybrowser/src/qtpropertybrowser.pri)

SOURCES += main.cpp\
        ./window/mainwindow.cpp \
    ./window/leftwidget.cpp \
    ./window/widgetselection.cpp \
    ./com/comobject.cpp \
    window/propertywidget.cpp \
    window/widget.cpp \
    window/formwindow.cpp \
    window/propertydialog.cpp

HEADERS  += common.h \
    ./window/mainwindow.h \
    ./window/leftwidget.h \
    ./window/widgetselection.h \
    ./com/comobject.h \
    window/propertywidget.h \
    window/widget.h \
    window/formwindow.h \
    window/propertydialog.h


RESOURCES += \
    application.qrc

FORMS += \
    window/propertydialog.ui
