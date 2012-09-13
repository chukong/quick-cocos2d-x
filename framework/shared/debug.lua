
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

function vardump(...)
    local count = select("#", ...)
    if count < 1 then return end

    echo("vardump:")
    for i = 1, count do
        local v = select(i, ...)
        local t = type(v)
        if t == "string" then
            printf("  %02d: [string] %s", i, v)
        elseif t == "boolean" then
            printf("  %02d: [boolean] %s", i, tostring(v))
        elseif t == "number" then
            printf("  %02d: [number] %0.2f", i, v)
        else
            printf("  %02d: [%s] %s", i, t, tostring(v))
        end
    end
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
                result[#result +1 ] = string.format("%s%s = {", indent, label)
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
                table.sort(keys)
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
