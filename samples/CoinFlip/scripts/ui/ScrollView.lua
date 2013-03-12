
local ScrollView = class("ScrollView", function(rect)
    return display.newClippingRegionNode(rect)
end)

ScrollView.DIRECTION_VERTICAL   = 1
ScrollView.DIRECTION_HORIZONTAL = 2

function ScrollView:ctor(rect, direction)
    -- rect passed to newClippingNode()
    assert(direction == ScrollView.DIRECTION_VERTICAL or direction == ScrollView.DIRECTION_HORIZONTAL,
           "ScrollView:ctor() - invalid direction")
    self.direction = direction
    self.scrollEnabled = true
    self.offsetX = 0
    self.offsetY = 0
    self.view = display.newNode()
    self:addChild(self.view)
end

function ScrollView:getView()
    return self.view
end

function ScrollView:setContentOffset(offset, animated, speed)
    local ox, oy = self.offsetX, self.offsetY
    local x, y = ox, oy
    if self.direction == ScrollView.DIRECTION_VERTICAL then
        self.offsetY = offset
        y = offset
    else
        self.offsetX = offset
        x = offset
    end

    if animated then
        -- calc transition time
        -- speed = scroll offset / per seconds
        local time
        if self.direction == ScrollView.DIRECTION_VERTICAL then
            speed = speed or display.height / 2
            time = math.abs(y - oy) / speed
        else
            speed = speed or display.width / 2
            time = math.abs(x - ox) / speed
        end
        print(time)
        transition.moveTo(self.view, {x = x, y = y, time = time})
    else
        self.view:setPosition(x, y)
    end
end

return ScrollView
