--[[

Copyright (c) 2011-2012 qeeplay.com

http://dualface.github.com/quick-cocos2d-x/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

Play music, sound effects.

]]

local audio = {}

local sharedEngine = SimpleAudioEngine:sharedEngine()
local isEnabled    = true

--[[--

Disable audio sharedEngine.

]]
function audio.disable()
    isEnabled = false
end

--[[--

Enable audio sharedEngine. (default is enabled)

]]
function audio.enable()
    isEnabled = true
end

--[[--

The volume of the background music. max value is 1.0, the min value is 0.0

### Returns:

-   The volume of the background music

### Alias:

-   audio.getBackgroundMusicVolume()

]]
function audio.getMusicVolume()
    if not isEnabled then return 0 end
    return sharedEngine:getBackgroundMusicVolume()
end
audio.getBackgroundMusicVolume = audio.getMusicVolume

--[[--

Set the volume of background music

### Parameters:

-   float **volume** must be in 0.0 ~ 1.0

### Alias:

-   audio.setBackgroundMusicVolume()

]]
function audio.setMusicVolume(volume)
    if not isEnabled then return end
    sharedEngine:setBackgroundMusicVolume(volume)
end
audio.setBackgroundMusicVolume = audio.setMusicVolume

--[[--

The volume of the effects. max value is 1.0, the min value is 0.0

### Returns:

-   The volume of the effects

### Alias:

-   audio.getEffectsVolume()

]]
function audio.getSoundsVolume()
    if not isEnabled then return 0 end
    return sharedEngine:getEffectsVolume()
end
audio.getEffectsVolume = audio.getSoundsVolume

--[[--

Set the volume of sound effecs

### Parameters:

-   float **volume** must be in 0.0 ~ 1.0

### Alias:

-   audio.setEffectsVolume()

]]
function audio.setSoundsVolume(volume)
    if not isEnabled then return end
    sharedEngine:setEffectsVolume(volume)
end
audio.setEffectsVolume = audio.setSoundsVolume

--[[--

Preload background music

### Parameters:

-   string **filename** The path of the background music file

### Alias:

-   audio.preloadBackgroundMusic()

]]
function audio.preloadMusic(filename)
    if not isEnabled then return end
    if DEBUG > 1 then
        echoInfo("audio.preloadMusic() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadBackgroundMusic(filename)
end
audio.preloadBackgroundMusic = audio.preloadMusic

--[[--

Play background music

### Parameters:

-   string **filename** The path of the background music file
-   [_optional bool **isLoop**_] Whether the background music loop or not

### Alias:

-   audio.playBackgroundMusic()

]]
function audio.playMusic(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = true end

    audio.stopMusic(true)
    if DEBUG > 1 then
        echoInfo("audio.playMusic() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    sharedEngine:playBackgroundMusic(filename, isLoop)
end
audio.playBackgroundMusic = audio.playMusic

--[[--

Stop playing background music

### Parameters:

-   bool **isReleaseData** If release the background music data or not. As default value is false

### Alias:

-   audio.stopBackgroundMusic()

]]
function audio.stopMusic(isReleaseData)
    if not isEnabled then return end
    if type(isReleaseData) ~= "boolean" then isReleaseData = false end
    sharedEngine:stopBackgroundMusic(isReleaseData)
end
audio.stopBackgroundMusic = audio.stopMusic

--[[--

Pause playing background music

### Alias:

-   audio.pauseBackgroundMusic()

]]
function audio.pauseMusic()
    if not isEnabled then return end
    sharedEngine:pauseBackgroundMusic()
end
audio.pauseBackgroundMusic = audio.pauseMusic

--[[--

Resume playing background music

### Alias:

-   audio.resumeBackgroundMusic()

]]
function audio.resumeMusic()
    if not isEnabled then return end
    sharedEngine:resumeBackgroundMusic()
end
audio.resumeBackgroundMusic = audio.resumeMusic

--[[--

Rewind playing background music

### Alias:

-   audio.rewindBackgroundMusic()

]]
function audio.rewindMusic()
    if not isEnabled then return end
    ending:rewindBackgroundMusic()
end
audio.rewindBackgroundMusic = audio.rewindMusic

--[[--

### Alias:

-   audio.willPlayBackgroundMusic()

]]
function audio.willPlayMusic()
    if not isEnabled then return false end
    return sharedEngine:willPlayBackgroundMusic()
end
audio.willPlayBackgroundMusic = audio.willPlayMusic

--[[--

Whether the background music is playing

### Returns:

-   If is playing return true,or return false

### Alias:

-   audio.isBackgroundMusicPlaying()

]]
function audio.isMusicPlaying()
    if not isEnabled then return false end
    return sharedEngine:isBackgroundMusicPlaying()
end
audio.isBackgroundMusicPlaying = audio.isMusicPlaying

--[[--

Play sound effect

### Parameters:

-   string **filename** The path of the effect file
-   [_optional bool **isLoop**_] Whether to loop the effect playing, default value is false

### Returns:

-   int: Handle of sound effect

### Alias:

-   audio.playEffect()

]]
function audio.playSound(filename, isLoop)
    if not isEnabled then return end
    if type(isLoop) ~= "boolean" then isLoop = false end
    if DEBUG > 1 then
        echoInfo("audio.playSound() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    return sharedEngine:playEffect(filename, isLoop)
end
audio.playEffect = audio.playSound

--[[--

Pause playing sound effect

### Parameters:

-   int **handle** The return value of function playEffect

### Alias:

-   audio.pauseEffect()

]]
function audio.pauseSound(handle)
    if not isEnabled then return end
    sharedEngine:pauseEffect(handle)
end
audio.pauseEffect = audio.pauseSound

--[[--

Pause all playing sound effect

### Alias:

-   audio.pauseAllEffects()

]]
function audio.pauseAllSounds()
    if not isEnabled then return end
    sharedEngine:pauseAllEffects()
end
audio.pauseAllEffects = audio.pauseAllSounds

--[[--

Resume paused sound effect

### Parameters:

-   int **handle** The return value of function playEffect

### Alias:

-   audio.resumeEffect()

]]
function audio.resumeSound(handle)
    if not isEnabled then return end
    sharedEngine:resumeEffect(handle)
end
audio.resumeEffect = audio.resumeSound

--[[--

Resume all paused sound effects

### Alias:

-   audio.resumeAllEffects()

]]
function audio.resumeAllSounds(handle)
    if not isEnabled then return end
    sharedEngine:resumeAllEffects()
end
audio.resumeAllEffects = audio.resumeAllSounds

--[[--

Stop playing sound effect

### Parameters:

-   int **handle** The return value of function playEffect

### Alias:

-   audio.stopEffect()

]]
function audio.stopSound(handle)
    if not isEnabled then return end
    sharedEngine:stopEffect(handle)
end
audio.stopEffect = audio.stopSound

--[[--

Stop all playing sound effects

### Alias:

-   audio.stopAllEffects()

]]
function audio.stopAllSounds()
    if not isEnabled then return end
    sharedEngine:stopAllEffects()
end
audio.stopAllEffects = audio.stopAllSounds

--[[--

Preload a sound effect

### Parameters:

-   string **filename** The path of the effect file

### Alias:

-   audio.preloadEffect()

]]
function audio.preloadSound(filename)
    if not isEnabled then return end
    if DEBUG > 1 then
        echoInfo("audio.preloadSound() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadEffect(filename)
end
audio.preloadEffect = audio.preloadSound

--[[--

Unload the preloaded effect

### Parameters:

-   string **filename** The path of the effect file

### Alias:

-   audio.unloadEffect()

]]
function audio.unloadSound(filename)
    if not isEnabled then return end
    sharedEngine:unloadEffect(filename)
end
audio.unloadEffect = audio.unloadSound

return audio
