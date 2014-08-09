
local TestUIButtonScene = class("TestUIButtonScene", function()
    return display.newScene("TestUIButtonScene")
end)

TestUIButtonScene.PUSH_BUTTON_IMAGES = {
    normal = "Button01.png",
    pressed = "Button01Pressed.png",
    disabled = "Button01Disabled.png",
}
function TestUIButtonScene:ctor()
    app:createGrid(self)

    self:createButtonGroup1()

    app:createTitle(self, "Test UIButton")
    app:createNextButton(self)
end

function TestUIButtonScene:createButtonGroup1()
    local function createButton(x, y)
        cc.ui.UIPushButton.new(TestUIButtonScene.PUSH_BUTTON_IMAGES, {scale9 = true})
            :setButtonSize(240, 200)
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
            :pos(x, y)
            :addTo(self)
    end

    createButton(display.left + 180, display.top - 180)
    createButton(display.right - 180, display.top - 180)
    createButton(display.left + 180, display.bottom + 180)
    createButton(display.right - 180, display.bottom + 180)
end

return TestUIButtonScene
