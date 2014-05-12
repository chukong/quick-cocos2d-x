--[[

Copyright (c) 2011-2014 chukong-inc.com

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

PRINT_DEPRECATED("CCSceneExtend is deprecated, please use cc.SceneEx")

CCSceneExtend = class("CCSceneExtend", CCNodeExtend)
CCSceneExtend.__index = CCSceneExtend

function CCSceneExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCSceneExtend)

    local function handler(event)
        if event == "enter" then
            printInfo("Scene \"%s:onEnter()\"", target.name or (target.__cname or "unknown"))
            target:onEnter()
        elseif event == "enterTransitionFinish" then
            target:onEnterTransitionFinish()
        elseif event == "exitTransitionStart" then
            target:onExitTransitionStart()
        elseif event == "cleanup" then
            target:onCleanup()
        elseif event == "exit" then
            printInfo("Scene \"%s:onExit()\"", target.name or (target.__cname or "unknown"))

            if target.autoCleanupImages_ then
                for imageName, v in pairs(target.autoCleanupImages_) do
                    display.removeSpriteFrameByImageName(imageName)
                end
                target.autoCleanupImages_ = nil
            end

            target:onExit()

            if DEBUG_MEM then
                printInfo("----------------------------------------")
                printInfo(string.format("LUA VM MEMORY USED: %0.2f KB", collectgarbage("count")))
                CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
                printInfo("----------------------------------------")
            end
        end
    end
    target:setNodeEventEnabled(true, handler)

    return target
end

function CCSceneExtend:markAutoCleanupImage(imageName)
    if not self.autoCleanupImages_ then self.autoCleanupImages_ = {} end
    self.autoCleanupImages_[imageName] = true
    return self
end
