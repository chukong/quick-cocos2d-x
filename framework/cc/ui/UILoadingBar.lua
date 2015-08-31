
local UILoadingBar = class("UILoadingBar", function()
	local node = cc.ClippingNode:create()
	node:setAnchorPoint(cc.p(0, 0))
	return node
end)

UILoadingBar.DIRECTION_LEFT_TO_RIGHT = 0
UILoadingBar.DIRECTION_RIGHT_TO_LEFT = 1

function UILoadingBar:ctor(params)
	self:setStencilSize_(cc.size(params.viewRect.width, params.viewRect.height))
	if params.scale9 then
		self.scale9 = true
		if string.byte(params.image) == 35 then
			self.bar = cc.Scale9Sprite:createWithSpriteFrameName(
				string.sub(params.image, 2), params.capInsets);
		else
			self.bar = cc.Scale9Sprite:createWithInsets(
				params.capInsets, params.image)
		end
		-- self.stencil:setContentSize(cc.size(params.viewRect.width, params.viewRect.height))		
		-- self:setClippingRegion(cc.rect(0, 0, params.viewRect.width, params.viewRect.height))
	else
		self.bar = display.newSprite(params.image)
	end

	self.direction_ = params.direction or UILoadingBar.DIRECTION_LEFT_TO_RIGHT

	self:setViewRect(params.viewRect)
	self.bar:setAnchorPoint(cc.p(0, 0))
	self.bar:setPosition(0, 0)
	self:setPercent(params.percent or 0)
	self:addChild(self.bar)
end

function UILoadingBar:setPercent(percent)
	local rect = cc.rect(self.viewRect_.x, self.viewRect_.y,
		self.viewRect_.width, self.viewRect_.height)
	local newWidth = rect.width*percent/100

	rect.x = 0
	rect.y = 0
	if self.scale9 then
		self.bar:setPreferredSize(cc.size(newWidth, rect.height))
		if UILoadingBar.DIRECTION_LEFT_TO_RIGHT ~= self.direction_ then
			self.bar:setPosition(rect.width - newWidth,	0)
		end
	else
		if UILoadingBar.DIRECTION_LEFT_TO_RIGHT == self.direction_ then
			rect.width = newWidth
			-- self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
			self:changeStencilSize_(cc.size(rect.width, rect.height))
		else
			rect.x = rect.x + rect.width - newWidth
			rect.width = newWidth
			-- self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
			self:changeStencilSize_(cc.size(rect.width, rect.height), true)
		end
	end
end

function UILoadingBar:setDirction(dir)
	self.direction_ = dir
	if UILoadingBar.DIRECTION_LEFT_TO_RIGHT ~= self.direction_ then
		if self.bar.setFlipX then
			self.bar:setFlipX(true)
		end
	end
end

function UILoadingBar:setViewRect(rect)
	self.viewRect_ = rect
	self.bar:setContentSize(rect.width, rect.height)
end

function UILoadingBar:setStencilSize_(size)
	self.stencil = display.newRect(size)
	self.stencil:setFill(true)
	self.stencil:setAnchorPoint(cc.p(0, 0))
	self.stencil:setLineColor(cc.c4f(1, 1, 0, 1))
	self:setStencil(self.stencil)
end

function UILoadingBar:changeStencilSize_(size, bRightToLeft)
	self.stencil:setSize(size)
	if bRightToLeft then
		self.stencil:setPosition((self.viewRect_.width - size.width)/2, 0)
	else
		self.stencil:setPosition(-self.viewRect_.width/2 + size.width/2, 0)
	end
end

return UILoadingBar
