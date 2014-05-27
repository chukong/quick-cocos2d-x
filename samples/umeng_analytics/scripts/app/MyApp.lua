
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:onEnterBackground()
    cc.analytics:doCommand{command = "applicationDidEnterBackground"}
end

function MyApp:onEnterForeground()
    cc.analytics:doCommand{command = "applicationWillEnterForeground"}
end

function MyApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    -- init analytics
    if device.platform == "android" or device.platform == "ios" then
        cc.analytics:start("analytics.UmengAnalytics")
    end

    -- 改为真实的应用ID，第二参数为渠道号(可选)
    if device.platform == "android" then
    	cc.analytics:doCommand{command = "startWithAppkey",
    			args = {appKey = "536b184d56240bb2cd02adbf"}}
    elseif device.platform == "ios" then
    	cc.analytics:doCommand{command = "startWithAppkey",
    			args = {appKey = "5369de0b56240b5363019991"}}
    end
    cc.analytics:doCommand{command = "updateOnlineConfig"}

    self:enterScene("MainScene")
end

return MyApp
