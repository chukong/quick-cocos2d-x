
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

xpcall(function()
    require("game")
    game.startup()
end, __G__TRACKBACK__)
