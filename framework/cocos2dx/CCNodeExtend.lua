
cc.CCNodeExtend = class("CCNodeExtend")
cc.CCNodeExtend.__index = cc.CCNodeExtend

function cc.CCNodeExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, cc.CCNodeExtend)
    return target
end

function cc.CCNodeExtend:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

function cc.CCNodeExtend:schedule(callback, interval)
    local seq = transition.sequence({
        cc.CCDelayTime:create(interval),
        cc.CCCallFunc:create(callback),
    })
    local action = cc.CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

function cc.CCNodeExtend:performWithDelay(callback, delay)
    local action = transition.sequence({
        cc.CCDelayTime:create(delay),
        cc.CCCallFunc:create(callback),
    })
    self:runAction(action)
    return action
end

function cc.CCNodeExtend:onEnter()
end

function cc.CCNodeExtend:onExit()
end

function cc.CCNodeExtend:onEnterTransitionFinish()
end

function cc.CCNodeExtend:onExitTransitionStart()
end

function cc.CCNodeExtend:onCleanup()
end

function cc.CCNodeExtend:setNodeEventEnabled(enabled, handler)
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

function cc.CCNodeExtend:removeSelf(cleanup)
    if not tolua.isnull(self) then
        if cleanup ~= false then cleanup = true end
        self:removeFromParentAndCleanup(cleanup)
    end
end
