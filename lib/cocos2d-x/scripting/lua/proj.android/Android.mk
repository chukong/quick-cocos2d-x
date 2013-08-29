
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_lua_static
LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := ../cocos2dx_support/CCLuaEngine.cpp \
    ../cocos2dx_support/CCLuaStack.cpp \
    ../cocos2dx_support/CCLuaValue.cpp \
    ../cocos2dx_support/Cocos2dxLuaLoader.cpp \
    ../cocos2dx_support/LuaCocos2d.cpp \
    ../cocos2dx_support/tolua_fix.c \
    ../cocos2dx_support/snapshot.c \
    ../cocos2dx_support/platform/android/CCLuaJavaBridge.cpp \
    ../cocos2dx_support/platform/android/org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp \
    ../tolua/tolua_event.c \
    ../tolua/tolua_is.c \
    ../tolua/tolua_map.c \
    ../tolua/tolua_push.c \
    ../tolua/tolua_to.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../luajit/include \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support \
                           $(LOCAL_PATH)/../cocos2dx_support/platform/android

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../luajit/include \
                    $(LOCAL_PATH)/../tolua \
                    $(LOCAL_PATH)/../cocos2dx_support \
                    $(LOCAL_PATH)/../cocos2dx_support/platform/android \
                    $(LOCAL_PATH)/../../../cocos2dx \
                    $(LOCAL_PATH)/../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../../extensions

LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static

LOCAL_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS)

include $(BUILD_STATIC_LIBRARY)

$(call import-module,scripting/lua/luajit)
