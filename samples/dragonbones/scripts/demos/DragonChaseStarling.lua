--- The Dragon Chase Starling
-- @author zrong(zengrong.net)
-- Creation 2014-07-08

local DragonChaseStarling = class("DragonChaseStarling", game.DragonBonesDemo)

local _head = nil
local _armR = nil
local _armL = nil

local _speedX = 0
local _touchX = 0
local _touchY = 0
local _moveDirection = 0
local _r = 0
local _distance = 0
local _isChasing = false

function DragonChaseStarling:ctor(...)
	self.mainTitle = "Dragon Chase Starling"
	self.subTitle = "Please touch screen..."
	self:_createDB()
	self:_createStarling()
	DragonChaseStarling.super.ctor(self, ...)
	self._touchScreen = display.newNode():addTo(self, 0)
	self._touchScreen:setCascadeBoundingBox(cc.rect(0,0,display.width, display.height))
	self._touchScreen:setTouchEnabled(true)
	self._touchScreen:addTouchEventListener(handler(self, self._onTouch))
end

function DragonChaseStarling:_update(dt)
    self:_checkDistance();
    self:_updateMove();
	self:_updateBones();
end

function DragonChaseStarling:_onTouch(event,x, y, px, py)
	if event == "began" then 
		if not _isChasing then
			self:scheduleUpdate(handler(self, self._update));
			_isChasing = true
		end
		return true 
	end
	if event == "moved" then 
		self:_updatePosition(x, y)
	elseif event == "ended" then
	end
end

function DragonChaseStarling:_updatePosition(x, y)
    _touchX = x
    _touchY = y
    self._starlingBird:pos(x,y);
end

function DragonChaseStarling:_checkDistance()
    _distance = self._db:getPositionX() - _touchX;

    if _distance<150 then
        self:_updateBehavior(1);
    elseif _distance>190 then
        self:_updateBehavior(-1);
    else
        self:_updateBehavior(0);
	end
end

function DragonChaseStarling:_updateBones()
	local dbsize = self._db:getContentSize()
  	-- update the bones' pos or rotation
    _r = math.pi + math.atan2(self._db:getPositionY() + 
		dbsize.height / 2-_touchY , 
		_touchX - self._db:getPositionX())
    if _r > math.pi then
        _r = _r - math.pi * 2;
	end
    
    _head.offset:setRotation(_r*0.3);
    _armR.offset:setRotation(_r*0.8);
	_armL.offset:setRotation(_r*1.5);
    -- print("updateBones %.2f", _r*0.2*(180 / math.pi));
    self._starlingBird:setRotation(_r*0.2*(180/math.pi));
end

function DragonChaseStarling:_updateMove()
    if _speedX ~= 0 then
        self._db:setPositionX(self._db:getPositionX() + _speedX)
        if self._db:getPositionX() < 0 then
            self._db:setPositionX(0);
        elseif self._db:getPositionX() > display.width then
            self._db:setPositionX(display.width);
		end
	end
end

function DragonChaseStarling:_updateBehavior(direction)
    if _moveDirection == direction then return end
    _moveDirection = direction
    if _moveDirection == 0 then
        _speedX = 0;
        self._db:gotoAndPlay("stand")
    else
        _speedX = 6 * _moveDirection;
		self._db:gotoAndPlay("walk")
	end
end

function DragonChaseStarling:_createDB()
	print("DragonChaseStarling", display.newDragonBones)
	self._db = display.newDragonBones({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			dragonBonesName="Dragon",
			armatureName="Dragon",
			aniName="",
		})
		:addTo(self, 10)
		:pos(display.cx, display.cy-200)

	self._db:setContentSize(cc.size(373,377))
    _head = self._db:getArmature():getBone("head")
    _armR = self._db:getArmature():getBone("armUpperR")
    _armL = self._db:getArmature():getBone("armUpperL")
end

function DragonChaseStarling:_createStarling()
	self._starlingBird = display.newSprite("starling.png")
		:pos(display.left + 20, display.cy)
		:addTo(self, 10)
end

function DragonChaseStarling:onExit()
	DragonChaseStarling.super.onExit(self)
	print("DragonChaseStarling onExit")
	self:unscheduleUpdate()
	self._db:removeSelf(true)
	self._db = nil
	self._touchScreen:setTouchEnabled(false)
	self._touchScreen:removeTouchEventListener()
	self._touchScreen:removeSelf(self)
	self._touchScreen = nil
	self._starlingBird:removeSelf(true)
	self._starlingBird = nil

	_head = nil
	_armR = nil
	_armL = nil
	
	_speedX = 0
	_touchX = 0
	_touchY = 0
	_moveDirection = 0
	_r = 0
	_distance = 0
	_isChasing = false
end

return DragonChaseStarling
