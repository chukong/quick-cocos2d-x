
local UIButton = class("UIButton", function()
    return display.newSprite()
end)

function UIButton:ctor(image, imagePressed, imageDisabled)
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:addComponent("components.ui.Button"):exportMethods()
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)
    self:setLayoutAlignment(display.CENTER)
    self:setButtonImage(image, imagePressed, imageDisabled)
end

return UIButton
