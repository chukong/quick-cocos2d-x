
import("..includes.functions")

local TestSingleTouch2Scene = class("TestSingleTouch2Scene", function()
    return display.newScene("TestSingleTouch2Scene")
end)

function TestSingleTouch2Scene:ctor()
    local debugLabel = ui.newTTFLabel({text = "touch state: -\n\n\n"})
    debugLabel:setPosition(display.cx, display.top - 160)
    self:addChild(debugLabel)

    -- button1 是 button1parent 的子节点
    local button1 = createTouchableSprite({
        image = "GreenButton.png",
        x = display.cx,
        y = display.cy,
        size = CCSize(400, 360),
        label = "Touchable Node\n\nTOUCH ME !",
    })
    self:addChild(button1)
    -- 启用触摸
    button1:setTouchEnabled(true)
    -- 添加触摸事件处理函数
    button1:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local name, x, y, prevX, prevY = event.name, event.x, event.y, event.prevX, event.prevY
        -- name 是触摸事件的状态：began, moved, ended, cancelled
        -- x, y 是触摸点当前位置
        -- prevX, prevY 是触摸点之前的位置
        -- offset 是触摸点相对于 button1 的位置
        local offset = button1:convertToNodeSpace(CCPoint(x, y))

        debugLabel:setString(string.format("touch button1, state: %s\nx,y: %0.2f, %0.2f\nprevX, prevY: %0.2f, %0.2f\noffsetX, offsetY: %0.2f, %0.2f", event, x, y, prevX, prevY, offset.x, offset.y))

        if name == "began" then
            -- 在 began 状态需要返回 true，表示接收该触摸事件的后续状态
            return true
        end
    end)

    --
    app:createNextButton(self)
    app:createTitle(self, "Test Single Touch 2")
end

return TestSingleTouch2Scene
