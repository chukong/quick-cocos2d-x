--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

针对 cc.Node 的扩展

]]

local c = cc
local Node = c.Node

function Node:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

function Node:schedule(callback, interval)
    local seq = transition.sequence({
        CCDelayTime:create(interval),
        CCCallFunc:create(callback),
    })
    local action = CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

function Node:performWithDelay(callback, delay)
    local action = transition.sequence({
        CCDelayTime:create(delay),
        CCCallFunc:create(callback),
    })
    self:runAction(action)
    return action
end

function Node:onEnter()
end

function Node:onExit()
end

function Node:onEnterTransitionFinish()
end

function Node:onExitTransitionStart()
end

function Node:onCleanup()
end

function Node:setNodeEventEnabled(enabled, listener)
    local handle
    if enabled then
        if not listener then
            listener = function(event)
                local name = event.name
                if name == "enter" then
                    self:onEnter()
                elseif name == "exit" then
                    self:onExit()
                elseif name == "enterTransitionFinish" then
                    self:onEnterTransitionFinish()
                elseif name == "exitTransitionStart" then
                    self:onExitTransitionStart()
                elseif name == "cleanup" then
                    self:onCleanup()
                end
            end
        end
        handle = self:addNodeEventListener(c.NODE_EVENT, listener)
    else
        self:removeNodeEventListener(handle)
    end
    return self
end

function Node:removeScriptEventListenersByEvent(event)
    PRINT_DEPRECATED("Node:removeScriptEventListenersByEvent() is deprecated, please use c.node):removeNodeEventListenersByEvent()")
    self:removeNodeEventListenersByEvent(event)
end

function Node:registerScriptHandler(listener)
    PRINT_DEPRECATED("Node:registerScriptHandler() is deprecated, please use Node:addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_EVENT, listener)
end

function Node:unregisterScriptHandler()
    PRINT_DEPRECATED("Node:unregisterScriptHandler() is deprecated, please use Node:removeAllNodeEventListeners()")
    return self:removeAllNodeEventListeners()
end

function Node:addTouchEventListener(handler)
    PRINT_DEPRECATED("Node:addTouchEventListener() is deprecated, please use Node:addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
        return handler(event.name, event.x, event.y, event.prevX, event.prevY)
    end)
end
