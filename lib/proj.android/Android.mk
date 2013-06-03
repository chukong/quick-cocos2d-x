LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := quickcocos2dx

LOCAL_MODULE_FILENAME := quickcocos2dx

LOCAL_SRC_FILES := ../cocos2d-x/extensions/GUI/CCControlExtension/CCScale9Sprite.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControl.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControlButton.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControlUtils.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCInvocation.cpp \
    ../cocos2d-x/extensions/GUI/CCEditBox/CCEditBox.cpp \
    ../cocos2d-x/extensions/GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
    ../cocos2dx_extensions_luabinding/cocos2dx_extensions_luabinding.cpp \
    ../cocos2dx_extra/extra/crypto/CCCrypto.cpp \
    ../cocos2dx_extra/extra/crypto/base64/libb64.c \
    ../cocos2dx_extra/extra/crypto/md5/md5.c \
    ../cocos2dx_extra/extra/crypto/sha1/sha1.cpp \
    ../cocos2dx_extra/extra/crypto/xxtea/xxtea.c \
    ../cocos2dx_extra/extra/network/CCHttpRequest.cpp \
    ../cocos2dx_extra/extra/network/CCNetwork.cpp \
    ../cocos2dx_extra/extra/platform/android/CCCryptoAndroid.cpp \
    ../cocos2dx_extra/extra/platform/android/CCNativeAndroid.cpp \
    ../cocos2dx_extra/extra/platform/android/CCNetworkAndroid.cpp \
    ../cocos2dx_extra/extra/luabinding/cocos2dx_extra_luabinding.cpp \
    ../lua_extensions/cjson/fpconv.c \
    ../lua_extensions/cjson/lua_cjson.c \
    ../lua_extensions/cjson/strbuf.c \
    ../lua_extensions/zlib/lua_zlib.c \
    ../lua_extensions/socket/auxiliar.c \
    ../lua_extensions/socket/luasocket_buffer.c \
    ../lua_extensions/socket/except.c \
    ../lua_extensions/socket/inet.c \
    ../lua_extensions/socket/luasocket_io.c \
    ../lua_extensions/socket/luasocket.c \
    ../lua_extensions/socket/mime.c \
    ../lua_extensions/socket/options.c \
    ../lua_extensions/socket/select.c \
    ../lua_extensions/socket/serial.c \
    ../lua_extensions/socket/socket_scripts.c \
    ../lua_extensions/socket/tcp.c \
    ../lua_extensions/socket/timeout.c \
    ../lua_extensions/socket/udp.c \
    ../lua_extensions/socket/unix.c \
    ../lua_extensions/socket/usocket.c \
    ../lua_extensions/lua_extensions.c \
    ../cocos2d-x/scripting/lua/tolua/tolua_event.c \
    ../cocos2d-x/scripting/lua/tolua/tolua_is.c \
    ../cocos2d-x/scripting/lua/tolua/tolua_map.c \
    ../cocos2d-x/scripting/lua/tolua/tolua_push.c \
    ../cocos2d-x/scripting/lua/tolua/tolua_to.c \
    ../cocos2d-x/scripting/lua/cocos2dx_support/CCLuaEngine.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/CCLuaStack.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/CCLuaValue.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/LuaCocos2d.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/tolua_fix.c \
    ../cocos2d-x/scripting/lua/cocos2dx_support/snapshot.c \
    ../cocos2d-x/scripting/lua/cocos2dx_support/platform/android/CCLuaJavaBridge.cpp \
    ../cocos2d-x/scripting/lua/cocos2dx_support/platform/android/org_cocos2dx_lib_LuaJavaBridge.cpp \
    ../third_party/chipmunk/cocos2dx_support/CCPhysicsBody.cpp \
    ../third_party/chipmunk/cocos2dx_support/CCPhysicsDebugNode.cpp \
    ../third_party/chipmunk/cocos2dx_support/CCPhysicsShape.cpp \
    ../third_party/chipmunk/cocos2dx_support/CCPhysicsSupport.cpp \
    ../third_party/chipmunk/cocos2dx_support/CCPhysicsWorld.cpp \
    ../third_party/chipmunk/luabinding/CCPhysicsWorld_luabinding.cpp \
    ../third_party/chipmunk/src/chipmunk.c \
    ../third_party/chipmunk/src/constraints/cpConstraint.c \
    ../third_party/chipmunk/src/constraints/cpDampedRotarySpring.c \
    ../third_party/chipmunk/src/constraints/cpDampedSpring.c \
    ../third_party/chipmunk/src/constraints/cpGearJoint.c \
    ../third_party/chipmunk/src/constraints/cpGrooveJoint.c \
    ../third_party/chipmunk/src/constraints/cpPinJoint.c \
    ../third_party/chipmunk/src/constraints/cpPivotJoint.c \
    ../third_party/chipmunk/src/constraints/cpRatchetJoint.c \
    ../third_party/chipmunk/src/constraints/cpRotaryLimitJoint.c \
    ../third_party/chipmunk/src/constraints/cpSimpleMotor.c \
    ../third_party/chipmunk/src/constraints/cpSlideJoint.c \
    ../third_party/chipmunk/src/cpArbiter.c \
    ../third_party/chipmunk/src/cpArray.c \
    ../third_party/chipmunk/src/cpBB.c \
    ../third_party/chipmunk/src/cpBBTree.c \
    ../third_party/chipmunk/src/cpBody.c \
    ../third_party/chipmunk/src/cpCollision.c \
    ../third_party/chipmunk/src/cpHashSet.c \
    ../third_party/chipmunk/src/cpPolyShape.c \
    ../third_party/chipmunk/src/cpShape.c \
    ../third_party/chipmunk/src/cpSpace.c \
    ../third_party/chipmunk/src/cpSpaceComponent.c \
    ../third_party/chipmunk/src/cpSpaceHash.c \
    ../third_party/chipmunk/src/cpSpaceQuery.c \
    ../third_party/chipmunk/src/cpSpaceStep.c \
    ../third_party/chipmunk/src/cpSpatialIndex.c \
    ../third_party/chipmunk/src/cpSweep1D.c \
    ../third_party/chipmunk/src/cpVect.c

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/ \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/GUI/CCControlExtension \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/GUI/CCEditBox \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extensions_luabinding/ \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extra/extra \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extra/extra/luabinding \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/cjson \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/zlib \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/socket \
    $(QUICK_COCOS2DX_ROOT)/lib/luajit2/include \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/scripting/lua/tolua \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/scripting/lua/cocos2dx_support \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/scripting/lua/cocos2dx_support/platform/android \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/include \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/luabinding \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/cocos2dx_support

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1
LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_curl_static luajit2

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,libcurl) \
$(call import-module,lib/luajit2/proj.android)
