
local create = CCScene.create
function CCScene:create()
    local scene = create(CCScene)

    local function handler(event)
        if event == "enter" then
            echoWarning("## Scene \"%s:onEnter()\"", scene.name)
            scene:onEnter()
        elseif event == "exit" then
            echoWarning("## Scene \"%s:onExit()\"", scene.name)

            if scene.autoCleanImages_ then
                for imageName, v in pairs(scene.autoCleanImages_) do
                    display.removeSpriteFrameByName(imageName)
                end
                scene.autoCleanImages_ = nil
            end

            scene:onExit()
        end
    end
    scene:registerScriptHandler(handler)

    function scene:addAutoCleanImage(imageName)
        if not self.autoCleanImages_ then self.autoCleanImages_ = {} end
        self.autoCleanImages_[imageName] = true
    end

    return scene
end
