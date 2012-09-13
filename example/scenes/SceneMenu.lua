
local SceneMenu = {}

function SceneMenu.new()
    -- 创建场景对象
    local scene = display.newScene("SceneMenu")

    -- uilayout 是一个容器，放置在屏幕重心。所有的界面元素都添加到 uilayout 中
    local uilayout = display.newGroup()
    -- display.cx, display.cy 是屏幕重心的坐标
    uilayout:setPosition(display.cx, display.cy)
    scene:addChild(uilayout)

    -- 添加背景图
    local bg = display.newSprite("SceneMenuBg.jpg")
    uilayout:addChild(bg)

    -- 标题图是水平居中，垂直方向从屏幕顶部向下移动 120 pt
    local title = display.newSprite("SceneMenuTitle.png")
    -- display.c_top 表示在父对象位于屏幕中心时，屏幕顶部的坐标
    title:setPosition(0, display.c_top - 180)
    uilayout:addChild(title)

    -- 添加两个按钮
    local buttonPlay = ui.newMenuItemImage({
        image = "SceneMenuButtonPlay.png",
        -- display.c_left 表示在父对象位于屏幕中心时，屏幕左侧的坐标
        x = display.c_left + 200,
        y = -160,
    })

    local buttonMore = ui.newMenuItemImage({
        image = "SceneMenuButtonMore.png",
        -- display.c_left 表示在父对象位于屏幕中心时，屏幕右侧的坐标
        x = display.c_right - 200,
        y = -160,
    })

    local menu = ui.newMenu({buttonPlay, buttonMore})
    uilayout:addChild(menu)

    return scene
end

return SceneMenu
