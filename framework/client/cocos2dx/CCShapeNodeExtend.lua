
CCShapeNodeExtend = class("CCShapeNodeExtend", CCNodeExtend)
CCShapeNodeExtend.__index = CCShapeNodeExtend

function CCShapeNodeExtend.extend(target)
    local t = {}
    setmetatable(t, CCShapeNodeExtend)
    tolua.setpeer(target, t)
    return target
end

function CCShapeNodeExtend:setColor(r, g, b, a)
    CCShapeNode.setColor(self, ccc4f(r / 255, g / 255, b / 255, (a or 255) / 255))
end
