
cc.FileUtils.getInstance 		= cc.FileUtils.sharedFileUtils
cc.FileUtils.getStringFromFile  = cc.FileUtils.getFileData

display.addSpriteFrames 		= display.addSpriteFramesWithFile

cc.Node.setLocalZOrder			= cc.Node.setZOrder
cc.Node.setGlobalZOrder			= cc.Node.setZOrder

cc.c3b 							= ccc3
cc.c4b 							= ccc4


function cc.rect(_x,_y,_width,_height)
	local r = CCRect(_x,_y,_width,_height)
	r.x = _x
	r.y = _y
	r.width = _width
	r.height = _height

    return r
end

function cc.rectContainsPoint( rect, point )
    local ret = false
    
    if (point.x >= rect.x) and (point.x <= rect.x + rect.width) and
       (point.y >= rect.y) and (point.y <= rect.y + rect.height) then
        ret = true
    end

    return ret
end

function cc.rectIntersectsRect( rect1, rect2 )
    local intersect = not ( rect1.x > rect2.x + rect2.width or
                    rect1.x + rect1.width < rect2.x         or
                    rect1.y > rect2.y + rect2.height        or
                    rect1.y + rect1.height < rect2.y )

    return intersect
end

local setPos = cc.Node.setPosition
function cc.Node:setPosition(_x, _y)
	if "table" == type(_x) then
		setPos(self, _x.x, _x.y)
	elseif _y then
		setPos(self, _x, _y)
	else
		setPos(self, _x)
	end
end

local setSize = cc.Node.setContentSize
function cc.Node:setContentSize(_w, _h)
	if _h then
		setSize(self, _w, _h)
	else
		setSize(self, _w)
	end
end

local setScale9Size = CCScale9Sprite.setContentSize
function CCScale9Sprite:setContentSize(_w, _h)
	if _h then
		setScale9Size(self, CCSize(_w, _h))
	else
		setScale9Size(self, _w)
	end
end

local rect2t = function(_r)
	_r.x = _r.origin.x
	_r.y = _r.origin.y
	_r.width = _r.size.width
	_r.height = _r.size.height

	return _r
end

local getCascade = cc.Node.getCascadeBoundingBox
function cc.Node:getCascadeBoundingBox()
	local r = getCascade(self)
	return rect2t(r)
end

local getBound = cc.Node.getBoundingBox
function cc.Node:getBoundingBox()
	local r = getBound(self)
	return rect2t(r)
end



cc.EDITBOX_INPUT_FLAG_PASSWORD = kEditBoxInputFlagPassword


CCEditBox.registerScriptEditBoxHandler = CCEditBox.addEditBoxEventListener

cc.Node.removeFromParent 		= cc.Node.removeFromParentAndCleanup


cc.SpriteFrameCache.getInstance = cc.SpriteFrameCache.sharedSpriteFrameCache
cc.SpriteFrameCache.addSpriteFrames = cc.SpriteFrameCache.addSpriteFramesWithFile

if CCArmatureDataManager then
	ccs = {}
	ccs.ArmatureDataManager 		= CCArmatureDataManager
	ccs.ArmatureDataManager.getInstance 	= CCArmatureDataManager.sharedArmatureDataManager
	ccs.Armature 					= CCArmature
end




