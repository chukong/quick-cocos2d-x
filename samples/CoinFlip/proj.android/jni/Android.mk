LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
    ../../sources/AppDelegate.cpp \
    ../../../../lib/framework_precompiled/framework_precompiled.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../sources \
    $(QUICK_COCOS2DX_ROOT)/lib/framework_precompiled

LOCAL_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := libquickcocos2dx

include $(BUILD_SHARED_LIBRARY)

$(call import-module,lib/proj.android)
