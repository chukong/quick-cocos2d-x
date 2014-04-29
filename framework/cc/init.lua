--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

初始化 cc 扩展

cc 扩展在 cocos2dx C++ API 和 quick 基本模块的基础上，提供了更好的事件接口、组件架构等扩展。

]]

local CURRENT_MODULE_NAME = ...

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
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), packageName)
end

-- init MVC
cc.mvc = import(".mvc.init")

-- init UI library
cc.ui = import(".ui.init")

-- 将 cc 转为一个包装函数
local ccmt = {}

ccmt.__call = function(self, target)
end

setmetatable(cc, ccmt)
