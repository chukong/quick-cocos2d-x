--- The Dragon Entry Demo
-- @author zrong(zengrong.net)
-- Creation 2014-04-28

local DragonDemoEntry = class("DragonEntryDemo", game.DragonBonesDemo)

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

function DragonDemoEntry:_onMovement(evtType, movId)
	printf("DragonDemoEntry:_onMovement eventType:%s, movId:%s", evtType, movId)
	if evtType == CCDragonBonesExtend.EVENTS.START then
		print("This is the first start!")
	end
end

function DragonDemoEntry:_createDB()
	print("DragonDemoEntry", display.newDragonBones)
	self._db = display.newDragonBones({
			skeleton="dragon/skeleton.xml",
			texture="dragon/texture.xml",
			dragonBonesName="Dragon",
			armatureName="Dragon",
			aniName="",
		})
		:addTo(self, 10)
		:pos(display.cx, display.cy-200)
		:addMovementScriptListener(handler(self, self._onMovement))
	self._db:gotoAndPlay("walk")
end

return DragonDemoEntry
