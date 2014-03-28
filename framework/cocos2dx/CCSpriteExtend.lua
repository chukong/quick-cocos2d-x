
CCSpriteExtend = class("CCSpriteExtend", CCNodeExtend)
CCSpriteExtend.__index = CCSpriteExtend

function CCSpriteExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCSpriteExtend)
    return target
end

function CCSpriteExtend:playAnimationOnce(animation, removeWhenFinished, onComplete, delay)
    return transition.playAnimationOnce(self, animation, removeWhenFinished, onComplete, delay)
end

function CCSpriteExtend:playAnimationForever(animation, delay)
    return transition.playAnimationForever(self, animation, delay)
end

-- NOTE!!! The method is very slowly! Please use it in carefully.
-- @param __point A coordinate for color.
-- @param __convertToNodeSpace Optional, default is true, convert a coordinate to node space from world space.
-- @param __isFloat Optional, default is false, convert a coordinate to node space from world space.
function CCSpriteExtend:getColor(__point, __convertToNodeSpace, __isFloat)
	if __convertToNodeSpace == nil then
		__convertToNodeSpace = true
	end
	if __convertToNodeSpace then
		__point = self:convertToNodeSpace(__point)
	end
	-- Create a new Texture to get the pixel datas.
	local __size = self:getContentSize()
	local __rt = CCRenderTexture:create(__size.width, __size.height)
	-- Hold the old anchor and position to restore it late on.
	local __oldAnchor = self:getAnchorPoint()
	local __oldPos = self:getPositionInCCPoint()
	-- Move the sprite to left bottom.
	self:align(display.LEFT_BOTTOM, 0,0)
	--print("getColor:", __point.x, __point.y, __size.width, __size.height)
	-- Render the sprite to get a new texture.
	__rt:begin();
	self:visit()
	__rt:endToLua();
	-- Restore the original anchor and position.
	self:setAnchorPoint(__oldAnchor)
	self:setPosition(__oldPos)
	local __img = __rt:newCCImage(false)
	local __color = nil
	if __isFloat then
		__color = __img:getColor4F(__point.x, __point.y)
	else
		__color = __img:getColor4B(__point.x, __point.y)
	end
	return __color, __rt
end

-- Only get a alpha value.
function CCSpriteExtend:getColorAlpha(__point, __convertToNodeSpace, __isFloat)
	local color = self:getColor(__point, __convertToNodeSpace, __isFloat)
	return color.a
end
