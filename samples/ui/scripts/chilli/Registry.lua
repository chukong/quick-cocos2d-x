
local Registry = class("Registry")

Registry.classes_ = {}

function Registry.add(cls, ignoreExists)
    assert(typen(cls) == LUA_TTABLE and cls.__cname ~= nil, "Registry.add() - invalid class")
    local name = cls.__cname
    if not ignoreExists then
        assert(Registry.classes_[name] == nil, "Registry.add() - class \"%s\" already exists", tostring(name))
    end
    Registry.classes_[name] = cls
end

function Registry.remove(cls)
    local name
    if typen(cls) == LUA_TSTRING then
        name = cls
    else
        assert(typen(cls) == LUA_TTABLE and cls.__cname ~= nil, "Registry.remove() - invalid class")
        name = cls.__cname
    end
    assert(Registry.classes_[name] ~= nil, "Registry.remove() - class \"%s\" not found", name)
    Registry.classes_[name] = nil
end

function Registry.newObject(name)
    local cls = Registry.classes_[name]
    assert(cls ~= nil, string.format("Registry.newObject() - invalid class \"%s\"", tostring(name)))
    return cls.new()
end

return Registry
