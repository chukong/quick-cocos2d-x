
require("config")
require("framework.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    if device.platform == "android" then
    	cc.update:start("update.UmengUpdate")
    end

    self:enterScene("MainScene")
end

return MyApp
