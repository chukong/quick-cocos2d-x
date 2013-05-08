
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    self.bg = display.newBackgroundSprite("#MenuSceneBg.png")
    self:addChild(self.bg)

    self.adBar = require("views.AdBar").new()
    self:addChild(self.adBar)

    -- create menu
    local BubbleButton = require("views.BubbleButton")
    self.moreGamesButton = BubbleButton.new({
        image = "#MenuSceneMoreGamesButton.png",
        x = display.left + 150,
        y = display.bottom + 300,
        sound = GAME_SFX.tapButton,
        prepare = function()
            self.menu:setEnabled(false)
            self.layer:setKeypadEnabled(false)
        end,
        listener = function()
            game.enterMoreGamesScene()
        end,
    })

    self.startButton = BubbleButton.new({
        image = "#MenuSceneStartButton.png",
        x = display.right - 150,
        y = display.bottom + 300,
        sound = GAME_SFX.tapButton,
        prepare = function()
            print("startButton prepare")
            self.menu:setEnabled(false)
            self.layer:setKeypadEnabled(false)
        end,
        listener = function()
            game.enterChooseLevelScene()
        end,
    })

    self.menu = ui.newMenu({self.moreGamesButton, self.startButton})
    self:addChild(self.menu)

    -- keypad layer, for android
    self.layer = display.newLayer()
    self.layer:addKeypadEventListener(function(event)
        if event == "back" then
            audio.playSound(GAME_SFX.backButton)
            game.exit()
        end
    end)
    self:addChild(self.layer)
end

function MenuScene:onEnter()
    -- avoid unmeant back
    self:performWithDelay(function()
        self.layer:setKeypadEnabled(true)
    end, 0.5)
end

return MenuScene
