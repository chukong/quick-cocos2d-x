
import("..includes.functions")

-- 演示基本的可触摸 sprite 用法
local TestSingleTouch1Scene = class("TestSingleTouch1Scene", function()
    return display.newScene("TestSingleTouch1Scene")
end)

function TestSingleTouch1Scene:ctor()
    self.debugLabel = cc.ui.UILabel.new({text = "touch state: -\n\n\n"})
        :pos(display.cx, display.top - 160)
        :addTo(self)

    -- button1parent 是 button1 的父节点
    local button1parent = createTouchableSprite({
        image = "WhiteButton.png",
        size = CCSize(600, 500),
        label = "Touchable Node\n\nTOUCH ME !"})
        :pos(display.cx, display.cy)
        :addTo(self)
    button1parent.name = "button1parent"

    local button1 = createTouchableSprite({
        image = "GreenButton.png",
        size = CCSize(400, 360),
        label = "Touchable Node\n\nTOUCH ME !"})
        :pos(300, 250)
        :addTo(button1parent)
    button1.name = "button1"

    button1parent:setTouchEnabled(true)
    button1parent:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        self.onTouch(event.name, event.x, event.y, event.prevX, event.prevY)
    end)

    -- 启用触摸
    button1:setTouchEnabled(true)
    -- 添加触摸事件处理函数
    button1:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local name, x, y, prevX, prevY = event.name, event.x, event.y, event.prevX, event.prevY

        -- name 是触摸事件的状态：began, moved, ended, cancelled
        -- x, y 是触摸点当前位置
        -- prevX, prevY 是触摸点之前的位置
        -- offset 是触摸点相对于 button1 的位置

        if name == "began" then
            -- 在 began 状态需要返回 true，表示接收该触摸事件的后续状态
            return true
        end
    end)

    --
    app:createNextButton(self)
    app:createTitle(self, "Test Single Touch 1")
end

function TestSingleTouch1Scene:onTouch(event, x, y, prevX, prevY)
    local offset = button1:convertToNodeSpace(CCPoint(x, y))
    self.debugLabel:setString(string.format("touch button1 state: %s\nx,y: %0.2f, %0.2f\nprevX, prevY: %0.2f, %0.2f\noffsetX, offsetY: %0.2f, %0.2f", event, x, y, prevX, prevY, offset.x, offset.y))
end

return TestSingleTouch1Scene
