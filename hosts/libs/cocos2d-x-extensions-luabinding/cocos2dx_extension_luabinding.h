
#ifndef __COCOS2DX_EXTENSION_CCSCALE9SPRITE_H_
#define __COCOS2DX_EXTENSION_CCSCALE9SPRITE_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"

using namespace cocos2d;
using namespace cocos2d::extension;

TOLUA_API int tolua_cocos2dx_extension_CCScale9Sprite_open(lua_State* tolua_S);

#endif // __COCOS2DX_EXTENSION_CCSCALE9SPRITE_H_
