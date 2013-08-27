
----------------------------------------
-- CCNode
----------------------------------------

CCNodeExtend.remove = CCNodeExtend.removeSelf

function CCNodeExtend:addTo(target, zorder, tag)
    target:addChild(self, zorder or 0, tag or 0)
    return self
end

function CCNodeExtend:show()
    self:setVisible(true)
    return self
end

function CCNodeExtend:hide()
    self:setVisible(false)
    return self
end

function CCNodeExtend:pos(x, y)
    self:setPosition(x, y)
    return self
end

function CCNodeExtend:center()
    self:setPosition(display.cx, display.cy)
    return self
end

function CCNodeExtend:scale(scale)
    self:setScale(scale)
    return self
end

function CCNodeExtend:rotation(r)
    self:setRotation(r)
    return self
end

function CCNodeExtend:size(width, height)
    if typen(width) == LUA_TUSERDATA then
        self:setContentSize(width)
    else
        self:setContentSize(CCSize(width, height))
    end
    return self
end

function CCNodeExtend:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

function CCNodeExtend:zorder(z)
    self:setZOrder(z)
    return self
end

-- actions

function CCNodeExtend:stop()
    self:stopAllActions()
    return self
end

function CCNodeExtend:fadeIn(time)
    self:runAction(CCFadeIn:create(time))
    return self
end

function CCNodeExtend:fadeOut(time)
    self:runAction(CCFadeOut:create(time))
    return self
end

function CCNodeExtend:fadeTo(time, opacity)
    self:runAction(CCFadeTo:create(time, opacity))
    return self
end

function CCNodeExtend:moveTo(time, x, y)
    self:runAction(CCMoveTo:create(time, CCPoint(x or self:getPositionX(), y or self:getPositionY())))
    return self
end

function CCNodeExtend:moveBy(time, x, y)
    self:runAction(CCMoveBy:create(time, CCPoint(x or 0, y or 0)))
    return self
end

function CCNodeExtend:rotateTo(time, rotation)
    self:runAction(CCRotateTo:create(time, rotation))
    return self
end

function CCNodeExtend:rotateBy(time, rotation)
    self:runAction(CCRotateBy:create(time, rotation))
    return self
end

function CCNodeExtend:scaleTo(time, scale)
    self:runAction(CCScaleTo:create(time, scale))
    return self
end

function CCNodeExtend:scaleBy(time, scale)
    self:runAction(CCScaleBy:create(time, scale))
    return self
end

function CCNodeExtend:skewTo(time, sx, sy)
    self:runAction(CCSkewTo:create(time, sx or self:getSkewX(), sy or self:getSkewY()))
end

function CCNodeExtend:skewBy(time, sx, sy)
    self:runAction(CCSkewBy:create(time, sx or 0, sy or 0))
end

function CCNodeExtend:tintTo(time, r, g, b)
    self:runAction(CCTintTo:create(time, r or 0, g or 0, b or 0))
    return self
end

function CCNodeExtend:tintBy(time, r, g, b)
    self:runAction(CCTintBy:create(time, r or 0, g or 0, b or 0))
    return self
end

----------------------------------------
-- CCSprite
----------------------------------------

CCSpriteExtend.playOnce = CCSpriteExtend.playAnimationOnce
CCSpriteExtend.playForever = CCSpriteExtend.playAnimationForever

function CCSpriteExtend:displayFrame(frame, index)
    if typen(frame) == LUA_TSTRING then
        self:setDisplayFrame(frame, index or 0)
    else
        self:setDisplayFrame(frame)
    end
    return self
end

function CCSpriteExtend:flipX(b)
    self:setFlipX(b)
    return self
end

function CCSpriteExtend:flipY(b)
    self:setFlipY(b)
    return self
end

----------------------------------------
-- CCLayer
----------------------------------------

function CCLayerExtend:onTouch(listener, isMultiTouches, priority, swallowsTouches)
    self:addTouchEventListener(listener, tobool(isMultiTouches), toint(priority), tobool(swallowsTouches))
    return self
end

function CCLayerExtend:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

function CCLayerExtend:onKeypad(listener)
    self:addKeypadEventListener(listener)
    return self
end

function CCLayerExtend:enableKeypad(enabled)
    self:setKeypadEnabled(enabled)
    return self
end

function CCLayerExtend:onAccelerate()
    self:addAccelerateEventListener(listener)
    return self
end

function CCLayerExtend:enableAccelerometer(enabled)
    self:setAccelerometerEnabled(enabled)
    return self
end
