
ccp = CCPoint
ccsize = CCSize
ccrect = CCRect

cc.p = CCPoint
cc.size = CCSize
cc.rect = CCRect

cc.c3 = ccc3
cc.c4 = ccc4
cc.c4f = ccc4f

cc.NODE_EVENT               = 0
cc.NODE_ENTER_FRAME_EVENT   = 1
cc.NODE_TOUCH_EVENT         = 2
cc.NODE_TOUCH_CAPTURE_EVENT = 3
cc.MENU_ITEM_CLICKED_EVENT  = 4
cc.ACCELERATE_EVENT         = 5
cc.KEYPAD_EVENT             = 6

cc.MULTI_TOUCHES            = 0
cc.SINLE_TOUCH              = 1

cc.size2t = function(size)
    return {width = size.width, height = size.height}
end

cc.point2t = function(point)
    return {x = point.x, y = point.y}
end

cc.rect2t = function(rect)
    return {origin = cc.point2t(rect.origin), size = cc.size2t(rect.size)}
end

cc.t2size = function(t)
    return CCSize(t.width, t.height)
end

cc.t2point = function(t)
    return CCPoint(t.x, t.y)
end

cc.t2rect = function(t)
    return CCRect(t.origin.x, t.origin.y, t.size.width, t.size.height)
end

require(cc.PACKAGE_NAME .. ".cocos2dx.CCNodeExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSceneExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSpriteExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCLayerExtend")
