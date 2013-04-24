
#include "lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

// cjson
#include "lua_cjson.h"

// zlib
#include "lua_zlib.h"

// socket
#include "luasocket.h"
#include "mime.h"
#include "socket_scripts.h"

static luaL_Reg luax_exts[] = {
    {"cjson", luaopen_cjson},
    {"zlib", luaopen_zlib},
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},

    {NULL, NULL}
};

#include "tolua_fix.h"

void luaopen_lua_extensions(lua_State *L)
{
    luaL_Reg* lib = luax_exts;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);

    // load extensions script
    luaopen_socket_scripts(L);
}

#if __cplusplus
} // extern "C"
#endif
