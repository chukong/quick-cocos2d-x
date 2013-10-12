
local WelcomeScene = class("WelcomeScene", function()
    return display.newScene("WelcomeScene")
end)

function WelcomeScene:ctor()
    local checkBoxButton1, pushButton

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

    local checkBoxButtonImages = {
        off = "CheckBoxButtonOff.png",
        off_pressed = "CheckBoxButtonOffPressed.png",
        off_disabled = "CheckBoxButtonOffDisabled.png",
        on = "CheckBoxButtonOn.png",
        on_pressed = "CheckBoxButtonOnPressed.png",
        on_disabled = "CheckBoxButtonOnDisabled.png",
    }
    checkBoxButton1 = cc.ui.UICheckBoxButton.new(checkBoxButtonImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 24,  color = ccc3(96, 96, 255)}))
        :setButtonLabelOffset(100, 0)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :pos(display.cx - 80, display.cy - 160)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton1)

    checkBoxButton2 = cc.ui.UICheckBoxButton.new(checkBoxButtonImages)
        :setButtonSelected(true)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 24, color = ccc3(96, 255, 96)}))
        :setButtonLabelOffset(100, 0)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :pos(display.cx - 80, display.cy - 100)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton2)

    local pushButtonImages = {
        normal = "Button01.png",
        pressed = "Button01Pressed.png",
        disabled = "Button01Disabled.png",
    }
    pushButton = cc.ui.UIPushButton.new(pushButtonImages, {scale9 = true})
        :setButtonSize(300, 80)
        :setButtonLabel("normal", ui.newTTFLabel({
            text = "This is a PushButton",
            size = 24
        }))
        :setButtonLabel("pressed", ui.newTTFLabel({
            text = "Button Pressed",
            size = 24,
            color = ccc3(255, 64, 64)
        }))
        :setButtonLabel("disabled", ui.newTTFLabel({
            text = "Button Disabled",
            size = 24,
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
        :pos(display.cx, display.cy + 160)
        :addTo(self)

end

return WelcomeScene
