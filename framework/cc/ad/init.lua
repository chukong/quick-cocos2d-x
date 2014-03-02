
local CURRENT_MODULE_NAME = ...

local providers = {
    "PunchBox",
}
for _, packageName in ipairs(providers) do
    local className = "ad." .. packageName
    if not cc.Registry.exists(className) then
        cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), className)
    end
end

local ad = {}
cc.GameObject.extend(ad):addComponent("components.behavior.EventProtocol")

ad.RECEIVED_EVENT          = "RECEIVED_EVENT"
ad.PRESENTED_EVENT         = "PRESENTED_EVENT"
ad.DISMISSED_EVENT         = "DISMISSED_EVENT"
ad.CLICKED_EVENT           = "CLICKED_EVENT"
ad.FAILED_TO_RECEIVE_EVENT = "FAILED_TO_RECEIVE_EVENT"

local DEFAULT_PROVIDER_OBJECT_NAME = "ad.default"

--[[--

启动一个广告服务，返回广告服务对象。

首次启动的广告服务对象将成为默认广告服务，可以通过 ad.show() 方法直接调用。

]]
function ad.start(name, options)
    if not cc.Registry.isObjectExists(name) then
        local providerFactoryClass = cc.Registry.newObject(name)
        local provider = providerFactoryClass.start(ad, options)
        cc.Registry.setObject(provider, name)
        if not cc.Registry.isObjectExists(DEFAULT_PROVIDER_OBJECT_NAME) then
            cc.Registry.setObject(provider, DEFAULT_PROVIDER_OBJECT_NAME)
        end
    end
    return cc.Registry.getObject(name)
end

function ad.show(command, options, name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    local provider = cc.Registry.getObject(name)
    provider:show(command, options)
end

function ad.remove(command, name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    local provider = cc.Registry.getObject(name)
    provider:remove(command, name)
end

return ad
