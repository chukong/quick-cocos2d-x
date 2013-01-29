
#ifndef __COCOS2DX_EXTENSION_NETWORK_MAC_H_
#define __COCOS2DX_EXTENSION_NETWORK_MAC_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"

using namespace cocos2d;

TOLUA_API int tolua_cocos2dx_extension_network_mac_open(lua_State* tolua_S);

#endif // __COCOS2DX_EXTENSION_NETWORK_MAC_H_
