
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

function CCLayerExtend:addTouchEventListener(listener, isMultiTouches, priority, swallowsTouches)
    if type(isMultiTouches) ~= "boolean" then isMultiTouches = false end
    if type(priority) ~= "number" then priority = 0 end
    if type(swallowsTouches) ~= "boolean" then swallowsTouches = false end
    self:registerScriptTouchHandler(listener, isMultiTouches, priority, swallowsTouches)
end

function CCLayerExtend:removeTouchEventListener()
    self:unregisterScriptTouchHandler()
end
