--- The Filters Sample
-- @author zrong(zengrong.net)
-- Creation 2014-04-09

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

MainScene._FILTERS = {
	-- colors
	{"GRAY", {}},
	{"RGB",{}},
	{"HUE", {}},
	{"BRIGHTNEWS", {}},
	{"SATURATION", {}},
	{"CONTRAST", {}},
	{"EXPOSURE", {}},
	{"GAMMA", {}},
	{"HAZE", {}},
	{"SEPIA", {}},
	-- blurs
	{"GAUSSIAN_VBLUR", {}},
	{"GAUSSIAN_HBLUR", {}},
	{"ZOOM_BLUR", {}},
	{"MOTION_BLUR", {}},
	-- others
	{"SHARPEN", {}},
}

function MainScene:ctor()
	self:_addUI()
	self:_createFilters()
	self:_showFilter()
end

function MainScene:_addUI()
	cc.ui.UIPushButton.new("close.png")
		:align(display.RIGHT_BOTTOM, display.width, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onClose))
	
	self._prevBtn = cc.ui.UIPushButton.new({normal="b1.png",pressed="b2.png"})
		:align(display.BOTTOM_CENTER, display.cx-100, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onPrev))
	self._resetBtn = cc.ui.UIPushButton.new({normal="r1.png",pressed="r2.png"})
		:align(display.BOTTOM_CENTER, display.cx, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onReset))
	self._nextBtn = cc.ui.UIPushButton.new({normal="f1.png",pressed="f2.png"})
		:align(display.BOTTOM_CENTER, display.cx+100, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onNext))

	self._title = ui.newTTFLabel({
		text="Filters test",
	})
		:align(display.CENTER, display.cx, display.top-50)
		:addTo(self, 10)
end

function MainScene:_createFilters()
	self._curFilter = 1
	self._filterCount = #self._FILTERS
end

function MainScene:_showFilter()
	if self._filterSprite then
		self._filterSprite:removeSelf()
		self._filterSprite = nil
	end
	local __curFilter = MainScene._FILTERS[self._curFilter]
	-- self._filterSprite = display.newFilteredSprite("helloworld.png", unpack(__curFilter))
	local __filters, __params = unpack(__curFilter)
	if __params and #__params == 0 then
		__params = nil
	end
	self._filterSprite = display.newFSprite("helloworld.png", __filters, __params)
		:align(display.CENTER, display.cx, display.cy)
		:addTo(self, 10)
end

function MainScene:_onPrev()
	self._curFilter = self._curFilter - 1
	if self._curFilter <= 0 then
		self._curFilter = self._filterCount
	end
	self:_showFilter()
end

function MainScene:_onReset()
end

function MainScene:_onNext()
	self._curFilter = self._curFilter + 1
	if self._curFilter > self._filterCount then
		self._curFilter = 1
	end
	self:_showFilter()
end

function MainScene:_onClose()
	game.exit()
end

return MainScene
