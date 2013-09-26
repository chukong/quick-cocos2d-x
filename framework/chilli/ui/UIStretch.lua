
local UIStretch = class("UIStretch")

function UIStretch:ctor()
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    self:setLayoutAlignment(display.LEFT_BOTTOM)
    self.position_ = {x = 0, y = 0}
end

function UIStretch:getPosition()
    return self.position_.x, self.position_.y
end

function UIStretch:getPositionX()
    return self.position_.x
end

function UIStretch:getPositionY()
    return self.position_.y
end

function UIStretch:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

function UIStretch:setPositionX(x)
    self.position_.x = x
end

function UIStretch:setPositionY(y)
    self.position_.y = y
end

return UIStretch
