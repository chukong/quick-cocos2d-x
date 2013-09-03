
-- init base classes
cc.Registry = import(".Registry")
cc.GameObject = import(".GameObject")

-- init components
local Button = import(".components.Button")
cc.Registry.add(Button)

-- init ui library
cc.ui = {}
cc.ui.UIButton = import(".ui.UIButton")
