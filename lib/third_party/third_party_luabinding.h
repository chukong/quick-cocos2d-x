
#ifndef __libquickcocos2dx__third_party_luabinding__
#define __libquickcocos2dx__third_party_luabinding__

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int luaopen_third_party_luabinding(lua_State* tolua_S);

#endif /* defined(__libquickcocos2dx__third_party_luabinding__) */
