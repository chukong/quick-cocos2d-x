
local ScrollViewCell = class("ScrollViewCell", function(contentSize)
    local node = display.newNode()
    if contentSize then
        node:setContentSize(contentSize)
    end
    return node;
end)

function ScrollViewCell:onTouch(event, x, y)
end

function ScrollViewCell:onTap(x, y)
end

return ScrollViewCell
