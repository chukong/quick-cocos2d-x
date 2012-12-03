
local ui = {}

local traceObject = traceObject

ui.DEFAULT_TTF_FONT      = "Arial"
ui.DEFAULT_TTF_FONT_SIZE = 24

ui.TEXT_ALIGN_LEFT    = kCCTextAlignmentLeft
ui.TEXT_ALIGN_CENTER  = kCCTextAlignmentCenter
ui.TEXT_ALIGN_RIGHT   = kCCTextAlignmentRight
ui.TEXT_VALIGN_TOP    = kCCVerticalTextAlignmentTop
ui.TEXT_VALIGN_CENTER = kCCVerticalTextAlignmentCenter
ui.TEXT_VALIGN_BOTTOM = kCCVerticalTextAlignmentBottom

function ui.newMenu(...)
    local menu
    menu = CCMenu:create()
    display.extendNode(menu)

    local item = select(1, ...)
    local items = {}

    if type(item) ~= "table" then
        for i = 1, select("#", ...) do
            items[i] = select(i, ...)
        end
    else
        items = item
    end

    for k, item in pairs(items) do
        if type(item) == "userdata" then
            menu:addChild(item, 0, item:getTag())
        end
    end

    menu:setPosition(0, 0)
    if DEBUG > 1 then traceObject(menu, "Menu") end
    return menu
end

function ui.newMenuItemImage(params)
    local imageNormal   = params.image
    local imageSelected = params.imageSelected
    local imageDisabled = params.imageDisabled
    local listener      = params.listener
    local tag           = params.tag
    local x             = params.x
    local y             = params.y

    if type(imageNormal) == "string" then
        imageNormal = display.newImage(imageNormal)
    end
    if type(imageSelected) == "string" then
        imageSelected = display.newImage(imageSelected)
    end
    if type(imageDisabled) == "string" then
        imageDisabled = display.newImage(imageDisabled)
    end

    local item = CCMenuItemSprite:create(imageNormal, imageSelected, imageDisabled)
    if item then
        display.extendSprite(item)
        if type(listener) == "function" then item:registerScriptTapHandler(listener) end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    if DEBUG > 1 then traceObject(item, "MenuItem") end
    return item
end

function ui.newMenuItemLabel(params)
    local label    = ui.newTTFLabel(params)
    local listener = params.listener
    local tag      = params.tag
    local x        = params.x
    local y        = params.y

    local item = CCMenuItemLabel:create(label)
    if item then
        display.extendSprite(item)
        if type(listener) == "function" then item:registerScriptTapHandler(listener) end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    if DEBUG > 1 then traceObject(item, "MenuItem") end
    return item
end

function ui.newBMFontLabel(params)
    assert(type(params) == "table",
           "[framework.client.ui] newBMFontLabel() invalid params")

    local text      = tostring(params.text)
    local font      = params.font or ui.DEFAULT_TTF_FONT
    local textAlign = params.align or ui.TEXT_ALIGN_LEFT
    local x, y      = params.x, params.y

    local label = CCLabelBMFont:create(text, font, kCCLabelAutomaticWidth, textAlign)
    if not label then return end

    display.extendNode(label)
    if type(x) == "number" and type(y) == "number" then
        label:setPosition(x, y)
    end

    if DEBUG > 1 then traceObject(label, format("Label - %s", text)) end
    return label
end

function ui.newTTFLabel(params)
    assert(type(params) == "table",
           "[framework.client.ui] newTTFLabel() invalid params")

    local text       = tostring(params.text)
    local font       = params.font or ui.DEFAULT_TTF_FONT
    local size       = params.size or ui.DEFAULT_TTF_FONT_SIZE
    local color      = params.color or display.COLOR_WHITE
    local textAlign  = params.align or ui.TEXT_ALIGN_LEFT
    local textValign = params.valign or ui.TEXT_VALIGN_CENTER
    local x, y       = params.x, params.y
    local dimensions = params.dimensions

    assert(type(size) == "number",
           "[framework.client.ui] newTTFLabel() invalid params.size")

    local label
    if dimensions then
        label = CCLabelTTF:create(text, font, size, dimensions, textAlign, textValign)
    else
        label = CCLabelTTF:create(text, font, size)
    end

    if label then
        display.extendNode(label)
        label:setColor(color)

        function label:realign(x, y)
            if textAlign == ui.TEXT_ALIGN_LEFT then
                label:setPosition(math.round(x + label:getContentSize().width / 2), y)
            elseif textAlign == ui.TEXT_ALIGN_RIGHT then
                label:setPosition(x - math.round(label:getContentSize().width / 2), y)
            else
                label:setPosition(x, y)
            end
        end

        if x and y then label:realign(x, y) end
    end

    if DEBUG > 1 then traceObject(label, format("Label - %s", text)) end
    return label
end

function ui.newTTFLabelWithShadow(params)
    assert(type(params) == "table",
           "[framework.client.ui] newTTFLabelWithShadow() invalid params")

    local color       = params.color or display.COLOR_WHITE
    local shadowColor = params.shadowColor or display.COLOR_BLACK
    local x, y        = params.x, params.y

    local g = display.newGroup()
    params.size = params.size
    params.color = shadowColor
    params.x, params.y = 0, 0
    g.shadow1 = ui.newTTFLabel(params)
    g.shadow1:realign(1, -1)
    g:addChild(g.shadow1)

    params.color = color
    g.label = ui.newTTFLabel(params)
    g.label:realign(0, 0)
    g:addChild(g.label)

    function g:setString(text)
        g.shadow1:setString(text)
        g.label:setString(text)
    end

    function g:getContentSize()
        return g.label:getContentSize()
    end

    function g:setColor(...)
        g.label:setColor(...)
    end

    function g:setShadowColor(...)
        g.shadow1:setColor(...)
    end

    function g:setOpacity(opacity)
        g.label:setOpacity(opacity)
        g.shadow1:setOpacity(opacity)
    end

    if x and y then
        g:setPosition(x, y)
        g:pixels()
    end
    if DEBUG > 1 then traceObject(g, format("Label - %s", _s(params.text))) end
    return g
end

function ui.newTTFLabelWithOutline(params)
    assert(type(params) == "table",
           "[framework.client.ui] newTTFLabelWithShadow() invalid params")

    local color        = params.color or display.COLOR_WHITE
    local outlineColor = params.outlineColor or display.COLOR_BLACK
    local x, y         = params.x, params.y

    local g = display.newGroup()
    params.size  = params.size
    params.color = outlineColor
    params.x, params.y = 0, 0
    g.shadow1 = ui.newTTFLabel(params)
    g.shadow1:realign(1, 0)
    g:addChild(g.shadow1)
    g.shadow2 = ui.newTTFLabel(params)
    g.shadow2:realign(-1, 0)
    g:addChild(g.shadow2)
    g.shadow3 = ui.newTTFLabel(params)
    g.shadow3:realign(0, -1)
    g:addChild(g.shadow3)
    g.shadow4 = ui.newTTFLabel(params)
    g.shadow4:realign(0, 1)
    g:addChild(g.shadow4)

    params.color = color
    g.label = ui.newTTFLabel(params)
    g.label:realign(0, 0)
    g:addChild(g.label)

    function g:setString(text)
        g.shadow1:setString(text)
        g.shadow2:setString(text)
        g.shadow3:setString(text)
        g.shadow4:setString(text)
        g.label:setString(text)
    end

    function g:getContentSize()
        return g.label:getContentSize()
    end

    function g:setColor(...)
        g.label:setColor(...)
    end

    function g:setOutlineColor(...)
        g.shadow1:setColor(...)
        g.shadow2:setColor(...)
        g.shadow3:setColor(...)
        g.shadow4:setColor(...)
    end

    function g:setOpacity(opacity)
        g.label:setOpacity(opacity)
        g.shadow1:setOpacity(opacity)
        g.shadow2:setOpacity(opacity)
        g.shadow3:setOpacity(opacity)
        g.shadow4:setOpacity(opacity)
    end

    if x and y then
        g:setPosition(x, y)
        g:pixels()
    end
    if DEBUG > 1 then traceObject(g, format("Label - %s", _s(params.text))) end
    return g
end

return ui
