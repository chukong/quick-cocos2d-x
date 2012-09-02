
log.warning("")
log.warning("# DEBUG                        = "..DEBUG)
log.warning("#")

-- define global module
device     = require("framework.client.device")
display    = require("framework.client.display")
scheduler  = require("framework.client.scheduler")
transition = require("framework.client.transition")
audio      = require("framework.client.audio")
ui         = require("framework.client.ui")
crypto     = require("framework.client.crypto")
network    = require("framework.client.network")
json       = require("framework.shared.json")

local timeCount = 0
local function checkMemory(dt)
    timeCount = timeCount + dt
    local used = collectgarbage("count")
    echo(string.format("[LUA] MEMORY USED: %0.2f KB, UPTIME: %04.2fs", used, timeCount))
end
-- if DEBUG > 1 then
--     CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(checkMemory, 2.0, false)
-- end

if DEBUG > 0 then
    CCDirector:sharedDirector():setDisplayStats(true)
end

local function onNotificationPost(msg)
    if msg == "app.enterFullScreen" or msg == "app.exitFullScreen" then
        display.reset()
    end
end

CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(onNotificationPost)

collectgarbage("setpause", 150)
collectgarbage("setstepmul", 1000)
