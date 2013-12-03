local ccs = {}

UI_WIDGET		= "Widget"
UI_BUTTON		= "Button"
UI_CHECKBOX		= "CheckBox"
UI_IMAGEVIEW	= "ImageView"
UI_LABEL 		= "Label"
UI_LABELATLAS	= "LabelAtlas"
UI_LABELBMFONT  = "LabelBMFont"
UI_LOADINGBAR	= "LoadingBar"
UI_PANEL 		= "Layout"
UI_SCROLLVIEW	= "ScrollView"
UI_SLIDER		= "Slider"
UI_TEXTFIELD	= "TextField"
UI_DRAGPANEL	= "DragPanel"
UI_LISTVIEW		= "ListView"
UI_LISTVIEWEX   = "ListViewEx"
UI_PAGEVIEW		= "PageView"

widget_table = 
{
    [UI_WIDGET]      = { name = "UIWidget", create = function() return UIWidget:create() end},
    [UI_BUTTON]      = { name = "UIButton", create = function() return UIButton:create() end},
    [UI_CHECKBOX]    = { name = "UICheckBox", create = function() return UICheckBox:create() end},
    [UI_IMAGEVIEW]   = { name = "UIImageView", create = function() return UIImageView:create() end},
    [UI_LABEL]       = { name = "UILabel", create = function() return UILabel:create() end},
    [UI_LABELATLAS]  = { name = "UILabelAtlas", create = function() return UILabelAtlas:create() end},
    [UI_LABELBMFONT] = { name = "UILabelBMFont", create = function() return UILabelBMFont:create() end},
    [UI_LOADINGBAR]  = { name = "UILoadingBar", create = function() return UILoadingBar:create() end},
    [UI_PANEL]       = { name = "UILayout", create = function() return UILayout:create() end},
    [UI_SCROLLVIEW]  = { name = "UIScrollView", create = function() return UIScrollView:create() end},
    [UI_SLIDER]      = { name = "UISlider", create = function() return UISlider:create() end},
    [UI_TEXTFIELD]   = { name = "UITextField", create = function() return UITextField:create() end},
    [UI_DRAGPANEL]   = { name = "UIDragPanel", create = function() return UIDragPanel:create() end},
    [UI_LISTVIEW]    = { name = "UIListView", create = function() return UIListView:create() end},
    [UI_LISTVIEWEX]  = { name = "UIListViewEx", create = function() return UIListViewEx:create() end},
    [UI_PAGEVIEW]    = { name = "UIPageView", create = function() return UIPageView:create() end},
 }

SET_POS = function(widget,x,y)
    if type(x) == "number" and type(y) == "number" then
        widget:setPosition(ccp(x,y))
    end
end

ccs.DEFAULT_TTF_FONT        = "宋体"
ccs.DEFAULT_TTF_FONT_SIZE   = "20"
ccs.DEFAULT_INPUT_HOLDER    = "在这里输入"
ccs.DEFAULT_TEXTAREA_SIZE   = CCSizeMake(40,40)
ccs.DEFAULT_CAPINSETS       = CCRectMake(0, 0, 0, 0)
ccs.DEFAULT_LAYOUT_SIZE     = CCSizeMake(280,150)
ccs.COLOR_WHITE             = ccc3(255,255,255)

ccs.SizeType = 
{
    absolute = 0,
    percent = 1,
}

ccs.PositionType = {
    absolute = 0,
    percent = 1,
}

--base event
ccs.TouchEventType =
{
    began       = "pushDown",
    moved       = "move",
    ended       = "releaseUp",
    canceled    = "cancelUp",
    state_change_to_normal = "changeToNormal",
    state_change_to_pressed = "changeToPressed",
    state_change_to_disabled = "changeToDisabled",
    longclick   = "longClick", --(这个studio还未实现)
}


--checkbox event
ccs.CheckBoxEventType = 
{
    selected   = "selected",
    unselected = "unSelected", 
}


--slider event
ccs.SliderEventType = 
{
    changed = "percentChanged",
}
       
--textfiled event
ccs.TextFiledEventType =
{
    attach_with_ime     = "attachWithIME",
    detach_with_ime     = "detachWithIME",
    insert_text         = "insertText",
    delete_backward     = "deleteBackward",
}

--listview event
ccs.ListViewEventType =
{
    initChild        = "initChild",
    updateChild      = "updateChild",
}

ccs.ListViewExEventType = 
{
    onSelectedItem   = "onSelectedItem",
}

--pageview event
ccs.PageViewEventType =
{
    turning         = "turning",
}

--scrollview event
ccs.ScrollViewEventType = 
{
  scrollToTop        = "scrollToTop",
  scrollToBottom     = "scrollToBottom",
  scrollToLeft       = "scrollToLeft",
  scrollToRight      = "scrollToRight",
  scrolling          = "scrolling",
  bounce_top         = "bounce_top",
  bounce_bottom      = "bounce_bottom",
  bounce_left        = "bounce_left",
  bounce_right       = "bounce_right",  
}

require(cc.PACKAGE_NAME .. ".ccs.CCSWidgetExtend")
require(cc.PACKAGE_NAME .. ".ccs.CCSLayerExtend")
require(cc.PACKAGE_NAME .. ".ccs.CCSLayoutExtend")

function ccs.layer()
	local layer = CCSLayerExtend.extend(UILayer:create())
	return layer
end

function ccs.widget(params)
    assert(type(params) == "table", "[ccs.widget] invalid params")
    local widget = CCSWidgetExtend.extend(widget_table[UI_WIDGET].create())
    if widget:init(params) == false then
        assert(false,"[ccs.widget] failed to initialize!")
        return nil
    end
    return widget
end

function ccs.button(params)
    assert(type(params) == "table","[ccs.button] invalid params")
    local normal    = params.normal or ""
    local pressed   = params.pressed or ""
    local disabled  = params.disabled or ""
    local scale9    = params.scale9 or false
    local capInsets = params.capInsets or ccs.DEFAULT_CAPINSETS
    local text      = params.text

	local button = CCSWidgetExtend.extend(widget_table[UI_BUTTON].create())
    
    if button:init(params) == false then
        assert(false,"[ccs.button] failed to initialize!")
        return nil
    end

    button:loadTextures(normal,pressed,disabled)

    if scale9 == true then
        if params.size then
            button:setScale9Enabled(scale9)
            button:setCapInsets(capInsets)
            button:setSize(params.size)
        end
    end

    if text and type(text) == "string" then
        button:setTitleText(text)
    end

    return button
end

function ccs.label(params)
    assert(type(params) == "table","[ccs.label] invalid params")
    local text      = tostring(params.text)
    local font      = params.font or ccs.DEFAULT_TTF_FONT
    local fontSize  = params.fontSize or ccs.DEFAULT_TTF_FONT_SIZE

    local label = CCSWidgetExtend.extend(widget_table[UI_LABEL].create())
    
    if label:init(params) == false then
        assert(false,"[ccs.label] failed to initialize!")
        return nil
    end
    label:setFontName(font)
    label:setFontSize(fontSize)
    label:setText(text)

    return label
end

function ccs.TextArea(params)
    assert(type(params) == "table", "[ccs.TextArea] invalid params")
    local areaSize      = params.size or ccs.DEFAULT_TEXTAREA_SIZE
    assert(tolua.type(areaSize) == "CCSize", "[ccs.TextArea] invalid params.size")
    local h_alignment   = params.H_alignment
    local v_alignment   = params.A_alignment
    local textArea      = ccs.label(params)

    textArea:setTextAreaSize(areaSize)
    if h_alignment then
        textArea:setTextHorizontalAlignment(h_alignment)
    end
    if v_alignment then
        textArea:setTextVerticalAlignment(v_alignment)
    end

    return textArea
end

function ccs.labelAtlas(params)
    assert(type(params) == "table","[ccs.labelAtlas] invalid params")
    local text      = params.text or "0"
    local start     = params.start or "0"
    local image     = params.image
    assert(image and type(image) == "string", "[ccs.labelAtlas] invalid params.image")
    local width     = params.w or 1
    local height    = params.h or 1

    local labelAtlas = CCSWidgetExtend.extend(widget_table[UI_LABELATLAS].create())
    
    if labelAtlas:init(params) == false then
        assert(false,"[ccs.labelAtlas] failed to initialize!")
        return nil
    end

    if image then
        labelAtlas:setProperty(text,image,width,height,start)
    end

    return labelAtlas
end

function ccs.image(params)
    assert(type(params) == "table","[ccs.image] invalid params")
    local image = params.image
    assert(image and type(image) == "string", "[ccs.image] invalid params.image")
    local imageView = CCSWidgetExtend.extend(widget_table[UI_IMAGEVIEW].create())

    if imageView:init(params) == false then
        assert(false,"[ccs.image] failed to initialize!")
        return nil
    end

    if image then
        imageView:loadTexture(image)
    end

    return imageView
end

function ccs.labelBMFont(params)
    assert(type(params) == "table","[ccs.labelBMFont] invalid params")
    local font      = params.font
    assert(font and type(font) == "string","[ccs.labelBMFont] invalid params.font")
    local text      = tostring(params.text)

    local labelBMF = CCSWidgetExtend.extend(widget_table[UI_LABELBMFONT].create())

    if labelBMF:init(params) == false then
        assert(false,"[ccs.labelBMF] failed to initialize!")
        return nil
    end
    
    labelBMF:setFntFile(font)
    labelBMF:setText(text)

    return labelBMF
end

function ccs.checkBox(params)
    assert(type(params) == "table","[ccs.checkBox] invalid params")
    local normal            = params.normal
    local pressed           = params.pressed or ""
    local active            = params.active or ""
    local normal_disable    = params.n_disable or ""
    local active_disable    = params.a_disable or ""
    assert(normal and type(normal) == "string","[ccs.checkBox] invalid params.normal")
    
    local checkBox = CCSWidgetExtend.extend(widget_table[UI_CHECKBOX].create())

    if checkBox:init(params) == false then
        assert(false,"[ccs.checkBox] failed to initialize!")
        return nil
    end

    checkBox:loadTextures(normal,pressed,active,normal_disable,active_disable)
    
    return checkBox
end

function ccs.slider(params)
    assert(type(params) == "table","[ccs.slider] invalid params")
    local bar_image        = params.bar or ""
    local progress         = params.progress or ""
    local ball_normal      = params.ball_n or ""
    local ball_pressed     = params.ball_p or ""
    local ball_disable     = params.ball_d or ""
    local capInsets        = params.capInsets or ccs.DEFAULT_CAPINSETS
    assert(tolua.type(capInsets) == "CCRect", "[ccs.slider] invalid params.capInsets")
    local size             = params.size

    local slider = CCSWidgetExtend.extend(widget_table[UI_SLIDER].create())

    if slider:init(params) == false then
        assert(false,"[ccs.slider] failed to initialize!")
        return nil
    end

    slider:loadBarTexture(bar_image)
    slider:loadSlidBallTextures(ball_normal,ball_pressed,ball_disable)
    slider:loadProgressBarTexture(progress)

    --开启9宫格模式
    if size then
        slider:setScale9Enabled(true)
        slider:setCapInsets(capInsets)
        slider:setSize(size)
    end

    return slider
end

function ccs.loadingbar(params)
    assert(type(params) == "table","[ccs.loadingbar] invalid params")
    local image     = tostring(params.image)
    local percent   = params.percent or 100 
    local direction = params.dir

    local loadingbar = CCSWidgetExtend.extend(widget_table[UI_LOADINGBAR].create())

    if loadingbar:init(params) == false then
        assert(false,"[ccs.loadingbar] failed to initialize!")
        return nil
    end

    loadingbar:loadTexture(image)
    loadingbar:setPercent(percent)

    if direction then
        loadingbar:setDirection(direction)
    end

    return loadingbar
end

function ccs.textField(params)
    assert(type(params) == "table","[ccs.textField] invalid params")
    local font      = params.font or ccs.DEFAULT_TTF_FONT
    local fontSize  = params.fontSize or ccs.DEFAULT_TTF_FONT_SIZE
    local placeHolder   = params.holder or ccs.DEFAULT_INPUT_HOLDER
    local maxLength = params.max
    local password  = params.password or false
    local passwordText = params.passwordText or "*"

    local textField = CCSWidgetExtend.extend(widget_table[UI_TEXTFIELD].create())

    if textField:init(params) == false then
        assert(false,"[ccs.textField] failed to initialize!")
        return nil
    end

    textField:setFontName(font)
    textField:setFontSize(fontSize)
    textField:setPlaceHolder(placeHolder)

    if maxLength then
        if type(maxLength) == "number" then
            textField:setMaxLengthEnabled(true)
            textField:setMaxLength(3)
        else
            assert(false,"[ccs.textField] invalid params.maxLength")
        end
    end

    if password == true then
        textField:setPasswordEnabled(true)
        textField:setPasswordStyleText(passwordText)
    end

    return textField
end

--
-- layout group
--

function ccs.panel(params)
    assert(type(params) == "table","[ccs.plane] invalid params")
    local clip          = params.clip

    local panel = CCSLayoutExtend.extend(widget_table[UI_PANEL].create())

    if panel:initlayout(params) == false then
        assert(false, "[ccs.panel] failed to initialize!")
        return nil
    end

    if clip then
        assert(type(clip) == "boolean", "[ccs.plane] invalid params.clip")
        panel:setClippingEnabled(clip)
    end

    return panel
end

function ccs.listView(params)
    assert(type(params) == "table","[ccs.listView] invalid params")
    local direction = params.direction

    local listView = CCSLayoutExtend.extend(widget_table[UI_LISTVIEW].create())

    if listView:initlayout(params) == false then
        assert(false, "[ccs.listView] failed to initialize!")
        return nil
    end

    if direction then
        listView:setDirection(direction)
    end

    return listView
end

function ccs.listViewEx(params)
    assert(type(params) == "table", "[ccs.listViewEx] invalid params")
    local gravity   = params.gravity
    local margin    = params.margin
    local direction = params.direction
    local bounce    = params.bounce
    local inertia   = params.inertia
    local innerSize = params.innerSize

    local listViewEx = CCSLayoutExtend.extend(widget_table[UI_LISTVIEWEX].create())

    if listViewEx:initlayout(params) == false then
        assert(false, "[ccs.listViewEx] failed to initialize!")
        return nil
    end

    if gravity then
        listViewEx:setGravity(gravity)
    end

    if margin then
        listViewEx:setItemsMargin(margin)
    end

    if direction then
        listViewEx:setDirection(direction)
    end

    if bounce then
        listViewEx:setBounceEnabled(bounce)
    end

    if inertia then
        listViewEx:setInertiaScrollEnabled(inertia)
    end

    if innerSize then
        listViewEx:setInnerContainerSize(innerSize)
    else
        listViewEx:setInnerContainerSize(scrollview:getSize())
    end

    return listViewEx
end

function ccs.dragPanel(params)
    params.direction = SCROLLVIEW_DIR_BOTH
    local dragPanel = ccs.scrollView(params)
    return dragPanel
end

function ccs.scrollView(params)
    assert(type(params) == "table","[ccs.scrollView] invalid params")
    local direction = params.direction
    local bounce    = params.bounce
    local inertia   = params.inertia
    local innerSize = params.innerSize

    local scrollView = CCSLayoutExtend.extend(widget_table[UI_SCROLLVIEW].create())

    if scrollView:initlayout(params) == false then
        assert(false, "[ccs.scrollView] failed to initialize!")
        return nil
    end
    
    if direction then
        scrollView:setDirection(direction)
    end

    if bounce then
        scrollView:setBounceEnabled(bounce)
    end

    if inertia then
        scrollView:setInertiaScrollEnabled(inertia)
    end

    if innerSize then
        scrollView:setInnerContainerSize(innerSize)
    else
        scrollview:setInnerContainerSize(scrollview:getSize())
    end

    return scrollView
end

function ccs.pageView(params)
    assert(type(params) == "table","[ccs.pageView] invalid params")

    local pageView = CCSLayoutExtend.extend(widget_table[UI_PAGEVIEW].create())

    if pageView:initlayout(params) == false then
        assert(false, "[ccs.pageView] failed to initialize!")
        return nil
    end

    return pageView
end

function ccs.loadLayer(filename)
    local layer = ccs.layer()
    layer:load(filename)
    return layer
end

function ccs.loadWidget(filename)
	local widget = CCSWidgetExtend.extend(GUIReader:shareReader():widgetFromJsonFile(filename))
	return widget
end

return ccs