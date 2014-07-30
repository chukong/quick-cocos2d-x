
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
		armatureName = "cyborg",
		skeletonName = "Cyborg",
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
		armatureName = "knight",
		skeletonName = "Knight",
	},
	{
		path = "motorcycle",
		armatureName = "motorcycleMan",
		skeletonName = "Motorcycle",
		textureName = "Motorcycle",
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
		textureName = "Shark",
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
		ui.newTTFLabelMenuItem({text="Add Dragon Sync" ,listener=handler(self, self._onSync)}),
		ui.newTTFLabelMenuItem({text="Add Dragon Async" ,listener=handler(self, self._onAsync)}),
		ui.newTTFLabelMenuItem({text="Add all animations Sync" ,listener=handler(self, self._onAllAniSync)}),
		ui.newTTFLabelMenuItem({text="Add all animations Async" ,listener=handler(self, self._onAllAniAsync)}),
		ui.newTTFLabelMenuItem({text="Remove all animation" ,listener=handler(self, self._onAllAniRemove)}),
	})
		:pos(display.left+140, display.cy)
		:addTo(self, 0)
	menu:alignItemsVertically()
end

function DragonAsyncLoading:_onSync()
	self:_onAllAniRemove()
	self:_createDBSync1()
	--self:_createDBSync2()
end

function DragonAsyncLoading:_onAsync()
	self:_onAllAniRemove()
	self:_createDBAsync1()
	--self:_createDBAsync2()
end

function DragonAsyncLoading:_onAllAniSync()
	self:_onAllAniRemove()
	dragonbones.loadDataList(_DB_FILES)
	self:_addAllDBs()
end

function DragonAsyncLoading:_onAllAniAsync()
	self:_onAllAniRemove()
	dragonbones.loadDataList(
		_DB_FILES,
		function(evt)
			print("async done")
			print(evt)
			self:_addAllDBs()
			CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
		end)
end

function DragonAsyncLoading:_onAllAniRemove()
	self:_removeAllDB()
	for __, value in ipairs(_DB_FILES) do
		if value.path ~= "dragon" then
			local obj = {}
			if value.skeletonName then
				obj.skeletonName = value.skeletonName
			else
				obj.skeletonName = value.armatureName
			end
			obj.textureName = value.textureName
			dragonbones.unloadData(obj)
		end
	end
	CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
	collectgarbage()
end

function DragonAsyncLoading:_createDBSync1()
	self._dbs[#self._dbs+1] = dragonbones.new({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			armatureName="Dragon",
			aniName="",
			aniName="",
		})
		:addTo(self, 10)
		:pos(display.cx,100)
	self:_playDB(self._dbs[#self._dbs])
end

function DragonAsyncLoading:_createDBSync2()
	self._dbs[#self._dbs+1] = dragonbones.new({
			path="dragon",
			armatureName="Dragon",
		})
		:addTo(self, -10)
		:pos(display.cx,100)
	self:_playDB(self._dbs[#self._dbs])
end

function DragonAsyncLoading:_createDBAsync1()
	dragonbones.new({
		path="dragon",
		armatureName="Dragon",
		handler=function(db)
			self._dbs[#self._dbs+1] = db:addTo(self, -10)
				:pos(display.cx,100)
			self:_playDB(db)
		end
	})
end

function DragonAsyncLoading:_createDBAsync2()
	dragonbones.loadData({
		skeleton="dragon/skeleton.xml",
		texture="dragon/texture.xml", 
		armatureName="Dragon",
		handler=function(evt)
			print("async done, evt:", evt)
			self._dbs[#self._dbs+1] = dragonbones.new({
					armatureName="Dragon",
				})
				:addTo(self, -10)
				:pos(display.cx,100)
			self:_playDB(self._dbs[#self._dbs])
		end})
end

function DragonAsyncLoading:_removeAllDB()
	for __, v in ipairs(self._dbs) do
		v:removeFromParentAndCleanup(true)
	end
	self._dbs = {}
end

function DragonAsyncLoading:_addAllDBs()
	for __, v in ipairs(_DB_FILES) do
		local db = dragonbones.new({
			armatureName = v.armatureName,
			animationiName = v.animationName,
			skeletonName = v.skeletonName,
			textureName = v.textureName,
			skinName = v.skinName,
		})
			:addTo(self, -10)
			:pos(#self._dbs*100+100,display.cy-100)
		self._dbs[#self._dbs+1] = db
		self:_playDB(db)
	end
end

function DragonAsyncLoading:_playDB(db)
	local aniList = db:getAnimations()
	local aniIndex = math.random(#aniList)
	db:gotoAndPlay(aniList[aniIndex])
end

function DragonAsyncLoading:onExit()
	DragonAsyncLoading.super.onExit(self)
	print("DragonAsyncLoading onExit")
	self:_onAllAniRemove()
end

return DragonAsyncLoading
