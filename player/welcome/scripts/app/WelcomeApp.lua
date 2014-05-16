
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local WelcomeApp = class("WelcomeApp", cc.mvc.AppBase)

function WelcomeApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(nil, function() self:enterSampleScene() end, "WELCOME_LIST_SAMPLES")
    CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(nil, function() self:enterMainFrame() end, "WELCOME_APP")
    self:enterScene("WelcomeScene")
end

function WelcomeApp:enterMainFrame()
    self:enterScene("WelcomeScene", nil, "slideInL", 0.3, display.COLOR_WHITE) 
end

function WelcomeApp:enterSampleScene()
    self:enterScene("SampleScene", nil, "slideInR", 0.3, display.COLOR_WHITE) 
end

return WelcomeApp
