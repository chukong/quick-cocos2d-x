
local WebSockets = require("WebSockets")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

local function bin2hex(binary)
    local t = {}
    for i = 1, string.len(binary) do
        t[#t + 1] = string.format("0x%02x", string.byte(binary, i))
    end
    return table.concat(t, " ")
end

function MainScene:ctor()
    local connectLabel = ui.newTTFLabelMenuItem({
        text = "connect",
        size = 32,
        x = display.cx,
        y = display.top - 32,
        listener = handler(self, self.onConnectClicked),
    })

    local sendTextLabel = ui.newTTFLabelMenuItem({
        text = "send text",
        size = 32,
        x = display.cx,
        y = display.top - 64,
        listener = handler(self, self.onSendTextClicked),
    })

    local sendBinaryLabel = ui.newTTFLabelMenuItem({
        text = "send binary",
        size = 32,
        x = display.cx,
        y = display.top - 96,
        listener = handler(self, self.onSendBinaryClicked),
    })

    self:addChild(ui.newMenu({connectLabel, sendTextLabel, sendBinaryLabel}))
end

function MainScene:onOpen(event)
    print("connected")
end

function MainScene:onMessage(event)
    if event.messageLength then
        printf("receive binary msg: len = %s, binary = %s", event.messageLength, bin2hex(event.message))
    else
        printf("receive text msg: %s", event.message)
    end
end

function MainScene:onClose(event)
    self.websocket = nil
end

function MainScene:onError(event)
    printf("error %s", event.error)
    self.websocket = nil
end

function MainScene:onConnectClicked()
    if self.websocket then return end
    self.websocket = WebSockets.new("ws://echo.websocket.org")
    self.websocket:addEventListener(WebSockets.OPEN_EVENT, handler(self, self.onOpen))
    self.websocket:addEventListener(WebSockets.MESSAGE_EVENT, handler(self, self.onMessage))
    self.websocket:addEventListener(WebSockets.CLOSE_EVENT, handler(self, self.onClose))
    self.websocket:addEventListener(WebSockets.ERROR_EVENT, handler(self, self.onError))
end

function MainScene:onSendTextClicked()
    if not self.websocket then
        print("not connected")
        return
    end

    local text = "hello " .. tostring(math.random())
    if self.websocket:send(text) then
        printf("send text msg: %s", text)
    end
end

function MainScene:onSendBinaryClicked()
    if not self.websocket then
        print("not connected")
        return
    end

    local t = {}
    for i = 1, math.random(4, 8) do
        t[#t + 1] = string.char(math.random(0, 31))
    end
    local binary = table.concat(t)
    if self.websocket:send(binary, WebSockets.BINARY_MESSAGE) then
        printf("send binary msg: len = %d, binary = %s", string.len(binary), bin2hex(binary))
    end
end

return MainScene
