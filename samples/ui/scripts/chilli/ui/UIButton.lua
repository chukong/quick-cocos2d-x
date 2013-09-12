
local UIButton = class("UIButton", function()
    return display.newSprite()
end)

function UIButton:ctor(image, imagePressed, imageDisabled)
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:addComponent("components.ui.Button"):exportMethods()
    self:setButtonImage(image, imagePressed, imageDisabled)
end

return UIButton
