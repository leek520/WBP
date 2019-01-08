QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets
qtHaveModule(printsupport): QT += printsupport
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


SOURCES += $$PWD/completer.cpp \
        $$PWD/highlighter.cpp \
        $$PWD/codeeditor.cpp \
        $$PWD/find_replace.cpp \
        $$PWD/mdichild.cpp \
        $$PWD/textedit.cpp
HEADERS += $$PWD/completer.h \
        $$PWD/highlighter.h \
        $$PWD/codeeditor.h \
        $$PWD/find_replace.h \
        $$PWD/mdichild.h \
        $$PWD/textedit.h

RESOURCES += $$PWD/resources.qrc

FORMS += \
    $$PWD/find_replace.ui \
    $$PWD/textedit.ui

