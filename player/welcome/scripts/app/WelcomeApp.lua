
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local WelcomeApp = class("WelcomeApp", cc.mvc.AppBase)

function WelcomeApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    self:enterScene("WelcomeScene")
end

return WelcomeApp
