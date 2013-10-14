
local Component = import("..Component")
local BasicLayoutProtocol = class("BasicLayoutProtocol", Component)

local MAX = 999999

function BasicLayoutProtocol:ctor()
    BasicLayoutProtocol.super.ctor(self, "BasicLayoutProtocol")
end

function BasicLayoutProtocol:getLayoutSize()
    if self.layoutSize_ then
        return self.layoutSize_.width, self.layoutSize_.height
    else
        if self.target_.getCascadeBoundingBox then
            local size = self.target_:getCascadeBoundingBox().size
            return size.width, size.height
        else
            return 0, 0
        end
    end
end

function BasicLayoutProtocol:setLayoutSize(width, height)
    if width == 0 and height == 0 then
        self.layoutSize_ = nil
    else
        self.layoutSize_ = {width = tonumber(width), height = tonumber(height)}
    end
    return self
end

function BasicLayoutProtocol:getLayoutMinSize()
    return self.minSize_.width, self.minSize_.height
end

function BasicLayoutProtocol:setLayoutMinSize(width, height)
    self.minSize_.width = tonumber(width)
    self.minSize_.height = tonumber(height)
    return self
end

function BasicLayoutProtocol:getLayoutMaxSize()
    return self.maxSize_.width, self.maxSize_.height
end

function BasicLayoutProtocol:setLayoutMaxSize(width, height)
    self.maxSize_.width = tonumber(width)
    self.maxSize_.height = tonumber(height)
    return self
end

function BasicLayoutProtocol:getLayoutSizePolicy()
    return self.sizePolicy_.horizontal, self.sizePolicy_.vertical
end

local function checkSizePolicy(p)
    if p ~= display.AUTO_SIZE and p ~= display.FIXED_SIZE then
        echoError("BasicLayoutProtocol - invalid size policy")
        return display.AUTO_SIZE
    else
        return p
    end
end

function BasicLayoutProtocol:setLayoutSizePolicy(horizontal, vertical)
    self.sizePolicy_.horizontal = checkSizePolicy(horizontal)
    self.sizePolicy_.vertical = checkSizePolicy(vertical)
    return self
end

function BasicLayoutProtocol:getLayoutPadding()
    return self.padding_.top, self.padding_.right, self.padding_.bottom, self.padding_.left
end

function BasicLayoutProtocol:setLayoutPadding(top, right, bottom, left)
    self.padding_.top = tonumber(top)
    self.padding_.right = tonumber(right)
    self.padding_.bottom = tonumber(bottom)
    self.padding_.left = tonumber(left)
    return self
end

function BasicLayoutProtocol:getLayoutMargin()
    return self.margin_.top, self.margin_.right, self.margin_.bottom, self.margin_.left
end

function BasicLayoutProtocol:setLayoutMargin(top, right, bottom, left)
    self.margin_.top = tonumber(top)
    self.margin_.right = tonumber(right)
    self.margin_.bottom = tonumber(bottom)
    self.margin_.left = tonumber(left)
    return self
end

function BasicLayoutProtocol:exportMethods()
    self:exportMethods_({
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
    })
    return self
end

function BasicLayoutProtocol:onBind_()
    self.layoutSize_ = nil
    self.minSize_    = {width = 0, height = 0}
    self.maxSize_    = {width = MAX, height = MAX}
    self.sizePolicy_ = {h = display.PREFERRED_SIZE, v = display.PREFERRED_SIZE}
    self.padding_    = {top = 0, right = 0, bottom = 0, left = 0}
    self.margin_     = {top = 0, right = 0, bottom = 0, left = 0}
end

function BasicLayoutProtocol:onUnbind_()
end

return BasicLayoutProtocol
