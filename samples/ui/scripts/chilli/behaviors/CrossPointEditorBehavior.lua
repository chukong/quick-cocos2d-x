
local math2d          = require("math2d")
local EditorConstants = require("editor.EditorConstants")
local BehaviorBase    = require("app.map.behaviors.BehaviorBase")

local CrossPointEditorBehavior = class("CrossPointEditorBehavior", BehaviorBase)

CrossPointEditorBehavior.SELECTED_COLOR = {255, 255, 0, 255}
CrossPointEditorBehavior.UNSELECTED_COLOR = {190, 190, 90, 255}

function CrossPointEditorBehavior:ctor()
    CrossPointEditorBehavior.super.ctor(self, "CrossPointEditorBehavior", nil, 0)
end

function CrossPointEditorBehavior:bind(object)
    object.isSelected_  = false
    object.flagsSprite_ = {}

    local function createView(object, batch, marksLayer, debugLayer)
        object.idLabel_ = ui.newTTFLabel({
            text  = object:getId(),
            font  = EditorConstants.LABEL_FONT,
            size  = EditorConstants.LABEL_FONT_SIZE,
            color = cc.c3(unpack(EditorConstants.UNSELECTED_LABEL_COLOR)),
            align = ui.TEXT_ALIGN_CENTER,
        })
        debugLayer:addChild(object.idLabel_, EditorConstants.LABEL_ZORDER)

        if object.movingForward_ then
            object.flagSprite_ = display.newSprite("#CrossPointMovingForwardFlag.png")
        else
            object.flagSprite_ = display.newSprite("#CrossPointMovingBackwardFlag.png")
        end
        debugLayer:addChild(object.flagSprite_, EditorConstants.FLAG_ZORDER)
    end
    object:bindMethod(self, "createView", createView)

    local function removeView(object)
        if object.polygons_ then
            for i, polygon in ipairs(object.polygons_) do
                polygon:removeSelf()
            end
            object.polygons_ = nil
        end

        object.idLabel_:removeSelf()
        object.idLabel_ = nil

        object.flagSprite_:removeSelf()
        object.flagSprite_ = nil
    end
    object:bindMethod(self, "removeView", removeView, true)

    local function updateView(object)
        if object.polygons_ then
            for i, polygon in ipairs(object.polygons_) do
                polygon:removeSelf()
            end
        end

        if not object:isValid() then
            object.idLabel_:setVisible(false)
            return
        end

        local scale = object.debugLayer_:getScale()
        if scale > 1 then scale = 1 / scale end

        local map = object.map_
        object.polygons_ = {}
        local x1, y1 = object.x_, object.y_
        for i, dest in ipairs(object.dests_) do
            local destPath = map:getObject(dest.pathId)
            local x2, y2 = destPath:getPoint(dest.pointIndex)
            local radians = math2d.radians4point(x1, y1, x2, y2)
            local degrees = math2d.radians2degrees(radians)
            local x3, y3 = math2d.pointAtCircle(x2, y2, math2d.degrees2radians(degrees - 160), 20)
            local x4, y4 = math2d.pointAtCircle(x2, y2, math2d.degrees2radians(degrees + 160), 20)
            local points = {{x1, y1}, {x2, y2}, {x3, y3}, {x2, y2}, {x4, y4}}
            local polygon = display.newPolygon(points)
            polygon:setLineWidth(2)
            object.debugLayer_:addChild(polygon, EditorConstants.POLYGON_ZORDER - 1)
            object.polygons_[#object.polygons_ + 1] = polygon

            if i == object.selectedIndex_ then
                polygon:setColor(0, 100, 255, 255)
            else
                polygon:setColor(80, 80, 80, 255)
            end
        end

        object.idLabel_:setVisible(true)
        object.idLabel_:setPosition(display.pixels(object.x_, object.y_ + 30))
        object.idLabel_:setScale(scale)

        if object.flagSprite_ then object.flagSprite_:removeSelf() end
        if object.movingForward_ then
            object.flagSprite_ = display.newSprite("#CrossPointMovingForwardFlag.png")
        else
            object.flagSprite_ = display.newSprite("#CrossPointMovingBackwardFlag.png")
        end
        object.debugLayer_:addChild(object.flagSprite_, EditorConstants.FLAG_ZORDER)
        object.flagSprite_:setPosition(display.pixels(object.x_, object.y_ - 10))
        object.flagSprite_:setScale(scale)
    end
    object:bindMethod(self, "updateView", updateView)

    local function checkPointAtDestSegment(object, x, y)
        local map = object.map_
        local minDist = 999999
        local minDistIndex
        local ax, ay = object.x_, object.y_
        for index, dest in ipairs(object.dests_) do
            local bx, by = map:getObject(dest.pathId):getPoint(dest.pointIndex)
            local cx, cy = math2d.pointAtLineToPoint(x, y, ax, ay, bx, by)
            local dist = math2d.dist(x, y, cx, cy)
            if dist <= EditorConstants.CHECK_POINT_DIST and dist < minDist then
                minDist = dist
                minDistIndex = index
            end
        end

        return minDistIndex, minDist
    end
    object:bindMethod(self, "checkPointAtDestSegment", checkPointAtDestSegment)

    local function checkPointAtDestPoint(object, x, y)
        local map = object.map_
        local minDist = 999999
        local minDistIndex
        for index, dest in ipairs(object.dests_) do
            local bx, by = map:getObject(dest.pathId):getPoint(dest.pointIndex)
            local dist = math2d.dist(x, y, bx, by)
            if dist <= EditorConstants.CHECK_POINT_DIST and dist < minDist then
                minDist = dist
                minDistIndex = index
            end
        end

        return minDistIndex
    end
    object:bindMethod(self, "checkPointAtDestPoint", checkPointAtDestPoint)
end

function CrossPointEditorBehavior:unbind(object)
    object.isSelected_  = nil
    object.flagsSprite_ = nil

    object:unbindMethod(self, "createView")
    object:unbindMethod(self, "removeView")
    object:unbindMethod(self, "updateView")
    object:unbindMethod(self, "checkPointAtDestSegment")
    object:unbindMethod(self, "checkPointAtDestPoint")
end

return CrossPointEditorBehavior
