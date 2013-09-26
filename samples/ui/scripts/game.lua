
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.chilli.init")

-- define global module
game = {}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    game.enterMainScene()
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.CharacterScene").new(), "fade", 0.6, display.COLOR_WHITE)
end
