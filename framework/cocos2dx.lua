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

针对 cocos2d-x 的一些封装和扩展

预定义的节点事件：

-   cc.NODE_EVENT - enter, exit 等事件
-   cc.NODE_ENTER_FRAME_EVENT - 帧事件
-   cc.NODE_TOUCH_EVENT - 触摸事件
-   cc.NODE_TOUCH_CAPTURE_EVENT - 捕获触摸事件

预定义的层事件：

-   cc.ACCELERATE_EVENT - 重力感应事件
-   cc.KEYPAD_EVENT - 硬件按键事件

预定义的菜单事件：

-   cc.MENU_ITEM_CLICKED_EVENT - CCMenu 菜单项点击事件

预定义的触摸模式：

-   cc.TOUCH_MODE_ALL_AT_ONCE - 多点触摸
-   cc.TOUCH_MODE_ONE_BY_ONE - 单点触摸

]]

--[[--

创建并返回一个 CCPoint 对象

~~~ lua

local point = cc.p(100, 50)
-- point 是一个 CCPoint 对象
print(point.x, point.y)
-- 输出 100 50

~~~

@param number x
@param number y

@return CCPoint

]]
cc.p = CCPoint

--[[--

创建并返回一个 CCSize 对象

~~~ lua

local size = cc.size(200, 80)
-- size 是一个 CCSize 对象
print(size.width, size.height)
-- 输出 200 80

~~~

@param number width
@param number height

@return CCSize

]]
cc.size = CCSize

--[[--

创建并返回一个 CCRect 对象

~~~ lua

local rect = cc.rect(100, 50, 200, 80)
-- rect 是一个 CCRect 对象
-- rect.origin 是一个 CCPoint 对象
-- rect.size 是一个 CCSize 对象
print(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height)
-- 输出 100 50 200 80

~~~

@param number x
@param number y
@param number width
@param number height

@return CCRect

]]
cc.rect = CCRect

--[[--

将 CCPoint 对象转换为一个 Lua 表格

~~~ lua

local point = cc.p(100, 50)
local res = cc.point2t(point)
-- res = {x = 100, y = 50}

~~~

@param CCPoint point

@return table

@see cc.t2point

]]
cc.point2t = function(point)
    return {x = point.x, y = point.y}
end

--[[--

将 CCSzie 对象转换为一个 Lua 表格

~~~ lua

local size = cc.size(200, 80)
local res = cc.size2t(size)
-- res = {width = 200, height = 80}

~~~

@param CCSzie size

@return table

@see cc.t2size

]]
cc.size2t = function(size)
    return {width = size.width, height = size.height}
end

--[[--

将 CCRect 对象转换为一个 Lua 表格

~~~ lua

local rect = cc.rect(100, 50, 200, 80)
local res = cc.rect2t(rect)
-- res = {origin = {x = 100, y = 50}, size = {width = 200, height = 80}}

~~~

@param CCRect rect

@return table

@see cc.t2rect

]]
cc.rect2t = function(rect)
    return {origin = cc.point2t(rect.origin), size = cc.size2t(rect.size)}
end

--[[--

将一个 Lua 表格转换为 CCPoint 对象

~~~ lua

local input = {width = 200, height = 80}
local res = cc.t2size(input)
-- res 是一个 CCSize 对象
-- res = CCSize(200, 80)

~~~

@param table t

@return CCSize

@see cc.size2t

]]
cc.t2point = function(t)
    return CCPoint(t.x, t.y)
end

--[[--

将一个 Lua 表格转换为 CCSize 对象

~~~ lua

local t = {width = 200, height = 80}
local res = cc.t2size(t)
-- res 是一个 CCSize 对象

~~~

@param table t

@return CCSize

@see cc.size2t

]]
cc.t2size = function(t)
    return CCSize(t.width, t.height)
end

--[[--

将一个 Lua 表格转换为 CCRect 对象

~~~ lua

local t = {origin = {x = 100, y = 50}, size = {width = 200, height = 80}}
local res = cc.t2rect(t)
-- res 是一个 CCRect 对象

~~~

@param table t

@return CCRect

@see cc.rect2t

]]
cc.t2rect = function(t)
    return CCRect(t.origin.x, t.origin.y, t.size.width, t.size.height)
end

--[[--

创建一个 ccColor3B 对象

~~~ lua

local color = cc.c3(255, 200, 120)
-- color 是一个 ccColor3B 对象
-- color.r 是红色通道，值为 255
-- color.g 是绿色通道，值为 200
-- color.b 是蓝色通道，值为 120

~~~

reg, green, blue 的取值范围是 0 ~ 255。

@param int red
@param int green
@param int blue

@return ccColor3B

]]
cc.c3 = ccc3

--[[--

创建一个 ccColor4B 对象

~~~ lua

local color = cc.c4(255, 200, 120, 50)
-- color 是一个 ccColor4B 对象
-- color.r 是红色通道，值为 255
-- color.g 是绿色通道，值为 200
-- color.b 是蓝色通道，值为 120
-- color.a 是 alpha 通道，值为 50

~~~

reg, green, blue, alpha 的取值范围是 0 ~ 255。

@param int red
@param int green
@param int blue
@param int alpha

@return ccColor4B

]]
cc.c4 = ccc4

--[[--

创建一个 ccColor4F 对象

~~~ lua

local color = cc.c4(1.0, 0.8, 0.5, 0.7)
-- color 是一个 ccColor4F 对象
-- color.r 是红色通道，值为 1.0
-- color.g 是绿色通道，值为 0.8
-- color.b 是蓝色通道，值为 0.5
-- color.a 是 alpha 通道，值为 0.7

~~~

reg, green, blue, alpha 的取值范围是 0 ~ 1.0

@param number red
@param number green
@param number blue
@param number alpha

@return ccColor4F

]]
cc.c4f = ccc4f

cc.NODE_EVENT               = 0
cc.NODE_ENTER_FRAME_EVENT   = 1
cc.NODE_TOUCH_EVENT         = 2
cc.NODE_TOUCH_CAPTURE_EVENT = 3
cc.MENU_ITEM_CLICKED_EVENT  = 4
cc.ACCELERATE_EVENT         = 5
cc.KEYPAD_EVENT             = 6

cc.TOUCH_MODE_ALL_AT_ONCE   = 0
cc.TOUCH_MODE_ONE_BY_ONE    = 1

require(cc.PACKAGE_NAME .. ".cocos2dx.CCNodeExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSceneExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCSpriteExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCLayerExtend")
require(cc.PACKAGE_NAME .. ".cocos2dx.CCDrawNodeExtend")
