
require("config")
require("framework.init")
require("framework.client.init")

-- define global module
game = {}

function game.startup()
    if display.contentScaleFactor <= 0.50 then
        -- for iPhone 3Gs, use low-res assets
        CCFileUtils:sharedFileUtils():addSearchResolutionsOrder("res/sd/")
        CCDirector:sharedDirector():setContentScaleFactor(display.contentScaleFactor)
    else
        CCFileUtils:sharedFileUtils():addSearchResolutionsOrder("res/hd/")
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
end
