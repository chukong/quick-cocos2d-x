
CCSpriteExtend = class("CCSpriteExtend", CCNodeExtend)
CCSpriteExtend.__index = CCSpriteExtend

function CCSpriteExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCSpriteExtend)
    return target
end


function CCSpriteExtend:playAnimationOnce(animation, removeWhenFinished, onComplete, delay)
    return transition.playAnimationOnce(self, animation, removeWhenFinished, onComplete, delay)
end

function CCSpriteExtend:playAnimationForever(animation, delay)
    return transition.playAnimationForever(self, animation, delay)
end

function CCSpriteExtend:autoCleanup()
    if not self.IMAGE_FILENAME or self.AUTO_CLEANUP then return end

    local function handler(event)
        if event == "exit" then
            display.removeSpriteFrameByImageName(self.IMAGE_FILENAME)
        end
    end
    self:registerScriptHandler(handler)
    self.AUTO_CLEANUP = true
end
