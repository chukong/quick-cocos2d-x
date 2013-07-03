
#ifndef __CSARMATURE_LUABINDING_H_
#define __CSARMATURE_LUABINDING_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int luaopen_CSArmature_luabinding(lua_State* tolua_S);

#endif // __CSARMATURE_LUABINDING_H_
