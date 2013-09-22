
function __G__TRACKBACK__(errorMessage)
    CCLuaLog("----------------------------------------")
    CCLuaLog("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    CCLuaLog(debug.traceback("", 2))
    CCLuaLog("----------------------------------------")
end

local lanes = require("lanes").configure({
    verbose_errors = true,
    protect_allocator = true,
})

-- xpcall(function()
--     require("game")
--     game.startup()
-- end, __G__TRACKBACK__)
