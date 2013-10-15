
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_extra
LOCAL_MODULE_FILENAME := libcocos2dx_extra

LOCAL_SRC_FILES := ../extra/crypto/CCCrypto.cpp \
    ../extra/crypto/base64/libb64.c \
    ../extra/crypto/xxtea/xxtea.c \
    ../extra/network/CCHTTPRequest.cpp \
    ../extra/network/CCNetwork.cpp \
    ../extra/platform/android/CCCryptoAndroid.cpp \
    ../extra/platform/android/CCNativeAndroid.cpp \
    ../extra/platform/android/CCNetworkAndroid.cpp \
    ../extra/luabinding/cocos2dx_extra_luabinding.cpp

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extra/extra \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extra/extra/luabinding

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += lua_extensions

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android)
$(call import-module,lib/lua_extensions/proj.android)
