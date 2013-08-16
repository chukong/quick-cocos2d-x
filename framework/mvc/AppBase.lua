
local AppBase = class("AppBase")

AppBase.APP_ENTER_BACKGROUND_EVENT = "APP_ENTER_BACKGROUND_EVENT"
AppBase.APP_ENTER_FOREGROUND_EVENT = "APP_ENTER_FOREGROUND_EVENT"

function AppBase:ctor(appName, packageRoot)
    require("framework.api.EventProtocol").extend(self)

    self.name = appName
    self.packageRoot = packageRoot or "app"

    local notificationCenter = CCNotificationCenter:sharedNotificationCenter()
    notificationCenter:registerScriptObserver(nil, handler(self, self.onEnterBackground), "APP_ENTER_BACKGROUND_EVENT")
    notificationCenter:registerScriptObserver(nil, handler(self, self.onEnterForeground), "APP_ENTER_FOREGROUND_EVENT")

    -- set global app
    app = self
end

function AppBase:run()
end

function AppBase:exit()
    audio.stopMusic()
    CCDirector:sharedDirector():endToLua()
    os.exit()
end

function AppBase:enterScene(sceneName, ...)
    local scenePackageName = self. packageRoot .. ".scenes." .. sceneName
    local sceneClass = require(scenePackageName)
    local scene = sceneClass.new(...)
    display.replaceScene(scene)
end

function AppBase:createView(viewName, ...)
    local viewPackageName = self. packageRoot .. ".views." .. viewName
    local viewClass = require(viewPackageName)
    return viewClass.new(...)
end

function AppBase:onEnterBackground()
    self:dispatchEvent({name = AppBase.APP_ENTER_BACKGROUND_EVENT})
end

function AppBase:onEnterForeground()
    self:dispatchEvent({name = AppBase.APP_ENTER_FOREGROUND_EVENT})
end

return AppBase
