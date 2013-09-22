
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := third_party
LOCAL_MODULE_FILENAME := libthird_party

LOCAL_SRC_FILES := ../chipmunk/cocos2dx_support/CCPhysicsBody.cpp \
    ../chipmunk/cocos2dx_support/CCPhysicsDebugNode.cpp \
    ../chipmunk/cocos2dx_support/CCPhysicsShape.cpp \
    ../chipmunk/cocos2dx_support/CCPhysicsSupport.cpp \
    ../chipmunk/cocos2dx_support/CCPhysicsWorld.cpp \
    ../chipmunk/luabinding/CCPhysicsWorld_luabinding.cpp \
    ../luaproxy/LuaEventHandler.cpp \
    ../luaproxy/tolua/luaopen_LuaProxy.cpp \
    ../luaproxy/ui/CursorTextField.cpp \
    ../luaproxy/ui/UIUtil.cpp \
    ../third_party_luabinding.cpp

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/third_party
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES) \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/cocos2dx_support \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/luabinding \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/chipmunk/include \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/luaproxy \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/luaproxy/tolua \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/luaproxy/ui

LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS) -std=c++11
LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_chipmunk_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx) \
$(call import-module,scripting/lua/proj.android) \
$(call import-module,lib/third_party/chipmunk/proj.android)
