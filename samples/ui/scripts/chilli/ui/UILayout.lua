
local UILayout = class("UILayout")

function UILayout:ctor()
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutAlignment(display.LEFT_BOTTOM)
    self.position_ = {x = 0, y = 0}
    self.order_ = 0
    self.layouts_ = {}
    self.widgets_ = {}
    local m = {__mode = "k"}
    setmetatable(self.widgets_, m)
end

function UILayout:addLayout(layout, weight)
    self:addWidget(layout, weight)
    self.layouts_[layout] = true
    return self
end

function UILayout:removeLayout(layout)
    self:removeWidget(layout)
    self.layouts_[layout] = nil
    return self
end

function UILayout:addWidget(widget, weight)
    self.order_ = self.order_ + 1
    self.widgets_[widget] = {weight = weight or 1, order = self.order_}
    return self
end

function UILayout:removeWidget(widget)
    self.widgets_[widget] = nil
    return self
end

function UILayout:getPosition()
    return self.position_.x, self.position_.y
end

function UILayout:getPositionX()
    return self.position_.x
end

function UILayout:getPositionY()
    return self.position_.y
end

function UILayout:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

function UILayout:setPositionX(x)
    self.position_.x = x
end

function UILayout:setPositionY(y)
    self.position_.y = y
end

function UILayout:apply(container)
end

return UILayout
