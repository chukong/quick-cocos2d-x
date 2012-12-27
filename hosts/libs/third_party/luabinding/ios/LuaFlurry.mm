
#if FLURRY_ENABLED > 0

#include "LuaFlurry.h"
#include "Flurry.h"

void LuaFlurry::logEvent(const char *eventName, bool timed/* = false*/)
{
    CCAssert(eventName != NULL, "eventName must not nil");
    [Flurry logEvent:[NSString stringWithCString:eventName encoding:NSUTF8StringEncoding]
               timed:timed];
}

void LuaFlurry::logEventWithParameters(const char *eventName, LUA_TABLE parameters, bool timed/* = false*/)
{
    CCAssert(eventName != NULL, "eventName must not nil");
    CC_UNUSED_PARAM(parameters);
    
    NSMutableDictionary *parameters_ = [NSMutableDictionary dictionary];
    
    CCLuaEngine* engine = CCLuaEngine::defaultEngine();
    lua_State* L = engine->getLuaState();
    if (lua_istable(L, -2))
    {
        lua_pushnil(L);                             /* L: ... eventName parameters timed key */
        while (lua_next(L, -3) != 0)                /* L: ... eventName parameters timed key value */
        {
            if (lua_type(L, -2) == LUA_TSTRING)
            {
                NSString *key_ = [NSString stringWithCString:lua_tostring(L, -2) encoding:NSUTF8StringEncoding];
                switch (lua_type(L, -1))
                {
                    case LUA_TBOOLEAN:
                        [parameters_ setObject:[NSNumber numberWithBool:lua_toboolean(L, -1) != 0]
                                        forKey:key_];
                        break;
                        
                    case LUA_TNUMBER:
                        [parameters_ setObject:[NSNumber numberWithFloat:lua_tonumber(L, -1)]
                                        forKey:key_];
                        break;
                        
                    case LUA_TSTRING:
                    default:
                        [parameters_ setObject:[NSString stringWithCString:lua_tostring(L, -1)
                                                                  encoding:NSUTF8StringEncoding]
                                        forKey:key_];
                        break;
                }
            }
            lua_pop(L, 1);                          /* L: ... eventName parameters timed key */
        }                                           /* L: ... eventName parameters timed */
    }
    
    [Flurry logEvent:[NSString stringWithCString:eventName encoding:NSUTF8StringEncoding]
      withParameters:parameters_
               timed:timed];
}

void LuaFlurry::endTimedEvent(const char *eventName)
{
    CCAssert(eventName != NULL, "eventName must not nil");
    [Flurry endTimedEvent:[NSString stringWithCString:eventName encoding:NSUTF8StringEncoding]
           withParameters:nil];
}

#endif // FLURRY_ENABLED > 0
