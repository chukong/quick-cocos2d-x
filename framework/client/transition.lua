
local M = {}

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

function M.newEasing(action, easingName, more)
    local key = string.upper(tostring(easingName))
    if string.sub(key, 1, 6) == "CCEASE" then
        key = string.sub(key, 7)
    end
    if ACTION_EASING[key] then
        local cls, count, default = unpack(ACTION_EASING[key])
        if count == 2 then
            easing = cls:actionWithAction(action, more or default)
        else
            easing = cls:actionWithAction(action)
        end
    end
    return easing
end

function M.execute(target, action, args)
    local delay = _n(args.delay)
    local time = _n(args.time)
    if time <= 0 then time = 0.2 end

    local onComplete = args.onComplete
    if type(onComplete) ~= "function" then onComplete = nil end

    if args.easing then
        if type(args.easing) == "table" then
            action = M.newEasing(action, unpack(args.easing))
        else
            action = M.newEasing(action, args.easing)
        end
    end

    if delay > 0 then
        action:retain()
        scheduler.performWithDelay(delay, function()
            target:runAction(action)
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

function M.moveTo(target, args)
    local x = args.x or target.x
    local y = args.y or target.y
    local action = CCMoveTo:create(args.time, ccp(x, y))
    return M.execute(target, action, args)
end

function M.moveBy(target, args)
    local x = args.x or target.x
    local y = args.y or target.y
    local action = CCMoveBy:create(args.time, ccp(x, y))
    return M.execute(target, action, args)
end

function M.fadeIn(target, args)
    local action = CCFadeIn:create(args.time)
    target.opacity = 0
    return M.execute(target, action, args)
end

function M.fadeOut(target, args)
    local action = CCFadeOut:create(args.time)
    target.opacity = 255
    return M.execute(target, action, args)
end

function M.fadeTo(target, args)
    local opacity = _i(args.opacity)
    if opacity < 0 then
        opacity = 0
    elseif opacity > 255 then
        opacity = 255
    end
    local action = CCFadeTo:create(args.time, opacity)
    return M.execute(target, action, args)
end

function M.scaleTo(target, args)
    local scale = _n(args.scale)
    local action = CCScaleTo:create(args.time, scale)
    return M.execute(target, action, args)
end

function M.removeAllActionsFromTarget(target)
    actionManager:removeAllActionsFromTarget(target)
end
M.removeTarget = M.removeAllActionsFromTarget

function M.removeAction(action)
    actionManager:removeAction(action)
end

function M.removeAllActions()
    actionManager:removeAllActions()
end
M.removeAll = M.removeAllActions

function M.pause(target)
    actionManager:pauseTarget(target)
end

function M.resume(target)
    actionManager:resumeTarget(target)
end

function M.sequence(actions)
    local arr = CCArray:array()
    for i = 1, #actions do
        arr:addObject(actions[i])
    end
    return CCSequence:actionsWithArrayLua(arr)
end

return M
