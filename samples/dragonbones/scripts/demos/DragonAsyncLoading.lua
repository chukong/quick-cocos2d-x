
--- The Dragon Async Loading
-- @author zrong(zengrong.net)
-- Creation 2014-07-23

local DragonAsyncLoading = class("DragonAsyncLoading", game.DragonBonesDemo)

local _DB_FILES = 
{
	-- It is same as armatureName if ignore skeletonName.
	-- path is a directory name, it MUST in search pathes.
	{
		path = "cyborg",
		armatureName = "Cyborg",
	},
	{
		path = "dragon",
		armatureName = "Dragon",
	},
	-- armatureName and skeleonName are NOT always same.
	{
		path = "frameani",
		armatureName = "iceEffect",
		skeletonName = "FrameAnimation",
	},
	{
		path = "knight",
		armatureName = "Knight",
	},
	{
		path = "motorcycle",
		armatureName = "MotorcycleMan",
		skeletonName = "Motorcycle",
	},
	-- The name is case sensitive.
	{
		path = "robot",
		armatureName = "robot",
		skeletonName = "Robot",
	},
	-- The "shank" is a typo.
	{
		path = "shark",
		armatureName = "shank",
		skeletonName = "Shark",
	},
}
local _ANIMATION_LIST = {}
local _aniIndex = 0

function DragonAsyncLoading:ctor(...)
	self.mainTitle = "Dragon Async Loading"
	DragonAsyncLoading.super.ctor(self, ...)
	self._dbs = {}
end

function DragonAsyncLoading:_addUI()
	DragonAsyncLoading.super._addUI(self)
	local menu = ui.newMenu({
		ui.newTTFLabelMenuItem({text="Add Dragon in Sync" ,listener=handler(self, self._onSync)}),
		ui.newTTFLabelMenuItem({text="Add Dragon in Async" ,listener=handler(self, self._onAsync)}),
		ui.newTTFLabelMenuItem({text="Add all animations" ,listener=handler(self, self._onAllAniAsync)}),
		ui.newTTFLabelMenuItem({text="Remove all animation" ,listener=handler(self, self._onAllAniRemove)}),
		ui.newTTFLabelMenuItem({text="add cache" ,listener=handler(self, self._onAddCache)}),
		ui.newTTFLabelMenuItem({text="remove cache" ,listener=handler(self, self._onRemoveCache)}),
	})
		:pos(display.left+140, display.cy)
		:addTo(self, 0)
	menu:alignItemsVertically()
end

function DragonAsyncLoading:_onSync()
	self:_createDBSync1()
	--self:_createDBSync2()
end

function DragonAsyncLoading:_onAsync()
	self:_createDBAsync1()
	--self:_createDBAsync2()
end

function DragonAsyncLoading:_onAllAniAsync()
	self:_createAllDBsAsync1()
end

function DragonAsyncLoading:_onAllAniRemove()
	for __, value in ipairs(_DB_FILES) do
		local obj = {}
		if value.skeletonName then
			obj.skeletonName = value.skeletonName
		else
			obj.skeletonName = value.armatureName
		end
		obj.textureName = value.textureName
		dragonbones.unloadData(obj)
	end
	CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
	collectgarbage()
	do return end
	_aniIndex = _aniIndex + 1
	if _aniIndex > #_ANIMATION_LIST then
		_aniIndex = _aniIndex - #_ANIMATION_LIST
	end

	self._db:gotoAndPlay(_ANIMATION_LIST[_aniIndex])
end

function DragonAsyncLoading:_onAddCache()
	for __,v in ipairs(_DB_FILES) do
		CCTextureCache:sharedTextureCache():addImage(v.path.."/texture.png")
	end
	CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
end

function DragonAsyncLoading:_onRemoveCache()
	for __,v in ipairs(_DB_FILES) do
		CCTextureCache:sharedTextureCache():removeTextureForKey(v.path.."/texture.png")
	end
	CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
end

function DragonAsyncLoading:_onMovement(evtType, movId)
	do return end
	printf("DragonAsyncLoading:_onMovement eventType:%s, movId:%s", evtType, movId)
	if evtType == CCDragonBonesExtend.EVENTS.START then
		print("This is the first start!")
	end
	print("getLastAnimationName:", self._db:getAnimation():getLastAnimationName())
end

function DragonAsyncLoading:_createDBSync1()
	self._db = dragonbones.new({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			armatureName="Dragon",
			aniName="",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
		:addMovementScriptListener(handler(self, self._onMovement))
	self:_updateAniList()
end

function DragonAsyncLoading:_createDBSync2()
	self._db = dragonbones.new({
			path="dragon",
			armatureName="Dragon",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
		:addMovementScriptListener(handler(self, self._onMovement))
	self:_updateAniList()
end

function DragonAsyncLoading:_createDBAsync1()
	dragonbones.new({
		path="dragon",
		armatureName="Dragon",
		handler=function(db)
			self._db = db:addTo(self, 10)
				:pos(display.cx,100)
				:addMovementScriptListener(handler(self, self._onMovement))
			self:_updateAniList()
		end
	})
end

function DragonAsyncLoading:_createDBAsync2()
	dragonbones.loadData({
		skeleton="dragon/skeleton.xml",
		texture="dragon/texture.xml", 
		armatureName="Dragon",
		handler=function(evt)
			print("async done")
			print(evt)
			self._db = dragonbones.new({
					armatureName="Dragon",
				})
				:addTo(self, 10)
				:pos(display.cx,100)
				:addMovementScriptListener(handler(self, self._onMovement))
			self:_updateAniList()
		end})
end

function DragonAsyncLoading:_createAllDBsAsync1()
	dragonbones.loadDataList(
		_DB_FILES,
		function(evt)
			print("async done")
			print(evt)
			CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
		end)
end

function DragonAsyncLoading:_updateAniList()
	do return end
	local aniList = self._db:getAnimationList()
	for i=0,aniList:count()-1 do
		_ANIMATION_LIST[#_ANIMATION_LIST+1] = aniList:objectAtIndex(i):getCString()
	end
	self:_onChangeAnimation()
end

function DragonAsyncLoading:onExit()
	DragonAsyncLoading.super.onExit(self)
	print("DragonAsyncLoading onExit")
	self:unscheduleUpdate()
	--self._db:removeMovementScriptListener()
	--self._db:removeSelf(true)
	--self._db = nil
	--_aniIndex = 0
end

return DragonAsyncLoading
