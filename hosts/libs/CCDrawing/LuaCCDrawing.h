
#ifndef __LUACCDRAWING_H_
#define __LUACCDRAWING_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCDrawing.h"

using namespace cocos2d;

TOLUA_API int tolua_CCDrawing_open(lua_State* tolua_S);

#endif // __LUACCDRAWING_H_
