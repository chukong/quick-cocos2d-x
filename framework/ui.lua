
local ui = {}

ui.DEFAULT_TTF_FONT      = "Arial"
ui.DEFAULT_TTF_FONT_SIZE = 24

ui.TEXT_ALIGN_LEFT    = cc.kCCTextAlignmentLeft
ui.TEXT_ALIGN_CENTER  = cc.kCCTextAlignmentCenter
ui.TEXT_ALIGN_RIGHT   = cc.kCCTextAlignmentRight
ui.TEXT_VALIGN_TOP    = cc.kCCVerticalTextAlignmentTop
ui.TEXT_VALIGN_CENTER = cc.kCCVerticalTextAlignmentCenter
ui.TEXT_VALIGN_BOTTOM = cc.kCCVerticalTextAlignmentBottom

function ui.newEditBox(params)
    local imageNormal = params.image
    local imagePressed = params.imagePressed
    local imageDisabled = params.imageDisabled

    if type(imageNormal) == "string" then
        imageNormal = display.newScale9Sprite(imageNormal)
    end
    if type(imagePressed) == "string" then
        imagePressed = display.newScale9Sprite(imagePressed)
    end
    if type(imageDisabled) == "string" then
        imageDisabled = display.newScale9Sprite(imageDisabled)
    end

    local editbox = cc.CCEditBox:create(params.size, imageNormal, imagePressed, imageDisabled)

    if editbox then
        cc.CCNodeExtend.extend(editbox)
        editbox:addEditBoxEventListener(params.listener)
        if params.x and params.y then
            editbox:setPosition(params.x, params.y)
        end
    end

    return editbox
end

function ui.newMenu(items)
    local menu
    menu = cc.CCNodeExtend.extend(cc.CCMenu:create())

    for k, item in pairs(items) do
        if not tolua.isnull(item) then
            menu:addChild(item, 0, item:getTag())
        end
    end

    menu:setPosition(0, 0)
    return menu
end

function ui.newImageMenuItem(params)
    local imageNormal   = params.image
    local imageSelected = params.imageSelected
    local imageDisabled = params.imageDisabled
    local listener      = params.listener
    local tag           = params.tag
    local x             = params.x
    local y             = params.y
    local sound         = params.sound

    if type(imageNormal) == "string" then
        imageNormal = display.newSprite(imageNormal)
    end
    if type(imageSelected) == "string" then
        imageSelected = display.newSprite(imageSelected)
    end
    if type(imageDisabled) == "string" then
        imageDisabled = display.newSprite(imageDisabled)
    end

    local item = cc.CCMenuItemSprite:create(imageNormal, imageSelected, imageDisabled)
    if item then
        cc.CCNodeExtend.extend(item)
        if type(listener) == "function" then
            item:registerScriptTapHandler(function(tag)
                if sound then audio.playSound(sound) end
                listener(tag)
            end)
        end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    return item
end

function ui.newTTFLabelMenuItem(params)
    local p = clone(params)
    p.x, p.y = nil, nil
    local label = ui.newTTFLabel(p)

    local listener = params.listener
    local tag      = params.tag
    local x        = params.x
    local y        = params.y
    local sound    = params.sound

    local item = cc.CCMenuItemLabel:create(label)
    if item then
        cc.CCNodeExtend.extend(item)
        if type(listener) == "function" then
            item:registerScriptTapHandler(function(tag)
                if sound then audio.playSound(sound) end
                listener(tag)
            end)
        end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    return item
end

function ui.newBMFontLabel(params)
    assert(type(params) == "table",
           "[framework.ui] newBMFontLabel() invalid params")

    local text      = tostring(params.text)
    local font      = params.font
    local textAlign = params.align or ui.TEXT_ALIGN_CENTER
    local x, y      = params.x, params.y
    assert(font ~= nil, "ui.newBMFontLabel() - not set font")

    local label = cc.CCLabelBMFont:create(text, font, cc.kCCLabelAutomaticWidth, textAlign)
    if not label then return end

    cc.CCNodeExtend.extend(label)
    if type(x) == "number" and type(y) == "number" then
        label:setPosition(x, y)
    end

    if textAlign == ui.TEXT_ALIGN_LEFT then
        label:align(display.LEFT_CENTER)
    elseif textAlign == ui.TEXT_ALIGN_RIGHT then
        label:align(display.RIGHT_CENTER)
    else
        label:align(display.CENTER)
    end

    return label
end

function ui.newTTFLabel(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabel() invalid params")

    local text       = tostring(params.text)
    local font       = params.font or ui.DEFAULT_TTF_FONT
    local size       = params.size or ui.DEFAULT_TTF_FONT_SIZE
    local color      = params.color or display.COLOR_WHITE
    local textAlign  = params.align or ui.TEXT_ALIGN_LEFT
    local textValign = params.valign or ui.TEXT_VALIGN_CENTER
    local x, y       = params.x, params.y
    local dimensions = params.dimensions

    assert(type(size) == "number",
           "[framework.ui] newTTFLabel() invalid params.size")

    local label
    if dimensions then
        label = cc.CCLabelTTF:create(text, font, size, dimensions, textAlign, textValign)
    else
        label = cc.CCLabelTTF:create(text, font, size)
    end

    if label then
        cc.CCNodeExtend.extend(label)
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

    return label
end

function ui.newTTFLabelWithShadow(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabelWithShadow() invalid params")

    local color       = params.color or display.COLOR_WHITE
    local shadowColor = params.shadowColor or display.COLOR_BLACK
    local x, y        = params.x, params.y

    local g = display.newNode()
    params.size = params.size
    params.color = shadowColor
    params.x, params.y = 0, 0
    g.shadow1 = ui.newTTFLabel(params)
    local offset = 1 / (display.widthInPixels / display.width)
    g.shadow1:realign(offset, -offset)
    g:addChild(g.shadow1)

    params.color = color
    g.label = ui.newTTFLabel(params)
    g.label:realign(0, 0)
    g:addChild(g.label)

    function g:setString(text)
        g.shadow1:setString(text)
        g.label:setString(text)
    end

    function g:realign(x, y)
        g:setPosition(x, y)
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
    end

    return g
end

function ui.newTTFLabelWithOutline(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabelWithShadow() invalid params")

    local color        = params.color or display.COLOR_WHITE
    local outlineColor = params.outlineColor or display.COLOR_BLACK
    local x, y         = params.x, params.y

    local g = display.newNode()
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
    end

    return g
end

return ui
