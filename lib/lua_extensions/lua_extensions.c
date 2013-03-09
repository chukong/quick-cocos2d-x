
#include "lua_extensions.h"

#if __cplusplus
extern "C" {
#endif

// cjson
#include "lua_cjson.h"

// zlib
#include "lua_zlib.h"

static luaL_Reg luax_exts[] = {
    {"cjson", luaopen_cjson},
    {"zlib", luaopen_zlib},

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
}

#if __cplusplus
} // extern "C"
#endif
