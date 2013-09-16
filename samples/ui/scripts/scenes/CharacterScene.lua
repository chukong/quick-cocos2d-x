
--[[--

角色场景，左侧为角色信息，右侧为背包界面。

角色信息固定宽度，背包则自动缩放。

]]

local CharacterScene = class("CharacterScene", function()
    return display.newScene("CharacterScene")
end)

function CharacterScene:ctor()
    -- 创建一个 UIGroup 用于左侧面板和右侧面板
    -- 宽度为屏幕总宽度 - 100, 高度为屏幕总高度 - 200
    local width = display.width - 60
    local height = display.height - 160
    local group = cc.ui.UIGroup.new()
        :setLayoutSize(width, height)
        -- 因为 UI 元素的锚点总是在左下角，所以计算初始位置要麻烦一点
        :pos(display.left + 30, display.top - height - 30)
        :addTo(self)

    -- 左侧面板
    local leftPanel = cc.ui.UIGroup.new()
        :setLayoutSizePolicy(display.FIXED_SIZE, display.AUTO_SIZE)
        :setLayoutSize(320, display.AUTO_SIZE)
        :setLayoutPadding(10, 10, 10, 10)
        :setBackgroundImage("PinkScale9Block.png", {scale9 = true})
        :addTo(group)

    -- 右侧面板
    local rightPanel = cc.ui.UIGroup.new()
        :setLayoutMargin(0, 0, 0, 30) -- top, right, bottom, left
        :setLayoutPadding(10, 10, 10, 10) -- top, right, bottom, left
        :setBackgroundImage("PinkScale9Block.png", {scale9 = true}) -- 背景图是九宫格
        :addTo(group)


    -- 设置左右面板的布局
    local groupLayout = cc.ui.UIBoxLayout.new(display.LEFT_TO_RIGHT)
        :addWidget(leftPanel)
        :addWidget(rightPanel)
    group:setLayout(groupLayout)

    -- 添加内容到左侧面板
    local label = ui.newTTFLabel({
        text = "角色信息",
        size = 48,
    }):addTo(leftPanel):pos(leftPanel:getLayoutSize().width / 2, leftPanel:getLayoutSize().height / 2)

    -- 添加内容到右侧面板，包含 6 行，每行 8 列
    local boxImageNames = {"BlueBlock.png", "GreenBlock.png", "RedBlock.png", "YellowBlock.png"}
    local vboxLayout = cc.ui.UIBoxLayout.new(display.TOP_TO_BOTTOM)
    local rowWeight = 1
    for row = 1, 5 do
        local hboxLayout = cc.ui.UIBoxLayout.new(display.LEFT_TO_BOTTOM)
        local colWeight = 1
        for col = 1, 6 do
            -- 随机颜色的格子
            local box = cc.ui.UIImage.new(boxImageNames[((col - 1) % 4) + 1], {scale9 = true})
                :setLayoutMargin(8, 8, 8, 8)
                :addTo(rightPanel)
            -- if col == 1 or col == 4 then
            --     -- 其中两个格子的为固定宽度
            --     box:setLayoutSizePolicy(display.FIXED_SIZE, display.AUTO_SIZE)
            --         :setLayoutSize(100, 0)
            -- end
            hboxLayout:addWidget(box, colWeight) -- 每一行的格子都水平布局
            -- colWeight = colWeight + 0.4
        end

        -- if row == 1 or row == 3 then
        --     hboxLayout:setLayoutSizePolicy(display.AUTO_SIZE, display.FIXED_SIZE)
        --         :setLayoutSize(0, row * 10 + 100)
        -- end
        vboxLayout:addLayout(hboxLayout, rowWeight)
        -- rowWeight = rowWeight + 0.2
    end
    rightPanel:setLayout(vboxLayout)

    -- local button1 = cc.ui.UIButton.new("Button01.png")
    -- button1:pos(display.right - 50, display.bottom + 50)
    --     :scale(0.5)
    --     :setButtonEnabled(true)
    --     :onButtonPressed(function()
    --         button1:setScale(0.6)
    --     end)
    --     :onButtonRelease(function()
    --         button1:setScale(0.5)
    --     end)
    --     :onButtonClicked(function(x, y)
    --         local size = group:getLayoutSize()
    --         if size.width > 700 then
    --             -- 缩小整个容器的宽度，可以看到左侧面板的宽度也会减小，但右侧面板宽度保持不变
    --             size.width = size.width - 20
    --             group:setLayoutSize(size)
    --         end
    --     end)
    -- self:addChild(button1)

end

return CharacterScene
