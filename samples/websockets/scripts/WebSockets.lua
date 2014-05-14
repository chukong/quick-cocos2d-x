
local WebSockets = class("WebSockets")

WebSockets.TEXT_MESSAGE = 0
WebSockets.BINARY_MESSAGE = 1
WebSockets.BINARY_ARRAY_MESSAGE = 2

WebSockets.OPEN_EVENT    = "open"
WebSockets.MESSAGE_EVENT = "message"
WebSockets.CLOSE_EVENT   = "close"
WebSockets.ERROR_EVENT   = "error"

function WebSockets:ctor(url)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.socket = WebSocket:create(url)

    if self.socket then
        self.socket:registerScriptHandler(handler(self, self.onOpen_), kWebSocketScriptHandlerOpen)
        self.socket:registerScriptHandler(handler(self, self.onMessage_), kWebSocketScriptHandlerMessage)
        self.socket:registerScriptHandler(handler(self, self.onClose_), kWebSocketScriptHandlerClose)
        self.socket:registerScriptHandler(handler(self, self.onError_), kWebSocketScriptHandlerError)
    end
end

function WebSockets:isReady()
    return self.socket and self.socket:getReadyState() == kStateOpen
end

function WebSockets:send(data, messageType)
    if not self:isReady() then
        printError("WebSockets:send() - socket is't ready")
        return false
    end

    messageType = checkint(messageType)
    if messageType == WebSockets.TEXT_MESSAGE then
        self.socket:sendTextMsg(tostring(data))
    elseif messageType == WebSockets.BINARY_ARRAY_MESSAGE then
        data = checktable(data)
        self.socket:sendBinaryMsg(data, table.nums(data))
    else
        self.socket:sendBinaryStringMsg(tostring(data))
    end
    return true
end

function WebSockets:close()
    if self.socket then
        self.socket:close()
        self.socket = nil
    end
    self:removeAllEventListeners()
end

function WebSockets:onOpen_()
    self:dispatchEvent({name = WebSockets.OPEN_EVENT})
end

function WebSockets:onMessage_(message, messageLength)
    self:dispatchEvent({
        name = WebSockets.MESSAGE_EVENT,
        message = message,
        messageLength = messageLength
    })
end

function WebSockets:onClose_()
    self:dispatchEvent({name = WebSockets.CLOSE_EVENT})
    self:close()
end

function WebSockets:onError_(error)
    self:dispatchEvent({name = WebSockets.ERROR_EVENT, error = error})
end

return WebSockets
