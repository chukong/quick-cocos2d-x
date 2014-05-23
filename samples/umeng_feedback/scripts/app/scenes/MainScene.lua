
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if device.platform == "android" or device.platform == "ios" then
        self:showView()
    else
        self:showNotSupport()
    end
end

function MainScene:showView()
    cc.ui.UILabel.new({text = "Umeng analytics demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - 70)
        :align(display.CENTER)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "feedback", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            cc.feedback:doCommand{command = "showFeedBack", args = {appKey = UMENG_APPKEY}}
        end)
        :pos(display.cx, display.cy)
        :addTo(self)
end

function MainScene:showNotSupport()
    cc.ui.UILabel.new({text = "Umeng feedback demo\n\nPlease run this demo on IOS or Android device.",
            size = 24,
            align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.cy)
        :align(display.CENTER)
        :addTo(self)
end

function MainScene:onEnter()
    if device.platform == "android" or device.platform == "ios" then
	   cc.feedback:doCommand{command = "checkReplies", args = {appKey = UMENG_APPKEY}}
    end
end

function MainScene:onExit()
end

return MainScene
