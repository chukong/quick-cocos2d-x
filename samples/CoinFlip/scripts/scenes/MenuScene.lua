
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
    self.startButton = BubbleButton.new({
        image = "#MenuSceneStartButton.png",
        x = display.cx - 200,
        y = display.cy - 140,
        sound = GAME_SFX.tapButton,
        listener = function()
            self.menu:setEnabled(false)
            display.replaceScene(require("scenes.ChooseLevelScene").new(),
                                 "fade",
                                 0.4,
                                 display.COLOR_WHITE)
        end,
    })

    self.moreGamesButton = BubbleButton.new({
        image = "#MenuSceneMoreGamesButton.png",
        x = display.cx + 200,
        y = display.cy - 140,
        sound = GAME_SFX.tapButton,
        listener = function()
            self.menu:setEnabled(false)
            display.replaceScene(require("scenes.MoreGamesScene").new(),
                                 "fade",
                                 0.4,
                                 display.COLOR_WHITE)
        end,
    })

    self.menu = ui.newMenu({self.startButton, self.moreGamesButton})
    self:addChild(self.menu)
end

return MenuScene
