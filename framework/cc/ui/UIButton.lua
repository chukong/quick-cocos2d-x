
local UIButton = class("UIButton", function(images, options)
    if options and options.scale9 then
        return display.newNode()
    else
        return display.newSprite()
    end
end)

UIButton.CLICKED_EVENT = "CLICKED_EVENT"
UIButton.PRESSED_EVENT = "PRESSED_EVENT"
UIButton.RELEASE_EVENT = "RELEASE_EVENT"
UIButton.STATE_CHANGED_EVENT = "STATE_CHANGED_EVENT"

UIButton.IMAGE_ZORDER = -100
UIButton.LABEL_ZORDER = 0

function UIButton:ctor(events, initialState, options)
    self.fsm_ = {}
    cc.GameObject.extend(self.fsm_)
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
    self:setLayoutAlignment(display.CENTER)
    self:setButtonEnabled(true)
    self:addTouchEventListener(handler(self, self.onTouch_))
    self:setNodeEventEnabled(true)
    self.images_ = {}
    self.scale9_ = options and options.scale9
    self.scale9Sprite_ = nil
    self.scale9Size_ = nil
    self.labels_ = {}
    self.labelOffset_ = {0, 0}
    self.labelAlign_ = display.CENTER
    self.initialState_ = initialState
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

function UIButton:setButtonLabelOffset(ox, oy)
    self.labelOffset_ = {ox, oy}
    self:updateButtonLable_()
    return self
end

function UIButton:setButtonLabelAlign(align)
    self.labelAlign_ = align
    self:updateButtonLable_()
    return self
end

function UIButton:setButtonSize(width, height)
    assert(self.scale9_, "UIButton:setButtonSize() - can't change size for non-scale9 button")
    self.scale9Size_ = {width, height}
    if self.scale9Sprite_ then
        self.scale9Sprite_:setContentSize(CCSize(self.scale9Size_[1], self.scale9Size_[2]))
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

function UIButton:addButtonClickedEventListener(callback, isWeakReference)
    return self:addEventListener(UIButton.CLICKED_EVENT, callback, isWeakReference)
end

function UIButton:onButtonClicked(callback, isWeakReference)
    self:addButtonClickedEventListener(callback, isWeakReference)
    return self
end

function UIButton:addButtonPressedEventListener(callback, isWeakReference)
    return self:addEventListener(UIButton.PRESSED_EVENT, callback, isWeakReference)
end

function UIButton:onButtonPressed(callback, isWeakReference)
    self:addButtonPressedEventListener(callback, isWeakReference)
    return self
end

function UIButton:addButtonReleaseEventListener(callback, isWeakReference)
    return self:addEventListener(UIButton.RELEASE_EVENT, callback, isWeakReference)
end

function UIButton:onButtonRelease(callback, isWeakReference)
    self:addButtonReleaseEventListener(callback, isWeakReference)
    return self
end

function UIButton:addButtonStateChangedEventListener(callback, isWeakReference)
    return self:addEventListener(UIButton.STATE_CHANGED_EVENT, callback, isWeakReference)
end

function UIButton:onButtonStateChanged(callback, isWeakReference)
    self:addButtonStateChangedEventListener(callback, isWeakReference)
    return self
end

function UIButton:onChangeState_(event)
    if self:isRunning() then
        self:updateButtonImage_()
        self:updateButtonLable_()
    end
end

function UIButton:onTouch_(event, x, y)
    echoError("UIButton:onTouch_() - must override in inherited class")
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
        if self.scale9_ then
            if self.scale9Sprite_ then
                self.scale9Sprite_:removeFromParentAndCleanup(true)
                self.scale9Sprite_ = nil
            end

            self.scale9Sprite_ = CCScale9Sprite:create(image)
            if not self.scale9Size_ then
                local size = self.scale9Sprite_:getContentSize()
                self.scale9Size_ = {size.width, size.height}
            else
                self.scale9Sprite_:setContentSize(CCSize(self.scale9Size_[1], self.scale9Size_[2]))
            end
            self:addChild(self.scale9Sprite_, UIButton.IMAGE_ZORDER)
        else
            self:setDisplayFrame(display.newSprite(image):getDisplayFrame())
        end
    else
        echoError("UIButton:updateButtonImage_() - not set image for state %s", state)
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

    if not self.scale9_ then
        local contentSize = self:getContentSize()
        ox = ox + contentSize.width / 2
        oy = oy + contentSize.height / 2
    end

    for _, l in pairs(self.labels_) do
        l:setVisible(l == label)
        display.align(l, self.labelAlign_, ox, oy)
    end
end

function UIButton:getDefaultState_()
    return {self.initialState_}
end

function UIButton:onEnter()
    self:updateButtonImage_()
end

return UIButton
