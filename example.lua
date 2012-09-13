
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: "..tostring(errorMessage).."\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

xpcall(function()
    require("example.config")
    require("framework.init")
    require("framework.client.init")

    CCFileUtils:sharedFileUtils():setResourceDirectory("example/img")

    local SceneMenu = require("example.scenes.SceneMenu")
    display.replaceScene(SceneMenu.new())
end, __G__TRACKBACK__)
