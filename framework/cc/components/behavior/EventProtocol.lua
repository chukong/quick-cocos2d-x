
local Component = import("..Component")
local EventProtocol = class("EventProtocol", Component)

function EventProtocol:ctor()
    EventProtocol.super.ctor(self, "EventProtocol")
    self.listeners_ = {}
    self.listenerHandleIndex_ = 0
end

function EventProtocol:addEventListener(eventName, listener, isWeakReference)
    eventName = string.upper(eventName)
    if self.listeners_[eventName] == nil then
        self.listeners_[eventName] = {}
    end

    self.listenerHandleIndex_ = self.listenerHandleIndex_ + 1
    local handle = string.format("HANDLE_%d", self.listenerHandleIndex_)
    local listener = {listener}
    if isWeakReference then
        setmetatable(listener, {__mode = "v"})
    end
    self.listeners_[eventName][handle] = listener
    return handle
end

function EventProtocol:dispatchEvent(event)
    event.name = string.upper(event.name)
    local eventName = event.name
    if self.listeners_[eventName] == nil then return end
    event.target = self.target_
    for handle, listener in pairs(self.listeners_[eventName]) do
        local callback = listener[1]
        if callback then
            local ret = callback(event, a)
            if ret == false then
                break
            elseif ret == "__REMOVE__" then
                self.listeners_[eventName][handle] = nil
            end
        else
            self.listeners_[eventName][handle] = nil
        end
    end
end

function EventProtocol:removeEventListener(eventName, key)
    eventName = string.upper(eventName)
    if self.listeners_[eventName] == nil then return end

    for handle, listener in pairs(self.listeners_[eventName]) do
        if key == handle or key == listener[1] then
            self.listeners_[eventName][handle] = nil
            break
        end
    end
end

function EventProtocol:removeAllEventListenersForEvent(eventName)
    self.listeners_[string.upper(eventName)] = nil
end

function EventProtocol:removeAllEventListeners()
    self.listeners_ = {}
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
