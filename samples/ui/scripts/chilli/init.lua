
local CURRENT_MODULE_NAME = ...

cc = cc or {}

-- init base classes
cc.Registry = import(".Registry")
cc.GameObject = import(".GameObject")

-- init components
cc.Registry.add(import(".components.ui.Button", CURRENT_MODULE_NAME), "components.ui.Button")
cc.Registry.add(import(".components.ui.LayoutProtocol", CURRENT_MODULE_NAME), "components.ui.LayoutProtocol")

-- init ui library
cc.ui = {}

cc.ui.FIXED_SIZE_POLICY = 0
cc.ui.PREFERRED_SIZE_POLICY = 1

cc.ui.UIGroup      = import(".ui.UIGroup")
cc.ui.UIImage      = import(".ui.UIImage")
cc.ui.UIButton     = import(".ui.UIButton")
cc.ui.UIBoxLayout  = import(".ui.UIBoxLayout")
cc.ui.UIHBoxLayout = import(".ui.UIHBoxLayout")
