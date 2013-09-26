
local BehaviorBase = class("BehaviorBase")

function BehaviorBase:ctor(behaviorName, depends, priority, conflictions)
    self.name_         = behaviorName
    self.depends_      = totable(depends)
    self.priority_     = toint(priority) -- 越大越先初始化
    self.conflictions_ = totable(conflictions)
end

function BehaviorBase:getName()
    return self.name_
end

function BehaviorBase:getDepends()
    return self.depends_
end

function BehaviorBase:getPriority()
    return self.priority_
end

function BehaviorBase:getConflictions()
    return self.conflictions_
end

function BehaviorBase:bind(object)
end

function BehaviorBase:unbind(object)
end

function BehaviorBase:reset(object)
end

return BehaviorBase
