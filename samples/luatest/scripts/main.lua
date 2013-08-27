
CCFileUtils:sharedFileUtils():addSearchPath("res/")

require "mainMenu"

-- run
local scene = CCScene:create()
scene:addChild(CreateTestMenu())
CCDirector:sharedDirector():runWithScene(scene)
