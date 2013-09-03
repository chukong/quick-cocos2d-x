
cc.CCLayerExtend = class("CCLayerExtend", cc.CCNodeExtend)
cc.CCLayerExtend.__index = cc.CCLayerExtend

function cc.CCLayerExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, cc.CCLayerExtend)
    return target
end
