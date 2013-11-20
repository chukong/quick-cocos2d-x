
local Registry = class("Registry")

Registry.classes_ = {}

function Registry.add(cls, name)
    assert(type(cls) == "table" and cls.__cname ~= nil, "Registry.add() - invalid class")
    if not name then name = cls.__cname end
    assert(Registry.classes_[name] == nil, "Registry.add() - class \"%s\" already exists", tostring(name))
    Registry.classes_[name] = cls
end

function Registry.remove(name)
    assert(Registry.classes_[name] ~= nil, "Registry.remove() - class \"%s\" not found", name)
    Registry.classes_[name] = nil
end

function Registry.newObject(name)
    local cls = Registry.classes_[name]
    if not cls then
        -- auto load
        pcall(function()
            cls = require(name)
            Registry.add(name)
        end)
    end
    assert(cls ~= nil, string.format("Registry.newObject() - invalid class \"%s\"", tostring(name)))
    return cls.new()
end

return Registry
