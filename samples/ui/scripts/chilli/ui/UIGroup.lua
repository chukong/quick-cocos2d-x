
local UIBoxLayout = import(".UIBoxLayout")
local UIImage = import(".UIImage")

local UIGroup = class("UIGroup", function()
    return display.newNode()
end)

function UIGroup:ctor()
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayout(UIBoxLayout.new())
    self:align(display.LEFT_BOTTOM)
end

function UIGroup:setLayoutSize(width, height)
    self:com("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    if self.backgroundSprite_ then
        self.backgroundSprite_:setLayoutSize(self:getLayoutSize())
    end
    return self
end

function UIGroup:setBackgroundImage(filename, isScale9)
    self.backgroundSprite_ = UIImage.new(filename, isScale9):setLayoutSize(self:getLayoutSize())
    self:addChild(self.backgroundSprite_)
    return self
end

-- function UIGroup:setLayoutSize(width, height)
--     self:com("components.ui.LayoutProtocol"):setLayoutSize(width, height)

--     if self.isScale9_ then
--         self:setContentSize(CCSize(width, height))
--     else
--         local sx = width / (w / self:getScaleX())
--         local sy = height / (h / self:getScaleY())
--         self:setScaleX(sx)
--         self:setScaleY(sy)
--     end

--     return self
-- end

return UIGroup
