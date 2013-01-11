
local M = {}

local EventProtocol = require("framework.client.api.EventProtocol")

local SCROLL_TO_VALID_RANGE_SPEED = 400

function M.new(args)
    local view = display.newLayer()

    view.marginTop          = 0
    view.marginBottom       = 0
    view.items              = {}
    view.isEnabled          = false

    ----

    local sumHeight         = 0
    local frameTime         = 0
    local touch             = nil
    local layer             = nil
    local swiping           = nil
    local paddingTop        = display.height / 8
    local paddingBottom     = paddingTop

    local validTouchTop     = 0
    local validTouchBottom  = 0
    local validTouchHeight  = 0

    ----

    local function snapLayer(isAutoScroll)
        local ny = layer:getPositionY()
        if ny < layer.topY then
            ny = layer.topY
        elseif ny > layer.bottomY then
            ny = layer.bottomY
        end

        if layer:getPositionY() ~= ny then
            local time = math.abs(layer:getPositionY() - ny) / SCROLL_TO_VALID_RANGE_SPEED
            local easing = "backOut"
            if isAutoScroll then easing = {"inOut", 2} end
            transition.moveTo(layer, {y = ny, time = time, easing = easing})
        end
    end

    local function onEnterFrame(dt)
        frameTime = frameTime + dt
        if not swiping then return end

        local moving = swiping.speed * dt
        if swiping.direction then
            -- up
            layer:setPositionY(layer:getPositionY() - moving)
        else
            -- down
            layer:setPositionY(layer:getPositionY() + moving)
        end
        if moving < 1 then
            swiping = nil
            snapLayer(true)
        elseif layer:getPositionY() < layer.topY or layer:getPositionY() > layer.bottomY then
            swiping.speed = swiping.speed * 0.5;
        else
            swiping.speed = swiping.speed * 0.9;
        end
    end

    local function cleanup()
        view:removeTouchEventListener()
        view:unscheduleUpdate()

        -- remove all event listeners
        for i, item in ipairs(view.items) do
            item:removeAllEventListeners()
        end
        view.items = {}
    end

    local function onTouch(event, x, y)
        if not view.isEnabled then return false end
        if event == "began" then
            if y > validTouchTop or y < validTouchBottom then return false end

            touch = {
                initTouchY      = y,
                initLayerY      = layer:getPositionY(),
                isMaybeTap      = (swiping == nil), -- 如果触摸开始时视图尚在自动卷动，则不考虑 tap 事件
                lastTouchTime   = frameTime,
                lastTouchY      = y,
                isMaybySwiping  = false,
                swipingBeganTime= 0,
                swipingBeganY   = 0
            }
            swiping = nil -- 一旦开始触摸，立即停止当前的自动卷动
            return true
        end

        if event == "moved" then
            if touch.lastTouchY == y then
                -- 如果两次触摸事件之间，坐标没有变化，则取消轻扫状态
                touch.isMaybySwiping = false
            else
                -- 如果当前处于轻扫状态，但本次事件距离上次事件的间隔时间超过一定范围，则取消轻扫状态
                if touch.isMaybySwiping then
                    if frameTime - touch.lastTouchTime > 0.034 then
                        touch.isMaybySwiping = false
                    end
                else
                    touch.isMaybySwiping   = true
                    touch.swipingBeganTime = frameTime
                    touch.swipingBeganY    = y
                end
            end

            touch.lastTouchY = y
            touch.lastTouchTime = frameTime

            if touch.isMaybeTap and math.abs(y - touch.initTouchY) >= 10 then
                -- 触摸移动范围超过 10 点，则不再视为 tap 操作
                touch.isMaybeTap = false
            end

            if not touch.isMaybeTap then
                local ny = touch.initLayerY + (y - touch.initTouchY)
                if ny < layer.topY - validTouchHeight / 2 then
                    ny = layer.topY - validTouchHeight / 2
                end
                if ny > layer.bottomY + validTouchHeight / 2 then
                    ny = layer.bottomY + validTouchHeight / 2
                end
                layer:setPositionY(ny)
            end

            return true
        end

        if event == "ended" and touch.isMaybeTap then
            -- tap 事件，确定触发哪一个条目的 listener
            local offset = view:getPositionY() + layer:getPositionY()
            for i, item in ipairs(view.items) do
                if y <= offset and y >= offset - item.itemHeight + 1 then
                    item:dispatchEvent({name = "tap"})
                    break
                end
                offset = offset - item.itemHeight
            end

            return false
        end

        if layer:getPositionY() <= layer.topY or layer:getPositionY() >= layer.bottomY then
            snapLayer()
        elseif touch.isMaybySwiping then
            -- 根据一定时间范围内手指的滑动速度计算惯性
            local time = frameTime - touch.swipingBeganTime
            if time > 0 then
                local offset = y - touch.swipingBeganY
                local speed = math.abs(offset) / time
                swiping = {speed = speed, direction = offset < 0} -- true = up, false = down
            end
        end

        return false
    end

    function setSumHeight()
        -- 计算列表的总高度，并依次排列所有条目
        sumHeight = 0
        for i, item in ipairs(view.items) do
            item:setPositionY(-sumHeight)
            sumHeight = sumHeight + item.itemHeight
        end

        -- 计算条目层的 y 值有效范围
        layer.topY = 0
        layer.bottomY = sumHeight - validTouchHeight + 1
        if layer.bottomY < 0 then layer.bottomY = 0 end
    end

    local function init()
        local keys = {
            marginTop        = "number",
            marginBottom     = "number",
            validTouchBottom = "number",
            validTouchTop    = "number",
            validTouchHeight = "number",
        }
        for k, t in pairs(keys) do
            if type(args[k]) == t then view[k] = args[k] end
        end

        layer = display.newNode()
        view:addChild(layer)

        validTouchTop    = view.validTouchTop    or display.height - view.marginTop - 1
        validTouchBottom = view.validTouchBottom or view.marginBottom
        validTouchHeight = view.validTouchHeight or validTouchTop - validTouchBottom + 1

        setSumHeight()

        view:registerScriptHandler(function(event)
            if event == kCCNodeOnExit then cleanup() end
        end)
    end

    ----

    function view:addItem(item)
        item:setPositionY(sumHeight)
        view.items[#view.items + 1] = item
        item.itemIndex = #view.items
        layer:addChild(item)
        setSumHeight()

        return item.itemIndex
    end

    function view:removeItem(itemIndex)
        for i, item in ipairs(view.items) do
            if i == itemIndex then
                item:removeSelf()
                table.remove(view.items, i)

                for j = i, #view.items do
                    view.items[j].itemIndex = j
                end

                return true
            end
        end
        return false
    end

    function view:getItem(itemIndex)
        if itemIndex >= 1 and itemIndex <= #view.items then
            return view.items[itemIndex]
        end
        return false
    end

    function view:getItemsCount()
        return #view.items
    end

    function view:getItemsLayer()
        return layer
    end

    -- 滚动到指定的条目，确保该条目完整显示在屏幕上
    function view:scrollToItem(itemIndex)
        if itemIndex < 1 or itemIndex > #view.items then return end

        setSumHeight()

        local top    = 0
        local bottom = 0
        for i, item in ipairs(view.items) do
            if i == itemIndex then
                bottom = top - item.itemHeight
                break
            else
                top = top - item.itemHeight
            end
        end

        local y = -layer:getPositionY()
        if top <= y and bottom >= y - validTouchHeight then return end
        if bottom < y - validTouchHeight then
            -- 如果是条目底部不在有效区，则向上滚动
            transition.moveTo(layer, {y = -bottom - validTouchHeight, time = 0.2})
        else
            -- 如果是条目顶部不在有效区，则向下滚动
            transition.moveTo(layer, {y = -top, time = 0.2})
        end
    end

    function view:prepare()
        view:addTouchEventListener(onTouch)
        view:setTouchEnabled(true)
        view:scheduleUpdate(onEnterFrame)
    end

    function view:enable()
        view.isEnabled = true
        for i, item in ipairs(view.items) do
            item:enable()
        end
    end

    function view:disable()
        view.isEnabled = false
        for i, item in ipairs(view.items) do
            item:disable()
        end
    end

    function view:newItem(params)
        if type(params) ~= "table" then params = {} end
        if type(params.height) ~= "number" then params.height = 40 end

        local item = display.newNode()
        EventProtocol.extend(item)
        item.scrollView = view
        item.itemHeight = params.height
        item.itemIndex  = 0
        item.isEnabled = false

        function item:enable()
            item.isEnabled = true
        end

        function item:disable()
            item.isEnabled = false
        end

        return item
    end

    ----

    init()
    return view
end

return M
