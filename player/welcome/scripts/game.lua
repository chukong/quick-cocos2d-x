
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    display.addSpriteFramesWithFile(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)
    game.openWelcome()
end

function settings()
    demoDataList = {{id="demo1", text="<b>One Demo</b> <br/> <img src=\":/QuickIcon.png\"</img>"}
                      , {id="demo2", text="<b>Two Demo</b> <br/> <img src=\":/QuickIcon.png\"</img>"}}
    settings = {demoList = demoDataList}
    QT_INTERFACE("core.settings", json.encode(settings))
end

function game.exit()
    os.exit()
end

function game.openWelcome()
	settings()

    local WelcomeScene = require("scenes.WelcomeScene")
    display.replaceScene(WelcomeScene.new())
end
