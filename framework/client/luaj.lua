
local luaj = {}

luaj.TYPE_INT             = 1
luaj.TYPE_FLOAT           = 2
luaj.TYPE_BOOLEAN         = 3
luaj.TYPE_STRING          = 4
luaj.TYPE_FUNCTION        = 5
luaj.TYPE_VOID            = 0

luaj.TYPE_INT_CHAR        = "1"
luaj.TYPE_FLOAT_CHAR      = "2"
luaj.TYPE_BOOLEAN_CHAR    = "3"
luaj.TYPE_STRING_CHAR     = "4"
luaj.TYPE_FUNCTION_CHAR   = "5"
luaj.TYPE_VOID_CHAR       = "0"

luaj.TYPE_INT_STRING      = "I"
luaj.TYPE_FLOAT_STRING    = "F"
luaj.TYPE_BOOLEAN_STRING  = "Z"
luaj.TYPE_STRING_STRING   = "Ljava/lang/String;"
luaj.TYPE_FUNCTION_STRING = "I"
luaj.TYPE_VOID_STRING     = "V"

local callJavaStaticMethod          = LuaJavaBridge.callStaticMethod
local callJavaStaticMethodWithArray = LuaJavaBridge.callStaticMethodWithArray

function to_float(v)
    v = tonumber(v)
    return v or 0
end

function to_integer(v)
    return math.floor(to_float(v) + 0.5)
end

function to_boolean(v)
    return (v ~= nil and v ~= false)
end

local function checkReturnType(returnType)
    local returnTypeString = luaj.TYPE_VOID_STRING

    if returnType == luaj.TYPE_INT then
        returnTypeString = luaj.TYPE_INT_STRING
    elseif returnType == luaj.TYPE_FLOAT then
        returnTypeString = luaj.TYPE_FLOAT_STRING
    elseif returnType == luaj.TYPE_BOOLEAN then
        returnTypeString = luaj.TYPE_BOOLEAN_STRING
    elseif returnType == luaj.TYPE_STRING then
        returnTypeString = luaj.TYPE_STRING_STRING
    else
        returnType = luaj.TYPE_VOID
    end

    return returnType, returnTypeString
end

local function checkParameters(args, argsType, returnType)
    if type(args) ~= "table" then args = {} end
    if type(argsType) ~= "table" then
        argsType = {}
        for i, v in ipairs(args) do
            local t = type(v)
            if t == "number" then
                argsType[i] = luaj.TYPE_FLOAT
            elseif t == "boolean" then
                argsType[i] = luaj.TYPE_BOOLEAN
            elseif t == "function" then
                argsType[i] = luaj.TYPE_FUNCTION
            else
                argsType[i] = luaj.TYPE_STRING
            end
        end
    end

    local args_     = {}
    local argsType_ = {}
    local sig_      = {}

    for i, t in ipairs(argsType) do
        if t == luaj.TYPE_INT then
            args_[i]     = to_integer(args[i])
            argsType_[i] = luaj.TYPE_INT_CHAR
            sig_[i]      = luaj.TYPE_INT_STRING
        elseif t == luaj.TYPE_FLOAT then
            args_[i]     = to_float(args[i])
            argsType_[i] = luaj.TYPE_FLOAT_CHAR
            sig_[i]      = luaj.TYPE_FLOAT_STRING
        elseif t == luaj.TYPE_BOOLEAN then
            args_[i]     = to_boolean(args[i])
            argsType_[i] = luaj.TYPE_BOOLEAN_CHAR
            sig_[i]      = luaj.TYPE_BOOLEAN_STRING
        elseif t == luaj.TYPE_FUNCTION then
            args_[i]     = args[i]
            argsType_[i] = luaj.TYPE_FUNCTION_CHAR
            sig_[i]      = luaj.TYPE_FUNCTION_STRING
        else -- string
            args_[i]     = tostring(args[i])
            argsType_[i] = luaj.TYPE_STRING_CHAR
            sig_[i]      = luaj.TYPE_STRING_STRING
        end
    end

    returnType, returnTypeString = checkReturnType(returnType)

    sig_ = "(" .. table.concat(sig_) .. ")" .. returnTypeString
    return args_, table.concat(argsType_), sig_, returnType
end

function luaj.callStaticMethod(className, methodName, args, argsType, returnType)
    local args, argsType, sig, returnType = checkParameters(args, argsType, returnType)
    return callJavaStaticMethod(className,
                                methodName,
                                sig,
                                argsType,
                                returnType,
                                args)
end

function luaj.callStaticMethodWithArray(className, methodName, args, returnType)
    returnType, returnTypeString = checkReturnType(returnType)
    return callJavaStaticMethodWithArray(className,
                                         methodName,
                                         "(Ljava/util/Vector;)" .. returnTypeString,
                                         returnType,
                                         args)
end

return luaj
