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

macx {
    CONFIG -= app_bundle
}

INCLUDEPATH += ../sources

LIBS += $${LINK_AGAINST_COCOS2DX}

SOURCES += main.cpp\
    aboutui.cpp \
    projectconfigui.cpp \
    mainmenu.cpp

SOURCES += ../sources/*.cpp

HEADERS  += \
    aboutui.h \
    projectconfigui.h \
    mainmenu.h

FORMS    += \
    aboutui.ui \
    projectconfigui.ui

OTHER_FILES +=

DESTDIR = $${LIB_OUTPUT_DIR}
