
local json = {}
local cjson = require("cjson")

function json.encode(var, isDebug)
    local status, result = pcall(cjson.encode, var)
    if status then return result end
    if isDebug then
        error(string.format("[framework.shared.json] encode failed: %s", tostring(result)))
    end
end

function json.decode(text, isDebug)
    local status, result = pcall(cjson.decode, text)
    if status then return result end
    if isDebug then
        error(string.format("[framework.shared.json] decode failed: %s", tostring(result)))
    end
end

return json
