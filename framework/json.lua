
local json = {}
local cjson = require("cjson")

function json.encode(var)
    local status, result = pcall(cjson.encode, var)
    if status then return result end
    if DEBUG > 1 then
        printError("json.encode() - encoding failed: %s", tostring(result))
    end
end

function json.decode(text)
    local status, result = pcall(cjson.decode, text)
    if status then return result end
    if DEBUG > 1 then
        printError("json.decode() - decoding failed: %s", tostring(result))
    end
end

json.null = cjson.null

return json
