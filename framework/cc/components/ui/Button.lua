
local Component = import("..Component")
local Button = class("Button", Component)

local NORMAL = 0
local PRESSED = 1
local DISABLED = 2

function Button:ctor()
    Button.super.ctor(self, "Button")
end

function Button:onButtonClicked(callback)
    self.onClickedCallback_ = callback
    return self
end

function Button:onButtonPressed(callback)
    self.onPressedCallback_ = callback
    return self
end

function Button:onButtonRelease(callback)
    self.onReleaseCallback_ = callback
    return self
end

function Button:setButtonImage(image, imagePressed, imageDisabled)
    if imagePressed then
        self.imagePressedName_ = imagePressed
        display.newSprite(imagePressed) -- load texture
    end
    if imageDisabled then
        self.imageDisabledName_ = imageDisabled
        display.newSprite(imageDisabled) -- load texture
    end

    self.imageNormalName_ = image
    display.newSprite(image)

    if self.target_:isTouchEnabled() then
        self:setDisplayFrame_(NORMAL)
    else
        self:setDisplayFrame_(DISABLED)
    end
    return self
end

function Button:isButtonEnabled()
    return self.target_:isTouchEnabled()
end

function Button:setButtonEnabled(enabled)
    self.target_:setTouchEnabled(enabled)
    if enabled then
        self:setDisplayFrame_(NORMAL)
    else
        self:setDisplayFrame_(DISABLED)
    end
    return self
end

function Button:exportMethods()
    self:exportMethods_({
        "onButtonClicked",
        "onButtonPressed",
        "onButtonRelease",
        "setButtonImage",
        "isButtonEnabled",
        "setButtonEnabled"
    })
    return self
end

function Button:onTouch_(event, x, y)
    if event == "began" then
        self:setDisplayFrame_(PRESSED)
        self.pressed_ = true
        if self.onPressedCallback_ then self.onPressedCallback_(x, y) end
        return true
    end

    local touchInTarget = self.target_:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
    if event == "moved" then
        if touchInTarget then
            if not self.pressed_ then
                self:setDisplayFrame_(PRESSED)
                self.pressed_ = true
                if self.onPressedCallback_ then self.onPressedCallback_(x, y) end
            end
        else
            if self.pressed_ then
                self:setDisplayFrame_(NORMAL)
                self.pressed_ = false
                if self.onReleaseCallback_ then self.onReleaseCallback_(x, y) end
            end
        end
    elseif event == "ended" then
        self:setDisplayFrame_(NORMAL)
        self.pressed_ = false
        if self.onReleaseCallback_ then self.onReleaseCallback_(x, y) end
        if touchInTarget then
            if self.onClickedCallback_ then self.onClickedCallback_(x, y) end
        end
    else
        self:setDisplayFrame_(NORMAL)
        self.pressed_ = false
        if self.onReleaseCallback_ then self.onReleaseCallback_(x, y) end
    end
end

function Button:setDisplayFrame_(state)
    if state == NORMAL then
        if self.imageNormalName_ then
            self.target_:setDisplayFrame(display.newSprite(self.imageNormalName_):getDisplayFrame())
        end
    elseif state == PRESSED then
        if self.imagePressedName_ then
            self.target_:setDisplayFrame(display.newSprite(self.imagePressedName_):getDisplayFrame())
        else
            self:setDisplayFrame_(NORMAL)
        end
    elseif state == DISABLED then
        if self.imageDisabledName_ then
            self.target_:setDisplayFrame(display.newSprite(self.imageDisabledName_):getDisplayFrame())
        else
            self:setDisplayFrame_(NORMAL)
        end
    end
end

function Button:onBind_()
    self.target_:addTouchEventListener(handler(self, self.onTouch_))
    self.pressed_ = false
end

function Button:onUnbind_()
    self.target_:removeTouchEventListener()
end

return Button
