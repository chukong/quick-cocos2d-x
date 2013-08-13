
local AppBase = class("AppBase")

function AppBase:ctor(appName, packageRoot)
    self.name = appName
    self.packageRoot = packageRoot or "app"

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

return AppBase
