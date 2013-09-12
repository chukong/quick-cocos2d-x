
local UIImage = class("UIImage", function(filename, isScale9)
    if isScale9 then
        return display.newScale9Sprite(filename)
    else
        return display.newSprite(filename)
    end
end)

function UIImage:ctor(filename, isScale9)
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:align(display.LEFT_BOTTOM)
    local contentSize = self:getContentSize()
    self:com("components.ui.LayoutProtocol"):setLayoutSize(contentSize.width, contentSize.height)
    self.isScale9_ = isScale9
end

function UIImage:setLayoutSize(width, height)
    self:com("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    local size = self:getLayoutSize()

    if self.isScale9_ then
        self:setContentSize(CCSize(size.width, size.height))
    else
        local boundingSize = self:getBoundingBox().size
        local sx = width / (boundingSize.width / self:getScaleX())
        local sy = height / (boundingSize.height / self:getScaleY())
        self:setScaleX(sx)
        self:setScaleY(sy)
    end

    if self.layout_ then
        self:setLayout(self.layout_)
    end

    return self
end

return UIImage
