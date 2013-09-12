
local UILayout = class("UILayout")

function UILayout:ctor()
    self.order_ = 0
    self.widgets_ = {}
    self.layouts_ = {}
    local m = {__mode = "k"}
    setmetatable(self.widgets_, m)
    setmetatable(self.layouts_, m)
end

function UILayout:addWidget(widget, weight)
    self.order_ = self.order_ + 1
    self.widgets_[widget] = {weight = weight or 1, order = self.order_}
    return self
end

function UILayout:removeWidget(widget)
    self.widgets_[widget] = nil
    return self
end

function UILayout:addLayout(layout)
end

function UILayout:removeLayout(layout)
end

function UILayout:apply(container)
end

return UILayout
