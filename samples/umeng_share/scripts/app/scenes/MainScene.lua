
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    -- if "ios" == device.platform or "android" == device.platform then
    --     self:showView()
    -- else
    --     self:showNotSupport()
    -- end
    self:showView()
end

function MainScene:showView()
    self.innerSpace = 80

    cc.ui.UILabel.new({text = "UmengShare demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*1)
        :align(display.CENTER)
        :addTo(self)

    cc.share:doCommand{command = "setAppWebSite",
        args = {shareMedia = cc.share.umengShareMedia.RENREN, webSite = "http://quick.cocoachina.com/"}}

    -- 友盟在android上有默认的分享平台,在IOS上没有,所以removePlatform在android上有效,在IOS上无效
    cc.share:doCommand {command = "removePlatform",
        args = {shareMedia = {cc.share.umengShareMedia.INSTAGRAM,
                            cc.share.umengShareMedia.TWITTER,
                            cc.share.umengShareMedia.SMS,
                            cc.share.umengShareMedia.DOUBAN}}}

    -- reorderPlatform其实也有添加分享平台的意思
    cc.share:doCommand {command = "reorderPlatform",
        args = {shareMedia = {cc.share.umengShareMedia.WEIXIN,
                            cc.share.umengShareMedia.WEIXIN_CIRCLE,
                            cc.share.umengShareMedia.SINA,
                            cc.share.umengShareMedia.TENCENT,
                            cc.share.umengShareMedia.QQ,
                            cc.share.umengShareMedia.RENREN}}}

    -- share text
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "share text", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            cc.share:doCommand{command = "shareText", args = {shareText = "UmengShare demo on Quick-X"}}
        end)
        :pos(display.cx, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "share image", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            cc.share:doCommand{command = "shareImg",
                args = {shareText = "UmengShare demo on Quick-X",
                shareImg = "http://cc.cocimg.com/bbs/attachment/upload/71/167711400484693.jpg",
                -- shareImg = "/mnt/sdcard/htl/badge.png"
                }}
        end)
        :pos(display.cx, display.top - self.innerSpace*4)
        :addTo(self)

    -- use EventProxy, ensure remove the listener when leave current the scene
    cc.share:addEventListener(cc.share.events.LISTENER, function(event)
        printInfo("suc:" .. cc.share.errors.SUCCESS)
        if cc.share.errors.SUCCESS == tonumber(event.code) then
            printInfo("share success to " .. event.shareSns)
        else
            printInfo("share fail to " .. event.shareSns .. " error:" .. event.code)
        end
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
