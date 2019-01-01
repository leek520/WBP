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
    window/propertydialog.cpp \
    window/comdialog.cpp \
    window/buttonwidget.cpp \
    window/textwidget.cpp \
    window/editwidget.cpp \
    window/imagewidget.cpp \
    window/toolbar.cpp \
    window/scrollarea.cpp \
    window/bottomwidget.cpp

HEADERS  += common.h \
    ./window/mainwindow.h \
    ./window/leftwidget.h \
    ./window/widgetselection.h \
    ./com/comobject.h \
    window/propertywidget.h \
    window/widget.h \
    window/formwindow.h \
    window/propertydialog.h \
    window/comdialog.h \
    window/buttonwidget.h \
    window/textwidget.h \
    window/editwidget.h \
    window/imagewidget.h \
    window/toolbar.h \
    window/scrollarea.h \
    window/bottomwidget.h


RESOURCES += \
    application.qrc

RC_ICONS = images/wbp.ico

FORMS += \
    window/propertydialog.ui \
    window/comdialog.ui
