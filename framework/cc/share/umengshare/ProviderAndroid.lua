
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.CocoPushSDK"


function ProviderAndroid:addListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {handler(self, self.callback_)})
end

function ProviderAndroid:removeListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderAndroid:setAppWebSite(shareMedia, webSite)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "setAppWebSite", {shareMedia, webSite})
    if not ok then
        printError("cc.share.ProviderAndroid:ctor() - call setAppWebSite failed.")
        return false
    end

    return true
end

function ProviderAndroid:removePlatform(shareMedia)
	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "removePlatform", {shareMedia})
    if not ok then
        printError("cc.share.ProviderAndroid:ctor() - call removePlatform failed.")
        return false
    end

    return true
end

function ProviderAndroid:reorderPlatform(shareMedia)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "reorderPlatform", {shareMedia})
    if not ok then
        printError("cc.share.ProviderAndroid:ctor() - call reorderPlatform failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareText(text)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareText", {text})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareImg(text, img, imgType)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareImg", {text, img, imgType})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareMusic(text, music, musicImg, title, author)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "delTags", {text, music, musicImg, title, author})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareVideo(text, video, videoImg, title)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "delTags", {text, video, videoImg, title})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

return ProviderAndroid
