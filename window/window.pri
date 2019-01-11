#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T13:40:10
#
#-------------------------------------------------
QT       += core gui
QT       += serialport
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(../com/com.pri)
include(../qtpropertybrowser/src/qtpropertybrowser.pri)
include(../codeeditor/codeeditor.pri)

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/leftwidget.cpp \
    $$PWD/widgetselection.cpp \
    $$PWD/propertywidget.cpp \
    $$PWD/widget.cpp \
    $$PWD/formwindow.cpp \
    $$PWD/propertydialog.cpp \
    $$PWD/comdialog.cpp \
    $$PWD/buttonwidget.cpp \
    $$PWD/textwidget.cpp \
    $$PWD/editwidget.cpp \
    $$PWD/imagewidget.cpp \
    $$PWD/toolbar.cpp \
    $$PWD/scrollarea.cpp \
    $$PWD/bottomwidget.cpp \
    $$PWD/buildinfo.cpp \
    $$PWD/publicvar.cpp \

HEADERS  += \
    ../common.h \
    $$PWD/mainwindow.h \
    $$PWD/leftwidget.h \
    $$PWD/widgetselection.h \
    $$PWD/propertywidget.h \
    $$PWD/widget.h \
    $$PWD/formwindow.h \
    $$PWD/propertydialog.h \
    $$PWD/comdialog.h \
    $$PWD/buttonwidget.h \
    $$PWD/textwidget.h \
    $$PWD/editwidget.h \
    $$PWD/imagewidget.h \
    $$PWD/toolbar.h \
    $$PWD/scrollarea.h \
    $$PWD/bottomwidget.h \
    $$PWD/buildinfo.h \
    $$PWD/publicvar.h \


FORMS += \
    $$PWD/propertydialog.ui \
    $$PWD/comdialog.ui \
