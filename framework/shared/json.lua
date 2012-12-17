
local json = {}

local _encode, _decode

local ok
if __FRAMEWORK_ENVIRONMENT__ == "client" then
    ok = pcall(function()
        local cjson = require("cjson")
        _encode = cjson.encode
        _decode = cjson.decode
    end)
end

if not ok then
    local simplejson = require("framework.shared.json.simplejson")
    _encode = simplejson.encode
    _decode = simplejson.decode
end

function json.encode(var, isDebug)
    local status, result = pcall(_encode, var)
    if status then return result end
    if isDebug then
        error(string.format("[framework.shared.json] encode failed: %s", tostring(result)))
    end
end

function json.decode(text, isDebug)
    local status, result = pcall(_decode, text)
    if status then return result end
    if isDebug then
        error(string.format("[framework.shared.json] decode failed: %s", tostring(result)))
    end
end

return json
