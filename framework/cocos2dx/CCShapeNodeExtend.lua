
CCShapeNodeExtend = class("CCShapeNodeExtend", CCNodeExtend)
CCShapeNodeExtend.__index = CCShapeNodeExtend

function CCShapeNodeExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCShapeNodeExtend)
    return target
end

function CCShapeNodeExtend:setColor(r, g, b, a)
    CCShapeNode.setColor(self, ccc4f(r / 255, g / 255, b / 255, (a or 255) / 255))
end
