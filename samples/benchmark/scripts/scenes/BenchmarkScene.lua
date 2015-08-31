
local BenchmarkScene = class("BenchmarkScene", function()
    return display.newScene("BenchmarkScene")
end)

local random = math.random

function BenchmarkScene:ctor()
    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME, 10000)
    self:addChild(self.batch)

    self.layer = display.newLayer()
    self:addChild(self.layer)

    local button = display.newSprite("#AddCoinButton.png", display.right - 100, display.bottom + 270)
    self:addChild(button)
    self.addCoinButtonBoundingBox = button:getBoundingBox()

    local button = display.newSprite("#RemoveCoinButton.png", display.right - 100, display.bottom + 100)
    self:addChild(button)
    self.removeCoinButtonBoundingBox = button:getBoundingBox()

    local button = ui.newImageMenuItem({
        image = "#ExitButton.png",
        listener = function()
            game.exit()
        end,
        x = display.right - 100,
        y = display.top - 100,
    })
    local menu = ui.newMenu({button})
    self:addChild(menu)

    self.label = ui.newBMFontLabel({
        text = "00000",
        font = "UIFont.fnt",
        x = display.cx,
        y = display.top - 40,
    })
    self:addChild(self.label)

    self.coins = {}
    self.state = "IDLE"

    local frames = display.newFrames("CoinSpin%02d.png", 1, 8)
    local animation = display.newAnimation(frames, 0.4 / 8)
    display.setAnimationCache("Coin", animation)

    self.left   = display.left   + display.width / 4
    self.right  = display.right  - display.width / 4
    self.top    = display.top    - display.height / 3
    self.bottom = display.bottom + display.height / 3
end

function BenchmarkScene:onTouch(event, x, y)
    if event == "began" then
        local p = CCPoint(x, y)
        if self.addCoinButtonBoundingBox:containsPoint(p) then
            self.state = "ADD"
        elseif self.removeCoinButtonBoundingBox:containsPoint(p) then
            self.state = "REMOVE"
        else
            self.state = "IDLE"
        end
        return true
    elseif event ~= "moved" then
        self.state = "IDLE"
    end
end

function BenchmarkScene:addCoin()
    local coin = display.newSprite("#CoinSpin01.png")
    coin:playAnimationForever(display.getAnimationCache("Coin"))
    coin:setPosition(random(self.left, self.right), random(self.bottom, self.top))
    self.batch:addChild(coin)

    function coin:onEnterFrame(dt)
        local x, y = self:getPosition()
        x = x + random(-2, 2)
        y = y + random(-2, 2)
        self:setPosition(x, y)
    end

    self.coins[#self.coins + 1] = coin
    self.coinsCount = #self.coins
    self.label:setString(string.format("%05d", self.coinsCount))
end

function BenchmarkScene:removeCoin()
    local coin = self.coins[self.coinsCount]
    coin:removeSelf()
    table.remove(self.coins, self.coinsCount)
    self.coinsCount = self.coinsCount - 1
    self.label:setString(string.format("%05d", self.coinsCount))
end

function BenchmarkScene:onEnterFrame(dt)
    if self.state == "ADD" then
        self:addCoin()
    elseif self.state == "REMOVE" and self.coinsCount > 0 then
        self:removeCoin()
    end

    local coins = self.coins
    for i = 1, #coins do
        local coin = coins[i]
        coin:onEnterFrame(dt)
    end
end

function BenchmarkScene:onEnter()
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt) self:onEnterFrame(dt) end)
    self:scheduleUpdate_()
    self.layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
    self.layer:setTouchEnabled(true)
end

return BenchmarkScene
