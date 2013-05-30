
#ifndef __SPARMATURE_LUABINDING_H_
#define __SPARMATURE_LUABINDING_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int luaopen_SPArmature_luabinding(lua_State* tolua_S);

#endif // __SPARMATURE_LUABINDING_H_
