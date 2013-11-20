
local ScrollViewCell = class("ScrollViewCell", function(contentSize)
    local node = display.newNode()
    if contentSize then node:setContentSize(contentSize) end
    node:setNodeEventEnabled(true)
    require("framework.api.EventProtocol").extend(node)
    return node
end)

function ScrollViewCell:onTouch(event, x, y)
end

function ScrollViewCell:onTap(x, y)
end

function ScrollViewCell:onExit()
    self:removeAllEventListeners()
end

return ScrollViewCell
