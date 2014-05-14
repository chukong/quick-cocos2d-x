
local ProviderBase = import(".ProviderBase")
local ProviderIOS = class("ProviderIOS", ProviderBase)

local SDK_CLASS_NAME = "UmengShareSDK"

function ProviderIOS:addListener()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {listener = handler(self, self.callback_)})
end

function ProviderIOS:removeListener()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderIOS:setAppWebSite()
	printInfo("cc.share.ProviderIOS not support setAppWebSite")
end

function ProviderIOS:removePlatform()
	printInfo("cc.share.ProviderIOS not support removePlatform")
end

function ProviderIOS:reorderPlatform()
	printInfo("cc.share.ProviderIOS not support reorderPlatform")
end

function ProviderIOS:shareText(text)
	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "share", {shareText = text})
	if not ok then
        printError("cc.share.ProviderIOS:ctor() - call shareText failed.")
    end
end

function ProviderIOS:shareImg()
	printInfo("cc.share.ProviderIOS not support shareImg")
end

function ProviderIOS:shareMusic()
	printInfo("cc.share.ProviderIOS not support shareMusic")
end

function ProviderIOS:shareVideo()
	printInfo("cc.share.ProviderIOS not support shareVideo")
end

return ProviderIOS
