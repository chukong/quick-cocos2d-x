
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

require(cc.packageName .. ".cocos2dx.CCNodeExtend")
require(cc.packageName .. ".cocos2dx.CCSceneExtend")
require(cc.packageName .. ".cocos2dx.CCSpriteExtend")
require(cc.packageName .. ".cocos2dx.CCLayerExtend")
