#-------------------------------------------------
#
# Project created by QtCreator 2019-01-10T14:01:17
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(./lua/lua.pri)

SOURCES += \
        $$PWD/codeeidtor.cpp \
        $$PWD/scilexerlua.cpp \
        $$PWD/sciapislua.cpp \
        $$PWD/qeditor.cpp \
    $$PWD/luafun.cpp

HEADERS  += \
        $$PWD/codeeidtor.h \
        $$PWD/scilexerlua.h \
        $$PWD/sciapislua.h \
        $$PWD/qeditor.h \
    $$PWD/luafun.h

FORMS   += \
        $$PWD/qeditor.ui

RESOURCES += $$PWD/resources.qrc

win32:CONFIG(release, debug|release): LIBS += -lqscintilla2
else:win32:CONFIG(debug, debug|release): LIBS += -lqscintilla2d
else:unix: LIBS += -lqscintilla2

win32:CONFIG(release, debug|release): LIBS += -lqscintilla2
else:win32:CONFIG(debug, debug|release): LIBS +=  -lqscintilla2d
else:unix: LIBS += -lqscintilla2


