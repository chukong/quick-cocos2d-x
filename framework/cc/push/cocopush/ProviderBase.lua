
local ProviderBase = class("ProviderBase")

local events = import("..events")

function ProviderBase:ctor(interface)
    self.interface_ = interface
end

function ProviderBase:callback_(event)
	echoInfo("cc.push.cocopush.ProviderBase:callback() - event:" .. event)

    local infos = string.split(event, "|")
    local evt = {
    provider = "push.CocoPush",
    type = infos[1],
    code = infos[2] }
    if infos[3] then
        evt.sucTags = string.split(infos[3], ",")
    end
    if infos[4] then
        evt.failTags = string.split(infos[4], ",")
    end
    
    evt.name = events.LISTENER
    self.interface_:dispatchEvent(evt)

end

return ProviderBase