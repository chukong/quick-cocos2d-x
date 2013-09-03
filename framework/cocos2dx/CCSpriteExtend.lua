
cc.CCSpriteExtend = class("CCSpriteExtend", cc.CCNodeExtend)
cc.CCSpriteExtend.__index = cc.CCSpriteExtend

function cc.CCSpriteExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, cc.CCSpriteExtend)
    return target
end

function cc.CCSpriteExtend:playAnimationOnce(animation, removeWhenFinished, onComplete, delay)
    return transition.playAnimationOnce(self, animation, removeWhenFinished, onComplete, delay)
end

function cc.CCSpriteExtend:playAnimationForever(animation, delay)
    return transition.playAnimationForever(self, animation, delay)
end
