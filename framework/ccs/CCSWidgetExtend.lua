CCSWidgetExtend = class("CCSWidgetExtend", CCNodeExtend)
CCSWidgetExtend.__index = CCSWidgetExtend

function CCSWidgetExtend.extend(target)
        local t = tolua.getpeer(target)
        if not t then
            t = {}
            tolua.setpeer(target, t)
        end
        setmetatable(t, CCSWidgetExtend)
        return target
end

function CCSWidgetExtend:init(params)
    local enabled = params.enabled
    local visible = params.visible
    local touchable = true
    if params.touch ~= nil then
        touchable = params.touch
    end
    local bright    = params.bright
    local foucs     = params.foucs
    local zOrder    = params.z
    local tag       = params.tag
    local color     = params.color
    local size      = params.size
    local sizeType  = params.sType
    local positionType = params.pType
    local x            = params.x or 0
    local y            = params.y or 0
    local name         = params.name
    local listener     = params.listener

    local init = true
    
    while true
    do
        if enabled then
            init = (type(enabled) == "boolean")
            assert(init,"widget invaild params.enabled")
            if init == false then break end
            self:setEnabled(enabled)
        end

        if visible then
            init = (type(visible) == "boolean")
            assert(init,"widget invaild params.visible")
            if init == false then break end
            self:setVisible(visible)
        end

        if touchable then
            init = (type(touchable) == "boolean")
            assert(init,"widget invaild params.touch")
            if init == false then break end
            self:setTouchEnabled(touchable)
        end

        if bright then
            init = (type(bright) == "boolean")
            assert(init,"widget invaild params.bright")
            if init == false then break end
            self:setBright(bright)
        end

        if foucs then
            init = (type(foucs) == "boolean")
            assert(init,"widget invaild params.foucs")
            if init == false then break end
            self:setFocused(foucs)
        end

        if zOrder then
            init = (type(zOrder) == "number")
            assert(init,"widget invaild params.z")
            if init == false then break end
            self:setZOrder(zOrder)
        end
        
        if name then
            init = (type(name) == "string")
            assert(init,"widget invaild params.name")
            if init == false then break end
            self:setName(name)
        end

        if tag then
            init = (type(tag) == "number")
            assert(init,"widget invaild params.tag")
            if init == false then break end
            self:setTag(tag)
        end

        if color then
            init = (tolua.type(color) == "ccColor3B" or tolua.type(color) == "const ccColor3B")
            assert(init,"widget invalid params.color")
            if init == false then break end
            self:setColor(color)
        end

        if size then
            init = (tolua.type(size) == "CCSize" or tolua.type(size) == "const CCSize")
            assert(init,"widget invaild params.size")
            if init == false then break end
            self:setSize(size)
        end

        if sizeType then
            cclog(type(sizeType))
            self:setSizeType(sizeType)
        end

        if positionType then
            cclog(type(positionType))
            self:setPositionType(positionType)
        end

        SET_POS(self,x,y)

        if listener then
            init = (type(listener) == "table")
            assert(init,"widget invaild params.listener")
            if init == false then break end
            self:setListener(listener)
        end

        break
    end

    return init
end

function CCSWidgetExtend:getChild(name)
	local child = nil
    while true
    do
    if not name then break end
    local uiwidget = self:getChildByName(name)
    if not uiwidget or not widget_table[uiwidget:getDescription()] then break end
    child = tolua.cast(uiwidget,widget_table[uiwidget:getDescription()].name)
    CCSWidgetExtend.extend(child)
    break
    end
    return child
end

function CCSWidgetExtend:setListener(params)
    while true
    do
        if type(params) ~= "table" then return end
        if table.nums(params) == 0 then self:unregisterEventScript() return end
        defaultCallbacks = 
        {
            [ccs.TouchEventType.state_change_to_normal]     = handler(self,self.onPressStateChangedToNormal),
            [ccs.TouchEventType.state_change_to_pressed]    = handler(self,self.onPressStateChangedToPressed),
            [ccs.TouchEventType.state_change_to_disabled]   = handler(self,self.onPressStateChangedToDisabled),
        }
        table.merge(defaultCallbacks,params)
        self.listener = defaultCallbacks
        handle = function(event,uiwidget)
            if self.listener[event] then
               self.listener[event](uiwidget)
            end
        end
        self:registerEventScript(handle)
        break
    end
end

function CCSWidgetExtend:onPressStateChangedToNormal(uiwidget)
end

function CCSWidgetExtend:onPressStateChangedToPressed(uiwidget)
end

function CCSWidgetExtend:onPressStateChangedToDisabled(uiwidget)
end