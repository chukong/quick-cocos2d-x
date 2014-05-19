-- For CCDragonBones 
-- @author zrong(zengrong.net)
-- Creation: 2014-04-24

CCDragonBonesExtend = class("CCDragonBonesExtend", CCNodeExtend)
CCDragonBonesExtend.__index = CCDragonBonesExtend

CCDragonBonesExtend.EVENTS = {
	MOVEMENT_CHANGE = AnimationEvent.START,
	FADE_IN = AnimationEvent.FADE_IN,
	FADE_OUT = AnimationEvent.FADE_OUT,
	START = AnimationEvent.START,
	COMPLETE = AnimationEvent.COMPLETE,
	LOOP_COMPLETE = AnimationEvent.LOOP_COMPLETE,
	FADE_IN_COMPLETE = AnimationEvent.FADE_IN_COMPLETE,
	FADE_OUT_COMPLETE = AnimationEvent.FADE_OUT_COMPLETE,
}

function CCDragonBonesExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCDragonBonesExtend)
    return target
end

function CCDragonBonesExtend:addMovementScriptListener(listener)
	-- for __k, __v in pairs(CCDragonBonesExtend.EVENTS) do
	-- 	print(__k, __v)
	-- end
	self:removeMovementScriptListener()
	self:addScriptListener(CCDragonBonesExtend.EVENTS.START, listener)
	self:addScriptListener(CCDragonBonesExtend.EVENTS.COMPLETE, listener)
	self:addScriptListener(CCDragonBonesExtend.EVENTS.LOOP_COMPLETE, listener)
	return self
end

function CCDragonBonesExtend:removeMovementScriptListener()
	self:removeScriptListener(CCDragonBonesExtend.EVENTS.START)
	self:removeScriptListener(CCDragonBonesExtend.EVENTS.COMPLETE)
	self:removeScriptListener(CCDragonBonesExtend.EVENTS.LOOP_COMPLETE)
	return self
end

function CCDragonBonesExtend:addScriptListener(evtType, listener)
	self:removeScriptListener(evtType, listener)
	local __bridge = function(evt)
		listener(evt:getType(), evt:getMovementID())
	end
	self._listeners[evtType] = __bridge
	self:registerScriptHandler(__bridge, evtType)
	return self
end

function CCDragonBonesExtend:removeScriptListener(evtType)
	if not self._listeners then self._listeners = {} end
	local __listener = self._listeners[evtType]
	if __listener then
		self:unregisterScriptHandler(evtType)
		self._listeners[evtType] = nil
	end
	return self
end

function CCDragonBonesExtend:removeAllScriptListener()
	for __k, __v in pairs(self._listeners) do
		self:removeScriptListener(__k)
	end
	self._listeners = {}
	return self
end

