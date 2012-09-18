
local M = {}

local eventProtocol = require("framework.client.api.EventProtocol")

function M.new()
    local context = {}

    ----

    local config = {}

    ----

    local function init()
        eventProtocol.extend(context)
    end

    ----

    --[[ Get value by key, return default value when key not exist

    Usage:
        local numOfEnemys = context:getConfig("NUM_OF_ENEMYS", 10)
    ]]
    function context:getConfig(key, defaultValue)
        if config[key] ~= nil then return config[key] end
        return defaultValue
    end

    --[[ Set value by key

    Usage:
        context:setConfig("NUM_OF_ENEMYS", 15)
    ]]
    function context:setConfig(key, value)
        config[key] = value
    end

    ----

    init()
    return context
end

return M
