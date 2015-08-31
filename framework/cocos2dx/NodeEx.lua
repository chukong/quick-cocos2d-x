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
    if enabled then
        if self.__node_event_handle__ then
            self:removeNodeEventListener(self.__node_event_handle__)
            self.__node_event_handle__ = nil
        end

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
        self.__node_event_handle__ = self:addNodeEventListener(c.NODE_EVENT, listener)
    elseif self.__node_event_handle__ then
        self:removeNodeEventListener(self.__node_event_handle__)
        self.__node_event_handle__ = nil
    end
    return self
end

function Node:removeScriptEventListenersByEvent(event)
    PRINT_DEPRECATED("Node.removeScriptEventListenersByEvent() is deprecated, please use c.node):removeNodeEventListenersByEvent()")
    self:removeNodeEventListenersByEvent(event)
end

function Node:registerScriptHandler(listener)
    PRINT_DEPRECATED("Node.registerScriptHandler() is deprecated, please use Node.addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_EVENT, function(event)
        listener(event.name)
    end)
end

function Node:unregisterScriptHandler()
    PRINT_DEPRECATED("Node.unregisterScriptHandler() is deprecated, please use Node.removeAllNodeEventListeners()")
    return self:removeAllNodeEventListeners()
end

function Node:addTouchEventListener(handler)
    PRINT_DEPRECATED("Node.addTouchEventListener() is deprecated, please use Node.addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
        return handler(event.name, event.x, event.y, event.prevX, event.prevY)
    end)
end

function Node:registerScriptTouchHandler(handler, isMultiTouches)
    PRINT_DEPRECATED("Node.registerScriptTouchHandler() is deprecated, please use Node.addNodeEventListener()")
    if isMultiTouches then
        self:setTouchMode(c.TOUCH_MODE_ALL_AT_ONCE)
    else
        self:setTouchMode(c.TOUCH_MODE_ONE_BY_ONE)
    end
    return self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
        if event.mode == c.TOUCH_MODE_ALL_AT_ONCE then
            local points = {}
            for id, p in pairs(event.points) do
                points[#points + 1] = p.x
                points[#points + 1] = p.y
                points[#points + 1] = p.id
            end
            return handler(event.name, points)
        else
            return handler(event.name, event.x, event.y, event.prevX, event.prevY)
        end
    end)
end

Node.scheduleUpdate_ = Node.scheduleUpdate
function Node:scheduleUpdate(handler)
    if handler then
        PRINT_DEPRECATED("Node.scheduleUpdate(handler) is deprecated, please use Node.addNodeEventListener()")
        self:addNodeEventListener(c.NODE_ENTER_FRAME_EVENT, handler)
        self:scheduleUpdate_()
    else
        self:scheduleUpdate_()
    end
end

function Node:scheduleUpdateWithPriorityLua(handler)
    PRINT_DEPRECATED("Node.scheduleUpdateWithPriorityLua() is deprecated, please use Node.addNodeEventListener()")
    self:addNodeEventListener(c.NODE_ENTER_FRAME_EVENT, handler)
    self:scheduleUpdate_()
end

function Node:setTouchPriority()
    PRINT_DEPRECATED("Node.setTouchPriority() is deprecated, remove it")
end

function Node:setCascadeOpacityEnabledRecursively(enabled)
    self:setCascadeOpacityEnabled(enabled)

    local children = self:getChildren()
    local childCount = self:getChildrenCount()
    if childCount < 1 then
        return
    end
    if type(children) == "table" then
        for i = 1, childCount do
            local node = children[i]
            node:setCascadeOpacityEnabledRecursively(enabled)
        end
    elseif type(children) == "userdata" then
        for i = 1, childCount do
            local node = children:objectAtIndex(i - 1)
            if node.setCascadeOpacityEnabledRecursively ~= nil then
                node:setCascadeOpacityEnabledRecursively(enabled)
            end
        end
    end
end