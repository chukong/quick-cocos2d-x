
#ifndef __LUA_FLURRY_H_
#define __LUA_FLURRY_H_

#if FLURRY_ENABLED > 0

#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

class LuaFlurry
{
public:
    static void logEvent(const char *eventName, bool timed = false);
    static void logEventWithParameters(const char *eventName, LUA_TABLE parameters, bool timed = false);
    static void endTimedEvent(const char *eventName);
};

#endif // FLURRY_ENABLED > 0

#endif // __LUA_FLURRY_H_

