--- The Dragon Switch Clothes Demo
-- @author zrong(zengrong.net)
-- Creation 2014-07-08

local DragonSwitchClothes = class("DragonSwitchClothes", game.DragonBonesDemo)
local _TEXTURES = {
	"parts/clothes1",
	"parts/clothes2",
	"parts/clothes3",
	"parts/clothes4",
}

local _moveDirection = 0
local _isJumping = false
local _speedX = 0
local _speedY = 0
local _footY = 100
local _textureIndex = 1

function DragonSwitchClothes:ctor(...)
	self.mainTitle = "Dragon Switch Clothes"
	self:_createDB()
	DragonSwitchClothes.super.ctor(self, ...)
	self:_updateBehavior()
	self:scheduleUpdate(function(dt)
		self:_update(dt)
	end)
end

function DragonSwitchClothes:_addUI()
	DragonSwitchClothes.super._addUI(self)
	local menu = ui.newMenu({
		ui.newTTFLabelMenuItem({text="Move Left" ,listener=handler(self, self._onMoveLeft)}),
		ui.newTTFLabelMenuItem({text="Move Right" ,listener=handler(self, self._onMoveRight)}),
		ui.newTTFLabelMenuItem({text="Stop" ,listener=handler(self, self._onStop)}),
		ui.newTTFLabelMenuItem({text="Jump" ,listener=handler(self, self._onJump)}),
		ui.newTTFLabelMenuItem({text="Switch Clothes" ,listener=handler(self, self._onSwitchClothes)}),
	})
		:pos(display.left+100, display.cy)
		:addTo(self, 10)
	menu:alignItemsVertically()

end

function DragonSwitchClothes:_onMoveLeft()
	_moveDirection = -1;
	self:_updateBehavior()
end

function DragonSwitchClothes:_onMoveRight()
	_moveDirection = 1;
	self:_updateBehavior()
end

function DragonSwitchClothes:_onStop()
	_moveDirection = 0;
	self:_updateBehavior()
end

function DragonSwitchClothes:_onJump()
	if _isJumping then return end
	_speedY = 17;
	_isJumping = true;
	self._db:gotoAndPlay("jump")
end

function DragonSwitchClothes:_onSwitchClothes()
	_textureIndex = _textureIndex + 1
	if _textureIndex > #_TEXTURES then
		_textureIndex = _textureIndex - #_TEXTURES
	end

    self._db:setBoneTexture("clothes", _TEXTURES[_textureIndex], "Dragon");
end

function DragonSwitchClothes:_updateBehavior()
	if _isJumping then return end
	if _moveDirection == 0 then
		_speedX = 0;
		self._db:gotoAndPlay("stand");
	else
		_speedX = 6 * _moveDirection;
		self._db:setScaleX(-_moveDirection);
		self._db:gotoAndPlay("walk");
	end
end

function DragonSwitchClothes:_update(dt)
	if _speedX ~= 0 then
		self._db:setPositionX(self._db:getPositionX() + _speedX);
		if self._db:getPositionX()< 0 then
			self._db:setPositionX(0)
		elseif self._db:getPositionX() > display.width then
			self._db:setPositionX(display.width)
		end
	end
	if _isJumping then
		if _speedY <= 0 and _speedY - 1 < 0 then
			self._db:gotoAndPlay("fall")
		end
		_speedY = _speedY - 1;
	end
	if _speedY ~= 0 then
		self._db:setPositionY(self._db:getPositionY() + _speedY)
		if self._db:getPositionY() < _footY then
			self._db:setPositionY(_footY)
			_isJumping = false;
			_speedY = 0;
			self:_updateBehavior()
		end
	end
end

function DragonSwitchClothes:_createDB()
	self._db = dragonbones.new({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			armatureName="Dragon",
			aniName="",
			skeletonName="Dragon",
		})
		:addTo(self, 10)
		:pos(display.cx, _footY)
end

function DragonSwitchClothes:onExit()
	DragonSwitchClothes.super.onExit(self)
	print("DragonSwitchClothes onExit")
	self:unscheduleUpdate()
	self._db:removeFromParentAndCleanup(true)
	self._db = nil
	_moveDirection = 0
	_isJumping = false
	_speedX = 0
	_speedY = 0
	_footY = 100
	_textureIndex = 1
end

return DragonSwitchClothes
