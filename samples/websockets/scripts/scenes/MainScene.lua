
local lanes = require("lanes").configure({
    verbose_errors = true,
    protect_allocator = true,
})

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local connectLabel = ui.newTTFLabelMenuItem({
        text = "connect",
        size = 32,
        x = display.cx,
        y = display.top - 32,
        listener = handler(self, self.onConnectClicked),
    })

    local sendLabel = ui.newTTFLabelMenuItem({
        text = "send number",
        size = 32,
        x = display.cx,
        y = display.top - 64,
        listener = handler(self, self.onSendNumberClicked),
    })

    self:addChild(ui.newMenu({connectLabel, sendLabel}))

    -- init websockets
    local websocket = require("websocket")
    self.client = websocket.client.sync({timeout = 2})
end

function MainScene:onConnectClicked()
    local f = lanes.gen(function(n) return 2*n end)
    local a = f(1)
    local b = f(2)
    print( a[1], b[1] )

    local ok,err = self.client:connect("ws://localhost:8088/s")
    if ok then
        print("connected")
        self:startListener()
    else
        print("could not connect", err)
    end
end

function MainScene:onSendNumberClicked()
    local ok = self.client:send("hello " .. tostring(math.random()))
    if ok then
       print("msg sent")
    else
       print("connection closed")
    end

end

function MainScene:startListener()

end

function MainScene:onEnter()
end

return MainScene
