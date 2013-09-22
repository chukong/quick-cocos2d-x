
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

function BasicLayoutProtocol:getLayoutAlignment()
    return self.alignment_
end

local function checkAlignment(a)
    a = toint(a)
    if a < 1 or a > 9 then
        echoError("BasicLayoutProtocol - invalid alignment")
        return display.CENTER
    else
        return a
    end
end

function BasicLayoutProtocol:setLayoutAlignment(alignment)
    self.alignment_ = checkAlignment(alignment)
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

-- function BasicLayoutProtocol:getLayoutScale()
--     if self.scale_ then
--         return self.scale_.horizontal, self.scale_.vertical
--     elseif self.target_.getScaleX then
--         return self.target_:getScaleX(), self.target_:getScaleY()
--     else
--         return 1, 1
--     end
-- end

-- function BasicLayoutProtocol:setLayoutScale(horizontal, vertical)
--     horizontal_v = tonumber(horizontal)
--     vertical_v = tonumber(vertical)
--     if horizontal_v == 0 and vertical_v == 0 then
--         self.scale_ = nil
--     else
--         if not vertical then vertical_v = horizontal_v end
--         self.scale_ = {horizontal = horizontal_v, vertical = vertical_v}
--         if self.target_.setScaleX then
--             self.target_:setScaleX(horizontal_v)
--             self.target_:setScaleY(vertical_v)
--         end
--     end
--     return self
-- end

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
        "getLayoutAlignment",
        "setLayoutAlignment",
        "getLayoutPadding",
        "setLayoutPadding",
        "getLayoutMargin",
        "setLayoutMargin",
        -- "getLayoutScale",
        -- "setLayoutScale",
    })
end

function BasicLayoutProtocol:onBind_()
    self.layoutSize_ = nil
    self.minSize_    = {width = 0, height = 0}
    self.maxSize_    = {width = MAX, height = MAX}
    self.sizePolicy_ = {h = display.PREFERRED_SIZE, v = display.PREFERRED_SIZE}
    self.alignment_  = display.LEFT_BOTTOM
    self.padding_    = {top = 0, right = 0, bottom = 0, left = 0}
    self.margin_     = {top = 0, right = 0, bottom = 0, left = 0}
    self.scale_      = nil
end

function BasicLayoutProtocol:onUnbind_()
end

return BasicLayoutProtocol
