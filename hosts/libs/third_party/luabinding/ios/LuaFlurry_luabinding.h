
#ifndef __LUAFLURRY_LUABINDING_H_
#define __LUAFLURRY_LUABINDING_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

TOLUA_API int tolua_LuaFlurry_luabinding_open(lua_State* tolua_S);

#endif // __LUAFLURRY_LUABINDING_H_
