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

-   device: [framework.client.device](framework.client.device.html)
-   transition: [framework.client.transition](framework.client.transition.html)
-   display: [framework.client.display](framework.client.display.html)
-   audio: [framework.client.audio](framework.client.audio.html)
-   ui: [framework.client.ui](framework.client.ui.html)
-   luaj: [framework.client.luaj](framework.client.device.html) , Android platform only

]]

__FRAMEWORK_ENVIRONMENT__ = "client"

require("framework.shared.debug")
require("framework.shared.functions")

echoWarning("")
echoWarning("# DEBUG                        = "..DEBUG)
echoWarning("#")

device     = require("framework.client.device")
transition = require("framework.client.transition")
display    = require("framework.client.display")
audio      = require("framework.client.audio")
ui         = require("framework.client.ui")

if device.platform == "android" then
    luaj = require("framework.client.luaj")
end

local timeCount = 0
--[[--

@ignore

]]
local function checkMemory(dt)
    timeCount = timeCount + dt
    local used = collectgarbage("count")
    echo(string.format("[LUA] MEMORY USED: %0.2f KB, UPTIME: %04.2fs", used, timeCount))
end
if DEBUG > 1 then
    CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(checkMemory, 30.0, false)
end

collectgarbage("setpause", 150)
collectgarbage("setstepmul", 1000)
