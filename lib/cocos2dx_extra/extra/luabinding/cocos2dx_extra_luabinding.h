
#ifndef __COCOS2DX_EXTRA_LUABINDING_H_
#define __COCOS2DX_EXTRA_LUABINDING_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

#if defined(_USRDLL)
    #define COCOS2DX_EXTRA_LUABINDING_DLL     __declspec(dllexport)
#else         /* use a DLL library */
    #define COCOS2DX_EXTRA_LUABINDING_DLL     __declspec(dllimport)
#endif

TOLUA_API int COCOS2DX_EXTRA_LUABINDING_DLL luaopen_cocos2dx_extra_luabinding(lua_State* tolua_S);

#endif // __COCOS2DX_EXTRA_LUABINDING_H_
