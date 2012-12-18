
#include "lualoadexts.h"
 
// luasocket
//#include "luasocket.h"
//#include "mime.h"
//#include "luasocketscripts.h"

// cjson
#include "lua_cjson.h"

// lanes
//#include "lanes.h"

static luaL_Reg luax_exts[] = {
//    {"socket.core", luaopen_socket_core},
//    {"mime.core", luaopen_mime_core},
//    {"socket", luaopen_socket},
//    {"socket.smtp", luaopen_socket_smtp},
//    {"socket.http", luaopen_socket_http},
//    {"socket.ftp", luaopen_socket_ftp},
//    {"socket.tp", luaopen_socket_tp},
//    {"socket.url", luaopen_socket_url},
//    {"mime", luaopen_socket_mime},
//    {"ltn12", luaopen_socket_ltn12},
    {"cjson", luaopen_cjson},
//    {"lua51-lanes", luaopen_lanes},

    {NULL, NULL}
};

void luax_loadexts(lua_State *L)
{
    luaL_Reg* lib = luax_exts;
    for (; lib->func; lib++)
    {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
        lua_pop(L, 2);
    }
}
