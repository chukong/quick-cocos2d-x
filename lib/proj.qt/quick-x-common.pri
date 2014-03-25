#CONFIG += c++11
DEFINES += CC_TARGET_QT _USRDLL
DEFINES += CC_LUA_ENGINE_ENABLED=1

# conflict with sigslot.h
CONFIG += no_keywords
QT += core gui opengl
# multimedia

ROOT=$${PWD}/../../
CC_ROOT=$${ROOT}/lib/cocos2d-x/

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    DEFINES +=  COCOS2D_DEBUG=1
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
    -Wno-sign-compare -Wno-unused-variable

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

    COCOS2DX_SYSTEM_LIBS += -lopengl32 -ladvapi32 -lShell32 -lWSOCK32 -lws2_32
    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/cocos2dx/platform/third_party/win32/libraries -llibpng \
                            -llibzlib -llibjpeg -llibiconv -lpthreadVCE2  -llibtiff  -llibwebp  -llibcurl_imp  -lglew32

    COCOS2DX_SYSTEM_LIBS += -L$${ROOT}/lib/cocos2d-x/external/libwebsockets/win32/lib/ -lwebsockets \
                            -L$${ROOT}/lib/cocos2d-x/scripting/lua/luajit/win32 -llua51
    QMAKE_LFLAGS_DEBUG  = /DEBUG /NODEFAULTLIB:libcmt.lib
    #QMAKE_CFLAGS_DEBUG += /TP /Od #/TP #/clr

    # http://msdn.microsoft.com/en-us/library/032xwy55.aspx

    # for chipmunk engine
#    QMAKE_CFLAGS_DEBUG += \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/chipmunk.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpConstraint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpDampedRotarySpring.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpDampedSpring.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpGearJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpGrooveJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpPinJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpPivotJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpRatchetJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpRotaryLimitJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpSimpleMotor.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpSlideJoint.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpArbiter.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpArray.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBB.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBBTree.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBody.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpCollision.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpHashSet.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpPolyShape.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpShape.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpace.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceComponent.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceHash.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceQuery.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceStep.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpatialIndex.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSweep1D.c \
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpVect.c
#/Tp$${ROOT}/lib/cocos2d-x/external/chipmunk/include/chipmunk_types.h \

    COCOS2DX_SYSTEM_LIBS += -L$${LIB_OUTPUT_DIR} -l$${CHIPMUNK_LIB}
}

QUICK_LIB = quickqt
LINK_AGAINST_COCOS2DX = -L$${LIB_OUTPUT_DIR} -l$${QUICK_LIB} $${COCOS2DX_SYSTEM_LIBS} $${LINK_AGANST_LUA_COCOS2D}

INCLUDEPATH += \
$${CC_ROOT}/cocos2dx \
$${CC_ROOT}/cocos2dx/actions \
$${CC_ROOT}/cocos2dx/base_nodes \
$${CC_ROOT}/cocos2dx/cocoa \
$${CC_ROOT}/cocos2dx/draw_nodes \
$${CC_ROOT}/cocos2dx/effects \
$${CC_ROOT}/cocos2dx/include \
$${CC_ROOT}/cocos2dx/kazmath \
$${CC_ROOT}/cocos2dx/kazmath/include \
$${CC_ROOT}/cocos2dx/kazmath/include/kazmath \
$${CC_ROOT}/cocos2dx/kazmath/include/kazmath/GL \
$${CC_ROOT}/cocos2dx/kazmath/src \
$${CC_ROOT}/cocos2dx/kazmath/src/GL \
$${CC_ROOT}/cocos2dx/keypad_dispatcher \
$${CC_ROOT}/cocos2dx/label_nodes \
$${CC_ROOT}/cocos2dx/layers_scenes_transitions_nodes \
$${CC_ROOT}/cocos2dx/menu_nodes \
$${CC_ROOT}/cocos2dx/misc_nodes \
$${CC_ROOT}/cocos2dx/particle_nodes \
$${CC_ROOT}/cocos2dx/platform \
$${CC_ROOT}/cocos2dx/platform/qt \
$${CC_ROOT}/cocos2dx/script_support \
$${CC_ROOT}/cocos2dx/shaders \
$${CC_ROOT}/cocos2dx/sprite_nodes \
$${CC_ROOT}/cocos2dx/support \
$${CC_ROOT}/cocos2dx/support/component \
$${CC_ROOT}/cocos2dx/support/data_support \
$${CC_ROOT}/cocos2dx/support/image_support \
$${CC_ROOT}/cocos2dx/support/tinyxml2 \
$${CC_ROOT}/cocos2dx/support/user_default \
$${CC_ROOT}/cocos2dx/support/zip_support \
$${CC_ROOT}/cocos2dx/text_input_node \
$${CC_ROOT}/cocos2dx/textures \
$${CC_ROOT}/cocos2dx/tilemap_parallax_nodes \
$${CC_ROOT}/cocos2dx/touch_dispatcher \
$${CC_ROOT}/CocosDenshion \
$${CC_ROOT}/CocosDenshion/include \
$${CC_ROOT}/extensions \
$${CC_ROOT}/extensions/AssetsManager \
$${CC_ROOT}/extensions/CCArmature \
$${CC_ROOT}/extensions/CCArmature/animation \
$${CC_ROOT}/extensions/CCArmature/datas \
$${CC_ROOT}/extensions/CCArmature/display \
$${CC_ROOT}/extensions/CCArmature/external_tool \
$${CC_ROOT}/extensions/CCArmature/external_tool/Json \
$${CC_ROOT}/extensions/CCArmature/external_tool/Json/lib_json \
$${CC_ROOT}/extensions/CCArmature/utils \
$${CC_ROOT}/extensions/CCBReader \
$${CC_ROOT}/extensions/GUI \
$${CC_ROOT}/extensions/GUI/CCControlExtension \
$${CC_ROOT}/extensions/GUI/CCEditBox \
$${CC_ROOT}/extensions/GUI/CCScrollView \
$${CC_ROOT}/extensions/network \
$${CC_ROOT}/external \
$${CC_ROOT}/external/chipmunk \
$${CC_ROOT}/external/chipmunk/cocos2dx_support \
$${CC_ROOT}/external/chipmunk/include \
$${CC_ROOT}/external/chipmunk/include/constraints \
$${CC_ROOT}/external/chipmunk/luabinding \
$${CC_ROOT}/external/chipmunk/src \
$${CC_ROOT}/external/chipmunk/src/constraints \
$${CC_ROOT}/external/extra \
$${CC_ROOT}/external/extra/crypto \
$${CC_ROOT}/external/extra/crypto/base64 \
$${CC_ROOT}/external/extra/crypto/md5 \
$${CC_ROOT}/external/extra/luabinding \
$${CC_ROOT}/external/extra/native \
$${CC_ROOT}/external/extra/network \
$${CC_ROOT}/external/extra/platform \
$${CC_ROOT}/external/extra/platform/mac \
$${CC_ROOT}/external/extra/platform/mac/openudid \
$${CC_ROOT}/external/extra/platform/win32 \
$${CC_ROOT}/external/extra/store \
$${CC_ROOT}/external/libwebsockets \
$${CC_ROOT}/external/luaproxy \
$${CC_ROOT}/external/luaproxy/tolua \
$${CC_ROOT}/external/luaproxy/ui \
$${CC_ROOT}/licenses \
$${CC_ROOT}/scripting \
$${CC_ROOT}/scripting/lua \
$${CC_ROOT}/scripting/lua/cocos2dx_support \
$${CC_ROOT}/scripting/lua/cocos2dx_support/platform \
$${CC_ROOT}/scripting/lua/lua_extensions \
$${CC_ROOT}/scripting/lua/lua_extensions/cjson \
$${CC_ROOT}/scripting/lua/lua_extensions/filesystem \
$${CC_ROOT}/scripting/lua/lua_extensions/lpack \
$${CC_ROOT}/scripting/lua/lua_extensions/lsqlite3 \
$${CC_ROOT}/scripting/lua/lua_extensions/socket \
$${CC_ROOT}/scripting/lua/lua_extensions/zlib \
$${CC_ROOT}/scripting/lua/luajit \
$${CC_ROOT}/scripting/lua/luajit/include \
$${CC_ROOT}/scripting/lua/luajit/LuaJIT-2.0.2 \
$${CC_ROOT}/scripting/lua/luajit/LuaJIT-2.0.2/src \
$${CC_ROOT}/scripting/lua/tolua \

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
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/iconv     \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/zlib      \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libjpeg   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libpng    \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/pthread   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libtiff   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/libwebp   \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/OGLES     \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/          \
            $${CC_ROOT}/cocos2dx/platform/third_party/win32/OGLES/GL
}
