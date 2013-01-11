
local MenuScene = {}

function MenuScene.new()
    local scene = display.newScene("MenuScene")

    ----

    function init()
        local bg = display.newSprite("#MenuSceneBg.png")
        bg:align(display.TOP_CENTER, display.cx, display.top)
        scene:addChild(bg)

        local adBar = require("scenes.ui.AdBar").new()
        scene:addChild(adBar)
    end

    ----

    function scene:onEnter()
    end

    function scene:onExit()
    end

    init()
    return scene
end

return MenuScene
