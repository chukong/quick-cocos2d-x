
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    display.addSpriteFramesWithFile(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)
    game.openWelcome()
end

function game.exit()
    os.exit()
end

function game.openWelcome()
    local WelcomeScene = require("scenes.WelcomeScene")
    display.replaceScene(WelcomeScene.new())
end
