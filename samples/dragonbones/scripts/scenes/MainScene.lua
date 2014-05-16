local MovementEventType =
{
	START = 0,
	COMPLETE = 1,
	LOOP_COMPLETE = 2,
}

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    self.animationNames = {"stand", "walk", "jump", "fall"}
    local manager = CCArmatureDataManager:sharedArmatureDataManager()
    manager:addArmatureFileInfo("Dragon.png", "Dragon.plist", "Dragon.xml")

    self.layer = display.newLayer()
    self:addChild(self.layer)

    local button = display.newSprite("#AddCoinButton.png", display.right - 100, display.bottom + 270)
    self:addChild(button)
    self.addButtonBoundingBox = button:getBoundingBox()

    local button = display.newSprite("#RemoveCoinButton.png", display.right - 100, display.bottom + 100)
    self:addChild(button)
    self.removeButtonBoundingBox = button:getBoundingBox()

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

    self.dragons = {}
    self.state = "IDLE"
end

function MainScene:onTouch(event, x, y)
    if event == "began" then
        local p = CCPoint(x, y)
        if self.addButtonBoundingBox:containsPoint(p) then
            self.state = "ADD"
        elseif self.removeButtonBoundingBox:containsPoint(p) then
            self.state = "REMOVE"
        else
            self.state = "IDLE"
        end
        return true
    elseif event ~= "moved" then
        self.state = "IDLE"
    end
end

function MainScene:addDragon()
    local dragon = CCArmature:create("Dragon")
	-- dragon:connectMovementEventSignal(function(__evtType, __moveId)
	-- 		printInfo("movement, evtType: %d, moveId: %s", __evtType, __moveId)
	-- 	end)
    local animation = dragon:getAnimation()
    animation:setSpeedScale(24 / 60) -- Flash fps is 24, cocos2d-x is 60
	local aniName = self.animationNames[math.random(1,4)]
    animation:play(aniName)
    dragon:setPosition(math.random(display.left, display.right), math.random(display.bottom, display.top))
    dragon:setScale(math.random(50, 100) / 100)
    self.layer:addChild(dragon)

    self.dragons[#self.dragons + 1] = dragon
    self.dragonsCount = #self.dragons
    self.label:setString(string.format("%05d", self.dragonsCount))
end

function MainScene:removeDragon()
    local dragon = self.dragons[self.dragonsCount]
	-- dragon:disconnectMovementEventSignal()
    dragon:removeSelf()
    table.remove(self.dragons, self.dragonsCount)
    self.dragonsCount = self.dragonsCount - 1
    self.label:setString(string.format("%05d", self.dragonsCount))
end

function MainScene:onEnterFrame(dt)
    if self.state == "ADD" then
        self:addDragon()
    elseif self.state == "REMOVE" and self.dragonsCount > 0 then
        self:removeDragon()
    end
end

function MainScene:onEnter()
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt) self:onEnterFrame(dt) end)
    self:scheduleUpdate_()
    self.layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
    self.layer:setTouchEnabled(true)
end

return MainScene
