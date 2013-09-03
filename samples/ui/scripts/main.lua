
function __G__TRACKBACK__(errorMessage)
    cc.CCLuaLog("----------------------------------------")
    cc.CCLuaLog("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    cc.CCLuaLog(debug.traceback("", 2))
    cc.CCLuaLog("----------------------------------------")
end

xpcall(function()
    require("game")
    game.startup()
end, __G__TRACKBACK__)
