
local SampleScene = class("SampleScene", function()
    return display.newScene("SampleScene")
end)

function SampleScene:ctor()
    self.ccs = {}
    self.ccs.TouchEventType = 
    {
        began = 0,
        moved = 1,
        ended = 2,
        canceled = 3,
    }
    self.samples     = require(__G__QUICK_PATH__ .. "/samples/samples.lua")
    self.sampleIndex = 1
    local bg         = CCLayerColor:create(ccc4(255, 255, 255, 255))
    self:addChild(bg)

    self:createLogo()
    self:createPageView()
    self:createCopyright()
end

function SampleScene:createLogo()
    cc.ui.UIPushButton.new("LogoBanner.png")
        :onButtonClicked(function() 
            CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_APP") 
        end)
        :align(display.LEFT_TOP, display.left + 20, display.top - 4)
        :addTo(self, 1)
end

function SampleScene:createCopyright()
    local label = ui.newTTFLabel({
        text = "Copyright (c) 2012-2014 chukong-inc.com, licensed under MIT.",
        size = 14,
        color = ccc3(144, 144, 144),
        x = display.cx,
        y = display.bottom + 24,
        align = ui.TEXT_ALIGN_CENTER,
    })
    self:addChild(label)
end

function SampleScene:createPageView()

    local originLeft  = display.left + 150
    local left        = originLeft
    local originTop   = display.top - 180
    local top         = originTop
    
    local vMargin     = 20
    local hMargin     = 30
    
    local imageWidth  = 200
    local imageHeight = 150

    local sampleCount = #self.samples
    local maxNum      = 12
    
    local pageCount = math.ceil(sampleCount / maxNum)
    local pageSize  = CCSize(display.width - 40 ,display.height - 50)
    local pageView  = PageView:create()
    pageView:setTouchEnabled(true)
    pageView:setSize(pageSize)
    pageView:setAnchorPoint(ccp(0.5,0.5))
    pageView:setPosition(CCPoint(display.width / 2, display.height / 2))
    
    for pageCount = 1, pageCount do
        local layout = Layout:create()
        layout:setSize(pageSize)
        
        top = originTop
        for i = 1, 3 do
            for j = 1, 4 do
                local sample = self.samples[self.sampleIndex]
                self.sampleIndex = self.sampleIndex + 1

                if sample ~= nil then
                    layout:addChild(self:createDemoTitle(sample, left, top+90))
                    layout:addChild(self:createDemoDescription(sample ,left ,top+70))
                    layout:addChild(self:createDemoButton(sample, left, top))
                else
                    break
                end
                left = left + vMargin + imageWidth
            end

            left = originLeft
            top  = top - hMargin - imageHeight
        end

        pageView:addPage(layout)
    end 

    local uiLayer = TouchGroup:create()
    uiLayer:addWidget(pageView)
    self:addChild(uiLayer)
end

-- helper

function SampleScene:createDemoTitle(sample, x, y)
    local title = Label:create()
    title:setText(sample.title)
    title:setFontSize(14)
    title:setFontName("Monaco")
    title:setColor(ccc3(144,144,144))
    title:setPosition(ccp(x, y))
    return title
end

function SampleScene:createDemoDescription(sample, x, y)
    local description = Label:create()
    description:setText(sample.description)
    description:setFontSize(12)
    description:setColor(ccc3(50,144,144))
    description:setPosition(ccp(x, y))
    return description
end

function SampleScene:createDemoButton(sample, x, y)
    function onButtonClick(sender,eventType)
        if eventType == self.ccs.TouchEventType.ended then
            local configPath = __G__QUICK_PATH__ .. sample.path .. "/scripts/config.lua"
            package.loaded[configPath] = nil
            require(configPath)
            local args = {
                "-workdir",
                __G__QUICK_PATH__ .. sample.path,
                "-size",
                CONFIG_SCREEN_WIDTH.."x"..CONFIG_SCREEN_HEIGHT,
                "-" .. CONFIG_SCREEN_ORIENTATION,
            }
            self.projectArgs = CCString:create(json.encode(args))
            CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_OPEN_PROJECT_ARGS",self.projectArgs)
        end
    end

    local demoImage = sample.image or "ListSamplesButton_zh.png"
    local button = Button:create()
    button:setTouchEnabled(true)
    button:setScale9Enabled(false)
    button:loadTextures(demoImage, demoImage, "")
    button:setPosition(CCPoint(x, y))
    button:addTouchEventListener(onButtonClick)
    return button
end


return SampleScene
