
import("..includes.functions")

local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)


function MenuScene:ctor()
    local scroll_view = CCScrollView:create()
    local view_width = 405
    local view_height = display.height / 2
    scroll_view:setViewSize(CCSizeMake(view_width,view_height))
    scroll_view:setDirection(1) -- 方向


    local containerLayer = CCLayer:create()
    containerLayer:resetCascadeBoundingBox()
    scroll_view:setContainer(containerLayer)
    self:addChild(scroll_view)


    local h =0


    for i=1,30 do
        local item = display.newSprite("WhiteButton.png") -- 405*77
        item:setAnchorPoint(ccp(0,0))
        local text = string.format("hello,world %s", i)
        local label =  CCLabelTTF:create(text,"",20,CCSize(0,0),1)
        label:setPosition(200, 20)
        item:addChild(label)
        print(i, h)
        item:setPosition(0, h)
        h = 77 * i
        containerLayer:addChild(item)
    end

    local function onTouch(evt,x,y)
        printInfo("-给我打印出来啊，亲，不到到--evt:%s,(x:%s,y:%s)",evt,x,y)
    end

    scroll_view:setContentOffset(ccp(0,view_height-h))
    -- scroll_view:setPosition(120,100)
    scroll_view:setContentSize(CCSizeMake(view_width,h))
    containerLayer:registerScriptTouchHandler(onTouch,false,-128)
    containerLayer:setTouchEnabled(true)
    containerLayer:setTouchSwallowEnabled(false)

    -- self:schedule(function()
        -- local box = scroll_view:getCascadeBoundingBox()
        -- printf("x, y: %0.2f, %0.2f - w, h: %0.2f, %0.2f", box.origin.x, box.origin.y, box.size.width, box.size.height)
        local box = containerLayer:getCascadeBoundingBox()
        printf("x, y: %0.2f, %0.2f - w, h: %0.2f, %0.2f, sh: %0.2f", box.origin.x, box.origin.y, box.size.width, box.size.height, box.origin.y + box.size.height)
        print("-----------------")
    -- end, 1)
end

return MenuScene
