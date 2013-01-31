
local ChooseLevelScene = class("ChooseLevelScene", function()
    return display.newScene("ChooseLevelScene")
end)

function ChooseLevelScene:ctor()
    local bg = display.newBackgroundSprite("#ChooseLevelSceneBg.png")
    self:addChild(bg)

    local adBar = require("views.AdBar").new()
    self:addChild(adBar)

    -- create levels list
    local levelsList = require("views.LevelsList").new()
    self:addChild(levelsList)

    -- create menu
    local unlockAllButton = ui.newImageMenuItem({
        image = "#UnlockAllButton.png",
        imageSelected = "#UnlockAllButtonSelected.png",
        x = display.left + 140,
        y = display.bottom + 120,
        sound = GAME_SFX.tapButton,
        listener = function()
            -- display.replaceScene(require("scenes.ChooseLevelScene").new())
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
            display.replaceScene(require("scenes.MenuScene").new(),
                                 "fade",
                                 0.4,
                                 display.COLOR_WHITE)
        end,
    })

    local menu = ui.newMenu({unlockAllButton, backButton})
    self:addChild(menu)
end

return ChooseLevelScene
