-- 0 - disable debug info, 1 - less debug info, 2 - verbose debug info
DEBUG = 2
DEBUG_FPS = false

-- design resolution
CONFIG_SCREEN_WIDTH  = 960
CONFIG_SCREEN_HEIGHT = 640

-- auto scale mode
CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"

CCFileUtils:sharedFileUtils():addSearchPath("res/")

require("framework.init")

-- musics
MUSIC = {
    backgroundMusic = "sound/newdali.mp3",
}

-- effects
EFFECT = {}

-- preload all musics
for k, v in pairs(MUSIC) do
    audio.preloadMusic(v)
end

-- preload all effects
for k, v in pairs(EFFECT) do
    audio.preloadSound(v)
end
