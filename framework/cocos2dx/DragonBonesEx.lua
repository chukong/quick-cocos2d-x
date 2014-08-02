-- For CCDragonBones
-- @author zrong(zengrong.net)
-- Creation: 2014-04-24
-- Modification: 2014-07-29

--[[--

针对 cc.Node 的扩展

]]
local c = cc
local DragonBonesNode = c.DragonBonesNode

DragonBonesNode.EVENTS = {
	MOVEMENT_CHANGE = AnimationEvent.START,
	FADE_IN = AnimationEvent.FADE_IN,
	FADE_OUT = AnimationEvent.FADE_OUT,
	START = AnimationEvent.START,
	COMPLETE = AnimationEvent.COMPLETE,
	LOOP_COMPLETE = AnimationEvent.LOOP_COMPLETE,
	FADE_IN_COMPLETE = AnimationEvent.FADE_IN_COMPLETE,
	FADE_OUT_COMPLETE = AnimationEvent.FADE_OUT_COMPLETE,
}

--[[--

注册动作相关的侦听器

@param function listener
@return DragonBonesNode

]]
function DragonBonesNode:addMovementScriptListener(listener)
	self:removeMovementScriptListener()
	local __bridge = function(evt)
		listener(evt:getType(), evt:getMovementID())
	end
	self:addScriptListener(DragonBonesNode.EVENTS.START, __bridge)
	self:addScriptListener(DragonBonesNode.EVENTS.COMPLETE, __bridge)
	self:addScriptListener(DragonBonesNode.EVENTS.LOOP_COMPLETE, __bridge)
	return self
end

--[[--

移除动作相关的侦听器

]]
function DragonBonesNode:removeMovementScriptListener()
	self:removeScriptListener(DragonBonesNode.EVENTS.START)
	self:removeScriptListener(DragonBonesNode.EVENTS.COMPLETE)
	self:removeScriptListener(DragonBonesNode.EVENTS.LOOP_COMPLETE)
	return self
end

--[[--

调用 `registerScriptHander` 为脚本引擎注册侦听器。

与 `registerScriptHandler` 不同的是:

1. 本方法会缓存侦听器的键名和函数方便反注册
2. 本方法会返回self

]]
function DragonBonesNode:addScriptListener(evtType, listener)
	self:removeScriptListener(evtType, listener)
	self._listeners[evtType] = listener
	self:registerScriptHandler(listener, evtType)
	return self
end

--[[--

在缓存列表中查询是否有对应的侦听器存在，若有，则调用 `unregisterScriptHandler` 移除它。

与 `unregisterScriptHandler` 不同的是:

1. 本方法会查询缓存；
2. 本方法会返回self 。

]]
function DragonBonesNode:removeScriptListener(evtType, listener)
	if not self._listeners then self._listeners = {} end
	local __listener = self._listeners[evtType]
	if __listener then
		self:unregisterScriptHandler(evtType)
		self._listeners[evtType] = nil
	end
	return self
end

function DragonBonesNode:removeAllScriptListener()
	for __k, __v in pairs(self._listeners) do
		self:removeScriptListener(__k)
	end
	self._listeners = {}
	return self
end

--[[--

获取一个DragonBones的所有可用动画名称

@param table 包含动画名称的一个table

]]
function DragonBonesNode:getAnimations()
	local aniList = self:getAnimationList()
	local anis = {}
	for i=0,aniList:count()-1 do
		anis[#anis+1] = aniList:objectAtIndex(i):getCString()
	end
	return anis
end

