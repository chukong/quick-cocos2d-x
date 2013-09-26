
local MapConstants     = require("app.map.MapConstants")
local PlayerProperties = require("app.properties.PlayerProperties")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local PlayerBehavior = class("PlayerBehavior", BehaviorBase)

function PlayerBehavior:ctor()
    local depends = {
        "DestroyedBehavior",
        "FireBehavior",
        "MovableBehavior",
        "DecorateBehavior",
    }
    PlayerBehavior.super.ctor(self, "PlayerBehavior", depends, 200)
end

function PlayerBehavior:bind(object)
    object.playerTestId_ = object.state_.playerTestId
    if type(object.playerTestId_) ~= "string" then
        object.playerTestId_ = ""
    end

    local function getPlayerTestId(object)
        return object.playerTestId_
    end
    object:bindMethod(self, "getPlayerTestId", getPlayerTestId)

    local function setPlayerTestId(object, playerTestId)
        object.playerTestId_ = playerTestId

        local define = PlayerProperties.get(object.playerTestId_)
        if not define then return end

        for k, v in pairs(define) do
            local kn = k .. "_"
            object[kn] = v
            object.state_[k] = v
        end
    end
    object:bindMethod(self, "setPlayerTestId", setPlayerTestId)

    local function setPlayerProperties(object, properties)
        for k, v in pairs(properties) do
            local kn = k .. "_"
            object[kn] = v
            object.state_[k] = v
        end
    end
    object:bindMethod(self, "setPlayerProperties", setPlayerProperties)

    local function setPlayerSprite(object, spriteFrameName)
        object.sprite_:setDisplayFrame(display.newSpriteFrame(spriteFrameName))
    end
    object:bindMethod(self, "setPlayerSprite", setPlayerSprite)

    local function getMaxMagic(object)
        return object.maxMagic_
    end
    object:bindMethod(self, "getMaxMagic", getMaxMagic)

    local function setMaxMagic(object, maxMagic)
        maxMagic = toint(maxMagic)
        assert(maxMagic > 0, format("PlayerBehavior.setMaxMagic() - invalid maxMagic %s", tostring(maxMagic)))
        object.maxMagic_ = maxMagic
    end
    object:bindMethod(self, "setMaxMagic", setMaxMagic)

    local function getMagic(object)
        return object.magic_
    end
    object:bindMethod(self, "getMagic", getMagic)

    local function setMagic(object, magic)
        magic = tonumber(magic)
        assert(magic >= 0 and magic <= object.maxMagic_,
               format("PlayerBehavior.setMagic() - invalid magic %s", tostring(magic)))
        object.magic_ = magic
    end
    object:bindMethod(self, "setMagic", setMagic)

    local function decreaseMagic(object, amount)
        amount = tonumber(amount)
        assert(amount >= 0, format("PlayerBehavior.decreaseMagic() - invalid amount %s", tostring(amount)))
        object.magic_ = object.magic_ - amount
        if object.magic_ <= 0 then
            object.magic_ = 0
        end
    end
    object:bindMethod(self, "decreaseMagic", decreaseMagic)

    local function increaseMagic(object, amount)
        amount = tonumber(amount)
        assert(amount >= 0, format("PlayerBehavior.increaseMagic() - invalid amount %s", tostring(amount)))
        object.magic_ = object.magic_ + amount
        if object.magic_ >= object.maxMagic_ then
            object.magic_ = object.maxMagic_
        end
    end
    object:bindMethod(self, "increaseMagic", increaseMagic)

    local function showDestroyedStatus(object, skipAnim)
        if skipAnim then
            object:getView():setVisible(false)
            object:getDecoration("ShipWavesUp"):setVisible(false)
            object:getDecoration("ShipWaves"):setVisible(false)
        else
            transition.fadeOut(object:getView(), {time = 1.0})
            transition.fadeOut(object:getDecoration("ShipWavesUp"):getView(), {time = 0.5})
            transition.fadeOut(object:getDecoration("ShipWaves"):getView(), {time = 0.5})
        end
    end
    object:bindMethod(self, "showDestroyedStatus", showDestroyedStatus)

    local function vardump(object, state)
        state.playerTestId = object.playerTestId_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function PlayerBehavior:unbind(object)
    object.player_ = false

    object:unbindMethod(self, "getPlayerTestId")
    object:unbindMethod(self, "setPlayerTestId")
    object:unbindMethod(self, "setPlayerProperties")
    object:unbindMethod(self, "setPlayerSprite")
    object:unbindMethod(self, "getMaxMagic")
    object:unbindMethod(self, "setMaxMagic")
    object:unbindMethod(self, "getMagic")
    object:unbindMethod(self, "setMagic")
    object:unbindMethod(self, "decreaseMagic")
    object:unbindMethod(self, "increaseMagic")
    object:unbindMethod(self, "showDestroyedStatus")
    object:unbindMethod(self, "vardump")
end

function PlayerBehavior:reset(object)
    object.campId_ = MapConstants.PLAYER_CAMP
    object.player_ = true
    object:setPlayerTestId(object:getPlayerTestId())

    object.maxMagic_ = toint(object.state_.maxMagic)
    if object.maxMagic_ < 0 then object.maxMagic_ = 0 end
    object.magic_ = object.maxMagic_
end

return PlayerBehavior
