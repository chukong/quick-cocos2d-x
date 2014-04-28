cache()

ROOT=$${PWD}/../../
CC_ROOT=$${ROOT}/lib/cocos2d-x/


CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    CHIPMUNK_LIB = chipmunk_d
} else {
    BUILD_TYPE = release
    CHIPMUNK_LIB = chipmunk
}

OBJECTS_DIR = obj/$${BUILD_TYPE}
MOC_DIR = obj/$${BUILD_TYPE}

INCLUDEPATH += \
$${CC_ROOT}/external/chipmunk \
$${CC_ROOT}/external/chipmunk/cocos2dx_support \
$${CC_ROOT}/external/chipmunk/include \
$${CC_ROOT}/external/chipmunk/include/constraints \
$${CC_ROOT}/external/chipmunk/luabinding \
$${CC_ROOT}/external/chipmunk/src \
$${CC_ROOT}/external/chipmunk/src/constraints

LIB_OUTPUT_DIR = $${ROOT}/lib/$${BUILD_TYPE}


#include(quick-x-common.pri)
include(chipmunk-src.pri)

win32 {
    QMAKE_CFLAGS += /TP
    QMAKE_CXXFLAGS += /TP
}

TEMPLATE = lib
CONFIG += static
#LIBS += $${COCOS2DX_SYSTEM_LIBS}
DESTDIR = $${LIB_OUTPUT_DIR}
TARGET = $${CHIPMUNK_LIB}
