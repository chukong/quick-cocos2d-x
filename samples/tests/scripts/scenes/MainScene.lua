
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local items = {
        "framework.display",
        "framework.crypto",
    }

    self:addChild(game.createMenu(items, handler(self, self.openTest)))
end

function MainScene:openTest(name)
    local Scene = require("tests." .. name .. "Test")
    display.replaceScene(Scene.new())
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
