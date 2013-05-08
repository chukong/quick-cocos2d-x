
local PlayLevelScene = class("PlayLevelScene", function()
    return display.newScene("PlayLevelScene")
end)

function PlayLevelScene:ctor(levelIndex)
    local bg = display.newSprite("#PlayLevelSceneBg.png")
    -- make background sprite always align top
    bg:setPosition(display.cx, display.top - bg:getContentSize().height / 2)
    self:addChild(bg)

    local title = display.newSprite("#Title.png", display.left + 150, display.top - 50)
    title:setScale(0.5)
    self:addChild(title)

    local label = ui.newBMFontLabel({
        text  = string.format("Level: %s", tostring(levelIndex)),
        font  = "UIFont.fnt",
        x     = display.left + 10,
        y     = display.bottom + 40,
        align = ui.TEXT_ALIGN_LEFT,
    })
    self:addChild(label)

    local Levels = require("data.Levels")
    local levelData = Levels.get(levelIndex)

    -- keypad layer, for android
    self.layer = display.newLayer()
    self.layer:addKeypadEventListener(function(event)
        if event == "back" then
            audio.playSound(GAME_SFX.backButton)
            self.layer:setKeypadEnabled(false)
            game.enterChooseLevelScene()
        end
    end)
    self:addChild(self.layer)
end

function PlayLevelScene:onEnter()
    -- avoid unmeant back
    self:performWithDelay(function()
        self.layer:setKeypadEnabled(true)
    end, 0.5)
end

return PlayLevelScene
