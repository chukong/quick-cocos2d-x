
require("config")
require("framework.init")
require("framework.shortcodes")
require("chilli.init")

-- define global module
game = {}

function game.startup()
    cc.CCFileUtils:sharedFileUtils():addSearchPath("res/")

    game.enterMainScene()
end

function game.exit()
    cc.CCDirector:sharedDirector():endToLua()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end
