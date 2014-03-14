
local WelcomeScene = class("WelcomeScene", function()
    return display.newScene("WelcomeScene")
end)

function WelcomeScene:ctor()
    local bg = CCLayerColor:create(ccc4(255, 255, 255, 255))
    self:addChild(bg)

    self:createLogo()
    self:createBannderAds()
    self:createButtons()
    self:createCopyright()

    local recents = json.decode(_G["OPEN_RECENTS"])
    if type(recents) ~= "table" then
        recents = {}
    end
    self:createOpenRecents(recents)
end

function WelcomeScene:createOpenRecents(recents)
end

function WelcomeScene:createLogo()
    display.newSprite("LogoBanner.png")
        :align(display.LEFT_TOP, display.left + 20, display.top - 4)
        :addTo(self)
end

function WelcomeScene:createBannderAds()
    self.bannerAds_ = {}

    local banner = display.newSprite("BannerAd_02.png")
    local size = banner:getContentSize()
    banner:pos(display.cx, display.top - size.height / 2 - 50)
        :addTo(self)
end

function WelcomeScene:createLine()
    local line = CCLayerColor:create(ccc4(238, 238, 238, 255), display.width - 80, 1)
    line:setPosition(display.left + 20, display.top - 280)
    self:addChild(line)
end

function WelcomeScene:createButtons()
    local left = display.left + 114
    local top = display.top - 386

    local newProjectButton = cc.ui.UIPushButton.new("NewProjectButton_zh.png")
        :pos(left, top)
        :addTo(self)

    local openProjectButton = cc.ui.UIPushButton.new("OpenProjectButton_zh.png")
        :pos(left + 200, top)
        :addTo(self)

    local listSamplesButton = cc.ui.UIPushButton.new("ListSamplesButton_zh.png")
        :pos(left + 400, top)
        :addTo(self)

    local openCommunityButton = cc.ui.UIPushButton.new("OpenCommunityButton_zh.png")
        :pos(left, top - 140)
        :addTo(self)

    local learnButton = cc.ui.UIPushButton.new("LearnButton_zh.png")
        :pos(left + 200, top - 140)
        :addTo(self)
end

function WelcomeScene:createCopyright()
    local label = ui.newTTFLabel({
        text = "Copyright (c) 2012-2013 quick-x.com, licensed under MIT.",
        size = 14,
        color = ccc3(180, 180, 180),
        x = display.cx,
        y = display.bottom + 30,
        align = ui.TEXT_ALIGN_CENTER,
    })
    self:addChild(label)
end

-- listeners

function WelcomeScene:onNewProjectButtonClicked()
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_NEW_PROJECT")
end

function WelcomeScene:onOpenButtonClicked()
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_OPEN")
end

function WelcomeScene:onSamplesButtonClicked()
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_SAMPLES")
end

function WelcomeScene:onGetStartedButtonClicked()
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_GET_STARTED")
end

return WelcomeScene
