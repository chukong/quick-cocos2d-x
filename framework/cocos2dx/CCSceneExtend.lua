
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
            echoInfo("Scene \"%s:onEnter()\"", target.name or (target.__cname or "unknown"))
            target:onEnter()
        elseif event == "enterTransitionFinish" then
            target:onEnterTransitionFinish()
        elseif event == "exitTransitionStart" then
            target:onExitTransitionStart()
        elseif event == "cleanup" then
            target:onCleanup()
        elseif event == "exit" then
            echoInfo("Scene \"%s:onExit()\"", target.name or (target.__cname or "unknown"))

            if target.autoCleanupImages_ then
                for imageName, v in pairs(target.autoCleanupImages_) do
                    display.removeSpriteFrameByImageName(imageName)
                end
                target.autoCleanupImages_ = nil
            end

            target:onExit()

            if DEBUG_MEM then
                echoInfo("----------------------------------------")
                echoInfo(string.format("LUA VM MEMORY USED: %0.2f KB", collectgarbage("count")))
                CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
                echoInfo("----------------------------------------")
            end
        elseif event == "cleanup" then
            target:onCleanup()
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
