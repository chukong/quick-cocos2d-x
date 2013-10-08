
local CURRENT_MODULE_NAME = ...

-- init base classes
cc.Registry = import(".Registry")
cc.GameObject = import(".GameObject")

-- init components
local components = {
    "components.behavior.StateMachine",
    "components.ui.Button",
    "components.ui.BasicLayoutProtocol",
    "components.ui.LayoutProtocol",
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), packageName)
end

-- init UI library
cc.ui = import(".ui.init")
