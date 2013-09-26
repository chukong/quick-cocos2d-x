function __G__TRACKBACK__(errorMessage)
    print("---------------------------------------------------------")
    print(debug.traceback("LUA ERROR: " .. tostring(errorMessage), 2))
    print("---------------------------------------------------------")
end

function main()
    require("config")
    display.replaceScene(require("scenes.MainScene").new())
end

xpcall(main, __G__TRACKBACK__)
