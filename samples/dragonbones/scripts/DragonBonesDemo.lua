--- The DragonBonesCPP Sample
-- @author zrong(zengrong.net)
-- Creation 2014-04-28

local DragonBonesDemo = class("DragonBonesDemo", function()
    return display.newScene("DragonBonesDemo")
end)

function DragonBonesDemo:ctor(nextHandler, prevHandler, resetHandler, closeHandler)
	self._onNext = nextHandler
	self._onPrev = prevHandler
	self._onReset = resetHandler
	self._onClose = closeHandler
	self:_addUI()
	self:_showTitles()
end

function DragonBonesDemo:_addUI()
	cc.ui.UIPushButton.new("close.png")
		:align(display.RIGHT_BOTTOM, display.width, display.bottom)
		:addTo(self, 10)
		:onButtonClicked(self._onClose)
	
	self._prevBtn = cc.ui.UIPushButton.new({normal="b1.png",pressed="b2.png"})
		:align(display.BOTTOM_CENTER, display.cx-100, display.bottom)
		:addTo(self, 10)
		:onButtonClicked(self._onPrev)
	self._resetBtn = cc.ui.UIPushButton.new({normal="r1.png",pressed="r2.png"})
		:align(display.BOTTOM_CENTER, display.cx, display.bottom)
		:addTo(self, 10)
		:onButtonClicked(self._onReset)
	self._nextBtn = cc.ui.UIPushButton.new({normal="f1.png",pressed="f2.png"})
		:align(display.BOTTOM_CENTER, display.cx+100, display.bottom)
		:addTo(self, 10)
		:onButtonClicked(self._onNext)

	self._title = ui.newTTFLabel({
		text="DragonBonesCPP for quick-cocos2d-x",
	})
		:align(display.CENTER, display.cx, display.top-20)
		:addTo(self, 0)
end

function DragonBonesDemo:_showTitles()
	print("DragonBonesDemo:", self.mainTitle)
	if self.mainTitle then
		ui.newTTFLabel({text=self.mainTitle})
			:addTo(self, 0)
			:pos(display.cx, display.top-50)
	end
	if self.subTitle then
		ui.newTTFLabel({text=self.subTitle})
			:addTo(self, 0)
			:pos(display.cx, display.top-80)
	end
end

function DragonBonesDemo:onExit()
	print("DragonBonesDemo onExit")
	self._onNext = nil
	self._onPrev = nil
	self._onReset = nil
	self._onClose = nil
end

return DragonBonesDemo
