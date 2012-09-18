
local AutoLayout = {}

function AutoLayout.alignItemsHorizontally(items, x, y, padding, separatorPadding)
    if type(separatorPadding) ~= "number" then
        separatorPadding = math.floor(padding / 4) * 2
    end
    local first, last, step = 1, #items, 1
    if padding < 0 then
        first, last, step = last, first, - 1
    end

    for index = first, last, step do
        local item = items[index]
        if type(item) ~= "string" then
            item:setPosition(x, y)
            x = x + padding
        else
            x = x + separatorPadding
        end
    end
end

return AutoLayout
