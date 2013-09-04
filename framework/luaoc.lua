
local luaoc = {}

local callStaticMethod = CCLuaObjcBridge.callStaticMethod

function luaoc.callStaticMethod(className, methodName, args)
    local ok, ret = callStaticMethod(className, methodName, args)
    if not ok then
        local msg = string.format("luaoc.callStaticMethod(\"%s\", \"%s\", \"%s\") - error: [%s] ",
                className, methodName, tostring(args), tostring(ret))
        if ret == -1 then
            echoError(msg .. "INVALID PARAMETERS")
        elseif ret == -2 then
            echoError(msg .. "CLASS NOT FOUND")
        elseif ret == -3 then
            echoError(msg .. "METHOD NOT FOUND")
        elseif ret == -4 then
            echoError(msg .. "EXCEPTION OCCURRED")
        elseif ret == -5 then
            echoError(msg .. "INVALID METHOD SIGNATURE")
        else
            echoError(msg .. "UNKNOWN")
        end
    end
    return ok, ret
end

return luaoc
