
local UIButton = class("UIButton", function()
    return display.newSprite()
end)

function UIButton:ctor(image, imagePressed, imageDisabled)
    cc.GameObject.extend(self)
    self:addComponent("Button")
    :exportMethods({
        "onClicked",
        "onPressed",
        "onRelease",
        "setButtonImage",
        "isEnabled",
        "setEnabled",
    })
    self:setButtonImage(image, imagePressed, imageDisabled)
end

return UIButton
