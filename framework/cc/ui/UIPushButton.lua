
local UIButton = import(".UIButton")
local UIPushButton = class("UIPushButton", UIButton)

UIPushButton.NORMAL   = "NORMAL"
UIPushButton.PRESSED  = "PRESSED"
UIPushButton.DISABLED = "DISABLED"

function UIPushButton:ctor(images)
    UIPushButton.super.ctor(self, {
        {name = "disable", from = {"NORMAL", "PRESSED"}, to = "DISABLED"},
        {name = "enable",  from = {"DISABLED"}, to = "NORMAL"},
        {name = "press",   from = "NORMAL",  to = "PRESSED"},
        {name = "release", from = "PRESSED", to = "NORMAL"},
    }, "NORMAL")
    self:setButtonImage(UIPushButton.NORMAL, images["normal"], true)
    self:setButtonImage(UIPushButton.PRESSED, images["pressed"], true)
    self:setButtonImage(UIPushButton.DISABLED, images["disabled"], true)
end

function UIPushButton:setButtonImage(state, image, ignoreEmpty)
    assert(state == UIPushButton.NORMAL
        or state == UIPushButton.PRESSED
        or state == UIPushButton.DISABLED,
        string.format("UIPushButton:setButtonImage() - invalid state %s", tostring(state)))
    UIPushButton.super.setButtonImage(self, state, image, ignoreEmpty)

    if state == UIPushButton.NORMAL then
        if not self.images_[UIPushButton.PRESSED] then
            self.images_[UIPushButton.PRESSED] = image
        end
        if not self.images_[UIPushButton.DISABLED] then
            self.images_[UIPushButton.DISABLED] = image
        end
    end

    return self
end

function UIPushButton:onButtonClicked(callback)
    self.onClickedCallback_ = callback
    return self
end

function UIPushButton:onButtonPressed(callback)
    self.onPressedCallback_ = callback
    return self
end

function UIPushButton:onButtonRelease(callback)
    self.onReleaseCallback_ = callback
    return self
end

function UIPushButton:onTouch_(event, x, y)
    if event == "began" then
        self.fsm_:doEvent("press")
        self:callHandler_("onPressedCallback_", x, y, true)
        return true
    end

    local touchInTarget = self:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
    if event == "moved" then
        if touchInTarget then
            if self.fsm_:canDoEvent("press") then
                self.fsm_:doEvent("press")
                self:callHandler_("onPressedCallback_", x, y, touchInTarget)
            end
        else
            if self.fsm_:canDoEvent("release") then
                self.fsm_:doEvent("release")
                self:callHandler_("onReleaseCallback_", x, y, touchInTarget)
            end
        end
    else
        if self.fsm_:canDoEvent("release") then
            self.fsm_:doEvent("release")
            self:callHandler_("onReleaseCallback_", x, y, touchInTarget)
        end
        if event == "ended" and touchInTarget then
            self:callHandler_("onClickedCallback_", x, y, touchInTarget)
        end
    end
end

return UIPushButton
