--[[

Copyright (c) 2011-2012 qeeplay.com

http://dualface.github.com/quick-cocos2d-x/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

Bootstrap for client.

**Auto registered global module**

Module | Descripton
------ | ----------
@see framework.device | Query information about the system
@see framework.transition | Actions, Transformations and Effects
@see framework.display | Create scene, layer, sprite
@see framework.audio | Play music, sound effect
@see framework.ui | Create menu, label, widgets
@see framework.network | ...
@see framework.luaoc | Call Objective-C from Lua, iOS platform only
@see framework.luaj | Call Java from Lua, Android platform only
@see framework.crypto | Crypto

<br />

**More client modules**

Module | Descripton
------ | ----------
[framework.scheduler](framework.scheduler.html) | Scheduler

]]
math.randomseed(os.time())
math.random()
math.random()
math.random()
math.random()

local n = ...
__FRAMEWORK_PACKAGE_NAME__ = string.sub(n, 1, -6)
__FRAMEWORK_VERSION__      = "2.1.5"
__FRAMEWORK_GLOBALS__      = {}

if type(DEBUG) ~= "number" then DEBUG = 1 end

require(__FRAMEWORK_PACKAGE_NAME__ .. ".debug")
require(__FRAMEWORK_PACKAGE_NAME__ .. ".functions")

echoInfo("")
echoInfo("# DEBUG                        = "..DEBUG)
echoInfo("#")

device     = require(__FRAMEWORK_PACKAGE_NAME__ .. ".device")
transition = require(__FRAMEWORK_PACKAGE_NAME__ .. ".transition")
display    = require(__FRAMEWORK_PACKAGE_NAME__ .. ".display")
audio      = require(__FRAMEWORK_PACKAGE_NAME__ .. ".audio")
ui         = require(__FRAMEWORK_PACKAGE_NAME__ .. ".ui")
network    = require(__FRAMEWORK_PACKAGE_NAME__ .. ".network")
crypto     = require(__FRAMEWORK_PACKAGE_NAME__ .. ".crypto")

if device.platform == "android" then
    luaj = require(__FRAMEWORK_PACKAGE_NAME__ .. ".luaj")
elseif device.platform == "ios" then
    luaoc = require(__FRAMEWORK_PACKAGE_NAME__ .. ".luaoc")
end

local timeCount = 0
--[[--
@ignore
]]
local function showMemoryUsage(dt)
    timeCount = timeCount + dt
    echoInfo(string.format("MEMORY USED: %0.2f KB, UPTIME: %04.2fs", collectgarbage("count"), timeCount))
end

if DEBUG_FPS then
    CCDirector:sharedDirector():setDisplayStats(true)
end

if DEBUG_MEM then
    CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(showMemoryUsage, 10.0, false)
end
