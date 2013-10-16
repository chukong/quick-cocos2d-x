
local CURRENT_MODULE_NAME = ...

cc = cc or {}

-- init base classes
cc.Registry = import(".Registry")
cc.GameObject = import(".GameObject")

-- init components
local components = {
    "components.behavior.StateMachine",
    "components.behavior.EventProtocol",
    "components.ui.BasicLayoutProtocol",
    "components.ui.LayoutProtocol",
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), packageName)
end

-- init MVC
cc.mvc = import(".mvc.init")

-- init UI library
cc.ui = import(".ui.init")
