
#ifndef __COCOS2D_X_EXTRA_LUABINDING_H_
#define __COCOS2D_X_EXTRA_LUABINDING_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int luaopen_cocos2d_x_extra_luabinding(lua_State* tolua_S);

#endif // __COCOS2D_X_EXTRA_LUABINDING_H_
