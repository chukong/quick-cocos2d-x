
local Component = import("..Component")
local EventProtocol = class("EventProtocol", Component)

function EventProtocol:ctor()
    EventProtocol.super.ctor(self, "EventProtocol")
    self.listeners_ = {}
    self.listenerHandleIndex_ = 0
    self.debug_ = false
end

function EventProtocol:addEventListener(eventName, listener, data)
    eventName = string.upper(eventName)
    if self.listeners_[eventName] == nil then
        self.listeners_[eventName] = {}
    end

    self.listenerHandleIndex_ = self.listenerHandleIndex_ + 1
    local handle = tostring(self.listenerHandleIndex_)
    self.listeners_[eventName][handle] = {listener, data}

    if self.debug_ then
        if data then
            echoInfo("EventProtocol:addEventListener() - add listener [%s] %s:%s for event %s", handle, tostring(data), tostring(listener), eventName)
        else
            echoInfo("EventProtocol:addEventListener() - add listener [%s] %s for event %s", handle, tostring(listener), eventName)
        end
    end

    return handle
end

function EventProtocol:dispatchEvent(event)
    event.name = string.upper(event.name)
    local eventName = event.name
    if self.debug_ then
        echoInfo("EventProtocol:dispatchEvent() - dispatching event %s", eventName)
    end

    if self.listeners_[eventName] == nil then return end
    event.target = self.target_

    for handle, listener in pairs(self.listeners_[eventName]) do
        if self.debug_ then
            echoInfo("EventProtocol:dispatchEvent() - dispatching event %s to listener [%s]", eventName, handle)
        end
        local ret
        if listener[2] then
            ret = listener[1](listener[2], event)
        else
            ret = listener[1](event)
        end
        if ret == false then
            if self.debug_ then
                echoInfo("EventProtocol:dispatchEvent() - break dispatching for event %s", eventName)
            end
            break
        end
    end
    return self
end

function EventProtocol:removeEventListener(eventName, key1, key2)
    eventName = string.upper(eventName)
    if self.listeners_[eventName] == nil then return end

    for handle, listener in pairs(self.listeners_[eventName]) do
        if key1 == handle or (key1 == listener[1] and key2 == listener[2]) then
            self.listeners_[eventName][handle] = nil
            if self.debug_ then
                echoInfo("EventProtocol:removeEventListener() - remove listener [%s] for event %s", handle, eventName)
            end
            return handle
        end
    end
    return self
end

function EventProtocol:removeAllEventListenersForEvent(eventName)
    self.listeners_[string.upper(eventName)] = nil
    if self.debug_ then
        echoInfo("EventProtocol:removeAllEventListenersForEvent() - remove all listeners for event %s", eventName)
    end
    return self
end

function EventProtocol:removeAllEventListeners()
    self.listeners_ = {}
    if self.debug_ then
        echoInfo("EventProtocol:removeAllEventListeners() - remove all listeners")
    end
    return self
end

function EventProtocol:dumpAllEventListeners()
    print("---- EventProtocol:dumpAllEventListeners() ----")
    for name, listeners in pairs(self.listeners_) do
        printf("-- event: %s", name)
        for handle, listener in pairs(listeners) do
            printf("--     handle: %s, %s", tostring(handle), tostring(listener))
        end
    end
    return self
end

function EventProtocol:setEventProtocolDebugEnabled(enabled)
    self.debug_ = enabled
    return self
end

function EventProtocol:exportMethods()
    self:exportMethods_({
        "addEventListener",
        "dispatchEvent",
        "removeEventListener",
        "removeAllEventListenersForEvent",
        "removeAllEventListeners",
    })
    return self
end

function EventProtocol:onBind_()
end

function EventProtocol:onUnbind_()
end

return EventProtocol
