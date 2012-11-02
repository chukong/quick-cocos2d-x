
require("framework.shared.errors")

if ngx and ngx.say then
    echo = ngx.say
elseif CCLuaLog then
    echo = CCLuaLog
else
    echo = print
end

if type(DEBUG) ~= "number" then DEBUG = 1 end
io.output():setvbuf('no')

local prt = function(...)
    echo("[LUA] "..string.format(...))
end

echoNotice  = function() end
echoWarning = function() end
echoError   = prt

if DEBUG > 0 then echoWarning = prt end
if DEBUG > 1 then echoNotice = prt end

function traceback()
    echo(debug.traceback())
end

function printf(fmt, ...)
    echo(string.format(fmt, ...))
end

-- prints human-readable information about a variable
function dump(object, label, isReturnContents, nesting)
    if type(nesting) ~= "number" then nesting = 99 end

    local lookupTable = {}
    local result = {}

    local function _v(v)
        if type(v) == "string" then
            v = "\"" .. v .. "\""
        end
        return tostring(v)
    end

    local function _dump(object, label, indent, nest, keylen)
        label = label or "<var>"
        spc = ""
        if type(keylen) == "number" then
            spc = string.rep(" ", keylen - string.len(_v(label)))
        end
        if type(object) ~= "table" then
            result[#result +1 ] = string.format("%s%s%s = %s", indent, _v(label), spc, _v(object))
        elseif lookupTable[object] then
            result[#result +1 ] = string.format("%s%s%s = *REF*", indent, label, spc)
        else
            lookupTable[object] = true
            if nest > nesting then
                result[#result +1 ] = string.format("%s%s = *MAX NESTING*", indent, label)
            else
                result[#result +1 ] = string.format("%s%s = {", indent, _v(label))
                local indent2 = indent.."    "
                local keys = {}
                local keylen = 0
                local values = {}
                for k, v in pairs(object) do
                    keys[#keys + 1] = k
                    local vk = _v(k)
                    local vkl = string.len(vk)
                    if vkl > keylen then keylen = vkl end
                    values[k] = v
                end
                table.sort(keys, function(a, b)
                    if type(a) == "number" and type(b) == "number" then
                        return a < b
                    else
                        return tostring(a) < tostring(b)
                    end
                end)
                for i, k in ipairs(keys) do
                    _dump(values[k], k, indent2, nest + 1, keylen)
                end
                result[#result +1] = string.format("%s}", indent)
            end
        end
    end
    _dump(object, label, "- ", 1)

    if isReturnContents then
        return table.concat(result, "\n")
    end

    for i, line in ipairs(result) do
        echo(line)
    end
end

function vardump(object, label)
    local lookupTable = {}
    local result = {}

    local function _v(v)
        if type(v) == "string" then
            v = "\"" .. v .. "\""
        end
        return tostring(v)
    end

    local function _vardump(object, label, indent, nest)
        label = label or "<var>"
        local postfix = ""
        if nest > 1 then postfix = "," end
        if type(object) ~= "table" then
            if type(label) == "string" then
                result[#result +1] = string.format("%s%s = %s%s", indent, label, _v(object), postfix)
            else
                result[#result +1] = string.format("%s%s%s", indent, _v(object), postfix)
            end
        elseif not lookupTable[object] then
            lookupTable[object] = true

            if type(label) == "string" then
                result[#result +1 ] = string.format("%s%s = {", indent, label)
            else
                result[#result +1 ] = string.format("%s{", indent)
            end
            local indent2 = indent .. "    "
            local keys = {}
            local values = {}
            for k, v in pairs(object) do
                keys[#keys + 1] = k
                values[k] = v
            end
            table.sort(keys, function(a, b)
                if type(a) == "number" and type(b) == "number" then
                    return a < b
                else
                    return tostring(a) < tostring(b)
                end
            end)
            for i, k in ipairs(keys) do
                _vardump(values[k], k, indent2, nest + 1)
            end
            result[#result +1] = string.format("%s}%s", indent, postfix)
        end
    end
    _vardump(object, label, "", 1)

    return table.concat(result, "\n")
end

function newError(errorCode, errorMessage)
    local err
    if type(errorCode) == "table" then
        err = clone(errorCode)
    else
        err = {
            errorCode    = errorCode,
            errorMessage = errorMessage,
        }
    end

    return err
end

_G_TRACE_MEMORY = {}
local mt = {__mode = "k"}
setmetatable(_G_TRACE_MEMORY, mt)

function traceObject(object, info)
    _G_TRACE_MEMORY[object] = {tostring(object), info, debug.traceback()}
end

function findLeaks()
    collectgarbage("collect")
    collectgarbage("collect")
    collectgarbage("collect")
    collectgarbage("collect")

    local values = table.values(_G_TRACE_MEMORY)
    table.sort(values, function(a, b)
        return a[2] < b[2]
    end)

    if #values > 0 then
        echo("[LUA] OBJECTS IN MEMORY:")
        for i, v in ipairs(values) do
            echo(string.format("[LUA]     [%s] %s", v[1], v[2]))
        end
    else
        echo("[LUA] NOT FOUND OBJECTS IN MEMORY")
    end
end
