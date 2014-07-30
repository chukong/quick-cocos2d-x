--- The Dragon Chase Starling
-- @author zrong(zengrong.net)
-- Creation 2014-07-08

local DragonChaseStarling = class("DragonChaseStarling", game.DragonBonesDemo)

function DragonChaseStarling:ctor(...)
	self.mainTitle = "Dragon Chase Starling"
	self.subTitle = "Please touch screen..."

	self._head = nil
	self._armR = nil
	self._armL = nil

	self._speedX = 0
	self._touchX = 0
	self._touchY = 0
	self.__moveDirection = 0
	self._r = 0
	self._distance = 0
	self._isChasing = false

	self:_createDB()
	self:_createStarling()

	DragonChaseStarling.super.ctor(self, ...)
	self._touchScreen = display.newNode():addTo(self, 0)
	self._touchScreen:setCascadeBoundingBox(cc.rect(0,0,display.width, display.height))
	self._touchScreen:setTouchEnabled(true)
	self._touchScreen:addNodeEventListener(cc.NODE_TOUCH_EVENT, handler(self, self._onTouch))
end

function DragonChaseStarling:_update(dt)
    self:_checkDistance();
    self:_updateMove();
	self:_updateBones();
end

function DragonChaseStarling:_onTouch(evt)
	if evt.name == "began" then 
		if not self._isChasing then
			self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, handler(self, self._update))
			self:scheduleUpdate_()
			self._isChasing = true
		end
		return true 
	end
	if evt.name == "moved" then 
		self:_updatePosition(evt.x, evt.y)
	end
end

function DragonChaseStarling:_updatePosition(x, y)
    self._touchX = x
    self._touchY = y
    self._starlingBird:pos(x,y);
end

function DragonChaseStarling:_checkDistance()
    self._distance = self._db:getPositionX() - self._touchX;

    if self._distance<150 then
        self:_updateBehavior(1);
    elseif self._distance>190 then
        self:_updateBehavior(-1);
    else
        self:_updateBehavior(0);
	end
end

function DragonChaseStarling:_updateBones()
	local dbsize = self._db:getContentSize()
  	-- update the bones' pos or rotation
    self._r = math.pi + math.atan2(self._db:getPositionY() + 
		dbsize.height / 2-self._touchY , 
		self._touchX - self._db:getPositionX())
    if self._r > math.pi then
        self._r = self._r - math.pi * 2;
	end
    
    self._head.offset:setRotation(self._r*0.3);
    self._armR.offset:setRotation(self._r*0.8);
	self._armL.offset:setRotation(self._r*1.5);
    --printf("updateBones %.2f", self._r*0.2*(180 / math.pi))
    self._starlingBird:setRotation(self._r*0.2*(180/math.pi));
end

function DragonChaseStarling:_updateMove()
    if self._speedX ~= 0 then
        self._db:setPositionX(self._db:getPositionX() + self._speedX)
        if self._db:getPositionX() < 0 then
            self._db:setPositionX(0);
        elseif self._db:getPositionX() > display.width then
            self._db:setPositionX(display.width);
		end
	end
end

function DragonChaseStarling:_updateBehavior(direction)
    if self.__moveDirection == direction then return end
    self.__moveDirection = direction
    if self.__moveDirection == 0 then
        self._speedX = 0;
        self._db:gotoAndPlay("stand")
    else
        self._speedX = 6 * self.__moveDirection;
		self._db:gotoAndPlay("walk")
	end
end

function DragonChaseStarling:_createDB()
	print("--- creaetDB")
	self._db = dragonbones.new({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			armatureName="Dragon",
			aniName="",
			skeletonName="Dragon",
		})
		:addTo(self, 10)
		:pos(display.cx, display.cy-200)

	self._db:setContentSize(cc.size(373,377))
    self._head = self._db:getArmature():getBone("head")
    self._armR = self._db:getArmature():getBone("armUpperR")
    self._armL = self._db:getArmature():getBone("armUpperL")
end

function DragonChaseStarling:_createStarling()
	self._starlingBird = display.newSprite("starling.png")
		:pos(display.left + 20, display.cy)
		:addTo(self, 10)
end

function DragonChaseStarling:onExit()
	DragonChaseStarling.super.onExit(self)
	print("DragonChaseStarling onExit")
	self:removeNodeEventListenersByEvent(cc.NODE_ENTER_FRAME_EVENT)
	self:unscheduleUpdate()
	self._db:removeFromParentAndCleanup(true)
	self._db = nil
	self._touchScreen:setTouchEnabled(false)
	self._touchScreen:removeNodeEventListenersByEvent(cc.NODE_TOUCH_EVENT)
	self._touchScreen:removeFromParentAndCleanup(true)
	self._touchScreen = nil
	self._starlingBird:removeFromParentAndCleanup(true)
	self._starlingBird = nil

	self._head = nil
	self._armR = nil
	self._armL = nil
	
	self._speedX = 0
	self._touchX = 0
	self._touchY = 0
	self.__moveDirection = 0
	self._r = 0
	self._distance = 0
	self._isChasing = false
end

return DragonChaseStarling
