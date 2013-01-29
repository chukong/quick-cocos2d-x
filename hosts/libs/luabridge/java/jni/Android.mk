
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := LuaJavaBridge
LOCAL_MODULE_FILENAME := libLuaJavaBridge

LOCAL_SRC_FILES := com_qeeplay_frameworks_LuaJavaBridge.cpp

LOCAL_C_INCLUDES := $(COCOS2DX_ROOT)/cocos2dx \
    $(COCOS2DX_ROOT)/cocos2dx/include \
    $(COCOS2DX_ROOT)/cocos2dx/kazmath/include \
    $(COCOS2DX_ROOT)/cocos2dx/platform \
    $(COCOS2DX_ROOT)/cocos2dx/platform/android \
    $(COCOS2DX_ROOT)/CocosDenshion/include \
    $(COCOS2DX_ROOT)/scripting/lua/cocos2dx_support \
    $(COCOS2DX_ROOT)/scripting/lua/lua \
    $(COCOS2DX_ROOT)/scripting/lua/tolua \
    $(LOCAL_PATH)/../luabinding

LOCAL_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1
LOCAL_EXPORT_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1

include $(BUILD_STATIC_LIBRARY)
