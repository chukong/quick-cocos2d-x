
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.CCFileUtils:sharedFileUtils():addSearchPath("res/")
    display.addSpriteFramesWithFile(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)

    -- preload all sounds
    for k, v in pairs(GAME_SFX) do
        audio.preloadSound(v)
    end

    game.enterMenuScene()
end

function game.exit()
    os.exit()
end

function game.enterMenuScene()
    display.replaceScene(require("scenes.MenuScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.enterMoreGamesScene()
    display.replaceScene(require("scenes.MoreGamesScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.enterChooseLevelScene()
    display.replaceScene(require("scenes.ChooseLevelScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.playLevel(levelIndex)
    local PlayLevelScene = require("scenes.PlayLevelScene")
    display.replaceScene(PlayLevelScene.new(levelIndex), "fade", 0.6, display.COLOR_WHITE)
end
