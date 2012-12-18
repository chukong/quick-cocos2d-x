
#ifndef __LUA_JAVA_BRIDGE_H_
#define __LUA_JAVA_BRIDGE_H_

#include <jni.h>

extern "C" {

#include "lua.h"

/*
HOW TO USE:

    local className = "com/java/MyClass"

    -- call: void Test1(String, int)
    local args = {"Hello", 123}
    local ok, ret = callJavaStaticMethodWithArgs(className, "Test1", "(Ljava/lang/String;I)V", args)
    if not ok then
        print("error code:", ret)
    end

    -- call: int Test2()
    local ok, ret = callJavaStaticMethodWithArgs(className, "Test2", "()I", {})
    if not ok then
        print("error code:", ret)
    else
        print("result:", ret)
    end

    -- call: String Test3(int)
    local ok, ret = callJavaStaticMethodWithArgs(className, "Test3", "(I)Ljava/lang/String;")
    if not ok then
        print("error code:", ret)
    else
        print("result string:", ret)
    end

    -- call: void TestVector(Vector)
    local args = {"Hello", 123}
    local ok, ret = callJavaStaticMethodWithArray(className, "TestVector", "(Ljava/util/Vector;I)V", args)

    -- call: void TestHash(Hashtable)
    local args = {name = "Andy", age = 16}
    local ok, ret = callJavaStaticMethodWithHash(className, "TestHash", "(Ljava/util/Hashtable;I)V", args)

        -- local ok, ret = luajb.callJavaStaticMethodWithArgs("com.qeeplay.games.killfruitcn",
    --                                                    "testMethod1",
    --                                                    "()V",
    --                                                    {})
    -- if not ok then
    --     echoWarning("testMethod1 failed, error code: %s", _s(ret))
    -- else
    --     echoWarning("testMethod1 ok, ret: %s", _s(ret))
    -- end


    -- local ok, ret = luajb.callJavaStaticMethodWithArgs("com.qeeplay.games.killfruitcn",
    --                                                    "testMethod2",
    --                                                    "(FLjava/lang/String;)I",
    --                                                    {123.456, "HELLO"})
    -- if not ok then
    --     echoWarning("testMethod2 failed, error code: %s", _s(ret))
    -- else
    --     echoWarning("testMethod2 ok, ret: %s", _s(ret))
    -- end

    -- local args = {1, 2, "3", true, false, "hello, luajb"}
    -- local ok, ret = luajb.callJavaStaticMethodWithArray("com.qeeplay.games.killfruitcn",
    --                                                     "testWithArray",
    --                                                     "(Ljava/util/Vector;)I",
    --                                                     args)
    -- if not ok then
    --     echoWarning("testWithArray failed, error code: %s", _s(ret))
    -- else
    --     echoWarning("testWithArray ok, ret: %s", _s(ret))
    -- end


    -- local args = {key1 = 1, key2 = 2, key3 = "3", key4 = true, key5 = false, key6 = "hello, luajb"}
    -- local ok, ret = luajb.callJavaStaticMethodWithHash("com.qeeplay.games.killfruitcn",
    --                                                    "testWithHash",
    --                                                    "(Ljava/util/Hashtable;)I",
    --                                                    args)
    -- if not ok then
    --     echoWarning("testWithHash failed, error code: %s", _s(ret))
    -- else
    --     echoWarning("testWithHash ok, ret: %s", _s(ret))
    -- end

*/

void LuaJavaBridge_setJavaVM(JavaVM *vm);
void LuaJavaBridge_setLuaState(lua_State *L);
void LuaJavaBridge_luabinding_open(lua_State *L);

int LuaJavaBridge_retainLuaFunctionById(int functionId);
int LuaJavaBridge_releaseLuaFunctionById(int functionId);

int LuaJavaBridge_callLuaFunctionById(int functionId, const char *arg);
int LuaJavaBridge_callLuaGlobalFunction(const char *functionName, const char *arg);

}

#endif /* __LUA_JAVA_BRIDGE_H_ */
