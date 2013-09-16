
local Component = import("..Component")
local BasicLayoutProtocol = class("BasicLayoutProtocol", Component)

local MAX = 999999

function BasicLayoutProtocol:ctor()
    BasicLayoutProtocol.super.ctor(self, "BasicLayoutProtocol")
end

function BasicLayoutProtocol:getLayoutPreferredSize()
    if self.preferredSize_ then
        return clone(self.preferredSize_)
    else
        return cc.size2t(self.target_:getCascadeBoundingBox().size)
    end
end

function BasicLayoutProtocol:setLayoutPreferredSize(width, height)
    if height then
        self.preferredSize_.width = tonumber(width)
        self.preferredSize_.height = tonumber(height)
    else
        self.preferredSize_.width = width.width
        self.preferredSize_.height = width.height
    end
    return self
end

function BasicLayoutProtocol:getLayoutSize()
    return clone(self.layoutSize_)
end

function BasicLayoutProtocol:setLayoutSize(width, height)
    if height then
        self.layoutSize_.width = tonumber(width)
        self.layoutSize_.height = tonumber(height)
    else
        self.layoutSize_.width = width.width
        self.layoutSize_.height = width.height
    end
    return self
end

function BasicLayoutProtocol:getLayoutMinSize()
    return clone(self.minSize_)
end

function BasicLayoutProtocol:setLayoutMinSize(width, height)
    if height then
        self.minSize_.width = tonumber(width)
        self.minSize_.height = tonumber(height)
    else
        self.minSize_.width = width.width
        self.minSize_.height = width.height
    end
    return self
end

function BasicLayoutProtocol:getLayoutMaxSize()
    return clone(self.maxSize_)
end

function BasicLayoutProtocol:setLayoutMaxSize(width, height)
    if height then
        self.maxSize_.width = tonumber(width)
        self.maxSize_.height = tonumber(height)
    else
        self.maxSize_.width = width.width
        self.maxSize_.height = width.height
    end
    return self
end

function BasicLayoutProtocol:getLayoutSizePolicy()
    return clone(self.sizePolicy_)
end

function BasicLayoutProtocol:setLayoutSizePolicy(h, v)
    if v then
        self.sizePolicy_.h = h
        self.sizePolicy_.v = v
    else
        self.sizePolicy_.h = h.h
        self.sizePolicy_.v = h.v
    end
    return self
end

function BasicLayoutProtocol:getLayoutAlignment()
    return clone(self.alignment_)
end

function BasicLayoutProtocol:setLayoutAlignment(alignment)
    self.alignment_ = alignment
    return self
end

function BasicLayoutProtocol:getLayoutPadding()
    return clone(self.padding_)
end

function BasicLayoutProtocol:setLayoutPadding(top, right, bottom, left)
    if right then
        self.padding_.top = tonumber(top)
        self.padding_.right = tonumber(right)
        self.padding_.bottom = tonumber(bottom)
        self.padding_.left = tonumber(left)
    else
        self.padding_.top = top.top
        self.padding_.right = top.right
        self.padding_.bottom = top.bottom
        self.padding_.left = top.left
    end
    return self
end

function BasicLayoutProtocol:getLayoutMargin()
    return clone(self.margin_)
end

function BasicLayoutProtocol:setLayoutMargin(top, right, bottom, left)
    if right then
        self.margin_.top = tonumber(top)
        self.margin_.right = tonumber(right)
        self.margin_.bottom = tonumber(bottom)
        self.margin_.left = tonumber(left)
    else
        self.margin_.top = top.top
        self.margin_.right = top.right
        self.margin_.bottom = top.bottom
        self.margin_.left = top.left
    end
    return self
end

function BasicLayoutProtocol:exportMethods()
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
        "getLayoutAlignment",
        "setLayoutAlignment",
        "getLayoutPadding",
        "setLayoutPadding",
        "getLayoutMargin",
        "setLayoutMargin",
    })
end

function BasicLayoutProtocol:onBind_()
    self.preferredSize_ = nil
    self.layoutSize_ = {width = 0, height = 0}
    self.minSize_    = {width = 0, height = 0}
    self.maxSize_    = {width = MAX, height = MAX}
    self.sizePolicy_ = {h = display.PREFERRED_SIZE, v = display.PREFERRED_SIZE}
    self.alignment_  = display.LEFT_BOTTOM
    self.padding_    = {top = 0, right = 0, bottom = 0, left = 0}
    self.margin_     = {top = 0, right = 0, bottom = 0, left = 0}
end

function BasicLayoutProtocol:onUnbind_()
end

return BasicLayoutProtocol
