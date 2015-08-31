
require("config")
require("framework.init")

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
    self:enterScene("SampleScene", nil, "pageTurn", 0.5, false)
end

function WelcomeApp:backToMainScene()
    self:enterScene("WelcomeScene", nil, "pageTurn", 0.5, true)
end

return WelcomeApp
