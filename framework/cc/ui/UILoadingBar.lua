
local UILoadingBar = class("UILoadingBar", function()
	local node = cc.ClippingRegionNode:create()
	return node
end)

UILoadingBar.DIRECTION_LEFT_TO_RIGHT = 0
UILoadingBar.DIRECTION_RIGHT_TO_LEFT = 1

function UILoadingBar:ctor(params)
	if params.scale9 then
		self.scale9 = true
		if string.byte(params.image) == 35 then
			self.bar = cc.Scale9Sprite:createWithSpriteFrameName(
				string.sub(params.image, 2), params.capInsets);
		else
			self.bar = cc.Scale9Sprite:create(
				params.capInsets, params.image)
		end
		self:setClippingRegion(cc.rect(0, 0, params.viewRect.width, params.viewRect.height))
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
			self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
		else
			rect.x = rect.x + rect.width - newWidth
			rect.width = newWidth
			self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
		end
	end
end

function UILoadingBar:setDirction(dir)
	self.direction_ = dir
	if UILoadingBar.DIRECTION_LEFT_TO_RIGHT ~= self.direction_ then
		self.bar:setFlipX(true)
	end
end

function UILoadingBar:setViewRect(rect)
	self.viewRect_ = rect
	self.bar:setContentSize(rect.width, rect.height)
end

return UILoadingBar
