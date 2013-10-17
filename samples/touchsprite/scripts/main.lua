
function __G__TRACKBACK__(errorMessage)
    CCLuaLog("----------------------------------------")
    CCLuaLog("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    CCLuaLog(debug.traceback("", 2))
    CCLuaLog("----------------------------------------")
end

require("game")
game.startup()
