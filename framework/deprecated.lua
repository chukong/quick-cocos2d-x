
--tip
local function replaceTip(oldName, newName)
    printf("\n********** \n%s was deprecated please use %s instead.\n**********", oldName, newName)
end

local function removeTip(oldName)
    printf("\n********** \n%s was removed.\n**********", oldName)
end

----------------------------------------

function display.newBackgroundSprite(filename)
    replaceTip("display.newBackgroundSprite(filename)", "newSprite(filename, display.cx, display.cy)")
    return display.newSprite(filename, display.cx, display.cy)
end

function display.pixels(x, y)
    removeTip("display.pixels()")
    local scale = 1 / display.contentScaleFactor
    if x then x = round(x / scale) * scale end
    if y then y = round(y / scale) * scale end
    return x, y
end

function display.newBackgroundTilesSprite(filename)
    replaceTip("display.newBackgroundTilesSprite(filename)", "newTilesSprite()")
    return display.newTilesSprite(filename)
end

function display.newFrame(frameName)
    replaceTip("display.newFrame(filename)", "newSpriteFrame()")
    return display.newSpriteFrame(frameName)
end

function display.newSpriteWithFrame(frame, x, y)
    replaceTip("display.newSpriteWithFrame(frame)", "newSprite()")
    return display.newSprite(frame, x, y)
end

function display.newAnimate(animation)
    removeTip("display.newAnimate()")
    return CCAnimate:create(animation)
end

function string.urlencodeChar(char)
    removeTip("string.urlencodeChar(char)")
    return "%" .. string.format("%02X", string.byte(c))
end

function CCNodeExtend:removeAction(action)
    replaceTip("CCNode:removeAction(action)", "stopAction()")
    self:stopAction(action)
end

function CCNodeExtend:numberOfRunningActions()
    replaceTip("CCNode:numberOfRunningActions()", "getNumberOfRunningActions()")
    return self:getNumberOfRunningActions()
end

function CCNodeExtend:registerNodeEvent(handler)
    replaceTip("CCNode:registerNodeEvent(handler)", "setNodeEventEnabled(true, handler)")
    self:setNodeEventEnabled(true, handler)
end

function CCNodeExtend:addScriptAccelerateHandler(...)
    replaceTip("CCLayer:addScriptAccelerateHandler(...)", "addAccelerateEventListener()")
    return self:addAccelerateEventListener(...)
end

function CCNodeExtend:removeScriptAccelerateListener()
    replaceTip("CCLayer:removeScriptAccelerateListener()", "removeAccelerateEventHandler()")
    return self:removeAccelerateEventHandler()
end

function CCNodeExtend:registerScriptTouchHandler(...)
    replaceTip("CCLayer:registerScriptTouchHandler(...)", "addTouchEventListener()")
    return self:addTouchEventListener(...)
end

function CCNodeExtend:unregisterScriptTouchHandler()
    replaceTip("CCLayer:unregisterScriptTouchHandler()", "removeTouchEventListener()")
    return self:removeTouchEventListener()
end

function CCNodeExtend:registerScriptKeypadHandler(...)
    replaceTip("CCLayer:registerScriptKeypadHandler(...)", "addKeypadEventListener()")
    return self:addKeypadEventListener(...)
end

function CCNodeExtend:unregisterScriptKeypadHandler()
    replaceTip("CCLayer:unregisterScriptKeypadHandler()", "removeKeypadEventListener()")
    return self:removeKeypadEventListener()
end

function CCSceneExtend:addAutoCleanImage(filename)
    replaceTip("CCScene:addAutoCleanImage(filename)", "markAutoCleanupImage(filename)")
    return self:markAutoCleanupImage(filename)
end
