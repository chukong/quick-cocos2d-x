#ifndef __LANES_DEEP_H__
#define __LANES_DEEP_H__ 1

/*
 * public 'deep' API to be used by external modules if they want to implement Lanes-aware userdata
 * said modules will have to link against lanes (it is not really possible to separate the 'deep userdata' implementation from the rest of Lanes)
 */


#include "lua.h"

typedef void (*luaG_IdFunction)( lua_State *L, char const * const which);

int luaG_deep_userdata( lua_State *L, luaG_IdFunction idfunc);
void *luaG_todeep( lua_State *L, luaG_IdFunction idfunc, int index);

#endif // __LANES_DEEP_H__