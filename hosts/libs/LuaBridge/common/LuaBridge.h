
#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_


#include <string>
#include <map>

extern "C" {
#include "lua.h"
}

using namespace std;

typedef enum {
    kLuaBridgeErrorOk                   = 0,
    kLuaBridgeErrorInvalidParameters    = -1,
    kLuaBridgeErrorClassNotFound        = -2,
    kLuaBridgeErrorMethodNotFound       = -3,
    kLuaBridgeErrorExceptionOccurred    = -4,
    kLuaBridgeErrorMethodSignature      = -5,
    kLuaBridgeErrorJavaVMError          = -6,
} LuaBridgeError;

typedef enum {
    kLuaBridgeTypeInvalid   = 0,
    kLuaBridgeTypeInt       = 1,
    kLuaBridgeTypeFloat     = 2,
    kLuaBridgeTypeBoolean   = 3,
    kLuaBridgeTypeString    = 4,
    kLuaBridgeTypeFunction  = 5,
    kLuaBridgeTypeArray     = 6,    // not used for LuaBridgeValueUnion
    kLuaBridgeTypeMap       = 7,    // not used for LuaBridgeValueUnion
    kLuaBridgeTypeVoid      = 8,    // not used for LuaBridgeValueUnion
} LuaBridgeType;

typedef union {
    int     intValue;
    float   floatValue;
    bool    boolValue;
    string  stringValue;
    int     functionRef;
} LuaBridgeValueUnion;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id
#define LUA_BRIDGE_REGISTRY_RETAIN      "lua_bridge_function_id_retain" // table[id] = retain count

class LuaBridge
{
public:
    static int retainLuaFunctionById(int functionId);
    static int releaseLuaFunctionById(int functionId);
    
    static int callLuaFunctionById(int functionId, const char *arg);
    static int callLuaFunctionById(int functionId, int arg);
    static int callLuaGlobalFunction(const char *functionName, const char *arg);
    static int callLuaGlobalFunction(const char *functionName, int arg);

protected:
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

#endif // __LUA_BRIDGE_H_
