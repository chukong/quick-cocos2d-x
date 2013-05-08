
local CCObjectTypes = {}

function string.split(str, delimiter)
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

function string.trim(str)
    str = string.gsub(str, "^[ \t\n\r]+", "")
    return string.gsub(str, "[ \t\n\r]+$", "")
end

if type(_extra_parameters) == "table" then
    if _extra_parameters.CCOBJECTS then
        CCObjectTypes = string.split(_extra_parameters.CCOBJECTS, ",")
        for i = #CCObjectTypes, 1, -1 do
            local v = string.trim(tostring(CCObjectTypes[i]))
            if v == "" then
                table.remove(CCObjectTypes, i)
            else
                CCObjectTypes[i] = v
            end
        end
    end
end

-- register CCObject types
_push_functions = _push_functions or {}
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_is_functions = _is_functions or {}
_to_functions = _to_functions or {}

_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"
