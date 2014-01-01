#-------------------------------------------------
#
# Project created by QtCreator 2013-10-16T03:16:56
#
#-------------------------------------------------
cache()

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quick-x-player
TEMPLATE = app

include(../../lib/proj.qt/quick-x-common.pri)

INCLUDEPATH += ../sources

LIBS += $${LINK_AGAINST_COCOS2DX}

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutui.cpp \
    projectconfigui.cpp \
    nodetreeview.cpp \
    nodetreemodel.cpp \
    mydatavisitor.cpp \
    mydatapriter.cpp

SOURCES += ../sources/*.cpp

HEADERS  += mainwindow.h \
    aboutui.h \
    projectconfigui.h \
    nodetreeview.h \
    nodetreemodel.h \
    mydatavisitor.h \
    mydatapriter.h

FORMS    += mainwindow.ui \
    aboutui.ui \
    projectconfigui.ui

OTHER_FILES +=

DESTDIR = $${LIB_OUTPUT_DIR}
