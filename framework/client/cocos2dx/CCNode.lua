
local nodeObject = getmetatable(CCNode)

function nodeObject:align(anchorPoint, x, y)
    display.align(self, anchorPoint, x, y)
end

local removeFromParentAndCleanup = nodeObject.removeFromParentAndCleanup
function nodeObject:removeFromParentAndCleanup(isCleanup)
    if type(isCleanup) ~= "boolean" then isCleanup = true end
    if not tolua.isnull(self) then
        removeFromParentAndCleanup(isCleanup)
    end
end

function nodeObject:removeSelf(isCleanup)
    self:removeFromParentAndCleanup(isCleanup)
end

function nodeObject:pixels()
    local x, y = self:getPosition()
    self:setPosition(display.pixels(x, y))
end

function nodeObject:scheduleUpdate(callback, priority)
    self:scheduleUpdateWithPriorityLua(callback, _i(priority))
end

function nodeObject:schedule(callback, interval)
    local seq = transition.sequence({
        CCDelayTime:create(interval),
        CCCallFunc:create(callback),
    })
    local action = CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

function nodeObject:performWithDelay(callback, delay)
    local action = transition.sequence({
        CCDelayTime:create(delay),
        CCCallFunc:create(callback),
    })
    self:runAction(action)
    return action
end

local actionManager = CCDirector:sharedDirector():getActionManager()
function nodeObject:removeAction(action)
    if not tolua.isnull(action) then
        actionManager:removeAction(action)
    end
end

function nodeObject:stopAllActions()
    if not tolua.isnull(target) then
        actionManager:removeAllActionsFromTarget(self)
    end
end

function nodeObject:onEnter()
end

function nodeObject:onExit()
end
