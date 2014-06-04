
local LuabindingTestScene = game.createSceneClass("LuabindingTestScene")

function LuabindingTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "avoidPeertableGC",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function LuabindingTestScene:avoidPeertableGCTest()
    local node = display.newNode()
    node:addNodeEventListener(cc.NODE_EVENT, function(event)
        printf("node event %s", event.name)
    end)
    node.customVar = 1
    node:setTag(1)
    self:addChild(node)

    printf("1. node.customVar = %s", tostring(node.customVar))
    collectgarbage()
    collectgarbage()
    printf("2. node.customVar = %s", tostring(node.customVar))
end

function LuabindingTestScene:onEnter()
    self:performWithDelay(function()
        printf("3. node.customVar = %s", tostring(self:getChildByTag(1).customVar))
        collectgarbage()
        collectgarbage()
        printf("4. node.customVar = %s", tostring(self:getChildByTag(1).customVar))
        local node = self:getChildByTag(1)
        printf("5. node.customVar = %s", tostring(node.customVar))
        self:removeChildByTag(1)
        printf("6. node = %s", tostring(self:getChildByTag(1)))
        printf("7. node.customVar = %s", tostring(node.customVar))
    end, 1.0)
end

return LuabindingTestScene
