
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

    -- init share
    if device.platform == "ios" or device.platform == "android" then
        cc.share:start("share.UmengShare")
    end

    self:enterScene("MainScene")
end

return MyApp
