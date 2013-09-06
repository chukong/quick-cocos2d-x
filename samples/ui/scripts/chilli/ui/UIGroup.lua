
local UIGroup = class("UIGroup", function()
    return display.newNode()
end)

function UIGroup:ctor()
    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
end

return UIGroup
