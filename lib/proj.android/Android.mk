
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := quickcocos2dx
LOCAL_MODULE_FILENAME := libquickcocos2dx

LOCAL_SRC_FILES := ../cocos2dx_extensions_luabinding/cocos2dx_extensions_luabinding.cpp

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/cocos2dx_extensions_luabinding
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1
LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_extra
LOCAL_WHOLE_STATIC_LIBRARIES += lua_extensions
LOCAL_WHOLE_STATIC_LIBRARIES += third_party

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx) \
$(call import-module,CocosDenshion/android) \
$(call import-module,extensions) \
$(call import-module,scripting/lua/proj.android) \
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl) \
$(call import-module,lib/cocos2dx_extra/proj.android) \
$(call import-module,lib/lua_extensions/proj.android) \
$(call import-module,lib/third_party/proj.android)
