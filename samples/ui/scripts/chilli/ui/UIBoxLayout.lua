
local UILayout = import(".UILayout")
local UIBoxLayout = class("UIBoxLayout", UILayout)

function UIBoxLayout:ctor(direction)
    UIBoxLayout.super.ctor(self)
    self.direction_ = direction or display.LEFT_TO_RIGHT
end

function UIBoxLayout:apply(container)
    if table.nums(self.widgets_) == 0 then return end

    -- step 1
    -- 1. calculate total weight for all widgets
    -- 2. calculate total fixed size
    -- 3. calculate max widget size
    local totalWeightH, totalWeightV = 0, 0
    local fixedWidth, fixedHeight = 0, 0
    local maxWidth, maxHeight = 0, 0
    local widgets = {}
    for widget, v in pairs(self.widgets_) do
        local item = {widget = widget, weight = v.weight, order = v.order}
        local widgetSize = widget:getLayoutSize()
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
    local isHBox = self.direction_ == display.LEFT_TO_RIGHT or self.direction_ == display.RIGHT_TO_LEFT
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
        widget:setLayoutSize(actualWidth, actualHeight)
        actualSize[#actualSize + 1] = {width = actualWidth, height = actualHeight}

        -- printf("x = %0.2f, y = %0.2f, width = %0.2f, height =  %0.2f, weight = %d, total weight = %d", wx, wy, actualWidth, actualHeight, item.weight, totalWeightH)

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

    for index, item in ipairs(widgets) do
        local widget = item.widget
        if iskindof(widget, "UILayout") then
            widget:apply(widget)
        end
    end
end

return UIBoxLayout
