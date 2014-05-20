
require("config")
require("framework.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)

    if device.platform == "ios" then
    	UMENG_APPKEY = "5369de0b56240b5363019991"
    elseif device.platform == "android" then
    	UMENG_APPKEY = "536b184d56240bb2cd02adbf"
    end
end

function MyApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    -- init feedback
    if device.platform == "android" or device.platform == "ios" then
        cc.feedback:start("feedback.UmengFeedback")
    end

    self:enterScene("MainScene")
end

return MyApp
