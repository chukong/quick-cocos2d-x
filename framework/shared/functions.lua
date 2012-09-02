
function _n(v)
    v = tonumber(v)
    return v or 0
end

function _s(v)
    return tostring(v)
end

function _b(v)
    return (v ~= nil and v ~= false)
end

function _t(v)
    if type(v) ~= "table" then v = {} end
    return v
end

function _i(v)
    return math.floor(_n(v))
end

function format(...)
    return string.format(select(1, ...))
end

function printf(...)
    echo(string.format(select(1, ...)))
end

---- math

math.round = function(num)
    return math.floor(num + 0.5)
end

math.comma = function(num)
    local formatted = tostring(_n(num))
    while true do
        formatted, k = string.gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
        if k == 0 then break end
    end
    return formatted
end


---- io

-- checks whether a file exists
io.exists = function(path)
    local file = io.open(path, "r")
    if file then
        io.close(file)
        return true
    end
    return false
end

-- reads entire file into a string, on failure return nil
io.readfile = function(path)
    local file = io.open(path, "r")
    if file then
        local content = file:read("*a")
        io.close(file)
        return content
    end
    return nil
end

-- write a string to a file
io.writefile = function(path, content)
    local file = io.open(path, "w+")
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    else
        return false
    end
end

-- returns information [dirname, filename, basename, extname] about a file path
io.pathinfo = function(path)
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

-- gets file size, on failure return false
io.filesize = function(path)
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

-- append filename to path
io.pathForFile = function(filename, path)
    path = string.gsub(path, "[\\\\/]+$", "")
    return path .. "/" .. filename
end



---- table

-- count all elements in an table
table.nums = function(t)
    if type(t) ~= "table" then
        if DEBUG > 0 then traceback() end
        return nil
    end
    local nums = 0
    for k, v in pairs(t) do
        nums = nums + 1
    end
    return nums
end

---- global functions

-- clones object
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

function class(classname, ctor, super)
    local cls
    if super then
        cls = clone(super)
    else
        cls = {}
    end

    if super then
        cls.super = super
        for k, v in pairs(super) do cls[k] = v end
    end

    cls.super     = super
    cls.classname = classname
    cls.ctor      = ctor
    cls.__index   = cls

    local function callctor(o, ctor, super, ...)
        if super then callctor(o, super.ctor, super.super, ...) end
        if ctor then ctor(o, ...) end
    end

    cls.new = function(...)
        local o = setmetatable({}, cls)
        o.class = cls
        -- 创建对象实例时，要按照正确的顺序调用继承层次上所有的 ctor 函数
        callctor(o, ctor, super, ...)

        return o
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

string.htmlspecialchars = function(input)
    for k, v in pairs(string._htmlspecialchars_set) do
        input = string.gsub(input, k, v)
    end
    return input
end

string.nl2br = function(input)
    return string.gsub(input, "\n", "<br />")
end

string.text2html = function(input)
    input = string.gsub(input, "\t", "    ")
    input = string.htmlspecialchars(input)
    input = string.gsub(input, " ", "&nbsp;")
    input = string.nl2br(input)
    return input
end

string.split = function(str, div)
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

string.ltrim = function(str)
    return string.gsub(str, "^[ \t]+", "")
end

string.rtrim = function(str)
    return string.gsub(str, "[ \t]+$", "")
end

string.trim = function(str)
    str = string.gsub(str, "^[ \t]+", "")
    return string.gsub(str, "[ \t]+$", "")
end

string.ucfirst = function(str)
    return string.upper(string.sub(str, 1, 1)) .. string.sub(str, 2)
end

string.urlencodeChar = function(char)
    return "%" .. string.format("%02X", string.byte(c))
end

string.urlencode = function(str)
    -- convert line endings
    str = string.gsub(tostring(str), "\n", "\r\n")
    -- escape all characters but alphanumeric, '.' and '-'
    str = string.gsub(str, "([^%w%.%- ])", string.urlencodeChar)
    -- convert spaces to "+" symbols
    return string.gsub(str, " ", "+")
end
