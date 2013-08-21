
CCNodeExtend = class("CCNodeExtend")
CCNodeExtend.__index = CCNodeExtend

--[[--

]]
function CCNodeExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCNodeExtend)
    return target
end

--[[--

Set node object anchorPoint and position.

### Example:

    sprite:align(display.LEFT_TOP, 100, 100)

### Parameters:

-   enum **anchorPoint** is one of the following:

    enum                                              | Value
    ------------------------------------------------- | ----------------------
    display.CENTER                                    | CCPoint(0.5, 0.5)
    display.TOP_LEFT,<br />display.LEFT_TOP           | CCPoint(  0,   1)
    display.TOP_CENTER,<br />display.CENTER_TOP       | CCPoint(0.5,   1)
    display.TOP_RIGHT,<br />display.RIGHT_TOP         | CCPoint(  1,   1)
    display.CENTER_LEFT,<br />display.LEFT_CENTER     | CCPoint(  0, 0.5)
    display.CENTER_RIGHT,<br />display.RIGHT_CENTER   | CCPoint(  1, 0.5)
    display.BOTTOM_LEFT,<br />display.LEFT_BOTTOM     | CCPoint(  0,   0)
    display.BOTTOM_RIGHT,<br />display.RIGHT_BOTTOM   | CCPoint(  1,   0)
    display.BOTTOM_CENTER,<br />display.CENTER_BOTTOM | CCPoint(0.5,   0)

-   [_optional float **x**, float **y**_] position of the node

]]
function CCNodeExtend:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
end


--[[--

]]
function CCNodeExtend:schedule(callback, interval)
    local seq = transition.sequence({
        CCDelayTime:create(interval),
        CCCallFunc:create(callback),
    })
    local action = CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

--[[--

]]
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
end

function CCNodeExtend:registerNodeEvent(handler)
end
