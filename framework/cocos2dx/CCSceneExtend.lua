
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
            echoInfo("Scene \"%s:onEnter()\"", target.name or (target.className or "unknown"))
            target:onEnter()
        elseif event == "enterTransitionFinish" then
            target:onEnterTransitionFinish()
        elseif event == "exitTransitionStart" then
            target:onExitTransitionStart()
        elseif event == "cleanup" then
            target:onCleanup()
        elseif event == "exit" then
            echoInfo("Scene \"%s:onExit()\"", target.name or (target.className or "unknown"))

            if target.AUTO_CLEANUP_IMAGES then
                for imageName, v in pairs(target.AUTO_CLEANUP_IMAGES) do
                    display.removeSpriteFrameByImageName(imageName)
                end
                target.AUTO_CLEANUP_IMAGES = nil
            end

            target:onExit()

            if DEBUG_MEM then
                CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
            end
        elseif event == "cleanup" then
            target:onCleanup()
        end
    end
    target:setNodeEventEnabled(true, handler)

    return target
end

function CCSceneExtend:markAutoCleanupImage(imageName)
    if not self.AUTO_CLEANUP_IMAGES then self.AUTO_CLEANUP_IMAGES = {} end
    self.AUTO_CLEANUP_IMAGES[imageName] = true
    return self
end
