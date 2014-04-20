
ccp = CCPoint
ccsize = CCSize
ccrect = CCRect

cc.p = CCPoint
cc.size = CCSize
cc.rect = CCRect

cc.c3 = ccc3
cc.c4 = ccc4
cc.c4f = ccc4f

cc.TOUCH_IGNORE               = 0
cc.TOUCH_BEGAN                = 1
cc.TOUCH_BEGAN_SWALLOWS       = cc.TOUCH_BEGAN
cc.TOUCH_BEGAN_NO_SWALLOWS    = 2
cc.TOUCH_MOVED                = 1
cc.TOUCH_MOVED_SWALLOWS       = cc.TOUCH_MOVED
cc.TOUCH_MOVED_NO_SWALLOWS    = 0
cc.TOUCH_MOVED_RELEASE_OTHERS = 2
cc.MULTI_TOUCHES_ON           = true
cc.MULTI_TOUCHES_OFF          = false

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
require(cc.PACKAGE_NAME .. ".cocos2dx.CCDrawNodeExtend")
