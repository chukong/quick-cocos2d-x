
local BubbleButton = require("views.BubbleButton")

local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    self.bg = display.newBackgroundSprite("#MenuSceneBg.png")
    self:addChild(self.bg)

    self.adBar = require("views.AdBar").new()
    self:addChild(self.adBar)

    -- create menu
    self.moreGamesButton = BubbleButton.new({
        image = "#MenuSceneMoreGamesButton.png",
        x = display.left + 150,
        y = display.bottom + 300,
        sound = GAME_SFX.tapButton,
        listener = function()
            self.menu:setEnabled(false)
            display.replaceScene(require("scenes.MoreGamesScene").new(),
                                 "fade",
                                 0.4,
                                 display.COLOR_WHITE)
        end,
    })

    self.startButton = BubbleButton.new({
        image = "#MenuSceneStartButton.png",
        x = display.right - 150,
        y = display.bottom + 300,
        sound = GAME_SFX.tapButton,
        listener = function()
            self.menu:setEnabled(false)
            display.replaceScene(require("scenes.ChooseLevelScene").new(),
                                 "fade",
                                 0.4,
                                 display.COLOR_WHITE)
        end,
    })

    self.menu = ui.newMenu({self.moreGamesButton, self.startButton})
    self:addChild(self.menu)
end

return MenuScene
