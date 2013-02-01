
local Levels = require("data.Levels")
local PageControlPage = require("views.PageControlPage")

local LevelsList = class("LevelsList", function()
    return display.newNode()
end)

function LevelsList:ctor()
    -- create page control
    local rect = {
        left   = display.left + 40,
        top    = display.top - 40,
        width  = display.width - 80,
        height = display.height - 180,
    }
    local pageControl = require("views.PageControl").new(rect)
    self:addChild(pageControl)

    -- add page
    local numPages = math.ceil(Levels.numLevels() / 18)

    for page = 1, numPages do
        local page = PageControlPage.new()
        pageControl:addPage(page)

        local batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
        page:addChild(batch)

        local y = display.cy + 140
        local offset = (display.width - 220) / 5
        for row = 1, 3 do
            local x = display.left + 110
            for column = 1, 6 do
                local icon = display.newSprite("#LockedLevelIcon.png", x, y)
                batch:addChild(icon)
                x = x + offset
            end

            y = y - 120
        end
    end
end

return LevelsList
