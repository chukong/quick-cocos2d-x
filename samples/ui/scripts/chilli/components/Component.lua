
local Component = class("Component")

function Component:ctor(name, depends)
    self.name_ = name
    self.depends_ = totable(depends)
end

function Component:getName()
    return self.name_
end

function Component:getDepends()
    return self.depends_
end

function Component:getTarget()
    return self.target_
end

function Component:exportMethods(methods)
    local target = self.target_
    local name = self.name_
    for _, key in ipairs(methods) do
        target[key] = function(__, ...)
            local r = {target:com(name)[key](self, ...)}
            if r[1] == self then
                r[1] = target
            end
            return unpack(r)
        end
    end
    return self
end

function Component:bind_(target)
    self.target_ = target
    for _, name in ipairs(self.depends_) do
        if not target:checkComponent(name) then
            target:addComponent(name)
        end
    end
    self:onBind_(target)
end

function Component:unbind_()
end

function Component:onBind_()
end

function Component:onUnbind_()
end

return Component
