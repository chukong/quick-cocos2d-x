
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local UIDemoApp = class("UIDemoApp", cc.mvc.AppBase)

function UIDemoApp:ctor()
    UIDemoApp.super.ctor(self)
    self.scenes_ = {
        "TestUIPageViewScene",
        "TestUIListViewScene",
        "TestUIScrollViewScene",
        "TestUIImageScene",
        "TestUIButtonScene",
        "TestUIButtonMoreScene",
        "TestUISliderScene",
    }
end

function UIDemoApp:run()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    self:enterNextScene()
end

function UIDemoApp:enterScene(sceneName, ...)
    self.currentSceneName_ = sceneName
    UIDemoApp.super.enterScene(self, sceneName, ...)
end

function UIDemoApp:enterNextScene()
    local index = 1
    while index <= #self.scenes_ do
        if self.scenes_[index] == self.currentSceneName_ then
            break
        end
        index = index + 1
    end
    index = index + 1
    if index > #self.scenes_ then index = 1 end
    self:enterScene(self.scenes_[index])
end

function UIDemoApp:createTitle(scene, title)
    cc.ui.UILabel.new({text = "-- " .. title .. " --", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER, display.cx, display.top - 20)
        :addTo(scene)
end

function UIDemoApp:createGrid(scene)
    display.newColorLayer(ccc4(255, 255, 255, 255)):addTo(scene)

    for y = display.bottom, display.top, 40 do
        local line = display.newPolygon({{display.left, y}, {display.right, y}}):addTo(scene)
        line:setLineColor(ccc4f(0.9, 0.9, 0.9, 1.0))
    end

    for x = display.left, display.right, 40 do
        local line = display.newPolygon({{x, display.top}, {x, display.bottom}}):addTo(scene)
        line:setLineColor(ccc4f(0.9, 0.9, 0.9, 1.0))
    end

    local line = display.newPolygon({{display.left, display.cy}, {display.right, display.cy}}):addTo(scene)
    line:setLineColor(ccc4f(1.0, 0.75, 0.75, 1.0))

    local line = display.newPolygon({{display.cx, display.top}, {display.cx, display.bottom}}):addTo(scene)
    line:setLineColor(ccc4f(1.0, 0.75, 0.75, 1.0))
end

function UIDemoApp:createNextButton(scene)
    cc.ui.UIPushButton.new("NextButton.png")
        :onButtonPressed(function(event)
            event.target:setScale(1.2)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
            self:enterNextScene()
        end)
        :align(display.RIGHT_BOTTOM, display.right - 20, display.bottom + 20)
        :addTo(scene)
end

return UIDemoApp
