
local UIButton = class("UIButton", function()
    return display.newNode()
end)

UIButton.CLICKED_EVENT = "CLICKED_EVENT"
UIButton.PRESSED_EVENT = "PRESSED_EVENT"
UIButton.RELEASE_EVENT = "RELEASE_EVENT"
UIButton.STATE_CHANGED_EVENT = "STATE_CHANGED_EVENT"

UIButton.IMAGE_ZORDER = -100
UIButton.LABEL_ZORDER = 0

function UIButton:ctor(events, initialState, options)
    self.fsm_ = {}
    cc(self.fsm_)
        :addComponent("components.behavior.StateMachine")
        :exportMethods()
    self.fsm_:setupState({
        initial = {state = initialState, event = "startup", defer = false},
        events = events,
        callbacks = {
            onchangestate = handler(self, self.onChangeState_),
        }
    })

    makeUIControl_(self)
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)
    self:setButtonEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, handler(self, self.onTouch_))

    self.touchInSpriteOnly_ = options and options.touchInSprite
    self.currentImage_ = nil
    self.images_ = {}
    self.sprite_ = {}
    self.scale9_ = options and options.scale9
    self.flipX_ = options and options.flipX
    self.flipY_ = options and options.flipY
    self.scale9Size_ = nil
    self.labels_ = {}
    self.labelOffset_ = {0, 0}
    self.labelAlign_ = display.CENTER
    self.initialState_ = initialState

    display.align(self, display.CENTER)

    if "boolean" ~= type(self.flipX_) then
        self.flipX_ = false
    end
    if "boolean" ~= type(self.flipY_) then
        self.flipY_ = false
    end

    self:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "enter" then
            self:updateButtonImage_()
        end
    end)
end

function UIButton:align(align, x, y)
    display.align(self, align, x, y)
    self:updateButtonImage_()
    self:updateButtonLable_()

    local size = self:getCascadeBoundingBox().size
    local ap = self:getAnchorPoint()

    -- self:setPosition(x + size.width * (ap.x - 0.5), y + size.height * (0.5 - ap.y))
    return self
end

function UIButton:setButtonImage(state, image, ignoreEmpty)
    if ignoreEmpty and image == nil then return end
    self.images_[state] = image
    if state == self.fsm_:getState() then
        self:updateButtonImage_()
    end
    return self
end

function UIButton:setButtonLabel(state, label)
    if not label then
        label = state
        state = self:getDefaultState_()
    end
    assert(label ~= nil, "UIButton:setButtonLabel() - invalid label")

    if type(state) == "table" then state = state[1] end
    local currentLabel = self.labels_[state]
    if currentLabel then currentLabel:removeSelf() end

    self.labels_[state] = label
    self:addChild(label, UIButton.LABEL_ZORDER)
    self:updateButtonLable_()
    return self
end

function UIButton:getButtonLabel(state)
    if not state then
        state = self:getDefaultState_()
    end
    if type(state) == "table" then state = state[1] end
    return self.labels_[state]
end

function UIButton:setButtonLabelString(state, text)
    assert(self.labels_ ~= nil, "UIButton:setButtonLabelString() - not add label")
    if text == nil then
        text = state
        for _, label in pairs(self.labels_) do
            label:setString(text)
        end
    else
        local label = self.labels_[state]
        if label then label:setString(text) end
    end
    return self
end

function UIButton:getButtonLabelOffset()
    return self.labelOffset_[1], self.labelOffset_[2]
end

function UIButton:setButtonLabelOffset(ox, oy)
    self.labelOffset_ = {ox, oy}
    self:updateButtonLable_()
    return self
end

function UIButton:getButtonLabelAlignment()
    return self.labelAlign_
end

function UIButton:setButtonLabelAlignment(align)
    self.labelAlign_ = align
    self:updateButtonLable_()
    return self
end

function UIButton:setButtonSize(width, height)
    assert(self.scale9_, "UIButton:setButtonSize() - can't change size for non-scale9 button")
    self.scale9Size_ = {width, height}
    for i,v in ipairs(self.sprite_) do
        v:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
    end
    return self
end

function UIButton:setButtonEnabled(enabled)
    self:setTouchEnabled(enabled)
    if enabled and self.fsm_:canDoEvent("enable") then
        self.fsm_:doEventForce("enable")
        self:dispatchEvent({name = UIButton.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    elseif not enabled and self.fsm_:canDoEvent("disable") then
        self.fsm_:doEventForce("disable")
        self:dispatchEvent({name = UIButton.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    end
    return self
end

function UIButton:isButtonEnabled()
    return self.fsm_:canDoEvent("disable")
end

function UIButton:addButtonClickedEventListener(callback)
    return self:addEventListener(UIButton.CLICKED_EVENT, callback)
end

function UIButton:onButtonClicked(callback)
    self:addButtonClickedEventListener(callback)
    return self
end

function UIButton:addButtonPressedEventListener(callback)
    return self:addEventListener(UIButton.PRESSED_EVENT, callback)
end

function UIButton:onButtonPressed(callback)
    self:addButtonPressedEventListener(callback)
    return self
end

function UIButton:addButtonReleaseEventListener(callback)
    return self:addEventListener(UIButton.RELEASE_EVENT, callback)
end

function UIButton:onButtonRelease(callback)
    self:addButtonReleaseEventListener(callback)
    return self
end

function UIButton:addButtonStateChangedEventListener(callback)
    return self:addEventListener(UIButton.STATE_CHANGED_EVENT, callback)
end

function UIButton:onButtonStateChanged(callback)
    self:addButtonStateChangedEventListener(callback)
    return self
end

function UIButton:onChangeState_(event)
    if self:isRunning() then
        self:updateButtonImage_()
        self:updateButtonLable_()
    end
end

function UIButton:onTouch_(event)
    printError("UIButton:onTouch_() - must override in inherited class")
end

function UIButton:updateButtonImage_()
    local state = self.fsm_:getState()
    local image = self.images_[state]

    if not image then
        for _, s in pairs(self:getDefaultState_()) do
            image = self.images_[s]
            if image then break end
        end
    end
    if image then
        if self.currentImage_ ~= image then
            for i,v in ipairs(self.sprite_) do
                v:removeFromParentAndCleanup(true)
            end
            self.sprite_ = {}
            self.currentImage_ = image

            if "table" == type(image) then
                for i,v in ipairs(image) do
                    if self.scale9_ then
                        self.sprite_[i] = display.newScale9Sprite(v)
                        if not self.scale9Size_ then
                            local size = self.sprite_[i]:getContentSize()
                            self.scale9Size_ = {size.width, size.height}
                        else
                            self.sprite_[i]:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
                        end
                    else
                        self.sprite_[i] = display.newSprite(v)
                    end
                    self:addChild(self.sprite_[i], UIButton.IMAGE_ZORDER)
                    if self.sprite_[i].setFlipX then
                        self.sprite_[i]:setFlipX(self.flipX_ or false)
                        self.sprite_[i]:setFlipY(self.flipY_ or false)
                    end
                end
            else
                if self.scale9_ then
                    self.sprite_[1] = display.newScale9Sprite(image)
                    if not self.scale9Size_ then
                        local size = self.sprite_[1]:getContentSize()
                        self.scale9Size_ = {size.width, size.height}
                    else
                        self.sprite_[1]:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
                    end
                else
                    self.sprite_[1] = display.newSprite(image)
                end
                if self.sprite_[1].setFlipX then
                    self.sprite_[1]:setFlipX(self.flipX_ or false)
                    self.sprite_[1]:setFlipY(self.flipY_ or false)
                end
                self:addChild(self.sprite_[1], UIButton.IMAGE_ZORDER)
            end
        end

        for i,v in ipairs(self.sprite_) do
            v:setAnchorPoint(self:getAnchorPoint())
            v:setPosition(0, 0)
        end
    elseif not self.labels_ then
        printError("UIButton:updateButtonImage_() - not set image for state %s", state)
    end
end

function UIButton:updateButtonLable_()
    if not self.labels_ then return end
    local state = self.fsm_:getState()
    local label = self.labels_[state]

    if not label then
        for _, s in pairs(self:getDefaultState_()) do
            label = self.labels_[s]
            if label then break end
        end
    end

    local ox, oy = self.labelOffset_[1], self.labelOffset_[2]
    if self.sprite_[1] then
        local ap = self:getAnchorPoint()
        local spriteSize = self.sprite_[1]:getContentSize()
        ox = ox + spriteSize.width * (0.5 - ap.x)
        oy = oy + spriteSize.height * (0.5 - ap.y)
    end

    for _, l in pairs(self.labels_) do
        l:setVisible(l == label)
        l:align(self.labelAlign_, ox, oy)
    end
end

function UIButton:getDefaultState_()
    return {self.initialState_}
end

function UIButton:checkTouchInSprite_(x, y)
    if self.touchInSpriteOnly_ then
        return self.sprite_[1] and self.sprite_[1]:getCascadeBoundingBox():containsPoint(cc.p(x, y))
    else
        return self:getCascadeBoundingBox():containsPoint(cc.p(x, y))
    end
end

return UIButton
