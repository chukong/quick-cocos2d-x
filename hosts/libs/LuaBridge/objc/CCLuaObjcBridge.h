
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "CCLuaBridge.h"

NS_CC_BEGIN

class CCLuaObjcBridge : public CCLuaBridge
{
public:
    static void luabindingOpen(lua_State *L);
    
protected:
    static int callObjcStaticMethod(lua_State *L);
    
    static void pushValue(lua_State *L, void *val);
};

NS_CC_END

#endif // __LUA_OBJC_BRIDGE_H_
