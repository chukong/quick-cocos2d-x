
local UIPanel = class("UIPanel", function(options)
	if options.clipAble then
		return cc.ClippingNode:create()
	else
		return display.newNode()
	end
end)

function UIPanel:ctor(options)
	self.subControl = {}
end

function UIPanel:setSize(width, height)
    self:setContentSize(width, height)
    for _, sub in ipairs(self.subControl) do
    	sub:setContentSize(width, height)
    end
end

function UIPanel:addSubControl(sub)
	self.subControl[#self.subControl + 1] = sub
end

return UIPanel
