
#ifndef __COCOS2DX_EXTENSIONS_LUABINDING_WIN32_H_
#define __COCOS2DX_EXTENSIONS_LUABINDING_WIN32_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

TOLUA_API int tolua_cocos2dx_extensions_luabinding_win32_open(lua_State* tolua_S);

#endif // __COCOS2DX_EXTENSIONS_LUABINDING_WIN32_H_
