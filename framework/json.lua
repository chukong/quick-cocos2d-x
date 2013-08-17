
local json = {}
local cjson = require("cjson")

--[[--

]]
function json.encode(var)
    local status, result = pcall(cjson.encode, var)
    if status then return result end
    echoError("[framework.json] encode failed: %s", tostring(result))
end

--[[--

]]
function json.decode(text)
    local status, result = pcall(cjson.decode, text)
    if status then return result end
    echoError("[framework.json] decode failed: %s", tostring(result))
end

return json
