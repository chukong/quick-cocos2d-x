
math.randomseed(os.time())
math.random()
math.random()
math.random()
math.random()

if type(DEBUG) ~= "number" then DEBUG = 1 end
local CURRENT_MODULE_NAME = ...

cc = cc or {}
cc.packageName = string.sub(CURRENT_MODULE_NAME, 1, -6)
cc.version = "2.5.0"

local exit = os.exit
function os.exit()
    CCDirector:sharedDirector():endToLua()
    exit()
end

require(cc.packageName .. ".debug")
require(cc.packageName .. ".functions")
require(cc.packageName .. ".cocos2dx")

echoInfo("")
echoInfo("# DEBUG                        = "..DEBUG)
echoInfo("#")

device     = require(cc.packageName .. ".device")
transition = require(cc.packageName .. ".transition")
display    = require(cc.packageName .. ".display")
audio      = require(cc.packageName .. ".audio")
network    = require(cc.packageName .. ".network")
ui         = require(cc.packageName .. ".ui")
crypto     = require(cc.packageName .. ".crypto")
json       = require(cc.packageName .. ".json")

if device.platform == "android" then
    luaj = require(cc.packageName .. ".luaj")
elseif device.platform == "ios" then
    luaoc = require(cc.packageName .. ".luaoc")
end

local timeCount = 0
local sharedTextureCache = CCTextureCache:sharedTextureCache()
local sharedDirector = CCDirector:sharedDirector()
local function showMemoryUsage(dt)
    timeCount = timeCount + dt
    echoInfo("----------------------------------------")
    echoInfo(string.format("LUA VM MEMORY USED: %0.2f KB, UPTIME: %04.2fs", collectgarbage("count"), timeCount))
    sharedTextureCache:dumpCachedTextureInfo()
    echoInfo("----------------------------------------")
end

if DEBUG_FPS then
    sharedDirector:setDisplayStats(true)
end

if DEBUG_MEM then
    sharedDirector:getScheduler():scheduleScriptFunc(showMemoryUsage, 10.0, false)
end
