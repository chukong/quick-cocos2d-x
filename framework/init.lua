
math.randomseed(os.time())
math.random()
math.random()
math.random()
math.random()

if type(DEBUG) ~= "number" then DEBUG = 1 end
local CURRENT_MODULE_NAME = ...

cc = cc or {}
cc.PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)
cc.VERSION = "2.5.0"
cc.REMOVE_HANDLER_SIGN = "__REMOVE_HANDLER__"

local exit = os.exit
function os.exit()
    CCDirector:sharedDirector():endToLua()
    exit()
end

require(cc.PACKAGE_NAME .. ".debug")
require(cc.PACKAGE_NAME .. ".functions")
require(cc.PACKAGE_NAME .. ".cocos2dx")

echoInfo("")
echoInfo("# DEBUG                        = "..DEBUG)
echoInfo("#")

device     = require(cc.PACKAGE_NAME .. ".device")
transition = require(cc.PACKAGE_NAME .. ".transition")
display    = require(cc.PACKAGE_NAME .. ".display")
audio      = require(cc.PACKAGE_NAME .. ".audio")
network    = require(cc.PACKAGE_NAME .. ".network")
ui         = require(cc.PACKAGE_NAME .. ".ui")
crypto     = require(cc.PACKAGE_NAME .. ".crypto")
json       = require(cc.PACKAGE_NAME .. ".json")

if device.platform == "android" then
    luaj = require(cc.PACKAGE_NAME .. ".luaj")
elseif device.platform == "ios" then
    luaoc = require(cc.PACKAGE_NAME .. ".luaoc")
end

if not NO_GAMEOBJETS then
    require(cc.PACKAGE_NAME .. ".cc.init")
end

if not NO_SHORTCODES then
    require(cc.PACKAGE_NAME .. ".shortcodes")
end

local sharedTextureCache = CCTextureCache:sharedTextureCache()
local sharedDirector = CCDirector:sharedDirector()
local function showMemoryUsage()
    echoInfo(string.format("LUA VM MEMORY USED: %0.2f KB", collectgarbage("count")))
end

if DEBUG_FPS then
    sharedDirector:setDisplayStats(true)
end

if DEBUG_MEM then
    sharedDirector:getScheduler():scheduleScriptFunc(showMemoryUsage, 10.0, false)
end
