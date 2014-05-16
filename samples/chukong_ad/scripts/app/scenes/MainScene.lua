
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
        :pos(display.cx, display.top - 200)
        :align(display.CENTER)
        :addTo(self)

    local resultLabel = cc.ui.UILabel.new({text = "result: -", size = 20, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - 260)
        :align(display.CENTER)
        :addTo(self)

    -- banner ad
    local function updateCheckBoxButtonLabel(checkbox)
        local state = ""
        if checkbox:isButtonSelected() then
            state = "at top"
        else
            state = "at bottom"
        end
        checkbox:setButtonLabelString(state)
    end

    local checkBoxButton
    checkBoxButton = cc.ui.UICheckBoxButton.new({on = "CheckButtonOn.png", off = "CheckButtonOff.png"})
        :setButtonSelected(true)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 22, color = display.COLOR_WHITE}))
        :setButtonLabelOffset(0, -50)
        :setButtonLabelAlignment(display.CENTER)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :align(display.LEFT_CENTER, display.cx - 240, display.cy + 160)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton)

    local bannerAdButton
    local bannerAdVisible = false
    bannerAdButton = cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show Banner Ad", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            if not bannerAdVisible then
                if checkBoxButton:isButtonSelected() then
                    cc.ad:doCommand{command = "banner", args = {id = PUNCHBOX_AD_SDK_BANNER_ID, position = "top"}}
                else
                    cc.ad:doCommand{command = "banner", args = {id = PUNCHBOX_AD_SDK_BANNER_ID, position = "bottom"}}
                end
                bannerAdButton:setButtonLabelString("Remove Banner Ad")
                bannerAdVisible = true
            else
                cc.ad:remove()
                bannerAdButton:setButtonLabelString("Show Banner Ad")
                bannerAdVisible = false
            end
        end)
        :pos(display.cx + 100, display.cy + 160)
        :addTo(self)

    -- use EventProxy, ensure remove the listener when leave current the scene
    local proxy = cc.EventProxy.new(cc.ad, self)
    proxy:addEventListener(cc.ad.events.RECEIVED,  function(event)
        resultLabel:setString("result: RECEIVED")
    end)
    proxy:addEventListener(cc.ad.events.PRESENT,  function(event)
        resultLabel:setString("result: PRESENT")
    end)
    proxy:addEventListener(cc.ad.events.DISMISS,  function(event)
        resultLabel:setString("result: DISMISS")
    end)
    proxy:addEventListener(cc.ad.events.FAILED,  function(event)
        resultLabel:setString(string.format("result: FAILED, error: %s, error code: %s", event.error, event.errorCode))
        -- reset button label, when failed to load ad
        bannerAdButton:setButtonLabelString("Show Banner Ad")
        bannerAdVisible = false
    end)

    -- interstitial ad
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show Interstitial Ad", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            cc.ad:doCommand{command = "interstitial", args = {id = PUNCHBOX_AD_SDK_INTERSTITIAL_ID}}
        end)
        :pos(display.cx, display.cy)
        :addTo(self)

    -- more game ad
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Show More Game Ad", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 80)
        :onButtonClicked(function()
            cc.ad:doCommand{command = "moregame"}
        end)
        :pos(display.cx, display.cy - 160)
        :addTo(self)
end

function MainScene:initNoAd()
    cc.ui.UILabel.new({text = "PunchBox AD demo\n\nPlease run this demo on iOS or Android device.",
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
