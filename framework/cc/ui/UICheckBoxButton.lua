
local UIButton = import(".UIButton")
local UICheckBoxButton = class("UICheckBoxButton", UIButton)

UICheckBoxButton.OFF          = "OFF"
UICheckBoxButton.OFF_PRESSED  = "OFF_PRESSED"
UICheckBoxButton.OFF_DISABLED = "OFF_DISABLED"
UICheckBoxButton.ON           = "ON"
UICheckBoxButton.ON_PRESSED   = "ON_PRESSED"
UICheckBoxButton.ON_DISABLED  = "ON_DISABLED"

function UICheckBoxButton:ctor(images)
    UICheckBoxButton.super.ctor(self, {
        {name = "disable",  from = {"OFF", "OFF_PRESSED"}, to = "OFF_DISABLED"},
        {name = "disable",  from = {"ON", "ON_PRESSED"},   to = "ON_DISABLED"},
        {name = "enable",   from = {"OFF_DISABLED"}, to = "OFF"},
        {name = "enable",   from = {"ON_DISABLED"},  to = "ON"},
        {name = "press",    from = "OFF", to = "OFF_PRESSED"},
        {name = "press",    from = "ON",  to = "ON_PRESSED"},
        {name = "release",  from = "OFF_PRESSED", to = "OFF"},
        {name = "release",  from = "ON_PRESSED", to = "ON"},
        {name = "select",   from = "OFF", to = "ON"},
        {name = "unselect", from = "ON", to = "OFF"},
    }, "OFF")
    self:setButtonImage(UICheckBoxButton.OFF, images["off"], true)
    self:setButtonImage(UICheckBoxButton.OFF_PRESSED, images["offpressed"], true)
    self:setButtonImage(UICheckBoxButton.OFF_DISABLED, images["offdisabled"], true)
    self:setButtonImage(UICheckBoxButton.ON, images["on"], true)
    self:setButtonImage(UICheckBoxButton.ON_PRESSED, images["onpressed"], true)
    self:setButtonImage(UICheckBoxButton.ON_DISABLED, images["ondisabled"], true)
end

function UICheckBoxButton:setButtonImage(state, image, ignoreEmpty)
    assert(state == UICheckBoxButton.OFF
        or state == UICheckBoxButton.OFF_PRESSED
        or state == UICheckBoxButton.OFF_DISABLED
        or state == UICheckBoxButton.ON
        or state == UICheckBoxButton.ON_PRESSED
        or state == UICheckBoxButton.ON_DISABLED,
        string.format("UICheckBoxButton:setButtonImage() - invalid state %s", tostring(state)))
    UICheckBoxButton.super.setButtonImage(self, state, image, ignoreEmpty)
    if state == UICheckBoxButton.OFF then
        if not self.images_[UICheckBoxButton.OFF_PRESSED] then
            self.images_[UICheckBoxButton.OFF_PRESSED] = image
        end
        if not self.images_[UICheckBoxButton.OFF_DISABLED] then
            self.images_[UICheckBoxButton.OFF_DISABLED] = image
        end
    elseif state == UICheckBoxButton.ON then
        if not self.images_[UICheckBoxButton.ON_PRESSED] then
            self.images_[UICheckBoxButton.ON_PRESSED] = image
        end
        if not self.images_[UICheckBoxButton.ON_DISABLED] then
            self.images_[UICheckBoxButton.ON_DISABLED] = image
        end
    end

    return self
end

function UICheckBoxButton:isButtonSelected()
    return self.fsm_:canDoEvent("unselect")
end

function UICheckBoxButton:onButtonClicked(callback)
    self.onClickedCallback_ = callback
    return self
end

function UICheckBoxButton:setButtonSelected(selected)
    if self:isButtonSelected() ~= selected then
        if selected then
            self.fsm_:doEventForce("select")
        else
            self.fsm_:doEventForce("unselect")
        end
    end
end

function UICheckBoxButton:onTouch_(event, x, y)
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
            if self.fsm_:canDoEvent("select") then
                self.fsm_:doEvent("select")
            else
                self.fsm_:doEvent("unselect")
            end
            self:callHandler_("onClickedCallback_", x, y, touchInTarget)
        end
    end
end

return UICheckBoxButton
