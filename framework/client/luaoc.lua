--[[

Copyright (c) 2011-2012 qeeplay.com

http://dualface.github.com/quick-cocos2d-x/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

Call Objective-C form Lua, and call Lua from Objective-C.

-   Call Objective-C Class Static Method from Lua
-   Pass aruments to Objective-C
-   Pass Lua function to Objective-C
-   Call Lua function from Objective-C

## HOW TO USE:

    local luaoc = require("framework.client.luaoc")

    local function onLogin(result)
        if result == "ok" then
            print("login ok")
        else
            print("login failure, error message = ", result)
        end
    end

    local args = {
        username  = "dualface",
        password  = "123456",
        autologin = true,
        callback  = onLogin
    }
    local ok, ret = luaoc.callStaticMethod("MySDK", "login", args)
    if ok then
        -- call success
        print("ret = ", ret)
    else
        -- call failure
        print("error code = ", ret)
    end


### Objective-C method:

    #include "LuaObjcBridge.h"

    + (NSString *)login:(NSDictionary *)dict
    {
        NSString *username = [dict objectForKey:@"username"];
        NSString *password = [dict objectForKey:@"password"];
        NSNumber autologin = [dict objectForKey:@"autologin"];
        int callback = [[dict objectForKey:@"callback"] intValue];

        if (.....)
        {
            LuaObjcBridge::callLuaFunctionById(callback, "ok");
        }
        else
        {
            LuaObjcBridge::callLuaFunctionById(callback, "error message");
        }
        LuaObjcBridge::releaseLuaFunctionById(callback);

        return @"return something";
    }


]]

local luaoc = {}

local callJavaStaticMethod = LuaObjcBridge.callStaticMethod

--[[--

Call Objective-C Class Method

### Parameters:

-   string **className** Objective-C class name
-   string **methodName** Method name
-   [_optional table **args**_] Arguments pass to Objective-C

### Returns:

-   boolean call success or failure
-   mixed Objective-C method returned value

]]
function luaoc.callStaticMethod(className, methodName, args)
    return callJavaStaticMethod(className, methodName, args)
end

return luaoc
