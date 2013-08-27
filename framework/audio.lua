
local audio = {}

local sharedEngine = SimpleAudioEngine:sharedEngine()

function audio.getMusicVolume()
    return sharedEngine:getBackgroundMusicVolume()
end
audio.getBackgroundMusicVolume = audio.getMusicVolume

function audio.setMusicVolume(volume)
    sharedEngine:setBackgroundMusicVolume(volume)
end
audio.setBackgroundMusicVolume = audio.setMusicVolume

function audio.getSoundsVolume()
    return sharedEngine:getEffectsVolume()
end
audio.getEffectsVolume = audio.getSoundsVolume

function audio.setSoundsVolume(volume)
    sharedEngine:setEffectsVolume(volume)
end
audio.setEffectsVolume = audio.setSoundsVolume

function audio.preloadMusic(filename)
    if DEBUG > 1 then
        echoInfo("audio.preloadMusic() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadBackgroundMusic(filename)
end
audio.preloadBackgroundMusic = audio.preloadMusic

function audio.playMusic(filename, isLoop)
    if type(isLoop) ~= "boolean" then isLoop = true end

    audio.stopMusic(true)
    if DEBUG > 1 then
        echoInfo("audio.playMusic() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    sharedEngine:playBackgroundMusic(filename, isLoop)
end
audio.playBackgroundMusic = audio.playMusic

function audio.stopMusic(isReleaseData)
    if type(isReleaseData) ~= "boolean" then isReleaseData = false end
    sharedEngine:stopBackgroundMusic(isReleaseData)
end
audio.stopBackgroundMusic = audio.stopMusic

function audio.pauseMusic()
    sharedEngine:pauseBackgroundMusic()
end
audio.pauseBackgroundMusic = audio.pauseMusic

--[[--

Resume playing background music

### Alias:

-   audio.resumeBackgroundMusic()

]]
function audio.resumeMusic()
    sharedEngine:resumeBackgroundMusic()
end
audio.resumeBackgroundMusic = audio.resumeMusic

function audio.rewindMusic()
    ending:rewindBackgroundMusic()
end
audio.rewindBackgroundMusic = audio.rewindMusic

function audio.willPlayMusic()
    return sharedEngine:willPlayBackgroundMusic()
end
audio.willPlayBackgroundMusic = audio.willPlayMusic

function audio.isMusicPlaying()
    return sharedEngine:isBackgroundMusicPlaying()
end
audio.isBackgroundMusicPlaying = audio.isMusicPlaying

function audio.playSound(filename, isLoop)
    if type(isLoop) ~= "boolean" then isLoop = false end
    if DEBUG > 1 then
        echoInfo("audio.playSound() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    return sharedEngine:playEffect(filename, isLoop)
end
audio.playEffect = audio.playSound

function audio.pauseSound(handle)
    sharedEngine:pauseEffect(handle)
end
audio.pauseEffect = audio.pauseSound

function audio.pauseAllSounds()
    sharedEngine:pauseAllEffects()
end
audio.pauseAllEffects = audio.pauseAllSounds

function audio.resumeSound(handle)
    sharedEngine:resumeEffect(handle)
end
audio.resumeEffect = audio.resumeSound

function audio.resumeAllSounds(handle)
    sharedEngine:resumeAllEffects()
end
audio.resumeAllEffects = audio.resumeAllSounds

function audio.stopSound(handle)
    sharedEngine:stopEffect(handle)
end
audio.stopEffect = audio.stopSound

function audio.stopAllSounds()
    sharedEngine:stopAllEffects()
end
audio.stopAllEffects = audio.stopAllSounds

function audio.preloadSound(filename)
    if DEBUG > 1 then
        echoInfo("audio.preloadSound() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadEffect(filename)
end
audio.preloadEffect = audio.preloadSound

function audio.unloadSound(filename)
    sharedEngine:unloadEffect(filename)
end
audio.unloadEffect = audio.unloadSound

return audio
