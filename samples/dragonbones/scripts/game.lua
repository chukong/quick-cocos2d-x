require("config")
require("framework.init")

-- define global module
game = {}

game.DragonBonesDemo = require("DragonBonesDemo")

game._DEMOS= {
	require("demos.DragonDemoEntry"),
	require("demos.DragonSwitchClothes"),
	require("demos.DragonChaseStarling"),
	require("demos.DragonAsyncLoading"),
}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

	game._curDemo = 1
	game._demoCount = #game._DEMOS

    game.showDemoScene()
end

function game.exit()
    --CCDirector:sharedDirector():endToLua()
    os.exit()
end

function game.showDemoScene()
    display.replaceScene(
		game._DEMOS[game._curDemo].new(
			game._onNext, 
			game._onPrev, 
			game._onReset,
			game.exit
		), 
		"fade", 0.6, display.COLOR_WHITE)
end

function game._onPrev()
	game._curDemo = game._curDemo - 1
	if game._curDemo <= 0 then
		game._curDemo = game._demoCount
	end
	game.showDemoScene()
end

function game._onReset()
	game.showDemoScene()
end

function game._onNext()
	game._curDemo = game._curDemo + 1
	if game._curDemo > game._demoCount then
		game._curDemo = 1
	end
	game.showDemoScene()
end

