
local config = {
    SCROLL_TO_VALID_RANGE_SPEED = 400
}

local PageControl = class("PageControl", function()
    return display.newNode()
end)

PageControl.config = config

function PageControl:ctor(size, delegate)
    self.size          = size
    self.delegate      = delegate
    self.pages         = {}
    self.selectedIndex = 0
end

function PageControl:addPage(page)
    self.pages[#self.pages + 1] = page
    self:addChild(page)
    page:setVisible(false)
end

function PageControl:getNumPages()
    return #self.pages
end

function PageControl:setSelectedIndex(index)
    assert(index > 0 and index < self:getNumPages(),
           format("PageControl:setSelectedIndex() - invalid index %s", _s(index)))

    if self.selectedIndex > 0 then
        local page = self.pages[self.selectedIndex]
        page:setVisible(false)
        page:onHide()
    end

    local page = self.pages[index]
    page:setVisible(true)
    page:onShow()

    self.selectedIndex = index
    self:updatePagesPosition()
end

function PageControl:scrollToPage(index)

end

function PageControl:updatePagesPosition()
    assert(index > 0 and index < self:getNumPages(),
           format("PageControl:updatePagesPosition() - invalid index %s", _s(index)))

    for i = 1, self:getNumPages() do
        local page = self.pages[i]
        local x = (i - self.selectedIndex) * self.size.width
        page:setPosition(x, 0)
    end
end

return PageControl
