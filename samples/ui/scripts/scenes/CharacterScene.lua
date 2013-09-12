
--[[--

角色场景，左侧为角色信息，右侧为背包界面。

角色信息固定宽度，背包则自动缩放。

]]

local CharacterScene = class("CharacterScene", function()
    return display.newScene("CharacterScene")
end)

function CharacterScene:ctor()
    -- 创建一个 UIGroup 用于放置角色面板和背包面板
    -- 宽度为屏幕总宽度 - 100, 高度为屏幕总高度 - 200
    local width = display.width - 60
    local height = display.height - 200
    local group = cc.ui.UIGroup.new()
        :setLayoutSize(width, height)
        -- 因为 UI 元素的锚点总是在左下角，所以计算初始位置要麻烦一点
        :pos(display.left + 30,
             display.top - height - 30)
        :addTo(self)

    -- 左侧面板
    local leftPanel = cc.ui.UIGroup.new()
        :setLayoutMargin(0, 30, 0, 0)
        :setLayoutPadding(10, 10, 10, 10)
        :setBackgroundImage("GreenScale9Block.png", true)
        :addTo(group)

    -- 右侧面板
    local rightPanel = cc.ui.UIGroup.new()
        :setLayoutSizePolicy(cc.ui.FIXED_SIZE_POLICY, cc.ui.PREFERRED_SIZE_POLICY)
        :setLayoutSize(200, 0)
        :setLayoutPadding(10, 10, 10, 10)
        :setBackgroundImage("PinkScale9Block.png", true)
        :addTo(group)

    -- 设置布局
    local layout = cc.ui.UIHBoxLayout.new()
        :addWidget(leftPanel)
        :addWidget(rightPanel)
    group:setLayout(layout)

    --

    -- 添加内容到左侧面板

    -- local box1 = cc.ui.UIImage.new("BlueBlock.png")
    --     :setLayoutMargin(10, 10, 10, 10)
    --     :addTo(leftPanel)
    -- local box2 = cc.ui.UIImage.new("GreenBlock.png")
    --     :setLayoutMargin(10, 10, 10, 10)
    --     :addTo(leftPanel)
    -- local box3 = cc.ui.UIImage.new("RedBlock.png")
    --     :setLayoutMargin(10, 10, 10, 10)
    --     :addTo(leftPanel)
    -- local box4 = cc.ui.UIImage.new("YellowBlock.png")
    --     :setLayoutMargin(10, 10, 10, 10)
    --     :addTo(leftPanel)

    -- local row1 = cc.ui.UIHBoxLayout.new()
    -- row1:addWidget(box1)
    --     :addWidget(box2)
    --     :addWidget(box3)
    --     :addWidget(box4)
    -- leftPanel:getLayout():addWidget(row1)

    -- 添加内容到右侧面板


    local button1 = cc.ui.UIButton.new("Button01.png")
    button1:pos(display.right - 50, display.bottom + 50)
        :scale(0.5)
        :setButtonEnabled(true)
        :onButtonPressed(function()
            button1:setScale(0.6)
        end)
        :onButtonRelease(function()
            button1:setScale(0.5)
        end)
        :onButtonClicked(function(x, y)
            local size = group:getLayoutSize()
            if size.width > 700 then
                -- 缩小整个容器的宽度，可以看到左侧面板的宽度也会减小，但右侧面板宽度保持不变
                size.width = size.width - 20
                group:setLayoutSize(size)
            end
        end)
    self:addChild(button1)

end

return CharacterScene
