
import("..includes.functions")

-- 演示可触摸的 Node，其中包含多个 Sprite
local TestSingleTouch2Scene = class("TestSingleTouch2Scene", function()
    return display.newScene("TestSingleTouch2Scene")
end)

function TestSingleTouch2Scene:ctor()
    -- touchableNode 是启用触摸的 Node
    self.touchableNode = display.newNode()
    self.touchableNode:setPosition(display.cx, display.cy)
    self:addChild(self.touchableNode)

    -- 在 touchableNode 中加入一些 sprite
    local count = math.random(3, 8)
    local images = {"WhiteButton.png", "BlueButton.png", "GreenButton.png", "PinkButton.png"}
    for i = 1, count do
        local sprite = display.newScale9Sprite(images[math.random(1, 4)])
        sprite:setContentSize(cc.size(math.random(100, 200), math.random(100, 200)))
        sprite:setPosition(math.random(-200, 200), math.random(-200, 200))
        drawBoundingBox(self.touchableNode, sprite, cc.c4f(1.0, 0, 0, 1.0))
        self.touchableNode:addChild(sprite)
    end

    self.stateLabel = cc.ui.UILabel.new({text = ""})
    self.stateLabel:align(display.CENTER, display.cx, display.top - 100)
    self:addChild(self.stateLabel)

    -- 启用触摸
    drawBoundingBox(self, self.touchableNode, cc.c4f(0, 1.0, 0, 1.0))
    self.touchableNode:setTouchEnabled(true)
    -- 添加触摸事件处理函数
    self.touchableNode:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("touchableNode: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.stateLabel:setString(label)
        return true
    end)

    --
    app:createNextButton(self)
    app:createTitle(self, "Test Single-Touch 2")
end

return TestSingleTouch2Scene
