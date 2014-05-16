
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

    -- init push
    if device.platform == "android" then
        cc.push:start("push.UmengPush")
    end

    self:enterScene("MainScene")
end

return MyApp
