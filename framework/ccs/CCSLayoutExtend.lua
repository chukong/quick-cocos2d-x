CCSLayoutExtend = class("CCSLayoutExtend", CCSWidgetExtend)
CCSLayoutExtend.__index = CCSLayoutExtend

function CCSLayoutExtend.extend(target)
        local t = tolua.getpeer(target)
        if not t then
            t = {}
            tolua.setpeer(target, t)
        end
        setmetatable(t, CCSLayoutExtend)
        return target
end

function CCSLayoutExtend:initlayout(params)
    if not params.size then params.size = ccs.DEFAULT_LAYOUT_SIZE end
    local color         = params.color
    local endColor      = params.endColor
    local colorType     = params.colorType
    local image         = params.image
    local scale9        = params.scale9
    local capInsets     = params.capInsets or ccs.DEFAULT_CAPINSETS
    local type          = params.type
    local clip          = params.clip


    local init = true
   
    while true
    do
        init = self:init(params)
        if init == false then break end
    --[[
        init = (tolua.type(size) == "CCSize")
        assert(init,"layout invalid params.size")
        self:setSize(size)
    ]]
        if colorType then
            self:setBackGroundColorType(colorType)
            if colorType == LAYOUT_COLOR_GRADIENT then
                if color and endColor then
                    init = (tolua.type(color) == "ccColor3B" or tolua.type(color) == "const ccColor3B")
                    assert(init,"layout invalid params.color")
                    init = (tolua.type(endColor) == "ccColor3B")
                    assert(init,"layout invalid params.endColor")
                    if init == false then break end
                    self:setBackGroundColor(color,endColor)
                end
            else
                if color then
                    init = (tolua.type(color) == "ccColor3B" or tolua.type(color) == "const ccColor3B")
                    assert(init,"[ccs.plane] invalid params.color")
                    if init == false then break end
                    self:setBackGroundColor(color)
                end
            end
        end

        if image then
            self:setBackGroundImage(image)
        end

        if scale9 then
            self:setBackGroundImageScale9Enabled(scale9)
            self:setBackGroundImageCapInsets(capInsets)
        end

        -- layout 的布局方式
        if type then
            self:setLayoutType(type)
        end

        if clip then
            assert(type(clip) == "boolean", "[ccs.plane] invalid params.clip")
            self:setClippingEnabled(clip)
        end
--[[
        if listener then
            init = (type(listener) == "table")
            if init == false then break end
            self:setListener(listener)
        end

        SET_POS(self,x,y)
]]
        break
    end
    return init
end

-- ccsmenu extend
function CCSLayoutExtend:AutoLayout(margin,... )
    local args = {...}
    local type = self:getLayoutType()
    for i,button in ipairs(args) do
        assert(tolua.type(button) == widget_table[UI_BUTTON].name,"[CCSLayoutExtend.AutoLayout] need UIButton params")
        local lp = UILinearLayoutParameter:create()
        if type == LAYOUT_ABSOLUTE then
            return
        elseif type == LAYOUT_LINEAR_VERTICAL then
            lp:setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL)
            if i == 1 then
                lp:setMargin(UIMargin(0,0,0,margin/2))
            else
                lp:setMargin(UIMargin(0,margin/2,0,margin/2))
            end 
        elseif type == LAYOUT_LINEAR_HORIZONTAL then
            lp:setGravity(LINEAR_GRAVITY_CENTER_VERTICAL)
            if i == 1 then
                lp:setMargin(UIMargin(0,0,margin/2,0))
            else
                lp:setMargin(UIMargin(margin/2,0,margin/2,0))
            end 
        elseif type == LAYOUT_RELATIVE then
        end
        button:setLayoutParameter(lp)
        self:addChild(button)
    end
    self:doLayout()
end