
local M = {}

M.ERROR_INVALID_FILE_CONTENTS = -1
M.ERROR_HASH_MISS_MATCH       = -2
M.ERROR_STATE_FILE_NOT_FOUND  = -3

local encodeSign    = "=QP="
local stateFilename = "state.txt"
local eventListener = nil
local secretKey     = nil

local function isEncodedContents_(contents)
    return string.sub(contents, 1, string.len(encodeSign)) == encodeSign
end

local function encode_(values)
    local s = crypto.encodeBase64(json.encode(values))
    local hash = crypto.md5(s..secretKey)
    local contents = json.encode({h = hash, s = s})
    return encodeSign..contents
end

local function decode_(fileContents)
    local contents = string.sub(fileContents, string.len(encodeSign) + 1)
    local j = json.decode(contents)

    if type(j) ~= "table" then
        echoError("[framework.client.api.GameState] ERR, decode_() invalid contents")
        return {errorCode = M.ERROR_INVALID_FILE_CONTENTS}
    end

    local hash,s = j.h, j.s
    local testHash = crypto.md5(s..secretKey)
    if testHash ~= hash then
        echoError("[framework.client.api.GameState] ERR, decode_() hash miss match")
        return {errorCode = M.ERROR_HASH_MISS_MATCH}
    end

    local values = json.decode(crypto.decodeBase64(s))

    if type(values) ~= "table" then
        echoError("[framework.client.api.GameState] ERR, decode_() invalid state data")
        return {errorCode = M.ERROR_INVALID_FILE_CONTENTS}
    end

    return {values = values}
end

----------------------------------------

function M.init(eventListener_, stateFilename_, secretKey_)
    if type(eventListener_) ~= "function" then
        echoError("[framework.client.api.GameState] ERR, init() invalid eventListener")
        return false
    end

    eventListener = eventListener_

    if type(stateFilename_) == "string" then
        stateFilename = stateFilename_
    end

    if type(secretKey_) == "string" then
        secretKey = secretKey_
    end

    eventListener({
        name     = "init",
        filename = M.getGameStatePath(),
        encode   = type(secretKey) == "string"
    })

    return true
end

function M.load()
    local filename = M.getGameStatePath()

    if not io.exists(filename) then
        echoWarning("[framework.client.api.GameState] load() file \"%s\" not found", filename)
        return eventListener({name = "load", errorCode = M.ERROR_STATE_FILE_NOT_FOUND})
    end

    local contents = io.readfile(filename)
    echoWarning("[framework.client.api.GameState] load() get values from \"%s\"", filename)

    local values
    local encode = false

    if secretKey and isEncodedContents_(contents) then
        local d = decode_(contents)
        if d.errorCode then
            return eventListener({name = "load", errorCode = d.errorCode})
        end

        values = d.values
        encode = true
    else
        values = json.decode(contents)
        if type(values) ~= "table" then
            echoError("[framework.client.api.GameState] ERR, load() invalid data")
            return eventListener({name = "load", errorCode = M.ERROR_INVALID_FILE_CONTENTS})
        end
    end

    return eventListener({
        name   = "load",
        values = values,
        encode = encode,
        time   = os.time()
    })
end

function M.save(newValues)
    local values = eventListener({
        name   = "save",
        values = newValues,
        encode = type(secretKey) == "string"
    })
    if type(values) ~= "table" then
        echoError("[framework.client.api.GameState] ERR, save() listener return invalid data")
        return false
    end

    local filename = M.getGameStatePath()
    local ret = false
    if secretKey then
        ret = io.writefile(filename, encode_(values))
    else
        local s = json.encode(values)
        if type(s) == "string" then
            ret = io.writefile(filename, s)
        end
    end

    echoWarning("[framework.client.api.GameState] save() update file \"%s\"", filename)
    return ret
end

function M.getGameStatePath()
    return io.pathForFile(stateFilename, device.writeablePath)
end

return M
