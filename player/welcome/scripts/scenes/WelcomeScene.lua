local WelcomeScene = class("WelcomeScene", function()
    return display.newScene("WelcomeScene")
end)

function getDemoData()
    -- body
    local demoDataList = {{id="demo1", text="<b>One Demo</b> <br/> <img src=\":/QuickIcon.png\"</img>"}
                  , {id="demo2", text="<b>Two Demo</b> <br/> <img src=\":/QuickIcon.png\"</img>"}}

    QT_INTERFACE("core.addDemoList", json.encode(demoDataList))
end

-- @return -p @packageName -f -r portrait -o @projectPath
function GET_CREATE_PROJECT_COMMAND_ARGS( projectPath, packageName, isPortrait )
    local screen = (isPortrait and " -r portrait") or " -r landscape"

    local cmd = "-f -p "..packageName..screen.." -o "..projectPath
    return  cmd, " "
end

function openDemo( demoId )
    QT_INTERFACE("core.openProject")
end

function LUA_Interface(messageId, messageData)
    print("messageId: ", messageId, "data : ", messageData)
    if messageId == "getDemoData" then
        getDemoData()
    elseif messageId == "core.openDemo" then
        openDemo(messageData)
    end
end

function PlayerLoginCallback(userName, password)
    print("Get username: ", userName, " passworld: ", password)
    -- return true, ""
    -- return false, "user name or password is invalid"
    return true, "user name or password is error"
end

function WelcomeScene:ctor()
    self.menu = nil -- self:createButtons()

    local bg = CCLayerColor:create(ccc4(255, 255, 255, 255))
    self:addChild(bg)

    self:createTitle()
    self:createDescription()
    self:createLogo()
    self:createLine()
    self:createButtons()
    self:createCopyright()

    local recents = json.decode(_G["OPEN_RECENTS"])
    if type(recents) ~= "table" then
        recents = {}
    end
    self:updateRecents(recents)
end

function WelcomeScene:updateRecents(recents)
end

function WelcomeScene:createTitle()
    local color = ccc3(102, 102, 102)
    local label = ui.newTTFLabel({
        text = "Welcome to quick-cocos2d-x",
        color = color,
        size = 46,
        x = display.left + 40,
        y = display.top - 60,
        align = ui.TEXT_ALIGN_LEFT,
    })
    self:addChild(label)

    local label = ui.newTTFLabel({
        text = "quick-cocos2d-x is a quick framework, based on cocos2d-x. Make mobile games in Lua.",
        color = color,
        size = 18,
        x = display.left + 40,
        y = display.top - 110,
        align = ui.TEXT_ALIGN_LEFT,
    })
    self:addChild(label)
end

function WelcomeScene:createDescription()
    local bg = CCLayerColor:create(ccc4(249, 249, 249, 255), 678, 88)
    bg:setPosition(display.left + 40, display.top - 240)

    local bar = CCLayerColor:create(ccc4(247, 123, 0, 255), 2, 88)
    bg:addChild(bar)

    local color = ccc3(102, 102, 102)
    local label = ui.newTTFLabel({
        text = [[cocos2d-x is a multi-platform 2D game engine in C++, based on cocos2d-iphone and licensed
under MIT. Now this engine has been expanded to iOS, Android, Bada, BlackBerry, Marmalade
and desktop operating systems like Linux, WindowsXP & Windows7.]],
        color = color,
        size = 15,
        x = 10,
        y = 44,
        align = ui.TEXT_ALIGN_LEFT,
        valign = ui.TEXT_VALIGN_CENTER,
        dimensions = CCSize(680, 88),
    })
    bg:addChild(label)

    self:addChild(bg)
end

function WelcomeScene:createLogo()
    local sprite = display.newSprite("#Logo.png")
    sprite:setPosition(display.right - 120, display.top - 110)
    self:addChild(sprite)
end

function WelcomeScene:createLine()
    local line = CCLayerColor:create(ccc4(238, 238, 238, 255), display.width - 80, 1)
    line:setPosition(display.left + 20, display.top - 280)
    self:addChild(line)
end

function WelcomeScene:createButtons()
    local x, y = display.left + 140, display.bottom + 150
    local newProjectButton = ui.newImageMenuItem({
        image = self:createButtonSprite("#NewProjectButton.png", "New Project"),
        imageSelected = self:createButtonSprite("#NewProjectButtonSelected.png", "New Project", 4, -4),
        x = x,
        y = y,
        listener = function() self:onNewProjectButtonClicked() end,
    })

    x = x + 220
    local openButton = ui.newImageMenuItem({
        image = self:createButtonSprite("#OpenButton.png", "Open"),
        imageSelected = self:createButtonSprite("#OpenButtonSelected.png", "Open", 4, -4),
        x = x,
        y = y,
        listener = function() self:onOpenButtonClicked() end,
    })

    x = x + 220
    local samplesButton = ui.newImageMenuItem({
        image = self:createButtonSprite("#SamplesButton.png", "Samples"),
        imageSelected = self:createButtonSprite("#SamplesButtonSelected.png", "Samples", 4, -4),
        x = x,
        y = y,
        listener = function() self:onSamplesButtonClicked() end,
    })

    x = x + 220
    local getStartedButton = ui.newImageMenuItem({
        image = self:createButtonSprite("#GetStartedButton.png", "Get Started"),
        imageSelected = self:createButtonSprite("#GetStartedButtonSelected.png", "Get Started", 4, -4),
        x = x,
        y = y,
        listener = function() self:onGetStartedButtonClicked() end,
    })

    self.menu = ui.newMenu({newProjectButton, openButton, samplesButton, getStartedButton})
    self:addChild(self.menu)
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
    QT_INTERFACE("core.newProject")
    --newProject();
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_NEW_PROJECT")
end

function WelcomeScene:onOpenButtonClicked()
    QT_INTERFACE("core.openProject")
    --openProject();
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_OPEN")
end

function WelcomeScene:onSamplesButtonClicked()
    QT_INTERFACE("core.openDemo")
    --openQuickDemoWithWebView();
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_SAMPLES")
end

function WelcomeScene:onGetStartedButtonClicked()
    QT_INTERFACE("core.openURL", "http://quick.cocoachina.com/wiki/doku.php?id=zh_cn")
    --openURL("http://wiki.quick-x.com/doku.php");
    CCNotificationCenter:sharedNotificationCenter():postNotification("WELCOME_GET_STARTED")
end

-- helper

function WelcomeScene:createButtonSprite(imageName, text, textOffsetX, textOffsetY)
    textOffsetX = textOffsetX or 0
    textOffsetY = textOffsetY or 0
    local sprite = display.newSprite(imageName)
    sprite:addChild(ui.newTTFLabel({
        text = text,
        color = ccc3(255, 255, 255),
        x = sprite:getContentSize().width / 2 + textOffsetX,
        y = 30 + textOffsetY,
        size = 22,
        align = ui.TEXT_ALIGN_CENTER,
    }))
    return sprite
end

return WelcomeScene
