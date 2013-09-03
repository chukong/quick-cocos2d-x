
local MapConstants            = require("app.map.MapConstants")
local StaticObjectsProperties = require("app.properties.StaticObjectsProperties")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local UpgradableBehavior = class("UpgradableBehavior", BehaviorBase)

function UpgradableBehavior:ctor()
    UpgradableBehavior.super.ctor(self, "UpgradableBehavior", {"CampBehavior"}, 100)
end

function UpgradableBehavior:bind(object)
    object.maxLevel_  = toint(object.state_.maxLevel)
    if object.maxLevel_ < 1 then object.maxLevel_ = 1 end

    object.level_ = toint(object.state_.level)
    if object.level_ < 1 then object.level_ = 1 end

    local function getMaxLevel(object)
        return object.maxLevel_
    end
    object:bindMethod(self, "getMaxLevel", getMaxLevel)

    local function getLevel(object)
        return object.level_
    end
    object:bindMethod(self, "getLevel", getLevel)

    local function setLevel(object, level)
        level = toint(level)
        assert(level >= 1 and level <= object.maxLevel_,
               format("UpgradableBehavior.setLevel() - invalid level %s", tostring(level)))
        object.level_ = level

        local define = StaticObjectsProperties.get(object.defineId_, object.level_)
        for k, v in pairs(define) do
            local kn = k .. "_"
            object[kn] = v
            object.state_[k] = v
        end
    end
    object:bindMethod(self, "setLevel", setLevel)

    local function vardump(object, state)
        state.level = object.level_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function UpgradableBehavior:unbind(object)
    object.maxLevel_ = nil
    object.level_    = nil

    object:unbindMethod(self, "getMaxLevel")
    object:unbindMethod(self, "getLevel")
    object:unbindMethod(self, "setLevel")
    object:unbindMethod(self, "vardump")
end

return UpgradableBehavior
