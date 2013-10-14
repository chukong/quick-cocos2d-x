
local BasicLayoutProtocol = import(".BasicLayoutProtocol")
local LayoutProtocol = class("LayoutProtocol", BasicLayoutProtocol)

function LayoutProtocol:ctor()
    LayoutProtocol.super.ctor(self, "LayoutProtocol")
end

function LayoutProtocol:setLayoutSize(width, height)
    LayoutProtocol.super.setLayoutSize(self, width, height)
    self:setLayout(self.layout_)
    return self
end

function LayoutProtocol:setLayout(layout)
    self.layout_ = layout
    if layout then
        layout:apply(self.target_)
    end
    return self
end

function LayoutProtocol:getLayout()
    return self.layout_
end

function LayoutProtocol:exportMethods()
    LayoutProtocol.super.exportMethods(self)
    self:exportMethods_({
        "setLayout",
        "getLayout",
    })
    return self
end

return LayoutProtocol
