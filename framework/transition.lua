
local transition = {}

local ACTION_EASING = {}
ACTION_EASING["BACKIN"]           = {cc.CCEaseBackIn, 1}
ACTION_EASING["BACKINOUT"]        = {cc.CCEaseBackInOut, 1}
ACTION_EASING["BACKOUT"]          = {cc.CCEaseBackOut, 1}
ACTION_EASING["BOUNCE"]           = {cc.CCEaseBounce, 1}
ACTION_EASING["BOUNCEIN"]         = {cc.CCEaseBounceIn, 1}
ACTION_EASING["BOUNCEINOUT"]      = {cc.CCEaseBounceInOut, 1}
ACTION_EASING["BOUNCEOUT"]        = {cc.CCEaseBounceOut, 1}
ACTION_EASING["ELASTIC"]          = {cc.CCEaseElastic, 2, 0.3}
ACTION_EASING["ELASTICIN"]        = {cc.CCEaseElasticIn, 2, 0.3}
ACTION_EASING["ELASTICINOUT"]     = {cc.CCEaseElasticInOut, 2, 0.3}
ACTION_EASING["ELASTICOUT"]       = {cc.CCEaseElasticOut, 2, 0.3}
ACTION_EASING["EXPONENTIALIN"]    = {cc.CCEaseExponentialIn, 1}
ACTION_EASING["EXPONENTIALINOUT"] = {cc.CCEaseExponentialInOut, 1}
ACTION_EASING["EXPONENTIALOUT"]   = {cc.CCEaseExponentialOut, 1}
ACTION_EASING["IN"]               = {cc.CCEaseIn, 2, 1}
ACTION_EASING["INOUT"]            = {cc.CCEaseInOut, 2, 1}
ACTION_EASING["OUT"]              = {cc.CCEaseOut, 2, 1}
ACTION_EASING["RATEACTION"]       = {cc.CCEaseRateAction, 2, 1}
ACTION_EASING["SINEIN"]           = {cc.CCEaseSineIn, 1}
ACTION_EASING["SINEINOUT"]        = {cc.CCEaseSineInOut, 1}
ACTION_EASING["SINEOUT"]          = {cc.CCEaseSineOut, 1}

local actionManager = cc.CCDirector:sharedDirector():getActionManager()

function transition.newEasing(action, easingName, more)
    local key = string.upper(tostring(easingName))
    if string.sub(key, 1, 6) == "CCEASE" then
        key = string.sub(key, 7)
    end
    local easing
    if ACTION_EASING[key] then
        local cls, count, default = unpack(ACTION_EASING[key])
        if count == 2 then
            easing = cls:create(action, more or default)
        else
            easing = cls:create(action)
        end
    end
    return easing or action
end

function transition.create(action, args)
    args = totable(args)
    if args.easing then
        if type(args.easing) == "table" then
            action = transition.newEasing(action, unpack(args.easing))
        else
            action = transition.newEasing(action, args.easing)
        end
    end

    local actions = {}
    local delay = tonumber(args.delay)
    if delay > 0 then
        actions[#actions + 1] = cc.CCDelayTime:create(delay)
    end
    actions[#actions + 1] = action

    local onComplete = args.onComplete
    if type(onComplete) ~= "function" then onComplete = nil end
    if onComplete then
        actions[#actions + 1] = cc.CCCallFunc:create(onComplete)
    end

    if #actions > 1 then
        return transition.sequence(actions)
    else
        return actions[1]
    end
end

function transition.execute(target, action, args)
    assert(not tolua.isnull(target), "transition.execute() - target is not CCNode")
    local action = transition.create(action, args)
    target:runAction(action)
    return action
end

function transition.rotateTo(target, args)
    assert(not tolua.isnull(target), "transition.rotateTo() - target is not CCNode")
    -- local rotation = args.rotate
    local action = cc.CCRotateTo:create(args.time, args.rotate)
    return transition.execute(target, action, args)
end

function transition.moveTo(target, args)
    assert(not tolua.isnull(target), "transition.moveTo() - target is not CCNode")
    local tx, ty = target:getPosition()
    local x = args.x or tx
    local y = args.y or ty
    local action = cc.CCMoveTo:create(args.time, cc.p(x, y))
    return transition.execute(target, action, args)
end

function transition.moveBy(target, args)
    assert(not tolua.isnull(target), "transition.moveBy() - target is not CCNode")
    local x = args.x or 0
    local y = args.y or 0
    local action = cc.CCMoveBy:create(args.time, cc.p(x, y))
    return transition.execute(target, action, args)
end

function transition.fadeIn(target, args)
    assert(not tolua.isnull(target), "transition.fadeIn() - target is not CCNode")
    local action = cc.CCFadeIn:create(args.time)
    target:setOpacity(0)
    return transition.execute(target, action, args)
end

function transition.fadeOut(target, args)
    assert(not tolua.isnull(target), "transition.fadeOut() - target is not CCNode")
    local action = cc.CCFadeOut:create(args.time)
    target:setOpacity(255)
    return transition.execute(target, action, args)
end

function transition.fadeTo(target, args)
    assert(not tolua.isnull(target), "transition.fadeTo() - target is not CCNode")
    local opacity = toint(args.opacity)
    if opacity < 0 then
        opacity = 0
    elseif opacity > 255 then
        opacity = 255
    end
    local action = cc.CCFadeTo:create(args.time, opacity)
    return transition.execute(target, action, args)
end

function transition.scaleTo(target, args)
    assert(not tolua.isnull(target), "transition.scaleTo() - target is not CCNode")
    local action
    if args.scale then
        action = cc.CCScaleTo:create(tonumber(args.time), tonumber(args.scale))
    elseif args.scaleX or args.scaleY then
        local scaleX, scaleY
        if args.scaleX then
            scaleX = tonumber(args.scaleX)
        else
            scaleX = target:getScaleX()
        end
        if args.scaleY then
            scaleY = tonumber(args.scaleY)
        else
            scaleY = target:getScaleY()
        end
        action = cc.CCScaleTo:create(tonumber(args.time), scaleX, scaleY)
    end
    return transition.execute(target, action, args)
end

function transition.sequence(actions)
    if #actions < 1 then return end
    if #actions < 2 then return actions[1] end

    local prev = actions[1]
    for i = 2, #actions do
        prev = cc.CCSequence:createWithTwoActions(prev, actions[i])
    end
    return prev
end

function transition.playAnimationOnce(target, animation, removeWhenFinished, onComplete, delay)
    local actions = {}
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        actions[#actions + 1] = cc.CCDelayTime:create(delay)
        actions[#actions + 1] = cc.CCShow:create()
    end

    actions[#actions + 1] = cc.CCAnimate:create(animation)

    if removeWhenFinished then
        actions[#actions + 1] = cc.CCRemoveSelf:create()
    end
    if onComplete then
        actions[#actions + 1] = cc.CCCallFunc:create(onComplete)
    end

    local action
    if #actions > 1 then
        action = transition.sequence(actions)
    else
        action = actions[1]
    end
    target:runAction(action)
    return action
end

function transition.playAnimationForever(target, animation, delay)
    local animate = cc.CCAnimate:create(animation)
    local action
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        local sequence = transition.sequence({
            cc.CCDelayTime:create(delay),
            cc.CCShow:create(),
            animate,
        })
        action = cc.CCRepeatForever:create(sequence)
    else
        action = cc.CCRepeatForever:create(animate)
    end
    target:runAction(action)
    return action
end

function transition.removeAction(action)
    if not tolua.isnull(action) then
        actionManager:removeAction(action)
    end
end

function transition.stopTarget(target)
    if not tolua.isnull(target) then
        actionManager:removeAllActionsFromTarget(target)
    end
end

function transition.pauseTarget(target)
    if not tolua.isnull(target) then
        actionManager:pauseTarget(target)
    end
end

function transition.resumeTarget(target)
    if not tolua.isnull(target) then
        actionManager:resumeTarget(target)
    end
end

return transition
