
local M = {}

local engine    = SimpleAudioEngine:sharedEngine()
local isEnabled = true
local isMusicOn = true
local isSoundsOn = true

function M.disable()
    isEnabled = false
end

function M.enable()
    isEnabled = true
end

function M.preloadMusic(filename)
    if not isEnabled then return end
    engine:preloadBackgroundMusic(filename)
end

function M.playMusic(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = true end
    engine:playBackgroundMusic(filename, isLoop)
end

function M.stopMusic(isReleaseData)
    if not isEnabled then return end
    if type(isReleaseData) ~= "boolean" then isReleaseData = false end
    engine:stopBackgroundMusic(isReleaseData)
end

function M.pauseMusic()
    if not isEnabled then return end
    engine:pauseBackgroundMusic()
end

function M.resumeMusic()
    if not isEnabled then return end
    engine:resumeBackgroundMusic()
end

function M.rewindMusic()
    if not isEnabled then return end
    ending:rewindBackgroundMusic()
end

function M.willPlayMusic()
    if not isEnabled then return false end
    return engine:willPlayBackgroundMusic()
end

function M.isMusicPlaying()
    if not isEnabled then return false end
    return engine:isBackgroundMusicPlaying()
end

function M.getMusicVolume()
    if not isEnabled then return 0 end
    return engine:getBackgroundMusicVolume()
end

function M.setMusicVolume(volume)
    if not isEnabled then return end
    engine:setBackgroundMusicVolume(volume)
    isMusicOn = volume > 0
end

function M.getSoundsVolume()
    if not isEnabled then return 0 end
    return engine:getEffectsVolume()
end
M.getEffectsVolume = M.getSoundsVolume

function M.setSoundsVolume(volume)
    if not isEnabled then return end
    engine:setEffectsVolume(volume)
    isSoundsOn = volume > 0
end
M.setEffectsVolume = M.setSoundsVolume

function M.switchMusicOnOff()
    if not isEnabled then return end
    if M.getMusicVolume() <= 0.01 then
        M.setMusicVolume(1)
        isMusicOn = true
    else
        M.setMusicVolume(0)
        isMusicOn = false
    end
end

function M.switchSoundsOnOff()
    if not isEnabled then return end
    if M.getSoundsVolume() <= 0.01 then
        M.setSoundsVolume(1)
        isSoundsOn = true
    else
        M.setSoundsVolume(0)
        isSoundsOn = false
    end
end
M.switchEffectsOnOff = M.switchSoundsOnOff

function M.playSound(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = false end
    return engine:playEffect(filename, isLoop)
end
M.playEffect = M.playSound

function M.stopSound(handle)
    if not isEnabled then return end
    engine:stopEffect(handle)
end
M.stopEffect = M.stopSound

function M.preloadSound(filename)
    if not isEnabled then return end
    engine:preloadEffect(filename)
end
M.preloadEffect = M.preloadSound

function M.unloadSound(filename)
    if not isEnabled then return end
    engine:unloadEffect(filename)
end
M.unloadEffect = M.unloadSound

local handleFadeMusicVolumeTo = nil
function M.fadeMusicVolumeTo(time, volume)
    if not isEnabled or not isMusicOn then return end
    local currentVolume = M.getMusicVolume()
    if volume == currentVolume then return end

    if handleFadeMusicVolumeTo then
        scheduler.remove(handleFadeMusicVolumeTo)
    end
    local stepVolume = (volume - currentVolume) / time * (1.0 / 60)
    local isIncr     = volume > currentVolume

    local function changeVolumeStep()
        currentVolume = currentVolume + stepVolume
        if (isIncr and currentVolume >= volume) or (not isIncr and currentVolume <= volume) then
            currentVolume = volume
            scheduler.remove(handleFadeMusicVolumeTo)
        end
        M.setMusicVolume(currentVolume)
    end

    handleFadeMusicVolumeTo = scheduler.enterFrame(changeVolumeStep, false)
end

local handleFadeToMusic = nil
function M.fadeToMusic(music, time, volume, isLoop)
    if not isEnabled then return end
    if handleFadeToMusic then scheduler.remove(handleFadeToMusic) end
    time = time / 2
    if type(volume) ~= "number" then volume = 1.0 end
    M.fadeMusicVolumeTo(volume, 0.01)
    handleFadeToMusic = scheduler.performWithDelay(time + 0.1, function()
        M.playMusic(music, isLoop)
        M.fadeMusicVolumeTo(time, volume)
    end)
end

return M
