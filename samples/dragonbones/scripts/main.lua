
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

--package.path = package.path
	 --.. ";d:/cocos2dx/quick/?.lua"
	 --.. ";/Users/zrong/cocos2dx/quick/?.lua"

require("game")
game.startup()
