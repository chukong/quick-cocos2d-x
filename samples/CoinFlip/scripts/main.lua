
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    CCLuaLog("----------------------------------------")
    CCLuaLog("LUA ERROR: "..tostring(errorMessage).."\n")
    CCLuaLog(debug.traceback("", 2))
    CCLuaLog("----------------------------------------")
end

xpcall(function()
    require("config")
    require("framework.init")
    require("framework.client.init")

    if display.contentScaleFactor <= 0.50 then
        -- for iPhone 3Gs, use low-res assets
        CCFileUtils:sharedFileUtils():setResourceDirectory("res/sd/")
        CCDirector:sharedDirector():setContentScaleFactor(display.contentScaleFactor)
    else
        CCFileUtils:sharedFileUtils():setResourceDirectory("res/hd/")
    end
    display.addSpriteFramesWithFile("AllSprites.plist", "AllSprites.png")

	display.replaceScene(require("scenes.MenuScene").new())
end, __G__TRACKBACK__)
