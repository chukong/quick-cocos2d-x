
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    -- init ad
    if device.platform == "ios" or device.platform == "android" then
        cc.ad:start({appId = PUNCHBOX_AD_SDK_APP_ID}, "ad.PunchBox")
    end

    -- open scene
    self:enterScene("MainScene")
end

return MyApp
