
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

local function newButton(imageName, listener)
    local sprite = display.newSprite(imageName)

    sprite:setTouchEnabled(true)
    sprite:addTouchEventListener(function(event, x, y)
        if event == "began" then
            sprite:setOpacity(128)
            return true
        end

        local touchInSprite = sprite:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
        if event == "moved" then
            if touchInSprite then
                sprite:setOpacity(128)
            else
                sprite:setOpacity(255)
            end
        elseif event == "ended" then
            if touchInSprite then listener() end
            sprite:setOpacity(255)
        else
            sprite:setOpacity(255)
        end
    end)

    return sprite
end

function MenuScene:ctor()
    newButton("GreenButton.png", function()
        print("GreenButton TAP")
    end):addTo(self):pos(display.right - 100, display.bottom + 200)

    local p = newButton("PinkButton.png", function()
        print("PinkButton TAP")
    end):addTo(self):pos(display.right - 200, display.bottom + 300):zorder(1000)
    newButton("BlueButton.png", function()
        print("BlueButton TAP")
    end):addTo(p):scale(0.5):pos(100, 100)

    newButton("WhiteButton.png", function()
        print("WhiteButton TAP")
    end):addTo(self):pos(display.right - 300, display.bottom + 400)

    newButton("BlueButton.png", function()
        print("BlueButton TAP")
    end):addTo(self):pos(display.right - 400, display.bottom + 500)
end

return MenuScene
