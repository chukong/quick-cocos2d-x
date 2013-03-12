
local ServerApp = class("ServerApp")

function ServerApp:ctor(config)
    if type(config) ~= "table" then config = {} end
    if type(config.appModuleName) ~= "string" then
        config.appModuleName = "app"
    end
    self.config = config

    self.requestMethod = ngx.req.get_method()
    self.GET = ngx.req.get_uri_args()
    if self.requestMethod == "POST" then
        ngx.req.read_body()
        self.POST = ngx.req.get_post_args()
    else
        self.POST = {}
    end
end

function ServerApp:run(actionName)
    local actionModuleName, actionMethodName = self:normalizeActionName(actionName)
    actionModuleName = "actions." .. string.ucfirst(actionModuleName) .. "Action"
    actionMethodName = actionMethodName .. "Action"

    local actionModule = self:require(actionModuleName)
    local action = actionModule.new(self)
    local method = action[actionMethodName]
    if type(method) ~= "function" then
        throw("ERROR_SERVER_INVALID_ACTION", ERROR_SERVER_INVALID_ACTION, actionModuleName, actionMethodName)
    end
    action.GET, action.POST = self.GET, self.POST
    return method(action)
end

function ServerApp:require(moduleName)
    moduleName = self.config.appModuleName .. "." .. moduleName
    return require(moduleName)
end

function ServerApp:normalizeActionName(actionName)
    local actionName = actionName or (self.GET.action or "index.index")
    actionName = string.gsub(actionName, "[^%a.]", "")
    actionName = string.gsub(actionName, "^[.]+", "")
    actionName = string.gsub(actionName, "[.]+$", "")

    local parts = string.split(actionName, ".")
    if #parts == 1 then parts[2] = 'index' end
    return parts[1], parts[2]
end

return ServerApp
