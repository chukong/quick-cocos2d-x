
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local world = PhysicsWorld:create(0, -200)
    self:addChild(world)

    local ship01 = display.newSprite("Ship01.png")
    self:addChild(ship01)

    local scaleFactor = 1.0
    local shapes = require("data.shapes").physicsData(scaleFactor)
    local shape = shapes:get("Ship01")
    local body = world:addPolygonShape(shape.fixtures[1].mass, shape.fixtures[1].polygons)
    world:bindNodeToBody(ship01, body)

     -- dump(shapes.get(shapes, "shop01"))


    --
end

function MainScene:onEnter()
    if device.platform ~= "android" then return end

    -- avoid unmeant back
    self:performWithDelay(function()
        -- keypad layer, for android
        local layer = display.newLayer()
        layer:addKeypadEventListener(function(event)
            if event == "back" then game.exit() end
        end)
        self:addChild(layer)

        layer:setKeypadEnabled(true)
    end, 0.5)
end

return MainScene
