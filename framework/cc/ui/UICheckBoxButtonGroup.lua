
local UIBoxLayout = import(".UIBoxLayout")

local UIGroup = import(".UIGroup")
local UICheckBoxButtonGroup = class("UICheckBoxButtonGroup", UIGroup)

function UICheckBoxButtonGroup:ctor(direction)
    UICheckBoxButtonGroup.super.ctor(self)
    self:setLayout(UIBoxLayout.new(direction or display.LEFT_TO_RIGHT))
    self.buttons_ = {}
end

function UICheckBoxButtonGroup:addButton(button)
    self:addChild(button)
    self.buttons_[#self.buttons_ + 1] = button
    self:getLayout():addWidget(button):apply(self)
    button:onButtonClicked(handler(self, self.onButtonStateClicked_))
    return self
end

function UICheckBoxButtonGroup:removeButtonAtIndex(index)
    assert(self.buttons_[index] ~= nil, "UICheckBoxButtonGroup:removeButtonAtIndex() - invalid index")

    local button = self.buttons_[index]
    local layout = self:getLayout()
    layout:removeWidget(button)
    layout:apply(self)

    button:removeSelf()
    table.remove(self.buttons_, index)

    return self
end

function UICheckBoxButtonGroup:getButtonAtIndex(index)
    return self.buttons_[index]
end

function UICheckBoxButtonGroup:getButtonsCount()
    return #self.buttons_
end

function UICheckBoxButtonGroup:setButtonsLayoutMargin(top, right, bottom, left)
    for _, button in ipairs(self.buttons_) do
        button:setLayoutMargin(top, right, bottom, left)
    end
    self:getLayout():apply(self)
    return self
end

function UICheckBoxButtonGroup:onButtonStateClicked_(event)
    local clickedButton = event.target
    for index, button in ipairs(self.buttons_) do
        button:setButtonSelected(button == clickedButton)
    end
end

return UICheckBoxButtonGroup
