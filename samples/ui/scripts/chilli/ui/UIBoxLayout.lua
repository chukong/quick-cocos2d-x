
local UILayout = import(".UILayout")
local UIBoxLayout = class("UIBoxLayout", UILayout)

function UIBoxLayout:ctor(direction, name)
    UIBoxLayout.super.ctor(self, name)
    self.direction_ = direction or display.LEFT_TO_RIGHT
end

local depth_ = 0

function UIBoxLayout:apply(container)
    if table.nums(self.widgets_) == 0 then return end
    if not container then container = self end

    if DEBUG > 1 then
        local prefix = string.rep("  ", depth_)
        echoInfo("%sAPPLY LAYOUT %s", prefix, self:getName())
    end

    -- step 1
    -- 1. calculate total weight for all widgets
    -- 2. calculate total fixed size
    -- 3. calculate max widget size
    local isHBox = self.direction_ == display.LEFT_TO_RIGHT or self.direction_ == display.RIGHT_TO_LEFT
    local totalWeightH, totalWeightV = 0, 0
    local fixedWidth, fixedHeight = 0, 0
    local maxWidth, maxHeight = 0, 0
    local widgets = {}
    for widget, v in pairs(self.widgets_) do
        local item = {widget = widget, weight = v.weight, order = v.order}
        local widgetSize = widget:getLayoutSize()
        -- if widgetSize.width == 0 and widgetSize.height == 0 then
        --     widgetSize = widget:getLayoutPreferredSize()
        -- end
        printf("name = %s, ww = %0.2f, wh = %0.2f", widget.name_, widgetSize.width, widgetSize.height)
        local widgetSizePolicy = widget:getLayoutSizePolicy()
        if widgetSizePolicy.h == display.FIXED_SIZE then
            fixedWidth = fixedWidth + widgetSize.width
            item.width = widgetSize.width
        else
            totalWeightH = totalWeightH + v.weight
        end

        if widgetSizePolicy.v == display.FIXED_SIZE then
            fixedHeight = fixedHeight + widgetSize.height
            item.height = widgetSize.height
        else
            totalWeightV = totalWeightV + v.weight
        end

        if widgetSize.width > maxWidth then
            maxWidth = widgetSize.width
        end
        if widgetSize.height > maxHeight then
            maxHeight = widgetSize.height
        end

        widgets[#widgets + 1] = item
    end

    -- sort all widgets by order
    table.sort(widgets, function(a, b)
        return a.order < b.order
    end)

    -- step 2
    local containerLayoutSize = container:getLayoutSize()
    local containerPadding = container:getLayoutPadding()
    containerLayoutSize.width = containerLayoutSize.width - containerPadding.left - containerPadding.right
    containerLayoutSize.height = containerLayoutSize.height - containerPadding.top - containerPadding.bottom

    if isHBox then
        maxHeight = containerLayoutSize.height
    else
        maxWidth = containerLayoutSize.width
    end

    local x, y, negativeX, negativeY
    local left = containerPadding.left
    local top = containerLayoutSize.height + containerPadding.bottom
    local right = containerLayoutSize.width + containerPadding.left
    local bottom = containerPadding.bottom
    if self.direction_ == display.LEFT_TO_RIGHT then
        x = left
        y = bottom
        negativeX, negativeY = 1, 0
    elseif self.direction_ == display.RIGHT_TO_LEFT then
        x = right
        y = bottom
        negativeX, negativeY = -1, 0
    elseif self.direction_ == display.TOP_TO_BOTTOM then
        x = left
        y = top
        negativeX, negativeY = 0, -1
    elseif self.direction_ == display.BOTTOM_TO_TOP then
        x = left
        y = bottom
        negativeX, negativeY = 0, 1
    else
        echoError("UIBoxLayout:apply() - invalid direction %s", tostring(self.direction_))
        return
    end

    if iskindof(container, "UILayout") then
        local cx, cy = container:getPosition()
        x = x + cx
        y = y + cy
    end

    -- step 3
    local containerWidth = containerLayoutSize.width - fixedWidth
    local remainingWidth = containerWidth
    local containerHeight = containerLayoutSize.height - fixedHeight
    local remainingHeight = containerHeight
    local count = #widgets
    local lastWidth, lastHeight = 0, 0
    local actualSize = {}
    for index, item in ipairs(widgets) do
        local width, height

        if isHBox then
            if item.width then
                width = item.width
            else
                if index ~= count then
                    width = item.weight / totalWeightH * containerWidth
                else
                    width = remainingWidth
                end
                remainingWidth = remainingWidth - width
            end
            if index == count then lastWidth = width end
            height = item.height or maxHeight
        else
            if item.height then
                height = item.height
            else
                if index ~= count then
                    height = item.weight / totalWeightV * containerHeight
                else
                    height = remainingHeight
                end
                remainingHeight = remainingHeight - height
            end
            if index == count then lastHeight = height end
            width = item.width or maxWidth
        end

        local widget = item.widget
        local margin = widget:getLayoutMargin()
        local actualWidth = width - margin.left - margin.right
        local actualHeight = height - margin.top - margin.bottom
        local wx = x + margin.left
        if self.direction_ == display.RIGHT_TO_LEFT then
            wx = x - margin.right
        end
        local wy = y + margin.bottom
        if self.direction_ == display.TOP_TO_BOTTOM then
            wy = y - margin.top
        end
        widget:setPosition(wx, wy)
        depth_ = depth_ + 1
        widget:setLayoutSize(actualWidth, actualHeight)
        depth_ = depth_ - 1
        actualSize[#actualSize + 1] = {width = actualWidth, height = actualHeight}

        if isHBox then
            x = x + width * negativeX
        else
            y = y + height * negativeY
        end
    end

    if self.direction_ == display.TOP_TO_BOTTOM then
        for index, item in ipairs(widgets) do
            local widget = item.widget
            widget:setPositionY(widget:getPositionY() - actualSize[index].height)
        end
    elseif self.direction_ == display.RIGHT_TO_LEFT then
        for index, item in ipairs(widgets) do
            local widget = item.widget
            widget:setPositionX(widget:getPositionX() - actualSize[index].width)
        end
    end

    depth_ = depth_ + 1
    for index, item in ipairs(widgets) do
        local widget = item.widget
        if iskindof(widget, "UILayout") then
            widget:apply()
        end
    end
    depth_ = depth_ - 1
end

return UIBoxLayout
