
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := quickcocos2dx
LOCAL_MODULE_FILENAME := libquickcocos2dx

LOCAL_SRC_FILES := ../cocos2d-x/extensions/GUI/CCControlExtension/CCScale9Sprite.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControl.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControlButton.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCControlUtils.cpp \
    ../cocos2d-x/extensions/GUI/CCControlExtension/CCInvocation.cpp \
    ../cocos2d-x/extensions/GUI/CCEditBox/CCEditBox.cpp \
    ../cocos2d-x/extensions/GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
    ../cocos2dx_extensions_luabinding/cocos2dx_extensions_luabinding.cpp \
    ../third_party/third_party_luabinding.cpp

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/ \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/GUI/CCControlExtension \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/extensions/GUI/CCEditBox \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extensions_luabinding \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1
LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_extra
LOCAL_WHOLE_STATIC_LIBRARIES += lua_extensions
LOCAL_WHOLE_STATIC_LIBRARIES += third_party_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx) \
$(call import-module,CocosDenshion/android) \
$(call import-module,scripting/lua/proj.android) \
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl) \
$(call import-module,lib/cocos2dx_extra/proj.android)
$(call import-module,lib/lua_extensions/proj.android) \
$(call import-module,lib/third_party/proj.android)
