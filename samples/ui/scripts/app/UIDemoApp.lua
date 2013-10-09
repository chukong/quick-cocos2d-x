
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local AppBase = require("framework.mvc.AppBase")
local UIDemoApp = class("UIDemoApp", AppBase)

function UIDemoApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    self:enterScene("WelcomeScene")
end

return UIDemoApp
