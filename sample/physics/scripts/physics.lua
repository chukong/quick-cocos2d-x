
local physics = {}

function physics.newWorld(gravityX, gravityY)
    local world = PhysicsWorld:create()
    if gravityX and gravityY then
        world:setGravity(gravityX, gravityY)
    end
    return world
end

return physics
