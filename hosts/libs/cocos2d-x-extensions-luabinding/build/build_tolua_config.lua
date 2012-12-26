
_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

local CCObjectTypes = {
    -- Add CCObject inherited class to here
    "CCScale9Sprite",
    "CCControl",
    "CCControlButton",
    "CCEditBox",
}

-- register CCObject types
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"


function get_property_methods_hook(ptype, name)
    if string.sub(ptype, 1, 2) == "CC" then
        ptype = string.sub(ptype, 3)
    end
    return "get"..ptype, "set"..ptype
end
