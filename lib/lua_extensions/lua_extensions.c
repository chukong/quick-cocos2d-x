
#include "lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

// cjson
#include "cjson/lua_cjson.h"

// zlib
#include "zlib/lua_zlib.h"

// lpack
#include "lpack/lpack.h"

// lanes
#include "lanes/lanes.h"
#include "lanes/lanes_scripts.h"

// coxpcall
#include "coxpcall/coxpcall.h"

// socket
#include "socket/luasocket.h"
#include "socket/mime.h"
#include "socket/socket_scripts.h"

// copas
#include "copas/copas.h"

// websockets
#include "websockets/websockets.h"

// filesystem
#include "filesystem/lfs.h"

static luaL_Reg luax_exts[] = {
    {"cjson", luaopen_cjson_safe},
    {"zlib", luaopen_zlib},
    {"pack", luaopen_pack},
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {"lfs", luaopen_lfs},

    {NULL, NULL}
};

void luaopen_lua_extensions(lua_State *L)
{
//    luaL_Reg* lib = luax_exts;
//    lua_getglobal(L, "package");
//    lua_getfield(L, -1, "loaders");
//    for (; lib->func; lib++)
//    {
//        lua_pushcfunction(L, lib->func);
//        lua_setfield(L, -2, lib->name);
//    }
//    lua_pop(L, 2);

    // load extensions script
    luaopen_lanes_embedded(L, luaopen_lua_m_lanes);
//    luaopen_coxpcall(L);
//    luaopen_socket_scripts(L);
//    luaopen_copas(L);
//    luaopen_websockets(L);
}

#if __cplusplus
} // extern "C"
#endif
