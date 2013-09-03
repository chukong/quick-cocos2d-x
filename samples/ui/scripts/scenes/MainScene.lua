
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local label = ui.newTTFLabel({
        text = "Hello, World",
        size = 64,
        x = display.cx,
        y = display.cy,
        align = ui.TEXT_ALIGN_CENTER
    })
    self:addChild(label)

    local button1 = cc.ui.UIButton.new("Button01.png", "Button01Pressed.png", "Button01Disabled.png")
    button1:pos(display.cx - 150, display.top - 100)
        :setEnabled(true)
        :onClicked(function(x, y)
            printf("x = %0.2f, y = %0.2f", x, y)
            button1:setEnabled(false)
        end)
    self:addChild(button1)

    local button2 = cc.ui.UIButton.new("Button01.png", "Button01Pressed.png", "Button01Disabled.png")
    button2:pos(display.cx + 150, display.top - 100)
        :setEnabled(true)
        :onClicked(function(x, y)
            printf("x = %0.2f, y = %0.2f", x, y)
            button1:setEnabled(true)
        end)
    self:addChild(button2)
end

function MainScene:onEnter()
    if device.platform ~= "android" then return end

    -- avoid unmeant back
    self:performWithDelay(function()
        -- keypad layer, for android
        local layer = display.newLayer()
        layer:addKeypadEventListener(function(event)
            if event == "back" then game.exit() end
        end)
        self:addChild(layer)

        layer:setKeypadEnabled(true)
    end, 0.5)
end

return MainScene
