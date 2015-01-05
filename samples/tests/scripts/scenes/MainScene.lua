
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local items = {
        "framework.display",
        "framework.crypto",
        "framework.network",
        "framework.luabinding",
        "framework.socketTcp",
    }

    self:addChild(game.createMenu(items, handler(self, self.openTest)))
end

function MainScene:openTest(name)
    local Scene = require("tests." .. name .. "Test")
    display.replaceScene(Scene.new())
end

function MainScene:onEnter()
end

return MainScene
