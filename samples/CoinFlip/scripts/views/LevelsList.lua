
local ScrollView = require("ui.ScrollView")
local LevelsList = class("LevelsList", ScrollView)

function LevelsList:ctor(rect)
    self.super.ctor(self, rect, ScrollView.DIRECTION_HORIZONTAL)

    -- create page control
    local rect = {
        left   = display.left + 40,
        top    = display.top - 40,
        width  = display.width - 80,
        height = display.height - 180,
    }
    local pageControl = require("views.PageControl").new(rect)
    self.view:addChild(pageControl)

    -- add page
    local Levels = require("data.Levels")
    local numPages = math.ceil(Levels.numLevels() / 18)

    local PageControlPage = require("views.PageControlPage")
    for page = 1, numPages do
        local page = PageControlPage.new()
        pageControl:addPage(page)

        local batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
        self.view:addChild(batch)

        local rows = 4
        if display.height > 1000 then rows = rows + 1 end
        local rowHeight = math.floor((display.height - 340) / rows)
        local y = display.top - 220

        local cols = 4
        local colWidth = math.floor(display.width * 0.9 / cols)
        local xStart = (display.width - colWidth * (cols - 1)) / 2

        for row = 1, rows do
            local x = xStart
            for column = 1, cols do
                local icon = display.newSprite("#LockedLevelIcon.png", x, y)
                batch:addChild(icon)
                x = x + colWidth
            end

            y = y - rowHeight
        end
    end
end

return LevelsList
