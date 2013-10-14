
#include "third_party_luabinding.h"
#include "chipmunk/luabinding/CCPhysicsWorld_luabinding.h"
//#include "luaproxy/tolua/luaopen_LuaProxy.h"


TOLUA_API int luaopen_third_party_luabinding(lua_State* tolua_S)
{
    luaopen_CCPhysicsWorld_luabinding(tolua_S);
//    luaopen_LuaProxy(tolua_S);

    return 1;
};
