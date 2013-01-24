
require("config")
require("framework.init")
require("framework.client.init")

-- define global module
game = {}

function game.startup()
    if display.contentScaleFactor <= 0.50 then
        -- for iPhone 3Gs, use low-res assets
        CCFileUtils:sharedFileUtils():setResourceDirectory("res/sd/")
        CCDirector:sharedDirector():setContentScaleFactor(display.contentScaleFactor)
    else
        CCFileUtils:sharedFileUtils():setResourceDirectory("res/hd/")
    end
    display.addSpriteFramesWithFile(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)

    if device.platform == "ios" then
        require("config_ios")
    elseif device.platform == "mac" then
        require("config_mac")
    end

    -- preload all sounds
    for k, v in pairs(GAME_SFX) do
        audio.preloadSound(v)
    end

    display.replaceScene(require("scenes.MenuScene").new())
    -- display.replaceScene(require("scenes.ChooseLevelScene").new())
end


-- create bubble button
function game.newBubbleButton(params)
    local listener = params.listener
    local button -- pre-reference

    params.listener = function(tag)
        local function zoom1(offset, time, onComplete)
            local x, y = button:getPosition()
            local size = button:getContentSize()

            local scaleX = button:getScaleX() * (size.width + offset) / size.width
            local scaleY = button:getScaleY() * (size.height - offset) / size.height

            transition.moveTo(button, {y = y - offset, time = time})
            transition.scaleTo(button, {
                scaleX     = scaleX,
                scaleY     = scaleY,
                time       = time,
                onComplete = onComplete,
            })
        end

        local function zoom2(offset, time, onComplete)
            local x, y = button:getPosition()
            local size = button:getContentSize()

            transition.moveTo(button, {y = y + offset, time = time / 2})
            transition.scaleTo(button, {
                scaleX     = 1.0,
                scaleY     = 1.0,
                time       = time,
                onComplete = onComplete,
            })
        end

        button:getParent():setEnabled(false)

        if params.sound then
            audio.playSound(params.sound)
        end

        zoom1(40, 0.08, function()
            zoom2(40, 0.09, function()
                zoom1(20, 0.10, function()
                    zoom2(20, 0.11, function()
                        button:getParent():setEnabled(true)
                        listener(tag)
                    end)
                end)
            end)
        end)
    end

    button = ui.newImageMenuItem(params)
    return button
end
