#CONFIG += c++11
DEFINES += CC_TARGET_QT _USRDLL
DEFINES += CC_LUA_ENGINE_ENABLED=1

# conflict with sigslot.h
CONFIG += no_keywords
QT += core gui opengl
# multimedia

ROOT=$${PWD}/../../
CC_ROOT=$${ROOT}/lib/cocos2d-x/

DEFINES +=  COCOS2D_DEBUG=1
DEFINES +=  DEBUG=1

#CONFIG += no_batch
#greaterThan(QT_MAJOR_VERSION, 4) {
#  CONFIG += object_parallel_to_source
#} else:equals(PWD, $$OUT_PWD) {
#  CONFIG += object_with_source
#}

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    CHIPMUNK_LIB = chipmunk_d
} else {
    BUILD_TYPE = release
    CHIPMUNK_LIB = chipmunk
}

OBJECTS_DIR = obj/$${BUILD_TYPE}
MOC_DIR = obj/$${BUILD_TYPE}

LIB_OUTPUT_DIR = $${ROOT}/lib/$${BUILD_TYPE}

# Disable some warnings to make compiler output easier to read during development
DISABLED_WARNINGS = \
    -Wno-ignored-qualifiers \
    -Wno-unused-parameter \
    -Wno-sign-compare -Wno-unused-variable \
    -Wignored-qualifiers

*-g++* {
    DISABLED_WARNINGS += -Wno-psabi
}

*-g++*|*-clang* {
    QMAKE_CXXFLAGS_WARN_ON += $${DISABLED_WARNINGS} -Wno-reorder
    QMAKE_CFLAGS_WARN_ON += $${DISABLED_WARNINGS}
}
macx {
#    CONFIG -= app_bundle
    # For zip api
    DEFINES += USE_FILE32API

    COCOS2DX_SYSTEM_LIBS += -lz
    COCOS2DX_SYSTEM_LIBS += -L$${QMAKE_MAC_SDK.macosx.path}/usr/lib -lcurl
    #COCOS2DX_SYSTEM_LIBS += -L/usr/local/lib -ljpeg -ltiff -lpng #-lGLEW
    #COCOS2DX_SYSTEM_LIBS += -L/usr/local/lib -lfontconfig -lfreetype

    COCOS2DX_SYSTEM_LIBS +=  -L$${ROOT}/lib/cocos2d-x/scripting/lua/luajit/mac -lluajit2
    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/cocos2dx/platform/third_party/mac/libraries/ -lwebp
    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/external/libwebsockets/mac/lib/ -lwebsockets

    CONFIG += objective_c
    COCOS2DX_SYSTEM_LIBS += -framework Foundation -framework AppKit -framework SystemConfiguration  \
                            -framework CoreFoundation -framework StoreKit

    # for audio
    COCOS2DX_SYSTEM_LIBS += -framework OpenAL -framework AudioToolbox

    LINK_AGANST_LUA_COCOS2D += -pagezero_size 10000 -image_base 100000000
}

win32 {
    QT += multimedia
    DEFINES += USING_GLEW

    # You may need to change this include directory
    DEFINES += WIN32
    # for lua socket
    DEFINES += _WIN32

    COCOS2DX_SYSTEM_LIBS += -lopengl32 -ladvapi32 -lShell32 -lWSOCK32 -lws2_32 -lWinmm
    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/cocos2dx/platform/third_party/win32/libraries -llibpng \
                            -llibzlib -llibjpeg -llibiconv -lpthreadVCE2  -llibtiff  -llibwebp  -llibcurl_imp  -lglew32

    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/external/libwebsockets/win32/lib/ -lwebsockets \
                            -L$${ROOT}/lib/cocos2d-x/scripting/lua/luajit/win32 -llua51
    QMAKE_LFLAGS_DEBUG  = /DEBUG /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:MSVCRT.lib

    COCOS2DX_SYSTEM_LIBS += -L$${LIB_OUTPUT_DIR} -l$${CHIPMUNK_LIB}
}

QUICK_LIB = quickqt
LINK_AGAINST_COCOS2DX = -L$${LIB_OUTPUT_DIR} -l$${QUICK_LIB} $${COCOS2DX_SYSTEM_LIBS} $${LINK_AGANST_LUA_COCOS2D}

INCLUDEPATH += \
$${CC_ROOT}/cocos2dx \
$${CC_ROOT}/cocos2dx/include \
$${CC_ROOT}/cocos2dx/platform \
$${CC_ROOT}/cocos2dx/platform/qt \
$${CC_ROOT}/cocos2dx/kazmath/include \
$${CC_ROOT}/cocos2dx/textures \
$${CC_ROOT}/cocos2dx/cocoa \
$${CC_ROOT}/cocos2dx/support \
$${CC_ROOT}/CocosDenshion \
$${CC_ROOT}/CocosDenshion/include \
$${CC_ROOT}/extensions \
$${CC_ROOT}/extensions/GUI \
$${CC_ROOT}/extensions/GUI/CCControlExtension \
$${CC_ROOT}/extensions/GUI/CCEditBox \
$${CC_ROOT}/extensions/GUI/CCScrollView \
$${CC_ROOT}/extensions/network \
$${CC_ROOT}/external/chipmunk/include \
$${CC_ROOT}/external/chipmunk/luabinding \
$${CC_ROOT}/external/chipmunk/cocos2dx_support \
$${CC_ROOT}/external/extra \
$${CC_ROOT}/external/extra/luabinding \
$${CC_ROOT}/external/luaproxy/tolua \
$${CC_ROOT}/scripting/lua/cocos2dx_support \
$${CC_ROOT}/scripting/lua/lua_extensions \
$${CC_ROOT}/scripting/lua/lua_extensions/cjson \
$${CC_ROOT}/scripting/lua/lua_extensions/filesystem \
$${CC_ROOT}/scripting/lua/lua_extensions/lpack \
$${CC_ROOT}/scripting/lua/lua_extensions/lsqlite3 \
$${CC_ROOT}/scripting/lua/lua_extensions/socket \
$${CC_ROOT}/scripting/lua/lua_extensions/zlib \
$${CC_ROOT}/scripting/lua/luajit/include \
$${CC_ROOT}/scripting/lua/tolua

macx {
    INCLUDEPATH += $${CC_ROOT}/external/libwebsockets/mac \
                    $${CC_ROOT}/external/libwebsockets/mac/include \
                    $${CC_ROOT}/external/libwebsockets/mac/lib

    INCLUDEPATH += $${CC_ROOT}/cocos2dx/platform/third_party/mac/webp/ \
                   /usr/local/include
}
win32 {
    INCLUDEPATH += $${CC_ROOT}/external/libwebsockets/win32 \
                    $${CC_ROOT}/external/libwebsockets/win32/include \
                    $${CC_ROOT}/external/libwebsockets/win32/include/win32helpers \
                    $${CC_ROOT}/external/libwebsockets/win32/lib
    INCLUDEPATH += $${CC_ROOT}/cocos2dx/platform/third_party/win32/libwebp/
    INCLUDEPATH += \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32           \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/iconv     \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/zlib      \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libjpeg   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libpng    \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/pthread   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libtiff   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libwebp   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/OGLES
}
