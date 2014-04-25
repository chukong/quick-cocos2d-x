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

提供一组常用函数，以及对 Lua 标准库的扩展

]]

--[[--

输出格式化字符串

~~~ lua

printf("The value = %d", 100)

~~~

@param fmt 输出格式
@param ... 更多参数

]]
function printf(fmt, ...)
    print(string.format(tostring(fmt), ...))
end

--[[--

检查并尝试转换为数值，如果无法转换则返回 0

@param v 要检查的值
@param base 进制，默认为十进制

@return 结果

]]
function checknumber(v, base)
    return tonumber(v, base) or 0
end

--[[--

检查并尝试转换为整数，如果无法转换则返回 0

@param v 要检查的值

@return 结果

]]
function checkint(v)
    return math.round(checknumber(v))
end

--[[--

检查并尝试转换为布尔值，除了 nil 和 false，其他任何值都会返回 true

@param v 要检查的值

@return 结果

]]
function checkbool(v)
    return (v ~= nil and v ~= false)
end

--[[--

检查值是否是一个表格，如果不是则返回一个空表格

@param v 要检查的值

@return 结果

]]
function checktable(v)
    if type(v) ~= "table" then v = {} end
    return v
end

--[[--

如果表格中指定 key 的值为 nil，或者输入值不是表格，返回 false，否则返回 true

@param arr 要检查的表格
@param key 要检查的键名

@return 结果

]]
function isset(arr, key)
    local t = type(arr)
    return (t == "table" or t == "userdata") and arr[key] ~= nil
end

--[[--

深度克隆一个值

~~~ lua

-- 下面的代码，t2 是 t1 的引用，修改 t2 的属性时，t1 的内容也会发生变化
local t1 = {a = 1, b = 2}
local t2 = t1
t2.b = 3    -- t1 = {a = 1, b = 3} <-- t1.b 发生变化

-- clone() 返回 t1 的副本，修改 t2 不会影响 t1
local t1 = {a = 1, b = 2}
local t2 = clone(t1)
t2.b = 3    -- t1 = {a = 1, b = 2} <-- t1.b 不受影响

~~~

@param object 要克隆的值

@return 结果

]]
function clone(object)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[_copy(key)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end

--[[--

创建一个类

~~~ lua

-- 定义名为 Shape 的基础类
local Shape = class("Shape")

-- ctor() 是类的构造函数，在调用 Shape.new() 创建 Shape 对象实例时会自动执行
function Shape:ctor(shapeName)
    self.shapeName = shapeName
    printf("Shape:ctor(%s)", self.shapeName)
end

-- 为 Shape 定义个名为 draw() 的方法
function Shape:draw()
    printf("draw %s", self.shapeName)
end

--

-- Circle 是 Shape 的继承类
local Circle = class("Circle", Shape)

function Circle:ctor()
    -- 如果继承类覆盖了 ctor() 构造函数，那么必须手动调用父类构造函数
    -- 类名.super 可以访问指定类的父类
    Circle.super.ctor(self, "circle")
    self.radius = 100
end

function Circle:setRadius(radius)
    self.radius = radius
end

-- 覆盖父类的同名方法
function Circle:draw()
    printf("draw %s, raidus = %0.2f", self.shapeName, self.raidus)
end

--

local Rectangle = class("Rectangle", Shape)

function Rectangle:ctor()
    Rectangle.super.ctor(self, "rectangle")
end

--

local circle = Circle.new()             -- 输出: Shape:ctor(circle)
circle:setRaidus(200)
circle:draw()                           -- 输出: draw circle, radius = 200.00

local rectangle = Rectangle.new()       -- 输出: Shape:ctor(rectangle)
rectangle:draw()                        -- 输出: draw rectangle

~~~

### 高级用法

class() 除了定义纯 Lua 类之外，还可以从 C++ 对象继承类。

比如需要创建一个工具栏，并在添加按钮时自动排列已有的按钮，那么我们可以使用如下的代码：

~~~ lua

-- 从 CCNode 对象派生 Toolbar 类，该类具有 CCNode 的所有属性和行为
local Toolbar = class("Toolbar", function()
    return display.newNode() -- 返回一个 CCNode 对象
end)

-- 构造函数
function Toolbar:ctor()
    self.buttons = {} -- 用一个 table 来记录所有的按钮
end

-- 添加一个按钮，并且自动设置按钮位置
function Toolbar:addButton(button)
    -- 将按钮对象加入 table
    self.buttons[#self.buttons + 1] = button

    -- 添加按钮对象到 CCNode 中，以便显示该按钮
    -- 因为 Toolbar 是从 CCNode 继承的，所以可以使用 addChild() 方法
    self:addChild(button)

    -- 按照按钮数量，调整所有按钮的位置
    local x = 0
    for _, button in ipairs(self.buttons) do
        button:setPosition(x, 0)
        -- 依次排列按钮，每个按钮之间间隔 10 点
        x = x + button:getContentSize().width + 10
    end
end

~~~

class() 的这种用法让我们可以在 C++ 对象基础上任意扩展行为。

~

既然是继承，自然就可以覆盖 C++ 对象的方法：

~~~ lua

function Toolbar:setPosition(x, y)
    -- 由于在 Toolbar 继承类中覆盖了 CCNode 对象的 setPosition() 方法
    -- 所以我们要用以下形式才能调用到 CCNode 原本的 setPosition() 方法
    getmetatable(self).setPosition(self, x, y)

    printf("x = %0.2f, y = %0.2f", x, y)
end

~~~

**注意:** Lua 继承类覆盖的方法并不能从 C++ 调用到。也就是说通过 C++ 代码调用这个 CCNode 对象的 setPosition() 方法时，并不会执行我们在 Lua 中定义的 Toolbar:setPosition() 方法。

@param classname 类名
@param super 父类或者创建对象实例的函数

@return 类定义

]]
function class(classname, super)
    local superType = type(super)
    local cls

    if superType ~= "function" and superType ~= "table" then
        superType = nil
        super = nil
    end

    if superType == "function" or (super and super.__ctype == 1) then
        -- inherited from native C++ Object
        cls = {}

        if superType == "table" then
            -- copy fields from super
            for k,v in pairs(super) do cls[k] = v end
            cls.__create = super.__create
            cls.super    = super
        else
            cls.__create = super
            cls.ctor = function() end
        end

        cls.__cname = classname
        cls.__ctype = 1

        function cls.new(...)
            local instance = cls.__create(...)
            -- copy fields from class to native object
            for k,v in pairs(cls) do instance[k] = v end
            instance.class = cls
            instance:ctor(...)
            return instance
        end

    else
        -- inherited from Lua Object
        if super then
            cls = {}
            setmetatable(cls, {__index = super})
            cls.super = super
        else
            cls = {ctor = function() end}
        end

        cls.__cname = classname
        cls.__ctype = 2 -- lua
        cls.__index = cls

        function cls.new(...)
            local instance = setmetatable({}, cls)
            instance.class = cls
            instance:ctor(...)
            return instance
        end
    end

    return cls
end

--[[--

如果对象是指定类或其子类的实例，返回 true，否则返回 false

~~~ lua

local Animal = class("Animal")
local Duck = class("Duck", Animal)

print(iskindof(Duck.new(), "Animal")) -- 输出 true

~~~

@param obj 要检查的对象
@param classname 类名

@return 结果

]]
function iskindof(obj, classname)
    local t = type(obj)

    if t == "table" then
        local mt = getmetatable(obj)
        while mt and mt.__index do
            if mt.__index.__cname == classname then
                return true
            end
            mt = mt.super
        end
        return false

    elseif t == "userdata" then

    else
        return false
    end
end

--[[--

载入一个模块

import() 与 require() 功能相同，但具有一定程度的自动化特性。

假设我们有如下的目录结构：

~~~

app/
app/classes/
app/classes/MyClass.lua
app/classes/MyClassBase.lua
app/data/Data1.lua
app/data/Data2.lua

~~~

MyClass 中需要载入 MyClassBase 和 MyClassData。如果用 require()，MyClass 内的代码如下：

~~~ lua

local MyClassBase = require("app.classes.MyClassBase")
local MyClass = class("MyClass", MyClassBase)

local Data1 = require("app.classes.data.Data1")
local Data2 = require("app.classes.data.Data2")

~~~

假如我们将 MyClass 及其相关文件换一个目录存放，那么就必须修改 MyClass 中的 require() 命令，否则将找不到模块文件。

而使用 import()，我们只需要如下写：

~~~ lua

local MyClassBase = import(".MyClassBase")
local MyClass = class("MyClass", MyClassBase)

local Data1 = import(".data.Data1")
local Data2 = import(".data.Data2")

~~~

当在模块名前面有一个“.”时，import() 会从当前模块所在目录中查找其他模块。因此 MyClass 及其相关文件不管存放到什么目录里，我们都不再需要修改 MyClass 中的 import() 命令。这在开发一些重复使用的功能组件时，会非常方便。

我们可以在模块名前添加多个“.”，这样 import() 会从更上层的目录开始查找模块。

~

不过 import() 只有在模块级别调用（也就是没有将 import() 写在任何函数中）时，才能够自动得到当前模块名。如果需要在函数中调用 import()，那么就需要指定当前模块名：

~~~ lua

# MyClass.lua

# 这里的 ... 是隐藏参数，包含了当前模块的名字，所以最好将这行代码写在模块的第一行
local CURRENT_MODULE_NAME = ...

local function testLoad()
    local MyClassBase = import(".MyClassBase", CURRENT_MODULE_NAME)
    # 更多代码
end

~~~

@param moduleName 要载入的模块的名字
@param currentModuleName 当前模块名

@return 返回载入的模块的返回值

]]
function import(moduleName, currentModuleName)
    local currentModuleNameParts
    local moduleFullName = moduleName
    local offset = 1

    while true do
        if string.byte(moduleName, offset) ~= 46 then -- .
            moduleFullName = string.sub(moduleName, offset)
            if currentModuleNameParts and #currentModuleNameParts > 0 then
                moduleFullName = table.concat(currentModuleNameParts, ".") .. "." .. moduleFullName
            end
            break
        end
        offset = offset + 1

        if not currentModuleNameParts then
            if not currentModuleName then
                local n,v = debug.getlocal(3, 1)
                currentModuleName = v
            end

            currentModuleNameParts = string.split(currentModuleName, ".")
        end
        table.remove(currentModuleNameParts, #currentModuleNameParts)
    end

    return require(moduleFullName)
end

--[[--

将 Lua 对象及其方法包装为一个匿名函数

在 quick-cocos2d-x 中，许多功能需要传入一个 Lua 函数做参数，然后在特定事件发生时就会调用传入的函数。例如触摸事件、帧事件等等。

~~~ lua

local MyScene = class("MyScene", function()
    return display.newScene("MyScene")
end)

function MyScene:ctor()
    self.frameTimeCount = 0
    -- 注册帧事件
    self:addEventListener(cc.ENTER_FRAME_EVENT, self.onEnterFrame)
end

function MyScene:onEnterFrame(dt)
    self.frameTimeCount = self.frameTimeCount + dt
end

~~~

上述代码执行时将出错，报告“Invalid self”，这就是因为 C++ 无法识别 Lua 对象方法。因此在调用我们传入的 self.onEnterFrame 方法时没有提供正确的参数。

要让上述的代码正常工作，就需要使用 handler() 进行一下包装：

~~~ lua

function MyScene:ctor()
    self.frameTimeCount = 0
    -- 注册帧事件
    self:addEventListener(cc.ENTER_FRAME_EVENT, handler(self, self.onEnterFrame))
end

~~~

实际上，除了 C++ 回调 Lua 函数之外，在其他所有需要回调的地方都可以使用 handler()。

@param target Lua 对象
@param method 对象方法

@return 包装后的匿名函数

]]
function handler(target, method)
    return function(...)
        return method(target, ...)
    end
end

function math.newrendomseed()
    local ok, socket = pcall(function()
        return require("socket")
    end)

    if ok then
        -- 如果集成了 socket 模块，则使用 socket.gettime() 获取随机数种子
        math.randomseed(socket.gettime() * 1000)
    else
        math.randomseed(os.time())
    end
    math.random()
    math.random()
    math.random()
    math.random()
end

function math.round(num)
    return math.floor(num + 0.5)
end

function io.exists(path)
    local file = io.open(path, "r")
    if file then
        io.close(file)
        return true
    end
    return false
end

function io.readfile(path)
    local file = io.open(path, "r")
    if file then
        local content = file:read("*a")
        io.close(file)
        return content
    end
    return nil
end

function io.writefile(path, content, mode)
    mode = mode or "w+b"
    local file = io.open(path, mode)
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    else
        return false
    end
end

function io.pathinfo(path)
    local pos = string.len(path)
    local extpos = pos + 1
    while pos > 0 do
        local b = string.byte(path, pos)
        if b == 46 then -- 46 = char "."
            extpos = pos
        elseif b == 47 then -- 47 = char "/"
            break
        end
        pos = pos - 1
    end

    local dirname = string.sub(path, 1, pos)
    local filename = string.sub(path, pos + 1)
    extpos = extpos - pos
    local basename = string.sub(filename, 1, extpos - 1)
    local extname = string.sub(filename, extpos)
    return {
        dirname = dirname,
        filename = filename,
        basename = basename,
        extname = extname
    }
end

function io.filesize(path)
    local size = false
    local file = io.open(path, "r")
    if file then
        local current = file:seek()
        size = file:seek("end")
        file:seek("set", current)
        io.close(file)
    end
    return size
end

function table.nums(t)
    local count = 0
    for k, v in pairs(t) do
        count = count + 1
    end
    return count
end

function table.keys(t)
    local keys = {}
    for k, v in pairs(t) do
        keys[#keys + 1] = k
    end
    return keys
end

function table.values(t)
    local values = {}
    for k, v in pairs(t) do
        values[#values + 1] = v
    end
    return values
end

function table.merge(dest, src)
    for k, v in pairs(src) do
        dest[k] = v
    end
end

--[[--

insert list.

**Usage:**

    local dest = {1, 2, 3}
    local src  = {4, 5, 6}
    table.insertTo(dest, src)
    -- dest = {1, 2, 3, 4, 5, 6}
	dest = {1, 2, 3}
	table.insertTo(dest, src, 5)
    -- dest = {1, 2, 3, nil, 4, 5, 6}


@param table dest
@param table src
@param table begin insert position for dest
]]
function table.insertTo(dest, src, begin)
	begin = tonumber(begin)
	if begin == nil then
		begin = #dest + 1
	end

	local len = #src
	for i = 0, len - 1 do
		dest[i + begin] = src[i + 1]
	end
end

--[[
search target index at list.

@param table list
@param * target
@param int from idx, default 1
@param bool useNaxN, the len use table.maxn(true) or #(false) default:false
@param return index of target at list, if not return -1
]]
function table.indexOf(list, target, from, useMaxN)
	local len = (useMaxN and #list) or table.maxn(list)
	if from == nil then
		from = 1
	end
	for i = from, len do
		if list[i] == target then
			return i
		end
	end
	return -1
end

function table.indexOfKey(list, key, value, from, useMaxN)
	local len = (useMaxN and #list) or table.maxn(list)
	if from == nil then
		from = 1
	end
	local item = nil
	for i = from, len do
		item = list[i]
		if item ~= nil and item[key] == value then
			return i
		end
	end
	return -1
end

function table.removeItem(t, item, removeAll)
    for i = #t, 1, -1 do
        if t[i] == item then
            table.remove(t, i)
            if not removeAll then break end
        end
    end
end

function table.map(t, fun)
    for k,v in pairs(t) do
        t[k] = fun(v, k)
    end
end

function table.walk(t, fun)
    for k,v in pairs(t) do
        fun(v, k)
    end
end

function table.filter(t, fun)
    for k,v in pairs(t) do
        if not fun(v, k) then
            t[k] = nil
        end
    end
end

function table.find(t, item)
    return table.keyOfItem(t, item) ~= nil
end

function table.unique(t)
    local r = {}
    local n = {}
    for i = #t, 1, -1 do
        local v = t[i]
        if not r[v] then
            r[v] = true
            n[#n + 1] = v
        end
    end
    return n
end

function table.keyOfItem(t, item)
    for k,v in pairs(t) do
        if v == item then return k end
    end
    return nil
end

function string.htmlspecialchars(input)
    for k, v in pairs(string._htmlspecialchars_set) do
        input = string.gsub(input, k, v)
    end
    return input
end
string._htmlspecialchars_set = {}
string._htmlspecialchars_set["&"] = "&amp;"
string._htmlspecialchars_set["\""] = "&quot;"
string._htmlspecialchars_set["'"] = "&#039;"
string._htmlspecialchars_set["<"] = "&lt;"
string._htmlspecialchars_set[">"] = "&gt;"

function string.htmlspecialcharsDecode(input)
    for k, v in pairs(string._htmlspecialchars_set) do
        input = string.gsub(input, v, k)
    end
    return input
end

function string.nl2br(input)
    return string.gsub(input, "\n", "<br />")
end

function string.text2html(input)
    input = string.gsub(input, "\t", "    ")
    input = string.htmlspecialchars(input)
    input = string.gsub(input, " ", "&nbsp;")
    input = string.nl2br(input)
    return input
end

function string.split(str, delimiter)
    str = tostring(str)
    delimiter = tostring(delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    -- for each divider found
    for st,sp in function() return string.find(str, delimiter, pos, true) end do
        table.insert(arr, string.sub(str, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(str, pos))
    return arr
end

function string.ltrim(str)
    return string.gsub(str, "^[ \t\n\r]+", "")
end

function string.rtrim(str)
    return string.gsub(str, "[ \t\n\r]+$", "")
end

function string.trim(str)
    str = string.gsub(str, "^[ \t\n\r]+", "")
    return string.gsub(str, "[ \t\n\r]+$", "")
end

function string.ucfirst(str)
    return string.upper(string.sub(str, 1, 1)) .. string.sub(str, 2)
end

local function urlencodeChar(char)
    return "%" .. string.format("%02X", string.byte(c))
end

function string.urlencode(str)
    -- convert line endings
    str = string.gsub(tostring(str), "\n", "\r\n")
    -- escape all characters but alphanumeric, '.' and '-'
    str = string.gsub(str, "([^%w%.%- ])", urlencodeChar)
    -- convert spaces to "+" symbols
    return string.gsub(str, " ", "+")
end

function string.urldecode(str)
    str = string.gsub (str, "+", " ")
    str = string.gsub (str, "%%(%x%x)", function(h) return string.char(checknumber(h,16)) end)
    str = string.gsub (str, "\r\n", "\n")
    return str
end

function string.utf8len(str)
    local len  = #str
    local left = len
    local cnt  = 0
    local arr  = {0, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc}
    while left ~= 0 do
        local tmp = string.byte(str, -left)
        local i   = #arr
        while arr[i] do
            if tmp >= arr[i] then
                left = left - i
                break
            end
            i = i - 1
        end
        cnt = cnt + 1
    end
    return cnt
end

function string.formatNumberThousands(num)
    local formatted = tostring(checknumber(num))
    local k
    while true do
        formatted, k = string.gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
        if k == 0 then break end
    end
    return formatted
end
