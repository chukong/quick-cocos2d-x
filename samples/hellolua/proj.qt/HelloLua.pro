cache()
include(../../../lib/proj.qt/quick-x-common.pri)

TARGET = HelloLua
CONFIG -= app_bundle

INCLUDEPATH += ..
INCLUDEPATH += ../Classes
win32 {
INCLUDEPATH += $${ROOT}/scripting/lua/cocos2dx_support/
INCLUDEPATH += $${ROOT}/scripting/lua/tolua/
INCLUDEPATH += $${ROOT}/scripting/lua/luajit/include
}

SOURCES += main.cpp
SOURCES += ../Classes/AppDelegate.cpp

LIBS += $${LINK_AGAINST_COCOS2DX}
DESTDIR = $${LIB_OUTPUT_DIR}
