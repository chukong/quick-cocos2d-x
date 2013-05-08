
local MoreGamesScene = class("MoreGamesScene", function()
    return display.newScene("MoreGamesScene")
end)

function MoreGamesScene:ctor()
    self.bg = display.newBackgroundSprite("#MenuSceneBg.png")
    self:addChild(self.bg)

    local editBoxBg = CCScale9Sprite:createWithSpriteFrameName("InputBox.png")
    local editBox = CCEditBox:create(CCSize(400, 64), editBoxBg)
    editBox:setPosition(display.cx, display.top - 100)
    editBox:registerScriptEditBoxHandler(function(eventType)
        self:onEdit({name = eventType, target = editBox})
    end)
    self:addChild(editBox)
end

function MoreGamesScene:onEdit(event)
    printf("EDITBOX %s, TEXT = %s", event.name, event.target:getText())
end

function MoreGamesScene:onRequest(event)
    local request = event.request
    printf("REQUEST state = %s, code = %s", tostring(request:getState()), tostring(request:getResponseStatusCode()))
    printf("REQUEST: %s", request:getResponseString())
end

function MoreGamesScene:onEnter()
    local url = "http://dualface.github.com/javascripts/generate-toc.js"
    local request = network.createHTTPRequest(function(event)
        self:onRequest(event)
    end, url)
    request:start()
end

return MoreGamesScene
