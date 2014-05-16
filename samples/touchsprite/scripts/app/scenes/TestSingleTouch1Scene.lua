
import("..includes.functions")

-- 演示基本的可触摸 sprite 用法
local TestSingleTouch1Scene = class("TestSingleTouch1Scene", function()
    return display.newScene("TestSingleTouch1Scene")
end)

function TestSingleTouch1Scene:ctor()
    -- parentButton 是 button1 的父节点
    self.parentButton = createTouchableSprite({
            image = "WhiteButton.png",
            size = CCSize(600, 500),
            label = "TOUCH ME !",
            labelColor = cc.c3(255, 0, 0)})
        :pos(display.cx, display.cy)
        :addTo(self)
    self.parentButton.name = "parentButton"
    drawBoundingBox(self, self.parentButton, cc.c4f(0, 1.0, 0, 1.0))

    -- -- 启用触摸
    self.parentButton:setTouchEnabled(true)
    -- -- 添加触摸事件处理函数
    self.parentButton:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        -- event.name 是触摸事件的状态：began, moved, ended, cancelled
        -- event.x, event.y 是触摸点当前位置
        -- event.prevX, event.prevY 是触摸点之前的位置
        local label = string.format("parentButton: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.parentButton.label:setString(label)
        -- 返回 true 表示要继续接收该触摸事件的状态变化
        return true
    end)

    -- button1 响应触摸后，会吞噬掉触摸事件
    self.button1 = createTouchableSprite({
            image = "GreenButton.png",
            size = CCSize(400, 120),
            label = "TOUCH ME !"})
        :pos(300, 400)
        :addTo(self.parentButton)
    cc.ui.UILabel.new({text = "SWALLOW = YES", size = 24})
        :align(display.CENTER, 200, 90)
        :addTo(self.button1)
    drawBoundingBox(self, self.button1, cc.c4f(1.0, 0, 0, 1.0))

    self.button1:setTouchEnabled(true)
    self.button1:setTouchSwallowEnabled(true) -- 是否吞噬事件，默认值为 true
    self.button1:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("button1: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.button1.label:setString(label)
        return true
    end)

    -- button2 响应触摸后，不会吞噬掉触摸事件
    self.button2 = createTouchableSprite({
            image = "PinkButton.png",
            size = CCSize(400, 120),
            label = "TOUCH ME !"})
        :pos(300, 200)
        :addTo(self.parentButton)
    cc.ui.UILabel.new({text = "SWALLOW = NO", size = 24})
        :align(display.CENTER, 200, 90)
        :addTo(self.button2)
    drawBoundingBox(self, self.button2, cc.c4f(0, 0, 1.0, 1.0))

    self.button2:setTouchEnabled(true)
    self.button2:setTouchSwallowEnabled(false)
    self.button2:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("button1: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.button2.label:setString(label)
        return true
    end)

    --
    app:createNextButton(self)
    app:createTitle(self, "Test Single-Touch 1")
end

return TestSingleTouch1Scene
