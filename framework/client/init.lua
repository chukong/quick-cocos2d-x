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

### Auto registered global module

Module | Descripton
------ | ----------
[framework.client.device](framework.client.device.html) | Query information about the system
[framework.client.transition](framework.client.transition.html) | Actions, Transformations and Effects
[framework.client.display](framework.client.display.html) | Create scene, layer, sprite
[framework.client.audio](framework.client.audio.html) | Play music, sound effect
[framework.client.ui](framework.client.ui.html) | Create menu, label, widgets
[framework.client.network](framework.client.network.html) | ...
[framework.client.luaoc](framework.client.luaoc.html) | Call Objective-C from Lua, iOS platform only
[framework.client.luaj](framework.client.luaj.html) | Call Java from Lua, Android platform only

<br />

### More client modules

Module | Descripton
------ | ----------
[framework.client.crypto](framework.client.crypto.html) | Crypto
[framework.client.network](framework.client.network.html) | Network
[framework.client.scheduler](framework.client.scheduler.html) | Scheduler

]]

__FRAMEWORK_ENVIRONMENT__ = "client"

require("framework.shared.debug")
require("framework.shared.functions")

echoInfo("")
echoInfo("# DEBUG                        = "..DEBUG)
echoInfo("#")

device     = require("framework.client.device")
transition = require("framework.client.transition")
display    = require("framework.client.display")
audio      = require("framework.client.audio")
ui         = require("framework.client.ui")
network    = require("framework.client.network")

if device.platform == "android" then
    -- luaj = require("framework.client.luaj")
elseif device.platform == "ios" then
    luaoc = require("framework.client.luaoc")
end

local timeCount = 0

--[[--

@ignore

]]
local function showMemoryUsage(dt)
    timeCount = timeCount + dt
    echoInfo(string.format("MEMORY USED: %0.2f KB, UPTIME: %04.2fs", collectgarbage("count"), timeCount))
end

if DEBUG > 1 then
    local sharedDirector = CCDirector:sharedDirector()
    sharedDirector:setDisplayStats(true)
end

if DEBUG_MEM_USAGE then
    sharedDirector:getScheduler():scheduleScriptFunc(showMemoryUsage, 10.0, false)
end
