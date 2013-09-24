
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

--[[--

创建一个按钮

以指定的图片创建一个 CCSprite 对象，并响应触摸操作。
当触摸操作开始和结束都在图片区域内时，调用指定的函数。

@param imageName 图像名称
@param function listener 按钮按下时要调用的函数

@return CCSprite

]]
local function newButton(imageName, listener)
    local sprite = display.newSprite(imageName) -- 以指定图像名创建 CCSprite 对象
    sprite:setTouchEnabled(true) -- 设置 CCSprite 接受触摸事件
    sprite:addTouchEventListener(function(event, x, y)
        -- 触摸事件传入四个参数：
        --     event 指示触摸事件的阶段
        --     x, y 触摸事件发生的位置（屏幕坐标）
        --     touchInSprite 触摸事件是否发生在图像区域内
        if event == "began" then
            sprite:setOpacity(128) -- 触摸开始时，将按钮设置为半透明
            return true -- 返回 true，表示响应该次触摸，阻止触摸事件继续传递给其他对象
        end

        local touchInSprite = sprite:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
        if event == "moved" then
            if touchInSprite then -- 手指移动时，判断是否移出了图像区域
                sprite:setOpacity(128) -- 在图像区域内，设置图像为半透明
            else
                sprite:setOpacity(255) -- 在区域外，设置为不透明
            end
        elseif event == "ended" then
            -- 触摸结束时如果手指在图像区域内，则视为点击按钮，调用指定的函数
            if touchInSprite then listener() end
            sprite:setOpacity(255)
        else -- event 还可能是 cancelled，表示触摸事件被取消
            sprite:setOpacity(255)
        end
    end)

    return sprite
end


function MenuScene:ctor()
    newButton("GreenButton.png", function()
        print("GreenButton TAP")
    end):addTo(self):pos(display.right - 100, display.bottom + 200)

    local p = newButton("PinkButton.png", function()
        print("PinkButton TAP")
    end):addTo(self):pos(display.right - 200, display.bottom + 300):zorder(1000)
    newButton("BlueButton.png", function()
        print("BlueButton TAP")
    end):addTo(p):scale(0.5):pos(100, 100)

    newButton("WhiteButton.png", function()
        print("WhiteButton TAP")
    end):addTo(self):pos(display.right - 300, display.bottom + 400)

    newButton("BlueButton.png", function()
        print("BlueButton TAP")
    end):addTo(self):pos(display.right - 400, display.bottom + 500)
end

return MenuScene
