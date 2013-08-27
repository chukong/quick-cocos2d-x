
CCLayerExtend = class("CCLayerExtend", CCNodeExtend)
CCLayerExtend.__index = CCLayerExtend

function CCLayerExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCLayerExtend)
    return target
end
