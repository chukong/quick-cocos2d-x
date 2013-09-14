
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
    if layout then layout:apply(self.target_) end
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
end

function LayoutProtocol:onBind_()
    self.preferredSize_ = nil
    self.layoutSize_ = {width = 0, height = 0}
    self.minSize_    = {width = 0, height = 0}
    self.maxSize_    = {width = MAX, height = MAX}
    self.sizePolicy_ = {h = display.AUTO_SIZE, v = display.AUTO_SIZE}
    self.alignment_  = display.LEFT_BOTTOM
    self.padding_    = {top = 0, right = 0, bottom = 0, left = 0}
    self.margin_     = {top = 0, right = 0, bottom = 0, left = 0}
end

function LayoutProtocol:onUnbind_()
end

return LayoutProtocol
