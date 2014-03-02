
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if device.platform == "ios" or device.platform == "android" then
        self:initAd()
    else
        self:initNoAd()
    end
end

function MainScene:initAd()
    cc.ui.UILabel.new({text = "PunchBox AD demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.bottom + 100)
        :addTo(self)

    -- banner ad
    local bannerAdButton
    local bannerAdVisible = false
    bannerAdButton = cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show Banner Ad", size = 22}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            if not bannerAdVisible then
                cc.ad.show("banner", {id = "100080n1p0aa", position = "top"})
                bannerAdButton:setButtonLabelString("Remove Banner Ad")
                bannerAdVisible = true
            else
                cc.ad.remove()
                bannerAdButton:setButtonLabelString("Show Banner Ad")
                bannerAdVisible = false
            end
        end)
        :pos(display.cx, display.cy)
        :addTo(self)

    -- interstitial ad
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show Interstitial Ad", size = 22}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            cc.ad.show("interstitial", {id = "100080n1titb"})
        end)
        :pos(display.cx, display.cy - 120)
        :addTo(self)

    -- more game ad
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show More Game Ad", size = 22}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            cc.ad.show("moregame", {id = "100080n1tbcj"})
        end)
        :pos(display.cx, display.cy - 240)
        :addTo(self)
end

function MainScene:initNoAd()
    cc.ui.UILabel.new({text = "PunchBox AD demo\n\nPlease run this demo on iOS or Android device.", size = 24, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.bottom + 200)
        :addTo(self)
end

function MainScene:onEnter()
    if device.platform == "android" then
        -- avoid unmeant back
        self:performWithDelay(function()
            -- keypad layer, for android
            local layer = display.newLayer()
            layer:addKeypadEventListener(function(event)
                if event == "back" then app.exit() end
            end)
            self:addChild(layer)

            layer:setKeypadEnabled(true)
        end, 0.5)
    end
end

function MainScene:onExit()
end

return MainScene
