#-------------------------------------------------
#
# Project created by QtCreator 2013-10-16T03:16:56
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4){
    cache()
    QT += widgets
}

TARGET = quick-x-player
TEMPLATE = app

include(../../lib/proj.qt/quick-x-common.pri)

#CONFIG += warn_off
macx {
    ICON = QuickIcon.icns
}

INCLUDEPATH += ../sources .

LIBS += $${LINK_AGAINST_COCOS2DX}

SOURCES += main.cpp\
    aboutui.cpp \
    projectconfigui.cpp \
    player.cpp \
    quickdemowebview.cpp \
    createprojectui.cpp \
    consoleui.cpp \
    msghandlerwapper.cpp \
    logindialog.cpp \
    preferenceui.cpp \
    qxjson.cpp

SOURCES += ../sources/*.cpp

HEADERS  += \
    aboutui.h \
    projectconfigui.h \
    player.h \
    quickdemowebview.h \
    createprojectui.h \
    consoleui.h \
    msghandlerwapper.h \
    logindialog.h \
    preferenceui.h

FORMS    += \
    aboutui.ui \
    projectconfigui.ui \
    createprojectui.ui \
    consoleui.ui \
    logindialog.ui \
    preferenceui.ui

OTHER_FILES +=

DESTDIR = $${LIB_OUTPUT_DIR}

RESOURCES += \
    res.qrc

