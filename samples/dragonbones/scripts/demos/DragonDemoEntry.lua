--- The Dragon Entry Demo
-- @author zrong(zengrong.net)
-- Creation 2014-04-28
-- Modification 2014-07-08

local DragonDemoEntry = class("DragonDemoEntry", game.DragonBonesDemo)

local _ANIMATION_LIST = {}
local _aniIndex = 0

function DragonDemoEntry:ctor(...)
	self.mainTitle = "Dragon Demo Entry"
	self:_createDB()
	DragonDemoEntry.super.ctor(self, ...)
end

function DragonDemoEntry:_addUI()
	DragonDemoEntry.super._addUI(self)
	local menu = ui.newMenu({
		ui.newTTFLabelMenuItem({text="Stop" ,listener=handler(self, self._onStop)}),
		ui.newTTFLabelMenuItem({text="Play" ,listener=handler(self, self._onPlay)}),
		ui.newTTFLabelMenuItem({text="SetColor(20,90,50)" ,listener=handler(self, self._onSetColor)}),
		ui.newTTFLabelMenuItem({text="SetOpacity(128)" ,listener=handler(self, self._onSetOpacity)}),
		ui.newTTFLabelMenuItem({text="Change Animation" ,listener=handler(self, self._onChangeAnimation)}),
	})
		:pos(display.left+100, display.cy)
		:addTo(self, 0)
	menu:alignItemsVertically()
end

function DragonDemoEntry:_onStop()
	self._db:getAnimation():stop()
end

function DragonDemoEntry:_onPlay()
	self._db:getAnimation():play()
end

function DragonDemoEntry:_onSetOpacity()
	self._db:setOpacity(128)
end

function DragonDemoEntry:_onSetColor()
	self._db:setColor(cc.c3(200,23,120))
end

function DragonDemoEntry:_onChangeAnimation()
	_aniIndex = _aniIndex + 1
	if _aniIndex > #_ANIMATION_LIST then
		_aniIndex = _aniIndex - #_ANIMATION_LIST
	end

	self._db:gotoAndPlay(_ANIMATION_LIST[_aniIndex])
end

function DragonDemoEntry:_onMovement(evtType, movId)
	printf("DragonDemoEntry:_onMovement eventType:%s, movId:%s", evtType, movId)
	if evtType == cc.DragonBonesNode.EVENTS.START then
		print("This is the first start!")
	end
	print("getLastAnimationName:", self._db:getAnimation():getLastAnimationName())
end

function DragonDemoEntry:_createDB()
	self._db = dragonbones.new({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			armatureName="Dragon",
			aniName="",
			skeletonName="Dragon",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
		:addMovementScriptListener(handler(self, self._onMovement))
	self:_updateAniList()
end

function DragonDemoEntry:_updateAniList()
	_ANIMATION_LIST = self._db:getAnimations()
	self:_onChangeAnimation()
end

function DragonDemoEntry:onExit()
	DragonDemoEntry.super.onExit(self)
	print("DragonDemoEntry onExit")
	self:unscheduleUpdate()
	self._db:removeMovementScriptListener()
	self._db:removeFromParentAndCleanup(true)
	self._db = nil
	_aniIndex = 0
end

return DragonDemoEntry
