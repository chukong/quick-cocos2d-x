local CURRENT_MODULE_NAME = ...

local providers = {
    "CocoPush",
}

for _, packageName in ipairs(providers) do
    local className = "push." .. packageName
    if not cc.Registry.exists(className) then
        cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), className)
    end
end

local push = class("cc.push")

local DEFAULT_PROVIDER_OBJECT_NAME = "push.default"

function push:ctor()
    cc.GameObject.extend(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.events = import(".events", CURRENT_MODULE_NAME)
    self.providers_ = {}
end

function push:start(name)
    if not self.providers_[name] then
        local providerFactoryClass = cc.Registry.newObject(name)
        local provider = providerFactoryClass.getInstance(self)
        if not provider then
            echoError("cc.push:start() - create push provider failed")
            return
        end

        self.providers_[name] = provider
        if not self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] then
            self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] = provider
        end
    end
end

function push:stop(name)
    local provider = self:getProvider(name)
    if provider then
        provider:removeListener()
        self.providers_[name or DEFAULT_PROVIDER_OBJECT_NAME] = nil
    end
end

function push:startPush(name)
    local provider = self:getProvider(name)
    if provider then
        provider:startPush()
    end
end

function push:stopPush(name)
    local provider = self:getProvider(name)
    if provider then
        provider:stopPush()
    end
end

function push:setAlias(alias, name)
    local provider = self:getProvider(name)
    if provider then
        provider:setAlias(alias)
    end
end

function push:delAlias()
    local provider = self:getProvider(name)
    if provider then
        provider:delAlias()
    end
end

function push:setTags(tags, name)
    if type(tags) ~= "table" then
        echoError("cc.push:setTags() - args must be table")
        return 
    end

    local provider = self:getProvider(name)
    if provider then
        provider:setTags(tags)
    end
end

function push:delTags(tags, name)
    if type(tags) ~= "table" then
        echoError("cc.push:delTags() - args must be table")
        return 
    end

    local provider = self:getProvider(name)
    if provider then
        provider:delTags(tags)
    end
end

-- private
function push:getProvider(name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    if self.providers_[name] then
        return self.providers_[name]
    end
    echoError("cc.push:getProvider() - provider %s not exists", name)
end

return push
