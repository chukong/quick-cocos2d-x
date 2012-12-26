
#ifndef __COCOS2DX_EXTENSIONS_LUABINDING_H_
#define __COCOS2DX_EXTENSIONS_LUABINDING_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "CCScale9Sprite.h"
#include "CCEditBox.h"

using namespace cocos2d;
using namespace cocos2d::extension;

TOLUA_API int tolua_cocos2dx_extensions_luabinding_open(lua_State* tolua_S);

#endif // __COCOS2DX_EXTENSIONS_LUABINDING_H_
