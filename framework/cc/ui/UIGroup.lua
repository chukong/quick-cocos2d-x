
local UIBoxLayout = import(".UIBoxLayout")
local UIImage = import(".UIImage")

local UIGroup = class("UIGroup", function()
    return display.newNode()
end)

function UIGroup:ctor()
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayout(UIBoxLayout.new(display.LEFT_TO_RIGHT))
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    self:align(display.LEFT_BOTTOM)
    self:setLayoutAlignment(display.LEFT_BOTTOM)
end

function UIGroup:onTouch(listener)
    if not listener then listener = function() return true end end
    self:addTouchEventListener(listener)
    return self
end

function UIGroup:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

function UIGroup:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    if self.backgroundSprite_ then
        self.backgroundSprite_:setLayoutSize(self:getLayoutSize())
    end
    return self
end

function UIGroup:setBackgroundImage(filename, args)
    self.backgroundSprite_ = UIImage.new(filename, args):setLayoutSize(self:getLayoutSize())
    self:addChild(self.backgroundSprite_)
    return self
end

return UIGroup
