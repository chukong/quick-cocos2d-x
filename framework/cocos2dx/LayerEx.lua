
local c = cc
local Layer = c.Layer

function Layer:addKeypadEventListener(listener)
    PRINT_DEPRECATED("Layer:addKeypadEventListener() is deprecated, please use Layer:addNodeEventListener()")
    self:addNodeEventListener(c.KEYPAD_EVENT, function(event)
        listener(event.key)
    end)
end

function Layer:addAccelerateEventListener(listener)
    PRINT_DEPRECATED("Layer:addAccelerateEventListener() is deprecated, please use Layer:addNodeEventListener()")
    self:addNodeEventListener(c.ACCELERATE_EVENT, function(event)
        listener(event.x, event.y, event.z, event.timestamp)
    end)
end
