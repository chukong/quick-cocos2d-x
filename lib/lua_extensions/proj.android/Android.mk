
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lua_extensions
LOCAL_MODULE_FILENAME := liblua_extensions

LOCAL_SRC_FILES := ../cjson/fpconv.c \
    ../cjson/lua_cjson.c \
    ../cjson/strbuf.c \
    ../zlib/lua_zlib.c \
    ../socket/auxiliar.c \
    ../socket/luasocket_buffer.c \
    ../socket/except.c \
    ../socket/inet.c \
    ../socket/luasocket_io.c \
    ../socket/luasocket.c \
    ../socket/mime.c \
    ../socket/options.c \
    ../socket/select.c \
    ../socket/serial.c \
    ../socket/socket_scripts.c \
    ../socket/tcp.c \
    ../socket/timeout.c \
    ../socket/udp.c \
    ../socket/unix.c \
    ../socket/usocket.c \
    ../filesystem/lfs.c \
    ../lua_extensions.c

LOCAL_EXPORT_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/cjson \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/zlib \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/socket \
    $(QUICK_COCOS2DX_ROOT)/lib/lua_extensions/filesystem
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 -DDEBUG=1 -DCOCOS2D_DEBUG=1

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,scripting/lua/proj.android)
