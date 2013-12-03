CCSLayerExtend = class("CCSLayerExtend", CCNodeExtend)
CCSLayerExtend.__index = CCSLayerExtend

function CCSLayerExtend.extend(target)
        local t = tolua.getpeer(target)
        if not t then
            t = {}
            tolua.setpeer(target, t)
        end
        setmetatable(t, CCSLayerExtend)
        return target
end

function CCSLayerExtend:load(filename)
    local widget = CCSWidgetExtend.extend(GUIReader:shareReader():widgetFromJsonFile(filename))
    if widget then
        self:addWidget(widget)
        self.group = {}
    else
        assert(false,string.format("CCSLayerExtend:load -invalid file :\"%s \" ",filename))
    end
    return self
end

function CCSLayerExtend:getChild(name)
    local child = nil
    while true
    do
    if not name then break end
    local uiwidget = self:getWidgetByName(name)
    if not uiwidget or not widget_table[uiwidget:getDescription()] then break end
    child = tolua.cast(uiwidget,widget_table[uiwidget:getDescription()].name)
    CCSWidgetExtend.extend(child)
    break
    end
    return child
end

function CCSLayerExtend:insterGroup(groupId,...)
    local arg = {...}
    for i,v in ipairs(arg) do
        if v == nil then
            assert(false,string.format("CCSLayerExtend:insterGroup error : invalid checkBox :%d",i))
        elseif v:getDescription() ~= "CheckBox" then
            assert(false,"CCSLayerExtend:insterGroup error : only support UICheckBox")
        elseif type(groupId) ~= "number" then
            assert(false,"CCSLayerExtend:insterGroup error : #1 groupId expected number")
        elseif groupId < 1 then
            assert(false,"CCSLayerExtend:insterGroup error : groupId must start at 1")
        else 
            if not self.group then self.group = {} end
            if self.group[groupId] == nil then
                self.group[groupId] = {}
            end
            self.group[groupId][#self.group[groupId]+1] = v
        end
    end
end

function CCSLayerExtend:GroupDefault(groupId,checkbox)
     if self.group then
        local group = self.group[groupId]
        if group then
            for i,v in ipairs(group) do
                if v ~= checkbox then
                    v:setSelectedState(false)
                else
                    v:setSelectedState(true)
                end
            end 
        end
    end
end

function CCSLayerExtend:GroupSelected(groupId,checkbox)
    if self.group then
        local group = self.group[groupId]
        if group then
            for i,v in ipairs(group) do
                if v ~= checkbox then
                    v:setSelectedState(false)
                end
            end 
        end
    end
end