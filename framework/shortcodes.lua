
----------------------------------------
-- cc.CCNode
----------------------------------------

cc.CCNodeExtend.remove = cc.CCNodeExtend.removeSelf

function cc.CCNodeExtend:addTo(target, zorder, tag)
    target:addChild(self, zorder or 0, tag or 0)
    return self
end

function cc.CCNodeExtend:show()
    self:setVisible(true)
    return self
end

function cc.CCNodeExtend:hide()
    self:setVisible(false)
    return self
end

function cc.CCNodeExtend:pos(x, y)
    self:setPosition(x, y)
    return self
end

function cc.CCNodeExtend:center()
    self:setPosition(display.cx, display.cy)
    return self
end

function cc.CCNodeExtend:scale(scale)
    self:setScale(scale)
    return self
end

function cc.CCNodeExtend:rotation(r)
    self:setRotation(r)
    return self
end

function cc.CCNodeExtend:size(width, height)
    if typen(width) == LUA_TUSERDATA then
        self:setContentSize(width)
    else
        self:setContentSize(cc.CCSize(width, height))
    end
    return self
end

function cc.CCNodeExtend:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

function cc.CCNodeExtend:zorder(z)
    self:setZOrder(z)
    return self
end

-- actions

function cc.CCNodeExtend:stop()
    self:stopAllActions()
    return self
end

function cc.CCNodeExtend:fadeIn(time)
    self:runAction(cc.CCFadeIn:create(time))
    return self
end

function cc.CCNodeExtend:fadeOut(time)
    self:runAction(cc.CCFadeOut:create(time))
    return self
end

function cc.CCNodeExtend:fadeTo(time, opacity)
    self:runAction(cc.CCFadeTo:create(time, opacity))
    return self
end

function cc.CCNodeExtend:moveTo(time, x, y)
    self:runAction(cc.CCMoveTo:create(time, cc.p(x or self:getPositionX(), y or self:getPositionY())))
    return self
end

function cc.CCNodeExtend:moveBy(time, x, y)
    self:runAction(cc.CCMoveBy:create(time, cc.p(x or 0, y or 0)))
    return self
end

function cc.CCNodeExtend:rotateTo(time, rotation)
    self:runAction(cc.CCRotateTo:create(time, rotation))
    return self
end

function cc.CCNodeExtend:rotateBy(time, rotation)
    self:runAction(cc.CCRotateBy:create(time, rotation))
    return self
end

function cc.CCNodeExtend:scaleTo(time, scale)
    self:runAction(cc.CCScaleTo:create(time, scale))
    return self
end

function cc.CCNodeExtend:scaleBy(time, scale)
    self:runAction(cc.CCScaleBy:create(time, scale))
    return self
end

function cc.CCNodeExtend:skewTo(time, sx, sy)
    self:runAction(cc.CCSkewTo:create(time, sx or self:getSkewX(), sy or self:getSkewY()))
end

function cc.CCNodeExtend:skewBy(time, sx, sy)
    self:runAction(cc.CCSkewBy:create(time, sx or 0, sy or 0))
end

function cc.CCNodeExtend:tintTo(time, r, g, b)
    self:runAction(cc.CCTintTo:create(time, r or 0, g or 0, b or 0))
    return self
end

function cc.CCNodeExtend:tintBy(time, r, g, b)
    self:runAction(cc.CCTintBy:create(time, r or 0, g or 0, b or 0))
    return self
end

----------------------------------------
-- cc.CCSprite
----------------------------------------

cc.CCSpriteExtend.playOnce = cc.CCSpriteExtend.playAnimationOnce
cc.CCSpriteExtend.playForever = cc.CCSpriteExtend.playAnimationForever

function cc.CCSpriteExtend:displayFrame(frame, index)
    if typen(frame) == LUA_TSTRING then
        self:setDisplayFrame(frame, index or 0)
    else
        self:setDisplayFrame(frame)
    end
    return self
end

function cc.CCSpriteExtend:flipX(b)
    self:setFlipX(b)
    return self
end

function cc.CCSpriteExtend:flipY(b)
    self:setFlipY(b)
    return self
end

----------------------------------------
-- cc.CCLayer
----------------------------------------

function cc.CCLayerExtend:onTouch(listener, isMultiTouches, priority, swallowsTouches)
    self:addTouchEventListener(listener, tobool(isMultiTouches), toint(priority), tobool(swallowsTouches))
    return self
end

function cc.CCLayerExtend:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

function cc.CCLayerExtend:onKeypad(listener)
    self:addKeypadEventListener(listener)
    return self
end

function cc.CCLayerExtend:enableKeypad(enabled)
    self:setKeypadEnabled(enabled)
    return self
end

function cc.CCLayerExtend:onAccelerate()
    self:addAccelerateEventListener(listener)
    return self
end

function cc.CCLayerExtend:enableAccelerometer(enabled)
    self:setAccelerometerEnabled(enabled)
    return self
end
