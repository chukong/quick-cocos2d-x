
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:createLayout(x, y, align)
    local group = cc.ui.UIGroup.new()
    group:align(align)
        :pos(x, y)
        :setLayoutSize(display.width - 100, 50)
        :addTo(self)

    local block1 = cc.ui.UIImage.new("BlueBlock.png")
        :setLayoutSizePolicy(cc.ui.FIXED_SIZE_POLICY, cc.ui.PREFERRED_SIZE_POLICY)
        :setLayoutSize(200, 0)
        :addTo(group)
    local block2 = cc.ui.UIImage.new("YellowBlock.png"):addTo(group)
    local block3 = cc.ui.UIImage.new("RedBlock.png")
        :setLayoutSizePolicy(cc.ui.FIXED_SIZE_POLICY, cc.ui.FIXED_SIZE_POLICY)
        :setLayoutSize(200, 30)
        :addTo(group)
    local block4 = cc.ui.UIImage.new("GreenBlock.png"):addTo(group)

    local hbox = cc.ui.UIHBoxLayout.new()
    hbox:addWidget(block1)
        :addWidget(block2, 2)
        :addWidget(block3)
        :addWidget(block4, 4)
    group:setLayout(hbox)
end

function MainScene:createLayout2()
    -- local group = cc.ui.UIGroup.new()
    --     :align(display.CENTER)
    --     :pos(display.cx, display.cy + 50)
    --     :setLayoutSize(display.width - 100, display.height - 200)
    --     :addTo(self)

    -- local leftPanel = cc.ui.UIImage.new("GreenScale9Block.png", true)
    --     :align(display.CENTER)
    --     :setLayoutMargin(0, 30, 0, 0)
    --     :setLayoutPadding(10, 10, 10, 10)
    --     :addTo(group)
    -- local rightPanel = cc.ui.UIImage.new("GreenScale9Block.png", true)
    --     :setLayoutSizePolicy(cc.ui.FIXED_SIZE_POLICY, cc.ui.PREFERRED_SIZE_POLICY)
    --     :setLayoutSize(200, 0)
    --     :setLayoutPadding(10, 10, 10, 10)
    --     :addTo(group)

    -- local groupLayout = cc.ui.UIHBoxLayout.new()
    -- groupLayout:addWidget(leftPanel)
    --     :addWidget(rightPanel)
    -- group:setLayout(groupLayout)

    --

    local a = display.newSprite("GreenScale9Block.png"):addTo(self):align(display.CENTER, display.cx, display.cy)
    display.newSprite("BlueBlock.png"):addTo(a):align(display.CENTER, 0, 0)

    -- local box1 = cc.ui.UIImage.new("BlueBlock.png")
    --     :align(display.CENTER, 0, 0)
    --     -- :setLayoutMargin(8, 8, 8, 8)
    --     :addTo(leftPanel)
    -- local box2 = cc.ui.UIImage.new("GreenBlock.png")
    --     :setLayoutMargin(8, 8, 8, 8)
    --     :addTo(leftPanel)
    -- local box3 = cc.ui.UIImage.new("RedBlock.png")
    --     :setLayoutMargin(8, 8, 8, 8)
    --     :addTo(leftPanel)
    -- local box4 = cc.ui.UIImage.new("YellowBlock.png")
    --     :setLayoutMargin(8, 8, 8, 8)
    --     :addTo(leftPanel)

    -- local row1 = cc.ui.UIHBoxLayout.new()
    -- row1:addWidget(box1)
    --     :addWidget(box2)
    --     :addWidget(box3)
    --     :addWidget(box4)
    -- leftPanel:setLayout(row1)

    -- print(box1:getPosition())

end

function MainScene:ctor()
    -- self:createLayout(display.left + 10, display.bottom + 50, display.LEFT_BOTTOM)
    -- self:createLayout(display.left + 10, display.bottom + 130, display.LEFT_CENTER)
    -- self:createLayout(display.left + 10, display.bottom + 210, display.LEFT_TOP)

    -- self:createLayout(display.right - 10, display.bottom + 240, display.RIGHT_BOTTOM)
    -- self:createLayout(display.right - 10, display.bottom + 320, display.RIGHT_CENTER)
    -- self:createLayout(display.right - 10, display.bottom + 400, display.RIGHT_TOP)

    -- self:createLayout(display.cx, display.bottom + 430, display.CENTER_BOTTOM)
    -- self:createLayout(display.cx, display.bottom + 510, display.CENTER)
    -- self:createLayout(display.cx, display.bottom + 590, display.CENTER_TOP)
    local layer = CCLayerColor:create(ccc4(230, 230, 230, 255))
    self:addChild(layer)

    self:createLayout2()

    -- local label = ui.newTTFLabel({
    --     text = "Hello, World",
    --     size = 64,
    --     x = display.cx,
    --     y = display.cy,
    --     align = ui.TEXT_ALIGN_CENTER
    -- })
    -- self:addChild(label)

    -- local button1 = cc.ui.UIButton.new("Button01.png", "Button01Pressed.png", "Button01Disabled.png")
    -- button1:pos(display.cx - 150, display.top - 100)
    --     :setButtonEnabled(true)
    --     :onButtonPressed(function(x, y)
    --         printf("button1 pressed x = %0.2f, y = %0.2f", x, y)
    --     end)
    --     :onButtonRelease(function(x, y)
    --         printf("button1 release x = %0.2f, y = %0.2f", x, y)
    --     end)
    --     :onButtonClicked(function(x, y)
    --         printf("button1 clicked x = %0.2f, y = %0.2f", x, y)
    --         button1:setButtonEnabled(false)
    --     end)
    -- self:addChild(button1)

    -- local button2 = cc.ui.UIButton.new("Button01.png", "Button01Pressed.png", "Button01Disabled.png")
    -- button2:pos(display.cx + 150, display.top - 100)
    --     :setButtonEnabled(true)
    --     :onButtonPressed(function(x, y)
    --         printf("button2 pressed x = %0.2f, y = %0.2f", x, y)
    --     end)
    --     :onButtonRelease(function(x, y)
    --         printf("button2 release x = %0.2f, y = %0.2f", x, y)
    --     end)
    --     :onButtonClicked(function(x, y)
    --         printf("button2 clicked x = %0.2f, y = %0.2f", x, y)
    --         button1:setButtonEnabled(true)
    --     end)
    -- self:addChild(button2)
end

function MainScene:onEnter()
    if device.platform ~= "android" then return end

    -- avoid unmeant back
    self:performWithDelay(function()
        -- keypad layer, for android
        local layer = display.newLayer()
        layer:addKeypadEventListener(function(event)
            if event == "back" then game.exit() end
        end)
        self:addChild(layer)

        layer:setKeypadEnabled(true)
    end, 0.5)
end

return MainScene
