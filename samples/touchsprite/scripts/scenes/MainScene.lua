
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

--[[--

Create a simple button

@param string imageName
@param function listener called when button clicked

@return CCSprite

]]
local function newButton(imageName, listener)
    local sprite = display.newSprite(imageName)
    sprite:setTouchEnabled(true) -- enable sprite touch
    sprite:addTouchEventListener(function(event, x, y)
        -- event: began, moved, ended
        -- x, y: world coordinate
        if event == "began" then
            sprite:setOpacity(128)
            -- return cc.TOUCH_BEGAN -- stop event dispatching
            return cc.TOUCH_BEGAN_NO_SWALLOWS -- continue event dispatching
        end

        local touchInSprite = sprite:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
        if event == "moved" then
            if touchInSprite then
                sprite:setOpacity(128)
            else
                sprite:setOpacity(255)
            end
            -- return cc.TOUCH_MOVED_SWALLOWS -- stop event dispatching
            -- return cc.TOUCH_MOVED_RELEASE_OTHERS -- stop event dispatching, remove others node
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

    local parentButton = newButton("PinkButton.png", function()
        print("PinkButton TAP")
    end):addTo(self):pos(display.right - 200, display.bottom + 300):zorder(1000)

    newButton("BlueButton.png", function()
        print("BlueButton TAP")
        -- parentButton:setVisible(false)
    end):addTo(parentButton):scale(0.5):pos(100, 100)

    newButton("WhiteButton.png", function()
        print("WhiteButton TAP")
    end):addTo(self):pos(display.right - 300, display.bottom + 400)

    newButton("BlueButton.png", function()
        print("BlueButton TAP")
    end):addTo(self):pos(display.right - 400, display.bottom + 500)

    ----

    local batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME):addTo(self)

    newButton("#GreenButton2.png", function()
        print("GreenButton2 TAP")
    end):addTo(batch):pos(display.right - 100, display.bottom + 600)

    local parentButton2 = newButton("#PinkButton2.png", function()
        print("PinkButton2 TAP")
    end):addTo(batch):pos(display.right - 200, display.bottom + 700):zorder(1000)

    newButton("#BlueButton2.png", function()
        print("BlueButton2 TAP")
        -- parentButton2:setVisible(false)
    end):addTo(parentButton2):scale(0.5):pos(100, 100)

    newButton("#WhiteButton2.png", function()
        print("WhiteButton2 TAP")
    end):addTo(batch):pos(display.right - 300, display.bottom + 800)

    newButton("#BlueButton2.png", function()
        print("BlueButton2 TAP")
    end):addTo(batch):pos(display.right - 400, display.bottom + 900)

end

return MenuScene
