
--[[--

角色场景，左侧为角色信息，右侧为背包界面。

角色信息固定宽度，背包则自动缩放。

]]

local CharacterScene = class("CharacterScene", function()
    return display.newScene("CharacterScene")
end)


function CharacterScene:createLeftPanel()
    -- 左侧面板
    local leftPanel = cc.ui.UIGroup.new()
        :setLayoutSizePolicy(display.FIXED_SIZE, display.AUTO_SIZE)
        :setLayoutSize(320, display.AUTO_SIZE)
        :setLayoutPadding(10, 10, 10, 10)
        :setBackgroundImage("PinkScale9Block.png", {scale9 = true})

    local button1 = cc.ui.UIPushButton.new({
            normal = "Button01.png",
            pressed = "Button01Pressed.png",
            disabled = "Button01Disabled.png",
        }):addTo(leftPanel)
    local button2 = cc.ui.UIPushButton.new({
            normal = "Button01.png",
            pressed = "Button01Pressed.png",
            disabled = "Button01Disabled.png",
        }):addTo(leftPanel)
    local button3 = cc.ui.UICheckBoxButton.new({
            off = "SwitchOffButton.png",
            on = "SwitchOnButton.png",
        }):addTo(leftPanel)

    button1:setScale(0.5)
    button2:setScale(0.5)
    button2:setButtonEnabled(false)
    button3:setScale(0.5)
    button3:onButtonClicked(function()
        print("button3:isButtonSelected() = ", button3:isButtonSelected())
        self:performWithDelay(function()
            button3:setButtonSelected(not button3:isButtonSelected())
        end, 0.2)
    end)

    local leftPanelLayout = cc.ui.UIBoxLayout.new(display.LEFT_TO_RIGHT, "left")
        :addWidget(button1)
        :addWidget(button2)
        :addStretch()
        :addWidget(button3)
    leftPanel:setLayout(leftPanelLayout)

    return leftPanel
end

function CharacterScene:createRightPanel()
    -- 右侧面板
    local rightPanel = cc.ui.UIGroup.new()
        :setLayoutMargin(0, 0, 0, 30) -- top, right, bottom, left
        :setLayoutPadding(10, 10, 10, 10) -- top, right, bottom, left
        :setBackgroundImage("PinkScale9Block.png", {scale9 = true}) -- 背景图是九宫格

    -- 添加内容到右侧面板，包含 6 行，每行 8 列
    local boxImageNames = {"BlueBlock.png", "GreenBlock.png", "RedBlock.png", "YellowBlock.png"}
    local vboxLayout = cc.ui.UIBoxLayout.new(display.TOP_TO_BOTTOM, "right_vbox")
    local rowWeight = 1
    for row = 1, 5 do
        local hboxLayout = cc.ui.UIBoxLayout.new(display.LEFT_TO_RIGHT, string.format("right_hbox_%d", row))
        local colWeight = 1
        for col = 1, 6 do
            -- 随机颜色的格子
            local box = cc.ui.UIImage.new(boxImageNames[((col - 1) % 4) + 1], {scale9 = true})
                :setLayoutMargin(8, 8, 8, 8)
                :addTo(rightPanel)
            if col == 1 or col == 4 then
                -- 其中两个格子的为固定宽度
                box:setLayoutSizePolicy(display.FIXED_SIZE, display.AUTO_SIZE)
                    :setLayoutSize(50, 0)
            end
            hboxLayout:addWidget(box, colWeight) -- 每一行的格子都水平布局
            colWeight = colWeight + 1
        end

        if row == 1 or row == 3 then
            hboxLayout:setLayoutSizePolicy(display.AUTO_SIZE, display.FIXED_SIZE)
                :setLayoutSize(0, row * 10 + 100)
        end
        vboxLayout:addLayout(hboxLayout, rowWeight)
        rowWeight = rowWeight + 0.2
    end
    rightPanel:setLayout(vboxLayout)

    return rightPanel
end

function CharacterScene:ctor()
    -- 创建一个 UIGroup 用于左侧面板和右侧面板
    local leftPanel = self:createLeftPanel()
    local rightPanel = self:createRightPanel()
    local detailsGroup = cc.ui.UIGroup.new()
        :add(leftPanel)
        :add(rightPanel)
        :addTo(self)

    -- 设置左右面板的布局
    self.detailsGroupLayout = cc.ui.UIBoxLayout.new(display.LEFT_TO_RIGHT, "details")
        :addWidget(leftPanel)
        :addWidget(rightPanel)

    -- 全局布局
    print("----------------------------------------")
    local sceneLayout = cc.ui.UIBoxLayout.new(display.TOP_TO_BOTTOM, "scene")
        :setLayoutSize(display.width, display.height)
        :setLayoutPadding(30, 30, 30, 30)
        :addLayout(self.detailsGroupLayout)
    sceneLayout:apply()

    self.leftPanel = leftPanel
end

function CharacterScene:onEnter()
end

return CharacterScene
