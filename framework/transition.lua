
local transition = {}

local ACTION_EASING = {}
ACTION_EASING["BACKIN"]           = {CCEaseBackIn, 1}
ACTION_EASING["BACKINOUT"]        = {CCEaseBackInOut, 1}
ACTION_EASING["BACKOUT"]          = {CCEaseBackOut, 1}
ACTION_EASING["BOUNCE"]           = {CCEaseBounce, 1}
ACTION_EASING["BOUNCEIN"]         = {CCEaseBounceIn, 1}
ACTION_EASING["BOUNCEINOUT"]      = {CCEaseBounceInOut, 1}
ACTION_EASING["BOUNCEOUT"]        = {CCEaseBounceOut, 1}
ACTION_EASING["ELASTIC"]          = {CCEaseElastic, 2, 0.3}
ACTION_EASING["ELASTICIN"]        = {CCEaseElasticIn, 2, 0.3}
ACTION_EASING["ELASTICINOUT"]     = {CCEaseElasticInOut, 2, 0.3}
ACTION_EASING["ELASTICOUT"]       = {CCEaseElasticOut, 2, 0.3}
ACTION_EASING["EXPONENTIALIN"]    = {CCEaseExponentialIn, 1}
ACTION_EASING["EXPONENTIALINOUT"] = {CCEaseExponentialInOut, 1}
ACTION_EASING["EXPONENTIALOUT"]   = {CCEaseExponentialOut, 1}
ACTION_EASING["IN"]               = {CCEaseIn, 2, 1}
ACTION_EASING["INOUT"]            = {CCEaseInOut, 2, 1}
ACTION_EASING["OUT"]              = {CCEaseOut, 2, 1}
ACTION_EASING["RATEACTION"]       = {CCEaseRateAction, 2, 1}
ACTION_EASING["SINEIN"]           = {CCEaseSineIn, 1}
ACTION_EASING["SINEINOUT"]        = {CCEaseSineInOut, 1}
ACTION_EASING["SINEOUT"]          = {CCEaseSineOut, 1}

local actionManager = CCDirector:sharedDirector():getActionManager()

local function newEasing(action, easingName, more)
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
            action = newEasing(action, unpack(args.easing))
        else
            action = newEasing(action, args.easing)
        end
    end

    local actions = {}
    local delay = tonumber(args.delay)
    if delay > 0 then
        actions[#actions + 1] = CCDelayTime:create(delay)
    end
    actions[#actions + 1] = action

    local onComplete = args.onComplete
    if type(onComplete) ~= "function" then onComplete = nil end
    if onComplete then
        actions[#actions + 1] = CCCallFunc:create(onComplete)
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
    local action = CCRotateTo:create(args.time, args.rotate)
    return transition.execute(target, action, args)
end

function transition.moveTo(target, args)
    assert(not tolua.isnull(target), "transition.moveTo() - target is not CCNode")
    local tx, ty = target:getPosition()
    local x = args.x or tx
    local y = args.y or ty
    local action = CCMoveTo:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

function transition.moveBy(target, args)
    assert(not tolua.isnull(target), "transition.moveBy() - target is not CCNode")
    local x = args.x or 0
    local y = args.y or 0
    local action = CCMoveBy:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

function transition.fadeIn(target, args)
    assert(not tolua.isnull(target), "transition.fadeIn() - target is not CCNode")
    local action = CCFadeIn:create(args.time)
    target:setOpacity(0)
    return transition.execute(target, action, args)
end

function transition.fadeOut(target, args)
    assert(not tolua.isnull(target), "transition.fadeOut() - target is not CCNode")
    local action = CCFadeOut:create(args.time)
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
    local action = CCFadeTo:create(args.time, opacity)
    return transition.execute(target, action, args)
end

function transition.scaleTo(target, args)
    assert(not tolua.isnull(target), "transition.scaleTo() - target is not CCNode")
    local action
    if args.scale then
        action = CCScaleTo:create(tonumber(args.time), tonumber(args.scale))
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
        action = CCScaleTo:create(tonumber(args.time), scaleX, scaleY)
    end
    return transition.execute(target, action, args)
end

function transition.sequence(actions)
    if #actions < 1 then return end
    if #actions < 2 then return actions[1] end

    local prev = actions[1]
    for i = 2, #actions do
        prev = CCSequence:createWithTwoActions(prev, actions[i])
    end
    return prev
end

function transition.playAnimationOnce(target, animation, removeWhenFinished, onComplete, delay)
    local actions = {}
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        actions[#actions + 1] = CCDelayTime:create(delay)
        actions[#actions + 1] = CCShow:create()
    end

    actions[#actions + 1] = CCAnimate:create(animation)

    if removeWhenFinished then
        actions[#actions + 1] = CCRemoveSelf:create()
    end
    if onComplete then
        actions[#actions + 1] = CCCallFunc:create(onComplete)
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
    local animate = CCAnimate:create(animation)
    local action
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        local sequence = transition.sequence({
            CCDelayTime:create(delay),
            CCShow:create(),
            animate,
        })
        action = CCRepeatForever:create(sequence)
    else
        action = CCRepeatForever:create(animate)
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
