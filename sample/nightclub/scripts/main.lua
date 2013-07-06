function __G__TRACKBACK__(errorMessage)
    CCLuaLog("---------------------------------------------------------")
    CCLuaLog(debug.traceback("LUA ERROR: " .. tostring(errorMessage), 2))
    CCLuaLog("---------------------------------------------------------")
end

function main()
    require("config")
    display.replaceScene(require("scenes.MainScene").new())
end

xpcall(main, __G__TRACKBACK__)
