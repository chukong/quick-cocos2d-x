
local ScrollViewCell = require("ui.ScrollViewCell")
local LevelsListCell = class("LevelsListCell", ScrollViewCell)

function LevelsListCell:ctor(size, beginLevelIndex, endLevelIndex, rows, cols)
    local rowHeight = math.floor((display.height - 340) / rows)
    local colWidth = math.floor(display.width * 0.9 / cols)

    local batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    self:addChild(batch)
    self.pageIndex_ = pageIndex
    self.buttons_ = {}

    local startX = (display.width - colWidth * (cols - 1)) / 2
    local y = display.top - 220
    local levelIndex = beginLevelIndex

    for row = 1, rows do
        local x = startX
        for column = 1, cols do
            local icon = display.newSprite("#LockedLevelIcon.png", x, y)
            batch:addChild(icon)
            icon.levelIndex_ = levelIndex
            self.buttons_[#self.buttons_ + 1] = icon

            local label = ui.newBMFontLabel({
                text = tostring(levelIndex),
                font = "UIFont.fnt",
                x = x,
                y = y - 4,
            })
            self:addChild(label)

            x = x + colWidth
            levelIndex = levelIndex + 1
            if levelIndex > endLevelIndex then break end
        end

        y = y - rowHeight
        if levelIndex > endLevelIndex then break end
    end

    -- add highlight level icon
    self.highlightButton_ = display.newSprite("#HighlightLevelIcon.png")
    self.highlightButton_:setVisible(false)
    self:addChild(self.highlightButton_)
end

function LevelsListCell:onTouch(event, x, y)
    if event == "began" then
        local button = self:checkButton(x, y)
        if button then
            self.highlightButton_:setVisible(true)
            self.highlightButton_:setPosition(button:getPosition())
        end
    elseif event ~= "moved" then
        self.highlightButton_:setVisible(false)
    end
end

function LevelsListCell:onTap(x, y)
    local button = self:checkButton(x, y)
    if button then
        print("tap button:", button.levelIndex_)
    end
end

function LevelsListCell:checkButton(x, y)
    local pos = ccp(x, y)
    for i = 1, #self.buttons_ do
        local button = self.buttons_[i]
        if button:boundingBox():containsPoint(pos) then
            return button
        end
    end
    return nil
end

return LevelsListCell
