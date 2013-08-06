
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local editBox1 = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(400, 96),
        x = display.cx,
        y = display.cy + 200,
        listener = self
    })
    self:addChild(editBox1)

    local editBox2 = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(400, 96),
        x = display.cx,
        y = display.cy,
        listener = function(event, editbox)
            printf("editBox2 event %s : text = %s", event, editbox:getText())
        end
    })
    self:addChild(editBox2)
end

function MainScene:onEditBoxBegan(editbox)
    printf("editBox1 event began : text = %s", editbox:getText())
end

function MainScene:onEditBoxEnded(editbox)
    printf("editBox1 event ended : %s", editbox:getText())
end

function MainScene:onEditBoxReturn(editbox)
    printf("editBox1 event return : %s", editbox:getText())
end

function MainScene:onEditBoxChanged(editbox)
    printf("editBox1 event changed : %s", editbox:getText())
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
