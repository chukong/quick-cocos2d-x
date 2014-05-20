
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
    	:setButtonLabel(cc.ui.UILabel.new({text = "feedback", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
        	cc.feedback:doCommand{command = "showFeedBack", args = {appKey = UMENG_APPKEY}}
        end)
    	:pos(display.cx, display.cy)
    	:addTo(self)
end

function MainScene:onEnter()
	cc.feedback:doCommand{command = "checkReplies", args = {appKey = UMENG_APPKEY}}
end

function MainScene:onExit()
end

return MainScene
