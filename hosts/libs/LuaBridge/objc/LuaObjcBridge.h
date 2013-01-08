
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "LuaBridge.h"

class LuaObjcBridge : public LuaBridge
{
public:
    static void luabindingOpen(lua_State *L);
    
protected:
    static int callObjcStaticMethod(lua_State *L);
};

#endif // __LUA_OBJC_BRIDGE_H_
