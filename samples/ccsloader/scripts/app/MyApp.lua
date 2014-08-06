
require("config")
require("framework.init")
require("app.ForQuickV2")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
    self.scenes_ = {
        "CCSSample1Scene",
        "CCSSample2Scene",
        "CCSSample3Scene",
        "CCSSample4Scene",
    }
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")

    self:enterNextScene()
end

function MyApp:enterScene(sceneName, ...)
    self.currentSceneName_ = sceneName
    MyApp.super.enterScene(self, sceneName, ...)
end

function MyApp:enterNextScene()
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

function MyApp:createTitle(scene, title)
    cc.ui.UILabel.new({text = "-- " .. title .. " --", size = 24, color = display.COLOR_WHITE})
        :align(display.CENTER, display.cx, display.top - 20)
        :addTo(scene)
end

function MyApp:createNextButton(scene)
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

function MyApp:loadCCSJsonFile(scene, jsonFile)
    local node = cc.uiloader:load(jsonFile)
    if node then
        node:setPosition((display.width - 480)/2, (display.height - 320)/2)
        -- node:setPosition(0, 0)
        scene:addChild(node)

        -- dumpUITree(node)
    end
end

depth = 1
function dumpUITree(node)
    if not node then
        return
    end

    if not node:isVisible() then
        return
    end

    -- if node.name then
    --  local info = {}
    --  table.insert(info, "")
    --  table.insert(info, getLinePreSym() .. string.format("Name:%s", node.name))
    --  table.insert(info, getLinePreSym() .. string.format("Tag:%d", node:getTag()))
    --  table.insert(info, getLinePreSym() .. string.format("Position:(%d, %d)", node:getPositionX(), node:getPositionY()))
    --  local size = node:getContentSize()
    --  table.insert(info, getLinePreSym() .. string.format("Size:(%d, %d)", size.width, size.height))
    --  table.insert(info, getLinePreSym() .. string.format("Scale:(%f, %f)", node:getScaleX(), node:getScaleY()))
    --  local anchor = node:getAnchorPoint()
    --  table.insert(info, getLinePreSym() .. string.format("Anchor:(%f, %f)", anchor.x, anchor.y))
    --  table.insert(info, getLinePreSym() .. "Visible:" .. tostring(node:isVisible()))
    --  table.insert(info, getLinePreSym() .. string.format("ChildCount:%d", node:getChildrenCount()))

    --  print(table.concat(info, "\n"))
    -- end

    print("")

    printLine(string.format("Name:%s", node.name))
    printLine(string.format("Tag:%d", node:getTag()))
    printLine(string.format("Position:(%d, %d)", node:getPositionX(), node:getPositionY()))
    local size = node:getContentSize()
    printLine(string.format("Size:(%d, %d)", size.width, size.height))
    -- printLine(string.format("Scale:(%f, %f)", node:getScaleX(), node:getScaleY()))
    local anchor = node:getAnchorPoint()
    -- printLine(string.format("Anchor:(%f, %f)", anchor.x, anchor.y))
    -- printLine("Visible:" .. tostring(node:isVisible()))
    -- printLine(string.format("ChildCount:%d", node:getChildrenCount()))

    depth = depth + 1
    local children = node:getChildren()
    local childCount = node:getChildrenCount()
    local subNode
    for i=1,childCount do
        if "table" == type(children) then
            subNode = children[i]
        else
            subNode = children:objectAtIndex(i - 1)
        end
        dumpUITree(subNode)
    end

    depth = depth - 1
end

function printLine(str)
    local t = {"+"}
    for i=1,depth do
        table.insert(t, "----")
    end
    table.insert(t, str)
    print(table.concat(t))
end

function drawRect(scene, rect)
    print("rect type:" .. tolua.type(rect))
    print(string.format("drawRect x:%d,y:%d,w:%d,h:%d", rect.x, rect.y, rect.width, rect.height))
    local drawNode = display.newRect(rect,
        {align = display.LEFT_BOTTOM, color = cc.c4f(1, 0, 0, 1)})
    scene:addChild(drawNode)
end

return MyApp
