
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if "ios" == device.platform or "android" == device.platform then
        self:showView()
    else
        self:showNotSupport()
    end
end

function MainScene:showView()
    self.innerSpace = 80

    cc.ui.UILabel.new({text = "UmengShare demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*1)
        :align(display.CENTER)
        :addTo(self)

    cc.share:doCommand{command = "setAppWebSite",
        args = {shareMedia = cc.share.umengShareMedia.RENREN, webSite = "http://quick.cocoachina.com/"}}

    -- share text
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "share text", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            cc.share:doCommand{command = "shareText", args = {shareText = "UmengShare demo on Quick-X"}}
        end)
        :pos(display.cx, display.top - self.innerSpace*3)
        :addTo(self)

    -- use EventProxy, ensure remove the listener when leave current the scene
    cc.share:addEventListener(cc.share.events.LISTENER, function(event)
        dump(event, "umeng share receive event:")
    end)
end

function MainScene:showNotSupport()
    cc.ui.UILabel.new({text = "UmengShare demo\nPlease run this demo on IOS or Android device.",
            size = 24,
            align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.cy)
        :align(display.CENTER)
        :addTo(self)
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
