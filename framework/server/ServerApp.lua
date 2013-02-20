
local ServerApp = class("ServerApp")

local function normalizeActionName(actionName)
    local actionName = actionName or (GET.action or "index.index")
    actionName = string.gsub(actionName, "[^%a.]", "")
    actionName = string.gsub(actionName, "^[.]+", "")
    actionName = string.gsub(actionName, "[.]+$", "")

    local parts = string.split(actionName, ".")
    if #parts == 1 then
        parts[2] = 'index'
    elseif #parts ~= 2 then
        throw("ERROR_SERVER_INVALID_ACTION", ERROR_SERVER_INVALID_ACTION)
    end

    return parts[1], parts[2]
end

function ServerApp:ctor(config)
    if type(config) ~= "table" then config = {} end
    if type(config.appModuleName) ~= "string" then config.appModuleName = "app" end
    self.config  = config

    local Session = require("framework.server.Session")
    self.session = Session.new(self)
end

function ServerApp:run(actionName)
    local actionModuleName, actionMethodName = normalizeActionName(actionName)
    actionModuleName = "actions." .. string.ucfirst(actionModuleName) .. "Action"
    actionMethodName = actionMethodName .. "Action"

    local actionModule = self:require(actionModuleName)
    local action = actionModule.new(self)
    local method = action[actionMethodName]
    if not method then
        throw("ERROR_SERVER_INVALID_ACTION", ERROR_SERVER_INVALID_ACTION)
    else
    return method(action)
end
end

function ServerApp:require(moduleName)
    moduleName = self.config.appModuleName .. "." .. moduleName
    return require(moduleName)
end

function ServerApp:redis(config)
    if not self.redisInstance then
        local RedisEasy = require("framework.server.RedisEasy")
        self.redisInstance = RedisEasy.new(config)
        self.redisInstance:connect()
    end

    return self.redisInstance
end

return ServerApp
