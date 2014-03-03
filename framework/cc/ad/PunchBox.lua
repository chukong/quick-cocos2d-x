
local CURRENT_MODULE_NAME = ...

local Factory = class("Factory")

function Factory.getInstance(interface, options)
    local providerClass
    if device.platform == "ios" then
        providerClass = import(".punchbox.ProviderIOS", CURRENT_MODULE_NAME)
    elseif device.platform == "android" then
        providerClass = import(".punchbox.ProviderAndroid", CURRENT_MODULE_NAME)
    else
        echoError("ad.PunchBox:ctor() - not supported platform %s", device.platform)
        return
    end

    local provider = providerClass.new(interface, options)
    if provider:start() then return provider end

    return nil -- create provider failed
end

return Factory
