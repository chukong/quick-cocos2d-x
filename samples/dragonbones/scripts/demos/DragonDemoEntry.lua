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

function DragonDemoEntry:_onChangeAnimation()
	_aniIndex = _aniIndex + 1
	if _aniIndex > #_ANIMATION_LIST then
		_aniIndex = _aniIndex - #_ANIMATION_LIST
	end

	self._db:gotoAndPlay(_ANIMATION_LIST[_aniIndex])
end

function DragonDemoEntry:_onMovement(evtType, movId)
	printf("DragonDemoEntry:_onMovement eventType:%s, movId:%s", evtType, movId)
	if evtType == CCDragonBonesExtend.EVENTS.START then
		print("This is the first start!")
	end
	print("getLastAnimationName:", self._db:getAnimation():getLastAnimationName())
end

function DragonDemoEntry:_createDB()
	print("DragonDemoEntry", display.newDragonBones)
	--self:_createDBSync1()
	--self:_createDBSync2()
	self:_createDBAsync()
end

function DragonDemoEntry:_createDBSync1()
	self._db = display.newDragonBones({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			dragonBonesName="Dragon",
			armatureName="Dragon",
			aniName="",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
		:addMovementScriptListener(handler(self, self._onMovement))
	self:_updateAniList()
end

function DragonDemoEntry:_createDBSync2()
	self._db = display.newDragonBones({
			path="dragon",
			dragonBonesName="Dragon",
			armatureName="Dragon",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
		:addMovementScriptListener(handler(self, self._onMovement))
	self:_updateAniList()
end

function DragonDemoEntry:_createDBAsync()
	local manager = CCDBManager:getInstance()
	-- factory:loadDataFiles(
	-- 		"dragon/skeleton.xml", 
	-- 		"dragon/texture.xml",
	-- 		"Dragon")
	-- factory:loadSkeletonFile("dragon/skeleton.xml", "Dragon")
	-- factory:loadTextureAtlasFile("dragon/texture.xml", "Dragon")

	display.loadDragonBonesDataFiles("dragon/skeleton.xml",
		"dragon/texture.xml", "Dragon",
			function(evt)
				print("async done")
				print(evt)
				self._db = display.newDragonBones({
						dragonBonesName="Dragon",
						armatureName="Dragon",
					})
					:addTo(self, 10)
					:pos(display.cx,100)
					:addMovementScriptListener(handler(self, self._onMovement))
				self:_updateAniList()
			end)
	-- manager:loadDataFilesAsync(
	-- 		"dragon/skeleton.xml", 
	-- 		"dragon/texture.xml",
	-- 		"Dragon",
	-- 		function(evt)
	-- 			print("async done")
	-- 			print(evt)
	-- 			self._db = display.newDragonBones({
	-- 					dragonBonesName="Dragon",
	-- 					armatureName="Dragon",
	-- 				})
	-- 				:addTo(self, 10)
	-- 				:pos(display.cx,100)
	-- 				:addMovementScriptListener(handler(self, self._onMovement))
	-- 			self:_updateAniList()
	-- 		end)
end

function DragonDemoEntry:_updateAniList()
	local aniList = self._db:getAnimationList()
	for i=0,aniList:count()-1 do
		_ANIMATION_LIST[#_ANIMATION_LIST+1] = aniList:objectAtIndex(i):getCString()
	end
	self:_onChangeAnimation()
end

function DragonDemoEntry:onExit()
	DragonDemoEntry.super.onExit(self)
	print("DragonDemoEntry onExit")
	self:unscheduleUpdate()
	self._db:removeMovementScriptListener()
	self._db:removeSelf(true)
	self._db = nil
	_aniIndex = 0
end

return DragonDemoEntry
