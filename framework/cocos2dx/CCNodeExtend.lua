
CCNodeExtend = class("CCNodeExtend")
CCNodeExtend.__index = CCNodeExtend

function CCNodeExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCNodeExtend)
    return target
end

function CCNodeExtend:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

function CCNodeExtend:schedule(callback, interval)
    local seq = transition.sequence({
        CCDelayTime:create(interval),
        CCCallFunc:create(callback),
    })
    local action = CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

function CCNodeExtend:performWithDelay(callback, delay)
    local action = transition.sequence({
        CCDelayTime:create(delay),
        CCCallFunc:create(callback),
    })
    self:runAction(action)
    return action
end

function CCNodeExtend:onEnter()
end

function CCNodeExtend:onExit()
end

function CCNodeExtend:onEnterTransitionFinish()
end

function CCNodeExtend:onExitTransitionStart()
end

function CCNodeExtend:onCleanup()
end

function CCNodeExtend:setNodeEventEnabled(enabled, handler)
    if enabled then
        if not handler then
            handler = function(event)
                if event == "enter" then
                    self:onEnter()
                elseif event == "exit" then
                    self:onExit()
                elseif event == "enterTransitionFinish" then
                    self:onEnterTransitionFinish()
                elseif event == "exitTransitionStart" then
                    self:onExitTransitionStart()
                elseif event == "cleanup" then
                    self:onCleanup()
                end
            end
        end
        self:registerScriptHandler(handler)
    else
        self:unregisterScriptHandler()
    end
    return self
end

function CCNodeExtend:removeSelf(cleanup)
    if not tolua.isnull(self) then
        if cleanup ~= false then cleanup = true end
        self:removeFromParentAndCleanup(cleanup)
    end
end
