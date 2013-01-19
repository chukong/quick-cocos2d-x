
local create = CCLayer.create
function CCLayer:create()
    local layer = create(CCLayer)

    function layer:addTouchEventListener(listener, isMultiTouches, priority, swallowsTouches)
        if type(isMultiTouches) ~= "boolean" then isMultiTouches = false end
        if type(priority) ~= "number" then priority = 0 end
        if type(swallowsTouches) ~= "boolean" then swallowsTouches = false end
        self:registerScriptTouchHandler(listener, isMultiTouches, priority, swallowsTouches)
    end

    function layer:removeTouchEventListener()
        self:unregisterScriptTouchHandler()
    end

    return layer
end
