
local audio = {}

local engine     = SimpleAudioEngine:sharedEngine()
local isEnabled  = true
local isMusicOn  = true
local isSoundsOn = true
local prefix     = ""

function audio.setPrefix(prefix_)
    if not prefix_ then prefix_ = "" end
    prefix = _s(prefix_)
end

function audio.disable()
    isEnabled = false
end

function audio.enable()
    isEnabled = true
end

function audio.preloadMusic(filename)
    if not isEnabled then return end
    engine:preloadBackgroundMusic(prefix .. filename)
end

local playMusicDelayHandle
function audio.playMusic(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = true end
    audio.stopMusic(true)

    if device.platform == device.PLATFORM_ANDROID then
        local sharedScheduler = CCDirector:sharedDirector():getScheduler()

        if playMusicDelayHandle then
            sharedScheduler:unscheduleScriptEntry(playMusicDelayHandle)
        end

        playMusicDelayHandle = sharedScheduler:scheduleScriptFunc(function()
            sharedScheduler:unscheduleScriptEntry(playMusicDelayHandle)
            playMusicDelayHandle = nil
            echoNotice("audio.playMusic() - filename: %s, isLoop: %s", _s(filename), _s(isLoop))
            engine:playBackgroundMusic(prefix .. filename, isLoop)
        end, 0.5, false)
    else
        echoNotice("audio.playMusic() - filename: %s, isLoop: %s", _s(filename), _s(isLoop))
        engine:playBackgroundMusic(prefix .. filename, isLoop)
    end
end

function audio.stopMusic(isReleaseData)
    if not isEnabled then return end
    if type(isReleaseData) ~= "boolean" then isReleaseData = false end
    engine:stopBackgroundMusic(isReleaseData)
end

function audio.pauseMusic()
    if not isEnabled then return end
    engine:pauseBackgroundMusic()
end

function audio.resumeMusic()
    if not isEnabled then return end
    engine:resumeBackgroundMusic()
end

function audio.rewindMusic()
    if not isEnabled then return end
    ending:rewindBackgroundMusic()
end

function audio.willPlayMusic()
    if not isEnabled then return false end
    return engine:willPlayBackgroundMusic()
end

function audio.isMusicPlaying()
    if not isEnabled then return false end
    return engine:isBackgroundMusicPlaying()
end

function audio.getMusicVolume()
    if not isEnabled then return 0 end
    return engine:getBackgroundMusicVolume()
end

function audio.setMusicVolume(volume)
    if not isEnabled then return end
    engine:setBackgroundMusicVolume(volume)
    isMusicOn = volume > 0
end

function audio.getSoundsVolume()
    if not isEnabled then return 0 end
    return engine:getEffectsVolume()
end
audio.getEffectsVolume = audio.getSoundsVolume

function audio.setSoundsVolume(volume)
    if not isEnabled then return end
    engine:setEffectsVolume(volume)
    isSoundsOn = volume > 0
end
audio.setEffectsVolume = audio.setSoundsVolume

function audio.switchMusicOnOff()
    if not isEnabled then return end
    if audio.getMusicVolume() <= 0.01 then
        audio.setMusicVolume(1)
        isMusicOn = true
    else
        audio.setMusicVolume(0)
        isMusicOn = false
    end
end

function audio.switchSoundsOnOff()
    if not isEnabled then return end
    if audio.getSoundsVolume() <= 0.01 then
        audio.setSoundsVolume(1)
        isSoundsOn = true
    else
        audio.setSoundsVolume(0)
        isSoundsOn = false
    end
end
audio.switchEffectsOnOff = audio.switchSoundsOnOff

function audio.playSound(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = false end
    return engine:playEffect(prefix .. filename, isLoop)
end
audio.playEffect = audio.playSound

function audio.stopSound(handle)
    if not isEnabled then return end
    engine:stopEffect(handle)
end
audio.stopEffect = audio.stopSound

function audio.preloadSound(filename)
    if not isEnabled then return end
    engine:preloadEffect(prefix .. filename)
end
audio.preloadEffect = audio.preloadSound

function audio.unloadSound(filename)
    if not isEnabled then return end
    engine:unloadEffect(prefix .. filename)
end
audio.unloadEffect = audio.unloadSound

local handleFadeMusicVolumeTo = nil
function audio.fadeMusicVolumeTo(time, volume)
    if not isEnabled or not isMusicOn then return end
    local currentVolume = audio.getMusicVolume()
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
        audio.setMusicVolume(currentVolume)
    end

    handleFadeMusicVolumeTo = scheduler.enterFrame(changeVolumeStep, false)
end

local handleFadeToMusic = nil
function audio.fadeToMusic(music, time, volume, isLoop)
    if not isEnabled then return end
    if handleFadeToMusic then scheduler.remove(handleFadeToMusic) end
    time = time / 2
    if type(volume) ~= "number" then volume = 1.0 end
    audio.fadeMusicVolumeTo(volume, 0.01)
    handleFadeToMusic = scheduler.performWithDelay(time + 0.1, function()
        audio.playMusic(music, isLoop)
        audio.fadeMusicVolumeTo(time, volume)
    end)
end

return audio
