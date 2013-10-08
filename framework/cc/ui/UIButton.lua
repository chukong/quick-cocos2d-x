
local UIButton = class("UIButton", function()
    return display.newSprite()
end)

UIButton.CHECKED          = "CHECKED"
UIButton.CHECKED_PRESSED  = "CHECKED_PRESSED"
UIButton.CHECKED_DISABLED = "CHECKED_DISABLED"

function UIButton:ctor(events, initialState)
    self.fsm_ = {}
    cc.GameObject.extend(self.fsm_):addComponent("components.behavior.StateMachine"):exportMethods()
    self.fsm_:setupState({
        initial = {state = initialState, event = "startup", defer = false},
        events = events,
        callbacks = {
            onchangestate = handler(self, self.onChangeState_),
        }
    })

    cc.GameObject.extend(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)
    self:setLayoutAlignment(display.CENTER)
    self:setButtonEnabled(true)
    self.images_ = {}

    self:addTouchEventListener(handler(self, self.onTouch_))
    self:setNodeEventEnabled(true)
end

function UIButton:setButtonImage(state, image, ignoreEmpty)
    if ignoreEmpty and image == nil then return end
    self.images_[state] = image
    if state == self.fsm_:getState() then
        self:updateButtonImage_()
    end
    return self
end

function UIButton:setButtonEnabled(enabled)
    self:setTouchEnabled(enabled)
    if enabled and self.fsm_:canDoEvent("enable") then
        self.fsm_:doEventForce("enable")
    elseif not enabled and self.fsm_:canDoEvent("disable") then
        self.fsm_:doEventForce("disable")
    end
    return self
end

function UIButton:isButtonEnabled()
    return self.fsm_:canDoEvent("disable")
end

function UIButton:onChangeState_(event)
    if self:isRunning() then self:updateButtonImage_() end
end

function UIButton:onTouch_(event, x, y)
    echoError("UIButton:onTouch_() - must override in inherited class")
end

function UIButton:updateButtonImage_()
    local state = self.fsm_:getState()
    local image = self.images_[state]

    if image then
        self:setDisplayFrame(CCSprite:create(image):getDisplayFrame())
    else
        echoError("UIButton:updateButtonImage_() - not set image for state %s", state)
    end
end

function UIButton:callHandler_(name, ...)
    local handler = self[name]
    if handler then
        local ret = handler(...)
        if ret == cc.REMOVE_HANDLER_SIGN then
            self[name] = nil
        end
    end
end

function UIButton:onEnter()
    self:updateButtonImage_()
end

return UIButton
