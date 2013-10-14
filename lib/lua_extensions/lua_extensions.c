
#include "lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

// cjson
#include "cjson/lua_cjson.h"

// zlib
#include "zlib/lua_zlib.h"

// socket
#include "socket/luasocket.h"
#include "socket/mime.h"
#include "socket/socket_scripts.h"

// filesystem
#include "filesystem/lfs.h"

// lsqlite3
#include "lsqlite3.h"

static luaL_Reg luax_exts[] = {
    {"cjson", luaopen_cjson_safe},
    {"zlib", luaopen_zlib},
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {"lsqlite3", luaopen_lsqlite3},
    {"lfs", luaopen_lfs},

    {NULL, NULL}
};

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
