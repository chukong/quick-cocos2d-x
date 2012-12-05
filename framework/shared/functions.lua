
--[[--

转换值为数值，结果可能是整数或浮点数。

@param mixed v
@return number

]]
function _n(v)
    v = tonumber(v)
    return v or 0
end

--[[--

转换值为整数（四舍五入）。

@param mixed v
@return number(integer)

]]
function _i(v)
    return math.round(_n(v))
end

--[[--

转换值为字符串。

@param mixed v
@return string

]]
function _s(v)
    return tostring(v)
end

--[[--

测试值是否为 nil 或 false，并返回结果。

@param mixed v
@return boolean

]]
function _b(v)
    return (v ~= nil and v ~= false)
end

--[[--

检查值是否是表格，如果值不是表格，则返回一个空表格。

@param mixed v
@return table

]]
function _t(v)
    if type(v) ~= "table" then v = {} end
    return v
end

--[[--

返回格式化后的字符串，string.format() 函数的别名。

@code
    local value = format("%0.2f", 0.4785) -- value = "0.48"
@endcode

@param string format
@param mixed ...
@return string

]]
function format(...)
    return string.format(select(1, ...))
end

--[[--

输出格式化后的字符串。

@code
    printf("%0.2f", 0.4785) -- 输出 0.48
@endcode

@param string format
@param mixed ...

在不同平台上，输出目的地可能是控制台或者日志文件，详情参考 echo() 函数。

@see echo

]]
function printf(...)
    echo(string.format(select(1, ...)))
end

--[[--

对值进行四舍五入，返回结果。

@param number num
@return number(integer)

]]
function math.round(num)
    return math.floor(num + 0.5)
end

--[[--

对数值采用千分位分隔符格式化。

@code
    local value = math.comma("232423.234") -- value = "232,423.234"
@endcode

@param number num
@return string

]]
function math.comma(num)
    local formatted = tostring(_n(num))
    while true do
        formatted, k = string.gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
        if k == 0 then break end
    end
    return formatted
end

--[[--

测试指定的文件是否存在。

@param string path
@return boolean

]]
function io.exists(path)
    local file = io.open(path, "r")
    if file then
        io.close(file)
        return true
    end
    return false
end

--[[--

读取指定文件的内容，失败返回 nil。

@param string path
@return string

]]
function io.readfile(path)
    local file = io.open(path, "r")
    if file then
        local content = file:read("*a")
        io.close(file)
        return content
    end
    return nil
end

--[[--

写入内容到指定的文件，并返回结果指示是否写入成功。

@param string path
@param string content
@return boolean

]]
function io.writefile(path, content)
    local file = io.open(path, "w+")
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    else
        return false
    end
end

--[[--

分割路径，提取出文件名、目录名等信息。

@code
    local path = "/var/app/test/abc.png"
    local pathinfo  = io.pathinfo(path)
    -- pathinfo.dirname  = "/var/app/test/"
    -- pathinfo.filename = "abc.png"
    -- pathinfo.basename = "abc"
    -- pathinfo.extname  = ".png"
@endcode

@param string path
@return table

]]
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

--[[--

确定指定文件的大小，如果失败返回 false。

@param string path
@return number(integer)

]]
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

--[[--

根据路径和文件名，构造文件的完整路径。

@code
    local path = "/var/app/test"
    local filename = "abc.png"
    local fullpath = io.pathForFile(filename, path)
    -- fullpath = "/var/app/test/abc.png"
@endcode

@param string filename
@param string path
@return string

]]
-- append filename to path
function io.pathForFile(filename, path)
    path = string.gsub(path, "[\\\\/]+$", "")
    return path .. "/" .. filename
end

--[[--

从 package.path 中查找指定模块的文件名，如果失败返回 false。

@param string moduleName
@return string

]]
function io.findModulePath(moduleName)
    local filename = string.gsub(moduleName, "%.", "/") .. ".lua"
    local paths = string.split(package.path, ";")
    for i, path in ipairs(paths) do
        if string.sub(path, -5) == "?.lua" then
            path = string.sub(path, 1, -6)
            if not string.find(path, "?", 1, true) then
                local fullpath = path .. filename
                if io.exists(fullpath) then
                    return fullpath
                end
            end
        end
    end
    return false
end

--[[--

统计表格中包含的值的总数。

@param table t
@return number(integer)

]]
function table.nums(t)
    return #table.keys(t)
end

--[[--

返回包含表格中所有值的键名的表格。

@code
    local t = {a = 1, b = 2, c = 3}
    local keys = table.keys(t)
    -- keys = {"a", "b", "c"}
@endcode

@param table t
@return table

]]
function table.keys(t)
    local keys = {}
    for k, v in pairs(t) do
        keys[#keys + 1] = k
    end
    return keys
end

--[[--

返回包含表格中所有值的表格。

@code
    local t = {a = "1", b = "2", c = "3"}
    local values = table.values(t)
    -- values = {1, 2, 3}
@endcode

@param table t
@return table

]]
function table.values(t)
    local values = {}
    for k, v in pairs(t) do
        values[#values + 1] = v
    end
    return values
end

--[[--

将一个表格的值复制到另一个表格中。

@code
    local dest = {a = 1, b = 2}
    local src = {c = 3, d = 4}
    table.merge(dest, src)
    -- dest = {a = 1, b = 2, c = 3, d = 4}
@endcode

@param table dest
@param table src

]]
function table.merge(dest, src)
    for k, v in pairs(src) do
        dest[k] = v
    end
end

--[[--

克隆一个值。

因为在 Lua 中，表格的赋值并不会拷贝表格中包含的值，而只是添加一个对表格引用。
因此下面的代码会导致原始数据被修改：

@code
    local t1 = {a = 1, b = 2}
    local t2 = t1
    t2.b = 3
    -- t1 = {a = 1, b = 3} <-- t1 中的数据也被修改了
@endcode

要避免这种情况，就需要使用 clone() 函数：

@code
    local t1 = {a = 1, b = 2}
    local t2 = clone(t1)
    t2.b = 3
    -- t1 = {a = 1, b = 2} <-- t1 中的数据没有被修改
@endcode

@param mixed object
@return mixed

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

function class(classname, super)
    local cls
    if super then
        cls = clone(super)
    else
        cls = {}
    end
    cls.super     = super
    cls.classname = classname
    cls.__index   = cls

    function cls.new(...)
        local instance = setmetatable({}, cls)
        instance.class = cls
        if cls.ctor then instance:ctor(...) end
        return instance
    end

    return cls
end

function try(f, catch_f, finally_f)
    local throw_err
    local function catch_err(err)
        if catch_f then
            throw_err = catch_f(err)
        end
    end

    local ok, result = xpcall(f, catch_err)
    if ok then
        if finally_f then finally_f() end
        return result
    elseif throw_err then
        error(throw_err)
    end
end

function throw(msg, code)
    if code then
        error(format("<<%08u>> - %s", _i(code), _s(msg)), 2)
    else
        error(msg, 2)
    end
end

function export(arr, names)
    local args = {}
    for k, def in pairs(names) do
        if type(k) == "number" then
            args[def] = arr[def]
        else
            args[k] = arr[k] or def
        end
    end
    return args
end

function isset(arr, key)
    return type(arr) == "table" and arr[key] ~= nil
end

string._htmlspecialchars_set = {}
string._htmlspecialchars_set["&"] = "&amp;"
string._htmlspecialchars_set["\""] = "&quot;"
string._htmlspecialchars_set["'"] = "&#039;"
string._htmlspecialchars_set["<"] = "&lt;"
string._htmlspecialchars_set[">"] = "&gt;"

function string.htmlspecialchars(input)
    for k, v in pairs(string._htmlspecialchars_set) do
        input = string.gsub(input, k, v)
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

function string.split(str, div)
    if (div=='') then return false end
    local pos,arr = 0,{}
    -- for each divider found
    for st,sp in function() return string.find(str,div,pos,true) end do
        table.insert(arr,string.sub(str,pos,st-1)) -- Attach chars left of current divider
        pos = sp + 1 -- Jump past current divider
    end
    table.insert(arr,string.sub(str,pos)) -- Attach chars right of last divider
    return arr
end

function string.ltrim(str)
    return string.gsub(str, "^[ \t]+", "")
end

function string.rtrim(str)
    return string.gsub(str, "[ \t]+$", "")
end

function string.trim(str)
    str = string.gsub(str, "^[ \t]+", "")
    return string.gsub(str, "[ \t]+$", "")
end

function string.ucfirst(str)
    return string.upper(string.sub(str, 1, 1)) .. string.sub(str, 2)
end

function string.urlencodeChar(char)
    return "%" .. string.format("%02X", string.byte(c))
end

function string.urlencode(str)
    -- convert line endings
    str = string.gsub(tostring(str), "\n", "\r\n")
    -- escape all characters but alphanumeric, '.' and '-'
    str = string.gsub(str, "([^%w%.%- ])", string.urlencodeChar)
    -- convert spaces to "+" symbols
    return string.gsub(str, " ", "+")
end

function string.utf8len(str)
    local len = #str
    local left = len
    local cnt = 0
    local arr={0,0xc0,0xe0,0xf0,0xf8,0xfc}
    while left ~= 0 do
        local tmp=string.byte(str,-left)
        local i=#arr
        while arr[i] do
            if tmp>=arr[i] then
                left=left-i
                break
            end
            i=i-1
        end
        cnt=cnt+1
    end
    return cnt
end
