
local UIImage = class("UIImage", function(filename, isScale9)
    if isScale9 then
        return display.newScale9Sprite(filename)
    else
        return display.newSprite(filename)
    end
end)

function UIImage:ctor(filename, isScale9)
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self.isScale9_ = isScale9
end

function UIImage:setLayoutSize(width, height)
    local bb = self:getBoundingBox()
    local w = bb.size.width
    local h = bb.size.height
    if width == 0 then width = w end
    if height == 0 then height = h end
    self:com("components.ui.LayoutProtocol"):setLayoutSize(width, height)

    if self.isScale9_ then
        self:setContentSize(CCSize(width, height))
    else
        local sx = width / (w / self:getScaleX())
        local sy = height / (h / self:getScaleY())
        self:setScaleX(sx)
        self:setScaleY(sy)
    end

    return self
end

return UIImage
