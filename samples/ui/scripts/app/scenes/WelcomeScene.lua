
local WelcomeScene = class("WelcomeScene", function()
    return display.newScene("WelcomeScene")
end)

WelcomeScene.CHECKBOX_BUTTON_IMAGES = {
    off = "CheckBoxButtonOff.png",
    off_pressed = "CheckBoxButtonOffPressed.png",
    off_disabled = "CheckBoxButtonOffDisabled.png",
    on = "CheckBoxButtonOn.png",
    on_pressed = "CheckBoxButtonOnPressed.png",
    on_disabled = "CheckBoxButtonOnDisabled.png",
}

WelcomeScene.PUSH_BUTTON_IMAGES = {
    normal = "Button01.png",
    pressed = "Button01Pressed.png",
    disabled = "Button01Disabled.png",
}

function WelcomeScene:createRow1()
    local checkBoxButton1, checkBoxButton2

    local function updateCheckBoxButtonLabel(checkbox)
        local state = ""
        if checkbox:isButtonSelected() then
            state = "on"
        else
            state = "off"
        end
        if not checkbox:isButtonEnabled() then
            state = state .. " (disabled)"
        end
        checkbox:setButtonLabelString(string.format("state is %s", state))
    end

    checkBoxButton1 = cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 22,  color = ccc3(255, 96, 255)}))
        :setButtonLabelOffset(0, -40)
        :setButtonLabelAlignment(display.CENTER)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :pos(display.left + 440, display.top - 60)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton1)

    checkBoxButton2 = cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES)
        :setButtonSelected(true)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 22, color = ccc3(96, 255, 96)}))
        :setButtonLabelOffset(0, -40)
        :setButtonLabelAlignment(display.CENTER)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :pos(display.left + 700, display.top - 60)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton2)

    cc.ui.UIPushButton.new(WelcomeScene.PUSH_BUTTON_IMAGES, {scale9 = true})
        :setButtonSize(240, 60)
        :setButtonLabel("normal", ui.newTTFLabel({
            text = "This is a PushButton",
            size = 18
        }))
        :setButtonLabel("pressed", ui.newTTFLabel({
            text = "Button Pressed",
            size = 18,
            color = ccc3(255, 64, 64)
        }))
        :setButtonLabel("disabled", ui.newTTFLabel({
            text = "Button Disabled",
            size = 18,
            color = ccc3(0, 0, 0)
        }))
        :onButtonClicked(function(event)
            if math.random(0, 1) == 0 then
                checkBoxButton1:setButtonEnabled(not checkBoxButton1:isButtonEnabled())
            else
                checkBoxButton2:setButtonEnabled(not checkBoxButton2:isButtonEnabled())
            end

            local button = event.target
            button:setButtonEnabled(false)
            button:setButtonLabelString("disabled", "Button Enable after 1s")
            self:performWithDelay(function()
                button:setButtonLabelString("disabled", "Button Disabled")
                button:setButtonEnabled(true)
            end, 1.0)
        end)
        :pos(display.left + 140, display.top - 60)
        :addTo(self)
end

function WelcomeScene:createRow2()
    -- local group = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
    --     :pos(display.left, display.bottom)
    --     :addTo(self)
    -- group:addButton(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES))
    -- group:addButton(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES))
    -- group:addButton(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES))

    local group = cc.ui.UIGroup.new():addTo(self)
    local layout = group:getLayout()
    layout:addWidget(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES):addTo(group))
    layout:addWidget(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES):addTo(group))
    layout:addWidget(cc.ui.UICheckBoxButton.new(WelcomeScene.CHECKBOX_BUTTON_IMAGES):addTo(group))
    layout:apply(group)
end

function WelcomeScene:ctor()
    display.newColorLayer(ccc4(100, 120, 140, 255)):addTo(self)
    self:createRow1()
    self:createRow2()

    local image = WelcomeScene.PUSH_BUTTON_IMAGES["normal"]
    cc.ui.UIPushButton.new(image, {scale9 = true})
        :setButtonSize(240, 60)
        :setButtonLabel(ui.newTTFLabel({
            text = "Goto next test",
            size = 18
        }))
        :onButtonPressed(function(event)
            event.target:setScale(0.9)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
            app:enterScene("CharacterScene")
        end)
        :pos(display.cx, display.bottom + 100)
        :addTo(self)
end

return WelcomeScene
