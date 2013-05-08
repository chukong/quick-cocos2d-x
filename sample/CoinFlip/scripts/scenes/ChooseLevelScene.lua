
local ChooseLevelScene = class("ChooseLevelScene", function()
    return display.newScene("ChooseLevelScene")
end)

function ChooseLevelScene:ctor()
    local bg = display.newSprite("#OtherSceneBg.png")
    -- make background sprite always align top
    bg:setPosition(display.cx, display.top - bg:getContentSize().height / 2)
    self:addChild(bg)

    local title = display.newSprite("#Title.png", display.cx, display.top - 100)
    self:addChild(title)

    local adBar = require("views.AdBar").new()
    self:addChild(adBar)

    -- create levels list
    local rect = CCRect(display.left, display.bottom + 180, display.width, display.height - 280)
    self.levelsList = require("views.LevelsList").new(rect)
    self.levelsList:addEventListener("onTapLevelIcon", function(event)
        return self:onTapLevelIcon(event)
    end)
    self:addChild(self.levelsList)

    -- create menu
    local unlockAllButton = ui.newImageMenuItem({
        image = "#UnlockAllButton.png",
        imageSelected = "#UnlockAllButtonSelected.png",
        x = display.left + 140,
        y = display.bottom + 120,
        sound = GAME_SFX.tapButton,
        listener = function()
            print("UNLOCK ALL")
        end,
    })

    local backButton = ui.newImageMenuItem({
        image = "#BackButton.png",
        imageSelected = "#BackButtonSelected.png",
        x = display.right - 100,
        y = display.bottom + 120,
        sound = GAME_SFX.backButton,
        listener = function()
            self.layer:setKeypadEnabled(false)
            self:backToMenuScene()
        end,
    })

    local menu = ui.newMenu({unlockAllButton, backButton})
    self:addChild(menu)

    -- keypad layer, for android
    self.layer = display.newLayer()
    self.layer:addKeypadEventListener(function(event)
        if event == "back" then
            audio.playSound(GAME_SFX.backButton)
            self.layer:setKeypadEnabled(false)
            self:backToMenuScene()
        end
    end)
    self:addChild(self.layer)
end

function ChooseLevelScene:onTapLevelIcon(event)
    audio.playSound(GAME_SFX.tapButton)
    game.playLevel(event.levelIndex)
end

function ChooseLevelScene:backToMenuScene()
    game.enterMenuScene()
end

function ChooseLevelScene:onEnter()
    self.levelsList:setTouchEnabled(true)

    -- avoid unmeant back
    self:performWithDelay(function()
        self.layer:setKeypadEnabled(true)
    end, 0.5)
end

return ChooseLevelScene
