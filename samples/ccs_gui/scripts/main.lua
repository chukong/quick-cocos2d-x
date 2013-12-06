-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

require("framework.init")
CCFileUtils:sharedFileUtils():addSearchPath("res/")
CCFileUtils:sharedFileUtils():addSearchPath("res/testscene/")
local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    require("game")
    game.startup()
end

xpcall(main, __G__TRACKBACK__)
