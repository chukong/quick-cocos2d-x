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

JSON 编码与解码

]]
local json = {}
local cjson = require("cjson")

--[[--

将表格数据编码为 JSON 字符串

~~~ lua

local str = json.encode({a=1,b="ss",c={c1=1,c2=2},d={10,11},100})
echo(str) -- {"a":1,"b":"ss","c":{"c1":1,"c2":2},"d":[10,11],"1":100}
local str = json.encode({1,2,"3",{10,11}})
echo(str) -- [ 1,2,"3",[10,11] ]

~~~

注意: table作为字典使用时，整型键值将被转换为字符串键值

~~~ lua

local str = json.encode({a=1,[5]=3})
echo(str) -- {"a":1,"5":3}

~~~

注意: table所有键值为整型时，会当作数组看待，空位将转化为null

~~~ lua

local str = json.encode({[3]=2,[5]=3})
echo(str) -- [null,null,2,null,3]

~~~

@param table 表格对象

@return string json字符串

]]
function json.encode(var)
    local status, result = pcall(cjson.encode, var)
    if status then return result end
    if DEBUG > 1 then
        printError("json.encode() - encoding failed: %s", tostring(result))
    end
end

--[[--

将 JSON 字符串解码为表格对象

~~~ lua

local json = require("framework.shared.json")
local tb = json.decode('{"a":1,"b":"ss","c":{"c1":1,"c2":2},"d":[10,11],"1":100}')
dump(tb) --[ [
- "<var>" = {
-     "1" = 100
-     "a" = 1
-     "b" = "ss"
-     "c" = {
-         "c1" = 1
-         "c2" = 2
-     }
-     "d" = {
-         1 = 10
-         2 = 11
-     }
- }
] ]
local tb = json.decode('[1,2,"3",[10,11] ]')
dump(tb) --[ [
- "<var>" = {
-     1 = 1
-     2 = 2
-     3 = "3"
-     4 = {
-         1 = 10
-         2 = 11
-     }
- }
] ]

~~~

@param string json字符串

@return table 表格对象

]]
function json.decode(text)
    local status, result = pcall(cjson.decode, text)
    if status then return result end
    if DEBUG > 1 then
        printError("json.decode() - decoding failed: %s", tostring(result))
    end
end

json.null = cjson.null

return json
