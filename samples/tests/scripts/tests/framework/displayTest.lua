
local DisplayTestScene = game.createSceneClass("DisplayTestScene")

function DisplayTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "addImageAsync",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function DisplayTestScene:runTest(name)
    local m = self[name .. "Test"]
    m(self)
end

function DisplayTestScene:addImageAsyncTest()
    if self.coin then
        self.coin:removeSelf()
        self.coin = nil
    end
    print("display.removeSpriteFrameByImageName(\"Coin0001.png\")")
    display.removeSpriteFrameByImageName("Coin0001.png")
    print("display.addImageAsync(\"Coin0001.png\")")

    display.addImageAsync("Coin0001.png", function(event, texture)
        printf("display.addImageAsync(\"Coin0001.png\") - event = %s, texture = %s", event, tostring(texture))
        self.coin = display.newSprite("Coin0001.png", display.left + 100, display.cy)
        self:addChild(self.coin)
    end)
end

return DisplayTestScene
