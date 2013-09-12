
local MapConstants  = require("app.map.MapConstants")
local BulletType    = require("app.map.BulletType")
local BulletFactory = require("app.map.BulletFactory")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local FireBehavior = class("FireBehavior", BehaviorBase)

function FireBehavior:ctor()
    FireBehavior.super.ctor(self, "FireBehavior", nil, 1)
end

function FireBehavior:bind(object)
    object.fireLock_ = 0

    local function getFireRange(object)
        return object.fireRange_
    end
    object:bindMethod(self, "getFireRange", getFireRange)

    local function getCooldown(object)
        return object.cooldown_
    end
    object:bindMethod(self, "getCooldown", getFireRange)

    local function addFireLock(object)
        object.fireLock_ = object.fireLock_ + 1
    end
    object:bindMethod(self, "addFireLock", addFireLock)

    local function removeFireLock(object)
        object.fireLock_ = object.fireLock_ - 1
        assert(object.collisionLock_ >= 0,
               "FireBehavior.removeFireLock() - object.fireLock_ must >= 0")
    end
    object:bindMethod(self, "removeFireLock", removeFireLock)

    local function getFireEnabled(object)
        return object.fireEnabled_
    end
    object:bindMethod(self, "getFireEnabled", getFireEnabled)

    local function setFireEnabled(object, enabled)
        object.fireEnabled_ = enabled
    end
    object:bindMethod(self, "setFireEnabled", setFireEnabled)

    local function fire(object, target)
        if not object.fireEnabled_ then
            echoError("FireBehavior.fire() - fire disabled")
            return
        end

        if object.fireCooldown_ > 0 then
            echoError("FireBehavior.fire() - cooldown must equal zero")
            return
        end

        if object:hasBehavior("DecorateBehavior") then
            local decorationName = object:getDefineId() .. "Fire"
            if object:isDecorationExists(decorationName) then
                local decoration = object:getDecoration(decorationName)
                local autoHide = decoration.visible_ == false
                if autoHide then decoration:setVisible(true) end
                decoration:playAnimationOnce(function()
                    if autoHide then decoration:setVisible(false) end
                    decoration:setDisplayFrameIndex(1)
                end)
            end

            local decorationName = object:getDefineId() .. "Fire2"
            if object:isDecorationExists(decorationName) then
                local decoration = object:getDecoration(decorationName)
                local autoHide = decoration.visible_ == false
                if autoHide then decoration:setVisible(true) end
                decoration:playAnimationOnce(function()
                    if autoHide then decoration:setVisible(false) end
                    decoration:setDisplayFrameIndex(1)
                end)
            end
        end

        object.fireCooldown_ = object.cooldown_ * math.random(80, 120) / 100
        local delay = nil
        if object:hasBehavior("NPCBehavior") or object:hasBehavior("PlayerBehavior") then
            delay = 0
        end

        return BulletFactory.newBullets(object.bulletType_, object, target, delay)
    end
    object:bindMethod(self, "fire", fire)

    local function tick(object, dt)
        local fireCooldown = object.fireCooldown_
        if fireCooldown > 0 then
            fireCooldown = fireCooldown - dt
            if fireCooldown <= 0 then fireCooldown = 0 end
            object.fireCooldown_ = fireCooldown
        end
    end
    object:bindMethod(self, "tick", tick)

    local function runtimeStateDump(object, state)
        state.fireEnabled_ = object.fireEnabled_
        state.fireCooldown_ = object.fireCooldown_
        return state
    end
    object:bindMethod(self, "runtimeStateDump", runtimeStateDump)

    self:reset(object)
end

function FireBehavior:unbind(object)
    object.fireOffsetX_   = nil
    object.fireOffsetY_   = nil
    object.fireRange_     = nil
    object.cooldown_      = nil
    object.fireCooldown_  = nil
    object.fireEnabled_   = nil

    object.minDamage_     = nil
    object.maxDamage_     = nil
    object.hitrate_       = nil
    object.critical_      = nil
    object.criticalPower_ = nil

    object:unbindMethod(self, "getFireRange")
    object:unbindMethod(self, "getCooldown")
    object:unbindMethod(self, "addFireLock")
    object:unbindMethod(self, "removeFireLock")
    object:unbindMethod(self, "getFireEnabled")
    object:unbindMethod(self, "setFireEnabled")
    object:unbindMethod(self, "fire")
    object:unbindMethod(self, "tick")
    object:unbindMethod(self, "runtimeStateDump")
end

function FireBehavior:reset(object)
    object.fireOffsetX_   = toint(object.state_.fireOffsetX)
    object.fireOffsetY_   = toint(object.state_.fireOffsetY)
    if object.staticIndex_ then
        local index = object.staticIndex_
        if type(object.state_.fireOffsetX) == "table" then
            object.fireOffsetX_ = object.state_.fireOffsetX[index]
        end
        if type(object.state_.fireOffsetY) == "table" then
            object.fireOffsetY_ = object.state_.fireOffsetY[index]
        end
    end
    object.fireRange_     = toint(object.state_.fireRange)
    object.cooldown_      = tonumber(object.state_.cooldown)
    object.fireCooldown_  = 0
    object.fireEnabled_   = object.state_.fireEnabled

    object.minDamage_     = toint(object.state_.minDamage)
    object.maxDamage_     = toint(object.state_.maxDamage)
    object.hitrate_       = toint(object.state_.hitrate)
    object.critical_      = toint(object.state_.critical)
    object.criticalPower_ = tonumber(object.state_.criticalPower)

    if type(object.fireEnabled_) ~= "boolean" then
        object.fireEnabled_ = true
    end
end

return FireBehavior
