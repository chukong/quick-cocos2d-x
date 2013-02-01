
#include "lanes_loader.h"
#include "tolua_fix.h"

extern int luaopen_lanes_core( lua_State* L);

int lanes_core_loader(lua_State* L)
{
    lua_pushliteral(L, "lanes.core");
    luaopen_lanes_core(L);
    return 1;
}
