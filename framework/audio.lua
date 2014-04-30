--[[

Copyright (c) 2011-2014 chukong-inc.com

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

播放音乐、音效

]]

local audio = {}

local sharedEngine = SimpleAudioEngine:sharedEngine()

--[[--

返回音乐的音量值

@return number 返回值在 0 到 1 之间，0 表示完全静音，1 表示 100% 音量。

]]
function audio.getMusicVolume()
    return sharedEngine:getBackgroundMusicVolume()
end
audio.getBackgroundMusicVolume = audio.getMusicVolume

--[[--

设置音乐的音量

@param number 0 到 1 之间, 0 表示完全静音,1 表示 100% 音量。

]]
function audio.setMusicVolume(volume)
    sharedEngine:setBackgroundMusicVolume(volume)
end
audio.setBackgroundMusicVolume = audio.setMusicVolume

--[[--

返回音效的音量值

@return number 0 到 1 之间，0 表示完全静音，1 表示 100% 音量。

]]
function audio.getSoundsVolume()
    return sharedEngine:getEffectsVolume()
end
audio.getEffectsVolume = audio.getSoundsVolume

--[[--

设置音效的音量

@param number 0 到 1 之间，0 表示完全静音，1 表示 100% 音量。

]]
function audio.setSoundsVolume(volume)
    sharedEngine:setEffectsVolume(volume)
end
audio.setEffectsVolume = audio.setSoundsVolume

--[[--

预载入一个音乐文件

在播放音乐前预先载入，可以在需要播放音乐时无延迟立即播放。不过限于硬件设备和操作系统的限制，通常只能预载入一个音乐文件。

@param string 音乐文件名

]]
function audio.preloadMusic(filename)
    if DEBUG > 1 then
        printInfo("audio.preloadMusic() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadBackgroundMusic(filename)
end
audio.preloadBackgroundMusic = audio.preloadMusic

--[[--

播放音乐

如果音乐文件尚未载入，则会首先载入音乐文件，然后开始播放。默认会无限循环播放音乐。

注意:即便音乐音量为 0，playMusic() 仍然会进行播放操作。如果希望停止音乐来降低 CPU 占用，应该使用 stopMusic() 接口完全停止音乐播放。

@param string 音乐文件名
@param boolean 是否循环播放

]]
function audio.playMusic(filename, isLoop)
    if type(isLoop) ~= "boolean" then isLoop = true end

    audio.stopMusic(true)
    if DEBUG > 1 then
        printInfo("audio.playMusic() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    sharedEngine:playBackgroundMusic(filename, isLoop)
end
audio.playBackgroundMusic = audio.playMusic

--[[--

停止播放音乐

默认在停止音乐时不会立即释放音乐数据占用的内存

@param boolean 是否释放音乐数据

]]
function audio.stopMusic(isReleaseData)
    if type(isReleaseData) ~= "boolean" then isReleaseData = false end
    sharedEngine:stopBackgroundMusic(isReleaseData)
end
audio.stopBackgroundMusic = audio.stopMusic

--[[--

暂停音乐的播放

]]
function audio.pauseMusic()
    sharedEngine:pauseBackgroundMusic()
end
audio.pauseBackgroundMusic = audio.pauseMusic

--[[--

恢复暂停的音乐

]]
function audio.resumeMusic()
    sharedEngine:resumeBackgroundMusic()
end
audio.resumeBackgroundMusic = audio.resumeMusic

--[[--

从头开始重新播放当前音乐

]]
function audio.rewindMusic()
    ending:rewindBackgroundMusic()
end
audio.rewindBackgroundMusic = audio.rewindMusic

--[[--

检查是否可以开始播放音乐

如果可以则返回 true。

如果尚未载入音乐，或者载入的音乐格式不被设备所支持，该方法将返回 false。

@return boolean 

]]
function audio.willPlayMusic()
    return sharedEngine:willPlayBackgroundMusic()
end
audio.willPlayBackgroundMusic = audio.willPlayMusic

--[[--

检查当前是否正在播放音乐

如果有音乐正在播放则返回 true，否则返回 false

@return boolean 

]]
function audio.isMusicPlaying()
    return sharedEngine:isBackgroundMusicPlaying()
end
audio.isBackgroundMusicPlaying = audio.isMusicPlaying

--[[--

播放音效，并返回音效句柄

如果音效尚未载入，则会载入后开始播放。

该方法返回的音效句柄用于 stopSound()、pauseSound() 等方法。

@param string 音效文件名
@param boolean 是否重复播放

@return integer 音效句柄

]]
function audio.playSound(filename, isLoop)
    if type(isLoop) ~= "boolean" then isLoop = false end
    if DEBUG > 1 then
        printInfo("audio.playSound() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    return sharedEngine:playEffect(filename, isLoop)
end
audio.playEffect = audio.playSound

--[[--

暂停指定的音效

@param integer 音效句柄

]]
function audio.pauseSound(handle)
    sharedEngine:pauseEffect(handle)
end
audio.pauseEffect = audio.pauseSound

--[[--

暂停所有音效

]]
function audio.pauseAllSounds()
    sharedEngine:pauseAllEffects()
end
audio.pauseAllEffects = audio.pauseAllSounds

--[[--

恢复暂停的音效

@param integer 音效句柄

]]
function audio.resumeSound(handle)
    sharedEngine:resumeEffect(handle)
end
audio.resumeEffect = audio.resumeSound

--[[--

恢复所有的音效

]]
function audio.resumeAllSounds()
    sharedEngine:resumeAllEffects()
end
audio.resumeAllEffects = audio.resumeAllSounds

--[[--

停止指定的音效

@param integer 音效句柄

]]
function audio.stopSound(handle)
    sharedEngine:stopEffect(handle)
end
audio.stopEffect = audio.stopSound

--[[--

停止所有音效

]]
function audio.stopAllSounds()
    sharedEngine:stopAllEffects()
end
audio.stopAllEffects = audio.stopAllSounds

--[[--

预载入一个音效文件

可以在进入场景前，载入该场景需要的所有音效。这样就不会因为首次播放某个未载入的音效，而导致游戏暂停执行。

@param string 音效文件名

]]
function audio.preloadSound(filename)
    if DEBUG > 1 then
        printInfo("audio.preloadSound() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadEffect(filename)
end
audio.preloadEffect = audio.preloadSound

--[[--

从内存卸载一个音效

退出场景时，可以卸载掉只有该场景使用的音效，从而节约内存。

@param string 音效文件名

]]
function audio.unloadSound(filename)
    sharedEngine:unloadEffect(filename)
end
audio.unloadEffect = audio.unloadSound

return audio
