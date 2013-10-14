
-- init ui library
local ui = {}

function makeUIControl_(control)
    cc.GameObject.extend(control)
    control:addComponent("components.ui.LayoutProtocol"):exportMethods()
    control:addComponent("components.behavior.EventProtocol"):exportMethods()

    control:setNodeEventEnabled(true)
    function control:onExit()
        self:removeAllEventListeners()
    end
end

ui.UIGroup               = import(".UIGroup")
ui.UIImage               = import(".UIImage")
ui.UIPushButton          = import(".UIPushButton")
ui.UICheckBoxButton      = import(".UICheckBoxButton")
ui.UICheckBoxButtonGroup = import(".UICheckBoxButtonGroup")
ui.UILabel               = import(".UILabel")
ui.UIBoxLayout           = import(".UIBoxLayout")

return ui
