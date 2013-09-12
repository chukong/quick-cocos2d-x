
local PathRunner = require("app.map.PathRunner")
local BehaviorBase = require("app.map.behaviors.BehaviorBase")

local PathIndicatorBehavior = class("PathIndicatorBehavior", BehaviorBase)

PathIndicatorBehavior.PATH_RUNNER_SPEED      = 5.0
PathIndicatorBehavior.CREATE_RUNNER_INTERVAL = 2
PathIndicatorBehavior.CREATE_RUNNER_DELAY    = 3
PathIndicatorBehavior.MAX_PATH_RUNNERS       = 10

function PathIndicatorBehavior:ctor()
    PathIndicatorBehavior.super.ctor(self, "PathIndicatorBehavior", nil, 0)
end

function PathIndicatorBehavior:bind(object)
    object.runners_        = {}
    object.runnerInterval_ = math.random(0, PathIndicatorBehavior.CREATE_RUNNER_INTERVAL * 100) / 100

    local function tick(object, dt)
        if not object.play_ then return end

        if #object.runners_ < PathIndicatorBehavior.MAX_PATH_RUNNERS then
            object.runnerInterval_ = object.runnerInterval_ - dt
            if object.runnerInterval_ < 0 then
                object.runnerInterval_ = PathIndicatorBehavior.CREATE_RUNNER_INTERVAL
                local runner = PathRunner.new(PathIndicatorBehavior.PATH_RUNNER_SPEED)
                object.runners_[#object.runners_ + 1] = runner
                runner:createView(object.batch_, "#MoveLine.png")
                runner:setRotationOffsetSteps(0)
            end
        else
            object.runnerInterval_ = PathIndicatorBehavior.CREATE_RUNNER_DELAY
        end

        local count = #object.points_
        local function getPoint(index)
            return object:getPoint(index)
        end
        for i = #object.runners_, 1, -1 do
            local runner = object.runners_[i]
            if not runner:tick(dt, count, getPoint) then
                runner:removeView()
                table.remove(object.runners_, i)
            end
        end
    end
    object:bindMethod(self, "tick", tick)

    local function removeAllRunners(object)
        for i, runner in ipairs(object.runners_) do
            runner:removeView()
        end
        object.runners_ = {}
    end
    object:bindMethod(self, "removeAllRunners", removeAllRunners)

    local function removeView(object)
        object:removeAllRunners()
    end
    object:bindMethod(self, "removeView", removeView, true)

    local function stopPlay(object)
        object:removeAllRunners()
    end
    object:bindMethod(self, "stopPlay", stopPlay)
end

function PathIndicatorBehavior:unbind(object)
    object.runners_        = nil
    object.runnerInterval_ = nil

    object:unbindMethod(self, "tick")
    object:unbindMethod(self, "removeAllRunners")
    object:unbindMethod(self, "removeView")
    object:unbindMethod(self, "stopPlay")
end

return PathIndicatorBehavior
