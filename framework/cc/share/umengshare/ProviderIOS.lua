
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
	echoInfo("cc.share.ProviderIOS not support setAppWebSite")
end

function ProviderIOS:removePlatform()
	echoInfo("cc.share.ProviderIOS not support removePlatform")
end

function ProviderIOS:reorderPlatform()
	echoInfo("cc.share.ProviderIOS not support reorderPlatform")
end

function ProviderIOS:shareText()
	echoInfo("cc.share.ProviderIOS not support shareText")
end

function ProviderIOS:shareImg()
	echoInfo("cc.share.ProviderIOS not support shareImg")
end

function ProviderIOS:shareMusic()
	echoInfo("cc.share.ProviderIOS not support shareMusic")
end

function ProviderIOS:shareVideo()
	echoInfo("cc.share.ProviderIOS not support shareVideo")
end

return ProviderIOS
