
local UIBoxLayout = import(".UIBoxLayout")

local UIGroup = import(".UIGroup")
local UICheckBoxButtonGroup = class("UICheckBoxButtonGroup", UIGroup)

function UICheckBoxButtonGroup:ctor(direction)
    UICheckBoxButtonGroup.super.ctor(self)
    self:setLayout(UIBoxLayout.new(direction or display.LEFT_TO_RIGHT))
    self.buttons_ = {}
    self.handles_ = {}
end

function UICheckBoxButtonGroup:addButton(button)
    self:addChild(button)
    self.buttons_[#self.buttons_ + 1] = button
    self.handles_[#self.handles_ + 1] = button:addButtonStateChangedEventListener(handler(self, self.onButtonStateChanged_))
    self:getLayout():addWidget(button):apply(self)
    return self
end

-- function UICheckBoxButtonGroup:removeButtonAtIndex(index)
--     table.remove(self.buttons_, index)
--     self:getLayout():apply(self)
--     return self
-- end

function UICheckBoxButtonGroup:getButtonsCount()
    return #self.buttons_
end

function UICheckBoxButtonGroup:onButtonStateChanged_(event)
    dump(event)
end

return UICheckBoxButtonGroup
