
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

function transition.newEasing(action, easingName, more)
    local key = string.upper(tostring(easingName))
    if string.sub(key, 1, 6) == "CCEASE" then
        key = string.sub(key, 7)
    end
    if ACTION_EASING[key] then
        local cls, count, default = unpack(ACTION_EASING[key])
        if count == 2 then
            easing = cls:create(action, more or default)
        else
            easing = cls:create(action)
        end
    end
    return easing
end

function transition.execute(target, action, args)
    local delay = _n(args.delay)
    local time = _n(args.time)
    if time <= 0 then time = 0.2 end

    local onComplete = args.onComplete
    if type(onComplete) ~= "function" then onComplete = nil end

    if args.easing then
        if type(args.easing) == "table" then
            action = transition.newEasing(action, unpack(args.easing))
        else
            action = transition.newEasing(action, args.easing)
        end
    end

    if delay > 0 then
        action:retain()
        scheduler.performWithDelay(delay, function()
            if not tolua.isnull(target) then
                target:runAction(action)
            end
            action:release()
        end)
    else
        target:runAction(action)
    end

    if onComplete then
        action.onCompleteHandle = scheduler.performWithDelay(delay + time, function()
            action.onCompleteHandle = nil
            onComplete()
        end)
    end

    return action
end

function transition.moveTo(target, args)
    local tx, ty = target:getPosition()
    local x = args.x or tx
    local y = args.y or ty
    local action = CCMoveTo:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

function transition.moveBy(target, args)
    local x = args.x or 0
    local y = args.y or 0
    local action = CCMoveBy:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

function transition.fadeIn(target, args)
    local action = CCFadeIn:create(args.time)
    target:setOpacity(0)
    return transition.execute(target, action, args)
end

function transition.fadeOut(target, args)
    local action = CCFadeOut:create(args.time)
    target:setOpacity(255)
    return transition.execute(target, action, args)
end

function transition.fadeTo(target, args)
    local opacity = _i(args.opacity)
    if opacity < 0 then
        opacity = 0
    elseif opacity > 255 then
        opacity = 255
    end
    local action = CCFadeTo:create(args.time, opacity)
    return transition.execute(target, action, args)
end

function transition.scaleTo(target, args)
    local action
    if args.scale then
        local scale = _n(args.scale)
        action = CCScaleTo:create(_n(args.time), scale)
    elseif args.scaleX or args.scaleY then
        local scaleX, scaleY
        if args.scaleX then
            scaleX = _n(args.scaleX)
        else
            scaleX = target:getScaleX()
        end
        if args.scaleY then
            scaleY = _n(args.scaleY)
        else
            scaleY = target:getScaleY()
        end
        action = CCScaleTo:create(_n(args.time), scaleX, scaleY)
    end
    return transition.execute(target, action, args)
end

function transition.removeAllActionsFromTarget(target)
    actionManager:removeAllActionsFromTarget(target)
end
transition.removeTarget = transition.removeAllActionsFromTarget

function transition.removeAction(action)
    actionManager:removeAction(action)
end

function transition.removeAllActions()
    actionManager:removeAllActions()
end
transition.removeAll = transition.removeAllActions

function transition.pause(target)
    actionManager:pauseTarget(target)
end

function transition.resume(target)
    actionManager:resumeTarget(target)
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

return transition
