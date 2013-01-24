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

Call Java form Lua, and call Lua from Java.

-   Call Java Class Static Method from Lua
-   Pass Lua function to Java
-   Call Lua function from Java

<br />

**References:**

-   [LuaJavaBridge - Call Java from Lua (Chinese only)](http://dualface.github.com/blog/2013/01/01/call-java-from-lua/)

]]

local luaj = {}

local callJavaStaticMethod = LuaJavaBridge.callStaticMethod

local function checkArguments(args, sig)
    if type(args) ~= "table" then args = {} end
    if sig then return args, sig end

    sig = {"("}
    for i, v in ipairs(args) do
        local t = type(v)
        if t == "number" then
            sig[#sig + 1] = "F"
        elseif t == "boolean" then
            sig[#sig + 1] = "Z"
        elseif t == "function" then
            sig[#sig + 1] = "I"
        else
            sig[#sig + 1] = "Ljava/lang/String;"
        end
    end
    sig[#sig + 1] = ")V"

    return args, table.concat(sig)
end

--[[--

Call Java Class Static Method

### Example:

    local className = "com/flurry/android/FlurryAgent"
    local args = {"APP_START"}
    local sig  = "(Ljava/lang/String;)V"
    local ok = luaj.callStaticMethod(className, "logEvent", args, sig)
    if ok then
        -- call success
    else
        -- call failure
    end

### Parameters:

-   string **className** Java class name
-   string **methodName** Method name
-   [_optional table **args**_] Arguments pass to Java
-   [_optional string **sig**_] Java Method Signature


> Java Method Signature reference: [JNI Types and Data Structures](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html#wp16432)

### Returns:

-   boolean call success or failure
-   mixed Java method returned value

]]
function luaj.callStaticMethod(className, methodName, args, sig)
    local args, sig = checkArguments(args, sig)
    echoInfo("luaj.callStaticMethod(\"%s\",\n\t\"%s\",\n\targs,\n\t\"%s", className, methodName, sig)
    return callJavaStaticMethod(className, methodName, args, sig)
end

return luaj
