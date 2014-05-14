
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

    -- init analytics
    if device.platform == "android" or device.platform == "ios" then
        cc.analytics:start("analytics.UmengAnalytics")
    end

    self:enterScene("MainScene")
end

return MyApp
