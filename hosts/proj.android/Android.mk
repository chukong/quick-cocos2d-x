LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := quickcocos2dx

LOCAL_MODULE_FILENAME := quickcocos2dx

LOCAL_SRC_FILES := ../libs/CCDrawing/CCDrawing.cpp \
    ../libs/CCDrawing/LuaCCDrawing.cpp \
    ../libs/cocos2d-x-extensions/extensions/crypto/CCCrypto.cpp \
    ../libs/cocos2d-x-extensions/extensions/crypto/base64/libb64.c \
    ../libs/cocos2d-x-extensions/extensions/crypto/md5/md5.c \
    ../libs/cocos2d-x-extensions/extensions/crypto/sha1/sha1.cpp \
    ../libs/cocos2d-x-extensions/extensions/network/CCHttpRequest_impl.cpp \
    ../libs/cocos2d-x-extensions/extensions/network/CCHttpRequest.cpp \
    ../libs/cocos2d-x-extensions/extensions/network/CCNetwork.cpp \
    ../libs/cocos2d-x-extensions/extensions/luabinding/cocos2dx_extension_crypto_android.cpp \
    ../libs/cocos2d-x-extensions/extensions/luabinding/cocos2dx_extension_network_android.cpp \
    ../libs/luaexts/cjson/fpconv.c \
    ../libs/luaexts/cjson/lua_cjson.c \
    ../libs/luaexts/cjson/strbuf.c \
    ../libs/luaexts/lualoadexts.c \
    ../libs/luaj/jni/com_qeeplay_frameworks_LuaJavaBridge.cpp \
    ../libs/luaj/luabinding/LuaJavaBridge.cpp \
    ../libs/cocos2d-x/scripting/lua/tolua/tolua_event.c \
    ../libs/cocos2d-x/scripting/lua/tolua/tolua_is.c \
    ../libs/cocos2d-x/scripting/lua/tolua/tolua_map.c \
    ../libs/cocos2d-x/scripting/lua/tolua/tolua_push.c \
    ../libs/cocos2d-x/scripting/lua/tolua/tolua_to.c \
    ../libs/cocos2d-x/scripting/lua/cocos2dx_support/CCLuaEngine.cpp \
    ../libs/cocos2d-x/scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
    ../libs/cocos2d-x/scripting/lua/cocos2dx_support/LuaCocos2d.cpp \
    ../libs/cocos2d-x/scripting/lua/cocos2dx_support/tolua_fix.c

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/hosts/libs/CCDrawing \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/cocos2d-x-extensions/extensions \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/cocos2d-x-extensions/extensions/include \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/cocos2d-x-extensions/extensions/luabinding \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/luaexts \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/luaexts/cjson \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/luaj/jni \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/luaj/luabinding \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/luajit2/include \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/cocos2d-x/scripting/lua/tolua \
    $(QUICK_COCOS2DX_ROOT)/hosts/libs/cocos2d-x/scripting/lua/cocos2dx_support

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_EXPORT_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1
LOCAL_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_curl_static luajit2

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,libcurl) \
$(call import-module,hosts/libs/luajit2/proj.android)
