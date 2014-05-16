
local SampleScene = class("SampleScene", function()
    return display.newScene("SampleScene")
end)

function SampleScene:ctor()
    self.samples     = require(__G__QUICK_PATH__ .. "/samples/samples.lua")
    self.sampleIndex = 1
    local bg         = CCLayerColor:create(ccc4(255, 255, 255, 255))
    self:addChild(bg)

    self:createLogo()
    self:createButtons()
    self:createCopyright()
end

function SampleScene:createLogo()
    cc.ui.UIPushButton.new("LogoBanner.png")
        :onButtonClicked(function() 
            CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_APP") 
        end)
        :align(display.LEFT_TOP, display.left + 20, display.top - 4)
        :addTo(self)
end

function SampleScene:createButtons()
    if self.uiLayer then
        self:removeChild(self.uiLayer, true)
    end
    self.uiLayer = display.newLayer()
    self:addChild(self.uiLayer)

    local function onButtonClicked(tag)
        self:createButtons()
    end

    local item = ui.newTTFLabelMenuItem({
        text = "NEXT",
        size = 20,
        color = ccc3(255, 0, 0),
        x = display.width - 30,
        y = display.BOTTOM_RIGHT + 20,
        listener = onButtonClicked,
    })

    -- 创建菜单并加入场景，否则菜单项不会工作
    local menu = ui.newMenu({item})
    self:addChild(menu)

    
    local originLeft = display.left + 150
    local left = originLeft
    local top = display.top - 150
    
    local vMargin = 20
    local hMargin = 30

    local imageWidth = 200
    local imageHeight = 150

    -- [[
    local c = 1
    local sampleCount = #self.samples
    local maxNum = 12

    for index=1,maxNum do

        if self.sampleIndex > sampleCount then 
            self.sampleIndex = 1
            break
        end

        local sample = self.samples[self.sampleIndex]
        self.sampleIndex = self.sampleIndex + 1


        local title = ui.newTTFLabel({
            text  = sample.title,
            size  = 14,
            color = ccc3(144, 144, 144),
            x     = left,
            y     = top+90,
            align = ui.TEXT_ALIGN_CENTER,
        })
        self.uiLayer:addChild(title)

        local description = ui.newTTFLabel({
            text  = sample.description,
            size  = 12,
            color = ccc3(50, 144, 144),
            x     = left,
            y     = top+75,
            align = ui.TEXT_ALIGN_CENTER
            })
        self.uiLayer:addChild(description)

        local button = cc.ui.UIPushButton.new(sample.image or "ListSamplesButton_zh.png")
            :onButtonClicked(function()
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
                SampleScene.projectArgs = CCString:create(json.encode(args))
                print(json.encode(args))
                CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_OPEN_PROJECT_ARGS",SampleScene.projectArgs)
            end)
            :pos(left, top)
            :addTo(self.uiLayer)

        --
        left = left + vMargin + imageWidth

        --
        if c >= 4 then
            c = 0
            left = originLeft
            top  = top - hMargin - imageHeight
        end
        c = c + 1
    end

    --]]

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

return SampleScene
