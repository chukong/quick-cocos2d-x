
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    CCLuaLog("----------------------------------------")
    CCLuaLog("LUA ERROR: "..tostring(errorMessage).."\n")
    CCLuaLog(debug.traceback("", 2))
    CCLuaLog("----------------------------------------")
end

xpcall(function()
    require("game")
    game.startup()
end, __G__TRACKBACK__)

-- require("config")
-- require("framework.init")
-- require("framework.client.init")

-- -- local lanes = require("lanes").configure()

-- local function callback(event)
--     local zlib = require("zlib")
--     local request = event.request
--     dump(request:getResponseString(), "request:getResponseString()")
-- end

-- local network = require("framework.client.network")
-- local request = network.sendHttpRequest("http://vm2.localhost/", "GET", callback)
-- request:addRequestHeader("Accept-Encoding:", "gzip")
-- request:start()
