
local ScrollView = class("ScrollView", function(rect)
    return display.newClippingRegionNode(rect)
end)

require("framework.client.api.EventProtocol").extend(ScrollView)

ScrollView.DIRECTION_VERTICAL   = 1
ScrollView.DIRECTION_HORIZONTAL = 2

function ScrollView:ctor(rect, direction)
    -- rect passed to newClippingNode()
    assert(direction == ScrollView.DIRECTION_VERTICAL or direction == ScrollView.DIRECTION_HORIZONTAL,
           "ScrollView:ctor() - invalid direction")
    self.dragThreshold = 40
    self.bouncThreshold = 140
    self.defaultAnimateTime = 0.4
    self.defaultAnimateEasing = "backOut"

    self.direction_ = direction
    self.touchRect_ = rect
    self.offsetX_ = 0
    self.offsetY_ = 0
    self.cells_ = {}
    self.currentIndex_ = 0

    -- create container layer
    self.view_ = display.newLayer()
    self:addChild(self.view_)

    self.view_:addTouchEventListener(function(event, x, y)
        return self:onTouch_(event, x, y)
    end)

    self:registerScriptHandler(function(event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function ScrollView:getCurrentCell()
    if self.currentIndex_ > 0 then
        return self.cells_[self.currentIndex_]
    else
        return nil
    end
end

function ScrollView:getCurrentIndex()
    return self.currentIndex_
end

function ScrollView:setCurrentIndex(index)
    self:scrollToCell(index)
end

function ScrollView:addCell(cell)
    self.view_:addChild(cell)
    self.cells_[#self.cells_ + 1] = cell
    self:reorderAllCells_()
    self:dispatchEvent({name = "addCell", count = #self.cells_})
end

function ScrollView:insertCellAtIndex(cell, index)
    self.view_:addChild(cell)
    table.insert(self.cells_, index, cell)
    self:reorderAllCells_()
    self:dispatchEvent({name = "insertCellAtIndex", index = index, count = #self.cells_})
end

function ScrollView:removeCellAtIndex(index)
    local cell = self.cells_[index]
    cell:removeSelf()
    table.remove(self.cells_, index)
    self:reorderAllCells_()
    self:dispatchEvent({name = "removeCellAtIndex", index = index, count = #self.cells_})
end

function ScrollView:getView()
    return self.view_
end

function ScrollView:getTouchRect()
    return self.touchRect_
end

function ScrollView:setTouchRect(rect)
    self.touchRect_ = rect
    self:dispatchEvent({name = "setTouchRect", rect = rect})
end

function ScrollView:getClippingRect()
    return self:getClippingRegion()
end

function ScrollView:setClippingRect(rect)
    self:setClippingRegion(rect)
    if self.debugClippingRect_ then
        self:createDebugView()
    end
    self:dispatchEvent({name = "setClippingRect", rect = rect})
end

function ScrollView:scrollToCell(index, animated, time, easing)
    local count = #self.cells_
    if count < 1 then
        self.currentIndex_ = 0
        return
    end

    if index < 1 then
        index = 1
    elseif index > count then
        index = count
    end
    self.currentIndex_ = index

    local offset = 0
    for i = 2, index do
        local cell = self.cells_[i - 1]
        local size = cell:getContentSize()
        if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
            offset = offset - size.width
        else
            offset = offset + size.height
        end
    end

    self:setContentOffset_(offset, animated, time, easing)
    self:dispatchEvent({name = "scrollToCell", animated = animated, time = time, easing = easing})
end

function ScrollView:isTouchEnabled()
    return self.view_:isTouchEnabled()
end

function ScrollView:setTouchEnabled(enabled)
    self.view_:setTouchEnabled(enabled)
    self:dispatchEvent({name = "setTouchEnabled", enabled = enabled})
end

---- events

function ScrollView:onEnter()
end

function ScrollView:onExit()
end

---- debug

function ScrollView:createDebugView()
    self:removeDebugView()
    self.debugClippingRect_ = display.newRect(self:getClippingRect())
    self.debugClippingRect_:setColor(64, 32, 32, 32)
    self.debugClippingRect_:setFill(true)
    self:addChild(self.debugClippingRect_, -10000)
end

function ScrollView:removeDebugView()
    if self.debugClippingRect_ then
        self.debugClippingRect_:removeSelf()
        self.debugClippingRect_ = nil
    end
end

---- private methods

function ScrollView:reorderAllCells_()
    local count = #self.cells_
    local x, y = 0, 0
    local maxWidth, maxHeight = 0, 0
    for i = 1, count do
        local cell = self.cells_[i]
        cell:setPosition(x, y)
        if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
            local width = cell:getContentSize().width
            if width > maxWidth then maxWidth = width end
            x = x + width
        else
            local height = cell:getContentSize().height
            if height > maxHeight then maxHeight = height end
            y = y - height
        end
    end

    if count > 0 then
        if self.currentIndex_ < 1 then
            self.currentIndex_ = 1
        elseif self.currentIndex_ > count then
            self.currentIndex_ = count
        end
    else
        self.currentIndex_ = 0
    end

    local size
    if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
        size = CCSize(x, maxHeight)
    else
        size = CCSize(maxWidth, math.abs(y))
    end
    self.view_:setContentSize(size)
end

function ScrollView:setContentOffset_(offset, animated, time, easing)
    local ox, oy = self.offsetX_, self.offsetY_
    local x, y = ox, oy
    if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
        self.offsetX_ = offset
        x = offset

        local maxX = self.bouncThreshold
        local minX = -self.view_:getContentSize().width - self.bouncThreshold + self.touchRect_.size.width
        if x > maxX then
            x = maxX
        elseif x < minX then
            x = minX
        end
    else
        self.offsetY_ = offset
        y = offset

        local maxY = self.view_:getContentSize().height + self.bouncThreshold - self.touchRect_.size.height
        local minY = -self.bouncThreshold
        if y > maxY then
            y = maxY
        elseif y < minY then
            y = minY
        end
    end

    if animated then
        transition.stopTarget(self.view_)
        transition.moveTo(self.view_, {
            x = x,
            y = y,
            time = time or self.defaultAnimateTime,
            easing = easing or self.defaultAnimateEasing,
        })
    else
        self.view_:setPosition(x, y)
    end
end

function ScrollView:onTouch_(event, x, y)
    if self.currentIndex_ < 1 then return end

    if event == "began" then
        if not self.touchRect_:containsPoint(ccp(x, y)) then return false end

        self.drag = {
            currentOffsetX = self.offsetX_,
            currentOffsetY = self.offsetY_,
            startX = x,
            startY = y,
            isTap = true,
        }

        local cell = self:getCurrentCell()
        cell:onTouch(event, x, y)

        return true

    elseif event == "moved" then
        local cell = self:getCurrentCell()
        if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
            if self.drag.isTap and math.abs(x - self.drag.startX) >= self.dragThreshold then
                self.drag.isTap = false
                cell:onTouch("cancelled", x, y)
            end

            if not self.drag.isTap then
                self:setContentOffset_(x - self.drag.startX + self.drag.currentOffsetX)
            else
                cell:onTouch(event, x, y)
            end
        else
            if self.drag.isTap and math.abs(y - self.drag.startY) >= self.dragThreshold then
                self.drag.isTap = false
                cell:onTouch("cancelled", x, y)
            end

            if not self.drag.isTap then
                self:setContentOffset_(y - self.drag.startY + self.drag.currentOffsetY)
            else
                cell:onTouch(event, x, y)
            end
        end

    elseif event == "ended" then
        if self.drag.isTap then
            local cell = self:getCurrentCell()
            cell:onTouch(event, x, y)
            cell:onTap(x, y)
        else
            local offsetX, offsetY = self.offsetX_, self.offsetY_
            local index = 0
            local count = #self.cells_
            if self.direction_ == ScrollView.DIRECTION_HORIZONTAL then
                offsetX = -offsetX
                local x = 0
                local i = 1
                while i <= count do
                    local cell = self.cells_[i]
                    local size = cell:getContentSize()
                    if offsetX < x + size.width / 2 then
                        index = i
                        break
                    end
                    x = x + size.width
                    i = i + 1
                end
                if i > count then index = count end
            else
                local y = 0
                local i = 1
                while i <= count do
                    local cell = self.cells_[i]
                    local size = cell:getContentSize()
                    if offsetY < y + size.height / 2 then
                        index = i
                        break
                    end
                    y = y + size.height
                    i = i + 1
                end
                if i > count then index = count end
            end

            self:scrollToCell(index, true)
        end

        self.drag = nil
    else -- ended, cancelled
        self.drag = nil
    end
end

return ScrollView
