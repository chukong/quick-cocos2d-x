
#include "LuaObjcBridge.h"
#include "cocos2d.h"

using namespace cocos2d;

void LuaObjcBridge::luabindingOpen(lua_State *L)
{
    s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, LuaObjcBridge::callObjcStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "LuaObjcBridge");
}

/**
 className
 methodName
 args
 */
int LuaObjcBridge::callObjcStaticMethod(lua_State *L)
{
    if (lua_gettop(L) != 3 || !lua_isstring(L, -3) || !lua_isstring(L, -2))
    {
    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, kLuaBridgeErrorInvalidParameters);
    	return 2;
    }
    
    const char *className  = lua_tostring(L, -3);
    const char *methodName = lua_tostring(L, -2);
    if (!className || !methodName)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorInvalidParameters);
        return 2;
    }
    
    Class targetClass = NSClassFromString([NSString stringWithCString:className encoding:NSUTF8StringEncoding]);
    if (!targetClass)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorClassNotFound);
        return 2;
    }
    
    SEL method;
    bool hasArguments = lua_istable(L, -1);
    if (hasArguments)
    {
        NSString *methodName_ = [NSString stringWithCString:methodName encoding:NSUTF8StringEncoding];
        methodName_ = [NSString stringWithFormat:@"%@:", methodName_];
        method = NSSelectorFromString(methodName_);
    }
    else
    {
        method = NSSelectorFromString([NSString stringWithCString:methodName encoding:NSUTF8StringEncoding]);
    }
    if (method == (SEL)0)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorMethodNotFound);
        return 2;
    }
    
    @try {
        id ret;
        if (hasArguments)
        {
            NSMutableDictionary *dict = [NSMutableDictionary dictionary];
            lua_pushnil(L);
            while (lua_next(L, -2))
            {
                NSString *key = [NSString stringWithCString:lua_tostring(L, -2) encoding:NSUTF8StringEncoding];
                
                switch (lua_type(L, -1))
                {
                    case LUA_TNUMBER:
                        [dict setObject:[NSNumber numberWithFloat:lua_tonumber(L, -1)] forKey:key];
                        break;
                        
                    case LUA_TBOOLEAN:
                        [dict setObject:[NSNumber numberWithBool:lua_toboolean(L, -1)] forKey:key];
                        break;
                        
                    case LUA_TSTRING:
                        [dict setObject:[NSString stringWithCString:lua_tostring(L, -1) encoding:NSUTF8StringEncoding]
                                 forKey:key];
                        break;
                        
                    case LUA_TFUNCTION:
                        int functionId = retainLuaFunction(L, -1, NULL);
                        [dict setObject:[NSNumber numberWithInt:functionId] forKey:key];
                        break;                        
                }
                
                lua_pop(L, 1);
            }
            ret = [targetClass performSelector:method withObject:dict];
        }
        else
        {
            ret = [targetClass performSelector:method];
        }
        
        if (ret == nil)
        {
            lua_pushboolean(L, 1);
            lua_pushnil(L);
            return 2;
        }
        else if ([ret isKindOfClass:[NSNumber class]])
        {
            lua_pushboolean(L, 1);
            NSNumber *number = (NSNumber *)ret;
            const char *numberType = [number objCType];
            if (strcmp(numberType, @encode(BOOL)) == 0)
            {
                lua_pushboolean(L, [number boolValue]);
            }
            else if (strcmp(numberType, @encode(int)) == 0)
            {
                lua_pushinteger(L, [number intValue]);
            }
            else
            {
                lua_pushnumber(L, [number floatValue]);
            }
            return 2;
        }
        else if ([ret isKindOfClass:[NSString class]])
        {
            lua_pushboolean(L, 1);
            lua_pushstring(L, [ret cStringUsingEncoding:NSUTF8StringEncoding]);
            return 2;
        }
        else
        {
            lua_pushboolean(L, 1);
            lua_pushstring(L, [[NSString stringWithFormat:@"%@", ret] cStringUsingEncoding:NSUTF8StringEncoding]);
            return 2;
        }
    }
    @catch (NSException *exception)
    {
        NSLog(@"EXCEPTION THROW: %@", exception);
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorExceptionOccurred);
        return 2;
    }
}
