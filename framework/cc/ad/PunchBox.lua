
local CURRENT_MODULE_NAME = ...

local PunchBox = class("PunchBox")

function PunchBox.start(interface, options)
    -- assert(type(options) == "table", "PunchBox.start() - invalid options")
    -- assert(type(options.appId) == "string", "PunchBox.start() - invalid options, miss appId")
    local providerClass
    if device.platform == "ios" then
        providerClass = import(".PunchBox_iOS", CURRENT_MODULE_NAME)
    elseif device.platform == "android" then
        providerClass = import(".PunchBox_Android", CURRENT_MODULE_NAME)
    else
        echoError("ad.PunchBox:ctor() - not supported platform %s", device.platform)
        return
    end

    local provider = providerClass.new()
    provider:start(interface, options)
    return provider
end

return PunchBox
