
local CURRENT_MODULE_NAME = ...

cc = cc or {}

-- init base classes
cc.Event      = import(".Event")
cc.Registry   = import(".Registry")
cc.GameObject = import(".GameObject")
cc.EventProxy = import(".EventProxy")

-- init components
local components = {
    "components.behavior.StateMachine",
    "components.behavior.EventProtocol",
    "components.ui.BasicLayoutProtocol",
    "components.ui.LayoutProtocol",
    "components.Component",
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), packageName)
end

-- init MVC
cc.mvc = import(".mvc.init")

-- init UI library
cc.ui = import(".ui.init")
