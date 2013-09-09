
local UILayout = import(".UILayout")
local UIHBoxLayout = class("UIHBoxLayout", UILayout)

function UIHBoxLayout:apply(container)
    local widgets = {}
    local totalWeight = 0
    local maxHeight = 0
    local fixedWidth = 0
    for widget, v in pairs(self.widgets_) do
        local item = {
            widget = widget,
            weight = v.weight,
            order = v.order
        }

        local widgetSize = widget:getLayoutSize()
        local sizePolicy = widget:getLayoutSizePolicy()
        if sizePolicy.h == cc.ui.FIXED_SIZE_POLICY then
            fixedWidth = fixedWidth + widgetSize.width
            item.width = widgetSize.width
        else
            totalWeight = totalWeight + v.weight
        end
        if sizePolicy.v == cc.ui.FIXED_SIZE_POLICY then
            item.height = widgetSize.height
        end

        if widgetSize.height > maxHeight then maxHeight = widgetSize.height end
        widgets[#widgets + 1] = item
    end

    table.sort(widgets, function(a, b)
        return a.order < b.order
    end)

    local size = container:getLayoutSize()
    local anchorPoint = container:getAnchorPoint()
    local x = -size.width * anchorPoint.x
    local y = -size.height * anchorPoint.y

    if maxHeight > size.height or maxHeight < size.height then
        maxHeight = size.height
    end
    local containerWidth = size.width - fixedWidth
    local remainingWidth = containerWidth
    local count = #widgets
    for index, item in ipairs(widgets) do
        local width

        if item.width then
            width = item.width
        else
            if index ~= count then
            width = item.weight / totalWeight * containerWidth
            width = math.ceil(width / 2) * 2
            else
                width = remainingWidth
            end
            remainingWidth = remainingWidth - width
        end

        local widget = item.widget
        local widgetSize = widget:getLayoutSize()
        local height = maxHeight
        if item.height then height = item.height end

        local padding = widget:getLayoutPadding()
        local margin = widget:getLayoutMargin()
        local actualWidth = width - margin.left - margin.right
        local actualHeight = height - margin.top - margin.bottom

        local widgetAnchorPoint = widget:getAnchorPoint()
        local wx = x + actualWidth * widgetAnchorPoint.x + margin.left
        local wy = y + actualHeight * widgetAnchorPoint.y + (maxHeight - actualHeight) * anchorPoint.y + margin.bottom
        widget:setPosition(wx, wy)
        widget:setLayoutSize(actualWidth, actualHeight)
        x = x + width
    end
end

return UIHBoxLayout
