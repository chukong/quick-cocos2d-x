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

Actions, Transformations and Effects

]]

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

--[[--
@ignore
]]
local function newEasing(action, easingName, more)
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

--[[--

Execute an action with a target.

### Example:

    -- moving right target 100 points, durations of 2.0 seconds.
    local action = CCMoveBy:create(ccp(100, 0), 0.2)

    local args = {
        delay = 3.0,                        -- before moving, delay 3.0 seconds
        easing = "CCEaseBackInOut",         -- use CCEaseBackInOut for easing
        onComplete = function()             -- call function after moving completed
            echo("MOVING COMPLETED")
        end,
    }
    transition.execute(sprite, action, args)

Note: **Other transiton methods can also use the same args parameters.**

### Parameters:

-   CCNode **target**

-   CCAction **action**

-   [_optional table **args**_]

]]
function transition.execute(target, action, args)
    assert(not tolua.isnull(target), "transition.execute() - target is not CCNode")

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
        action = transition.sequence(actions)
        target:runAction(action)
    else
        target:runAction(actions[1])
    end

    return action
end

--[[--

Moves a sprite to the position x,y. x and y are absolute coordinates by modifying it's position attribute.

### Example:

    -- Moving sprite to 100, 100
    transition.moveTo(sprite, {time = 2.0, x = 100, y = 100})

### Parameters:

-   CCNode **target**

-   table **args**

]]
function transition.moveTo(target, args)
    assert(not tolua.isnull(target), "transition.moveTo() - target is not CCNode")
    local tx, ty = target:getPosition()
    local x = args.x or tx
    local y = args.y or ty
    local action = CCMoveTo:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

--[[--

Moves a sprite x,y points by modifying it's position attribute. x and y are relative to the position of the object.

### Example:

    -- Moving right and up
    transition.moveBy(sprite, {time = 2.0, x = 100, y = 100})

### Parameters:

-   CCNode **target**

-   table **args**

]]
function transition.moveBy(target, args)
    assert(not tolua.isnull(target), "transition.moveBy() - target is not CCNode")
    local x = args.x or 0
    local y = args.y or 0
    local action = CCMoveBy:create(args.time, ccp(x, y))
    return transition.execute(target, action, args)
end

--[[--

Fades In an sprite. It modifies the opacity from 0 to 255. The "reverse" of this action is transition.fadeOut() .

### Example:

    transition.fadeIn(sprite, {time = 1.0})

### Parameters:

-   CCNode **target**

-   table **args**

]]
function transition.fadeIn(target, args)
    assert(not tolua.isnull(target), "transition.fadeIn() - target is not CCNode")
    local action = CCFadeIn:create(args.time)
    target:setOpacity(0)
    return transition.execute(target, action, args)
end

--[[--

Fades Out an sprite. It modifies the opacity from 255 to 0. The "reverse" of this action is transition.fadeIn() .

### Parameters:

-   CCNode **target**

-   table **args**

]]
function transition.fadeOut(target, args)
    assert(not tolua.isnull(target), "transition.fadeOut() - target is not CCNode")
    local action = CCFadeOut:create(args.time)
    target:setOpacity(255)
    return transition.execute(target, action, args)
end

--[[--

Fades an sprite. It modifies the opacity from the current value to a custom one.

### Example:

    transition.fadeTo(sprite, {time = 2.0, opacity = 200})

### Parameters:

-   CCNode **target**

-   table **args**

]]
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

--[[--

Scales a sprite to a zoom factor by modifying it's scale attribute.

### Example:

    transition.scaleTo(sprite1, {time = 2.0, scale = 2.0})      -- zoom sprite
    transition.scaleTo(sprite2, {time = 2.0, scaleX = 2.0})     -- zoom horizontal
    transition.scaleTo(sprite3, {time = 2.0, scaleY = 2.0})     -- zoom vertical

### Parameters:

-   CCNode **target**

-   table **args**

]]
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

--[[--

Create an array of sequenceable actions given an table.

### Example:

    local function onComplete()
        echo("SEQUENCE COMPLETED")
    end

    local action = transition.sequence({
        CCMoveBy:create(sprite, ccp(100, 0)),   -- moving right
        CCDelayTime:create(1.0),                -- delay 1 seconds
        CCMoveBy:create(sprite, ccp(0, 100)),   -- moving up
        CCCallFunc:create(onComplete),          -- call function
    })

    sprite:runAction(action)

### Parameters:

-   table **actions**

]]
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

    actions[#actions + 1] = display.newAnimate(animation)

    if removeWhenFinished or onComplete then
        actions[#actions + 1] = CCCallFunc:create(function()
            if removeWhenFinished then
                target:removeFromParentAndCleanup(true)
            end
            if type(onComplete) == "function" then
                onComplete()
            end
        end)
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

function transition.playAnimationForever(target, animation, isRestoreOriginalFrame, delay)
    local animate = display.newAnimate(animation, isRestoreOriginalFrame)
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

--[[--

Stop the action.

### Example:

    local action = transition.moveTo(sprite, {time = 2.0, x = 100, y = 100})
    ....
    transition.removeAction(action) -- stop moving

### Parameters:

-   CCAction **action**

]]
function transition.removeAction(action)
    if not tolua.isnull(action) then
        actionManager:removeAction(action)
    end
end

--[[--

Stop all actions for the target.

### Example:

    transition.moveTo(sprite, {time = 2.0, x = 100, y = 100})
    transition.fadeOut(sprite, {time = 2.0})
    ....
    transition.stopTarget(sprite) -- stop moving, stop fades


### Parameters:

-   CCNode **target**

]]
function transition.stopTarget(target)
    if not tolua.isnull(target) then
        actionManager:removeAllActionsFromTarget(target)
    end
end

--[[--

Pauses the target, all running actions and newly added actions will be paused.

### Parameters:

-   CCNode **target**

]]
function transition.pauseTarget(target)
    if not tolua.isnull(target) then
        actionManager:pauseTarget(target)
    end
end

--[[--

Resumes the target.

### Parameters:

-   CCNode **target**

]]
function transition.resumeTarget(target)
    if not tolua.isnull(target) then
        actionManager:resumeTarget(target)
    end
end

return transition
