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
macx:ICON = QuickIcon.icns
win32:RC_ICONS = quick-x-icon.ico

INCLUDEPATH += ../sources .

LIBS += $${LINK_AGAINST_COCOS2DX}

SOURCES += main.cpp\
    aboutui.cpp \
    projectconfigui.cpp \
    player.cpp \
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



DESTDIR = $${LIB_OUTPUT_DIR}

RESOURCES += \
    res.qrc

#
# copy files
#
win32{
    COPY = copy /y
}else{
    COPY = cp -a
}

IN__PROPERTY_FILE = $$PWD/bridge.lua

win32 {
    OUT_PATH = $$DESTDIR
    OUT_PATH = $$replace(OUT_PATH, /, \\)
    OUT_PROPERTY_FILE = $$OUT_PATH/bridge.lua
    !exists($$OUT_PATH):system(md $$OUT_PATH)
}

macx {
    OUT_PATH = $${DESTDIR}/quick-x-player.app/Contents/MacOS
    OUT_PROPERTY_FILE = $$OUT_PATH/bridge.lua
    !exists($$OUT_PATH):system(mkdir -p $$OUT_PATH)
}

win32{
    IN__PROPERTY_FILE = $$replace(IN__PROPERTY_FILE, /, \\)
    OUT_PROPERTY_FILE = $$replace(OUT_PROPERTY_FILE, /, \\)
}

system($$COPY $$IN__PROPERTY_FILE $$OUT_PROPERTY_FILE)
