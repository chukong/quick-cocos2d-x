
local Component = import("..Component")
local LayoutProtocol = class("LayoutProtocol", Component)

local MAX = 999999

function LayoutProtocol:ctor()
    LayoutProtocol.super.ctor(self, "LayoutProtocol")
end

function LayoutProtocol:getLayoutPreferredSize()
    if self.preferredSize_ then
        return self.preferredSize_
    else
        return cc.size2t(self.target_:getCascadeBoundingBox().size)
    end
end

function LayoutProtocol:setLayoutPreferredSize(width, height)
    if height then
        self.preferredSize_.width = width
        self.preferredSize_.height = height
    else
        self.preferredSize_.width = width.width
        self.preferredSize_.height = width.height
    end
    return self
end

function LayoutProtocol:getLayoutSize()
    return self.layoutSize_
end

function LayoutProtocol:setLayoutSize(width, height)
    if height then
        self.layoutSize_.width = width
        self.layoutSize_.height = height
    else
        self.layoutSize_.width = width.width
        self.layoutSize_.height = width.height
    end
    self:setLayout(self.layout_)
    return self
end

function LayoutProtocol:getLayoutMinSize()
    return self.minSize_
end

function LayoutProtocol:setLayoutMinSize(width, height)
    if height then
        self.minSize_.width = width
        self.minSize_.height = height
    else
        self.minSize_.width = width.width
        self.minSize_.height = width.height
    end
    return self
end

function LayoutProtocol:getLayoutMaxSize()
    return self.maxSize_
end

function LayoutProtocol:setLayoutMaxSize(width, height)
    if height then
        self.maxSize_.width = width
        self.maxSize_.height = height
    else
        self.maxSize_.width = width.width
        self.maxSize_.height = width.height
    end
    return self
end

function LayoutProtocol:getLayoutSizePolicy()
    return self.sizePolicy_
end

function LayoutProtocol:setLayoutSizePolicy(h, v)
    if v then
        self.sizePolicy_.h = h
        self.sizePolicy_.v = v
    else
        self.sizePolicy_.h = h.h
        self.sizePolicy_.v = h.v
    end
    return self
end

function LayoutProtocol:getLayoutPadding()
    return self.padding_
end

function LayoutProtocol:setLayoutPadding(top, right, bottom, left)
    if right then
        self.padding_.top = top
        self.padding_.right = right
        self.padding_.bottom = bottom
        self.padding_.left = left
    else
        self.padding_.top = top.top
        self.padding_.right = top.right
        self.padding_.bottom = top.bottom
        self.padding_.left = top.left
    end
    return self
end

function LayoutProtocol:getLayoutMargin()
    return self.margin_
end

function LayoutProtocol:setLayoutMargin(top, right, bottom, left)
    if right then
        self.margin_.top = top
        self.margin_.right = right
        self.margin_.bottom = bottom
        self.margin_.left = left
    else
        self.margin_.top = top.top
        self.margin_.right = top.right
        self.margin_.bottom = top.bottom
        self.margin_.left = top.left
    end
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
    self:exportMethods_({
        "getLayoutPreferredSize",
        "setLayoutPreferredSize",
        "getLayoutSize",
        "setLayoutSize",
        "getLayoutMinSize",
        "setLayoutMinSize",
        "getLayoutMaxSize",
        "setLayoutMaxSize",
        "getLayoutSizePolicy",
        "setLayoutSizePolicy",
        "getLayoutPadding",
        "setLayoutPadding",
        "getLayoutMargin",
        "setLayoutMargin",
        "setLayout",
        "getLayout",
    })
end

function LayoutProtocol:onBind_()
    self.preferredSize_ = nil
    self.layoutSize_ = {width = 0, height = 0}
    self.minSize_    = {width = 0, height = 0}
    self.maxSize_    = {width = MAX, height = MAX}
    self.sizePolicy_ = {h = cc.ui.PREFERRED_SIZE_POLICY, v = cc.ui.PREFERRED_SIZE_POLICY}
    self.padding_    = {top = 0, right = 0, bottom = 0, left = 0}
    self.margin_     = {top = 0, right = 0, bottom = 0, left = 0}
end

function LayoutProtocol:onUnbind_()
end

return LayoutProtocol
