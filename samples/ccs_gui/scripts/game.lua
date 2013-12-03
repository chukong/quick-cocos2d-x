game = game or {}

local sharedDirector = CCDirector:sharedDirector()
function  testLayer()
    local s = sharedDirector:getWinSize()
    local layer = ccs.layer()
    local label = ccs.label({ text = "Touch",
        x = s.width/2,
        y = s.height - 20,
        })
    layer:addWidget(label)
    local label2 = ccs.label({ text = "Touch",
    x = s.width/2,
    y = s.height - 50,
    })
    layer:addWidget(label2)
    local menu  = ccs.menu({
        size = CCSizeMake(200,200),
        colorType = LAYOUT_COLOR_SOLID,
        color = ccc3(200,0,0),
        x = s.width/2 - 100,
        y = s.height/2 - 100,
        type = LAYOUT_LINEAR_HORIZONTAL,
        })
    local button = ccs.button({ 
        touch = false,
        normal = "animationbuttonnormal.png",
        pressed = "animationbuttonpressed.png",
        x = s.width/2,
        y = s.height/2,
        text = "中文按键",
        
        listener = { [ccs.TouchEventType.began]  = function(uiwidget) label:setText("按键1 Touch Down") end,
                     [ccs.TouchEventType.moved]  = function(uiwidget) label:setText("按键1 Touch Move") end,
                     [ccs.TouchEventType.ended]  = function(uiwidget) label:setText("按键1 Touch Up") end,
                     [ccs.TouchEventType.canceled]   = function(uiwidget) label:setText("按键1 Touch Cancel") end,}
        
        })
    local button2 = ccs.button({ 
    touch = false,
    normal = "animationbuttonnormal.png",
    pressed = "animationbuttonpressed.png",
    x = s.width/2,
    y = s.height/2,
    text = "中文按键2",

    listener = { [ccs.TouchEventType.began]  = function(uiwidget) label2:setText("按键2 Touch Down") end,
                 [ccs.TouchEventType.moved]  = function(uiwidget) label2:setText("按键2 Touch Move") end,
                 [ccs.TouchEventType.ended]  = function(uiwidget) label2:setText("按键2 Touch Up") end,
                 [ccs.TouchEventType.canceled]   = function(uiwidget) label2:setText("按键2 Touch Cancel") end,}
    
    })

    menu:AutoLayout(1,button,button2)

    menu:doLayout()

    layer:addWidget(menu)
    return layer
end
function createLayer()
    local s = sharedDirector:getWinSize()
    local layer = ccs.layer()

    local label = ccs.label({ text = "Touch",
        x = s.width/2,
        y = s.height/2 - 35
        })
    local button = ccs.button({ 
        normal = "animationbuttonnormal.png",
        pressed = "animationbuttonpressed.png",
        x = s.width/2,
        y = s.height/2,
        text = "中文按键",
        listener = { [ccs.TouchEventType.began]  = function(uiwidget) label:setText("Touch Down") end,
                     [ccs.TouchEventType.moved]  = function(uiwidget) label:setText("Touch Move") end,
                     [ccs.TouchEventType.ended]  = function(uiwidget) label:setText("Touch Up") end,
                     [ccs.TouchEventType.canceled]   = function(uiwidget) label:setText("Touch Cancel") end,}
        })
    local labelAtlas = ccs.labelAtlas( {text = "9527", 
        image = "labelatlas.png",
        start = "0",
        w = 17,
        h = 22,
        x = s.width/2,
        y = s.height/2 + 35,
        })
    local imageView = ccs.image({ image = "ccicon.png",
        x = s.width/3,
        y = s.height/2, 
        })
    local labelBMF = ccs.labelBMFont({
        font = "bitmapFontTest2.fnt",
        text = "TestBMFont",
        x = s.width/2,
        y = s.height - 50,
        })
    local function checked(uiwidget)
        layer:GroupSelected(1,uiwidget)
    end
    local function unchecked(uiwidget)
        uiwidget:setSelectedState(true)
    end

    local checkBox1 = ccs.checkBox({
        normal      = "check_box_normal.png",
        pressed     = "check_box_normal_press.png",
        active      = "check_box_active.png",
        n_disable   = "check_box_normal_disable.png",
        a_disable   = "check_box_active_disable.png",
        x   = s.width/3*2,
        y   = s.height/3*2,
        listener    = {[ccs.CheckBoxEventType.selected]     = checked,
                       [ccs.CheckBoxEventType.unselected]   = unchecked,}
        })
    local checkBox2 = ccs.checkBox({
        normal      = "check_box_normal.png",
        pressed     = "check_box_normal_press.png",
        active      = "check_box_active.png",
        n_disable   = "check_box_normal_disable.png",
        a_disable   = "check_box_active_disable.png",
        x   = s.width/3*2,
        y   = s.height/3*2-40,
        listener    = {[ccs.CheckBoxEventType.selected]     = checked,
                       [ccs.CheckBoxEventType.unselected]   = unchecked,}
        })

    layer:insterGroup(1,checkBox1,checkBox2)
    layer:GroupDefault(1,checkBox1)

    local function sliderCallBack(uiwidget)
        local percent = uiwidget:getPercent()
        label:setText(string.format("Percent %d",percent))
    end
    local slider = ccs.slider({
        bar     = "sliderTrack.png",
        ball_n  = "sliderThumb.png",
        ball_p  = "sliderThumb.png",
        progress = "sliderProgress.png",
        listener = {[ccs.SliderEventType.changed] = sliderCallBack},
        x   = s.width/2,
        y   = label:getPosition().y - 20,
        })
    local slider2 = ccs.slider({
        bar     = "sliderTrack2.png",
        ball_n  = "sliderThumb.png",
        ball_p  = "sliderThumb.png",
        progress = "slider_bar_active_9patch.png",
        size     = CCSizeMake(250,10),
        listener = {[ccs.SliderEventType.changed] = sliderCallBack},
        x = s.width/2,
        y = slider:getPosition().y - 30,
        })

    local loadingbar1 = ccs.loadingbar({
        image = "sliderProgress.png",
        x = s.width/2,
        y = slider2:getPosition().y - 30,
        })

    local loadingbar2 = ccs.loadingbar({
        image = "sliderProgress.png",
        x = s.width/2,
        y = loadingbar1:getPosition().y - 30,
        dir = LoadingBarTypeRight,
        })
    
    local count = 0
    local function update(dt)
        count = count + 1
        if count > 100 then
            count = 0
        end
        loadingbar1:setPercent(count)
        loadingbar2:setPercent(count)
    end
    layer:scheduleUpdateWithPriorityLua(update,0)

    local nextbutton = ccs.button({
        normal  = "f1.png",
        pressed = "f2.png",
        listener = {[ccs.TouchEventType.ended] = function() game.next() end},
        })

    SET_POS(nextbutton,s.width-nextbutton:getContentSize().width/2,nextbutton:getContentSize().height/2)

    layer:addWidget(button)
    layer:addWidget(label)
    layer:addWidget(labelAtlas)
    layer:addWidget(imageView)
    layer:addWidget(labelBMF)
    layer:addWidget(checkBox1)
    layer:addWidget(checkBox2)
    layer:addWidget(slider)
    layer:addWidget(slider2)
    layer:addWidget(loadingbar1)
    layer:addWidget(loadingbar2)
    layer:addWidget(nextbutton)
    return layer
end

function game.startup()
    local sceneGame = CCScene:create()
  
    sceneGame:addChild(createLayer())
    sharedDirector:runWithScene(sceneGame)
end

function game.next()
    local sceneGame = CCScene:create()
    local layer = ccs.layer()
    local prevButton = ccs.button({
        normal  = "b1.png",
        pressed = "b2.png",
        listener = {[ccs.TouchEventType.ended] = function() game.prev() end},
        })
    SET_POS(prevButton,prevButton:getContentSize().width/2,prevButton:getContentSize().height/2)
    local s = sharedDirector:getWinSize()

    local label = ccs.label({
        text = "touch event here",
        x = s.width/2,
        y = s.height/2,
        })
    layer:addWidget(label)

    local panel = ccs.panel({
    size         = CCSizeMake(100,100),
    colorType    = LAYOUT_COLOR_SOLID, 
    color        = ccc3(128, 128, 128),
    x   = 0,
    y   = s.height - 100,
    })

    local panel2 = ccs.panel({
        size         = CCSizeMake(100,100),
        colorType    = LAYOUT_COLOR_GRADIENT, 
        color        = ccc3(64, 64, 64),
        endColor     = ccc3(192, 192, 192),
        x   = panel:getSize().width + 5,
        y   = s.height - 100,
        })
    local listView = ccs.listView({
        scale9 = true,
        image  = "green_edit.png",
        size   = CCSizeMake(110,100),
        x = panel2:getSize().width + panel2:getPosition().x + 5,
        y = s.height - 100,
        listener = { [ccs.ListViewEventType.updateChild] = function(uiwidget)
        label:setText(string.format("v_list_update:%d",uiwidget:getUpdateDataIndex()))
        uiwidget:setUpdateSuccess(true)
        end}
        })

    for i=0,4 do 
        local button = ccs.button({
            pressed     = "backtotoppressed.png",
            normal      = "backtotopnormal.png",
            text        = string.format("object_%d",i),
            })
        local layout = ccs.panel({
            size = button:getSize(),
            })
        SET_POS(button,layout:getSize().width/2,layout:getSize().height/2)
        layout:addChild(button)
        SET_POS(layout,(listView:getSize().width - layout:getSize().width)/2,listView:getSize().height - layout:getSize().height*1.25 * (i+1))
        listView:addChild(layout)
    end
    listView:initChildWithDataLength(20)

    local listView2 = ccs.listView({
        scale9 = true,
        image  = "green_edit.png",
        size   = CCSizeMake(110,100),
        direction = LISTVIEW_DIR_HORIZONTAL,
        x = listView:getSize().width + listView:getPosition().x + 5,
        y = listView:getPosition().y,
        listener = {[ccs.ListViewEventType.updateChild] = function(uiwidget)
        label:setText(string.format("h_list_update:%d",uiwidget:getUpdateDataIndex()))
        uiwidget:setUpdateSuccess(true)
        end}
        })

    for i=0,2 do
        local button = ccs.button({
            pressed     = "backtotoppressed.png",
            normal      = "backtotopnormal.png",
            text        = string.format("object_%d",i),
            })
        local layout = ccs.panel({
            size = button:getSize(),
            })
        SET_POS(button,layout:getSize().width/2,layout:getSize().height/2)
        SET_POS(layout,i*layout:getSize().width,(listView2:getSize().height - layout:getSize().height)/2)
        layout:addChild(button)
        listView2:addChild(layout)
    end
    listView2:initChildWithDataLength(20)

    local pageView = ccs.pageView({
        size = CCSizeMake(110,100),
        x = 0,
        y = panel:getPosition().y - 100,
        listener = {[ccs.PageViewEventType.turning] = function(uiwidget)
            label:setText(string.format("pageView turning %d",uiwidget:getCurPageIndex()+1))
        end}
        })
    for i=1,3 do
        local layout = ccs.panel({
            size = pageView:getSize()
            })
        local image = ccs.image({
            scale9 = true,
            image  = "scrollviewbg.png", 
            size   = pageView:getSize(),
            x = layout:getSize().width/2,
            y = layout:getSize().height/2,
            })
        layout:addChild(image)
        local pageLabel = ccs.label({
            text = string.format("page=%d",i),
            fontSize = 20,
            color = ccc3(192,192,192),
            x = layout:getSize().width/2,
            y = layout:getSize().height/2,
            })
        layout:addChild(pageLabel)
        pageView:addPage(layout)
    end

    local b11 = ccs.image({
        image = "b11.png",
        }) 

    local dragPanel = ccs.dragPanel({
        bounce  = true,
        size    = CCSizeMake(200,100),
        scale9  = true,
        image   = "green_edit.png",
        x       = listView2:getPosition().x,
        y       = listView2:getPosition().y - 100,
        innerSize = b11:getSize(),
        listener = { [ccs.ScrollViewEventType.scrollToTop] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.scrollToTop)
        end,
        [ccs.ScrollViewEventType.scrollToBottom] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.scrollToBottom)
        end,
        [ccs.ScrollViewEventType.scrollToLeft] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.scrollToLeft)
        end,
        [ccs.ScrollViewEventType.scrollToRight] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.scrollToRight)
        end,
        [ccs.ScrollViewEventType.scrolling] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.scrolling)
        end,
        [ccs.ScrollViewEventType.bounce_top] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.bounce_top)
        end,
        [ccs.ScrollViewEventType.bounce_bottom] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.bounce_bottom)
        end,
        [ccs.ScrollViewEventType.bounce_left] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.bounce_left)
        end,
        [ccs.ScrollViewEventType.bounce_right] = function(uiwidget) 
        label:setText(ccs.ScrollViewEventType.bounce_right)
        end,}
        })
    SET_POS(b11,b11:getSize().width/2,b11:getSize().height/2)
    dragPanel:addChild(b11)

    local nextbutton = ccs.button({
        normal  = "f1.png",
        pressed = "f2.png",
        listener = {[ccs.TouchEventType.ended] = function() game.test() end},
        })

    SET_POS(nextbutton,s.width-nextbutton:getContentSize().width/2,nextbutton:getContentSize().height/2)
    layer:addWidget(nextbutton)
    layer:addWidget(prevButton)
    layer:addWidget(panel)
    layer:addWidget(panel2)
    layer:addWidget(listView)
    layer:addWidget(listView2)
    layer:addWidget(pageView)
    layer:addWidget(dragPanel)
    sceneGame:addChild(layer)
    sharedDirector:replaceScene(sceneGame)
end

function game.prev()
     local sceneGame = CCScene:create()
     sceneGame:addChild(createLayer())
     sharedDirector:replaceScene(sceneGame)
end

function game.test()
    local s = sharedDirector:getWinSize()
    local scene = CCScene:create()
    local layer = ccs.loadLayer("DemoMap/DemoMap.ExportJson")
    local prevButton = ccs.button({
        normal  = "b1.png",
        pressed = "b2.png",
        listener = {[ccs.TouchEventType.ended] = function() game.next() end},
        })
    SET_POS(prevButton,prevButton:getContentSize().width/2,s.height - prevButton:getContentSize().height/2)
    layer:addWidget(prevButton)
    scene:addChild(layer)
    sharedDirector:replaceScene(scene)
end
