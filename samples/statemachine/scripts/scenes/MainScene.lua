
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    -- create Finite State Machine
    self.fsm_ = {}
    cc.GameObject.extend(self.fsm_)
        :addComponent("components.behavior.StateMachine")
        :exportMethods()

    self.fsm_:setupState({
        events = {
            {name = "start", from = "none",   to = "green" },
            {name = "warn",  from = "green",  to = "yellow"},
            {name = "panic", from = "green",  to = "red"   },
            {name = "panic", from = "yellow", to = "red"   },
            {name = "calm",  from = "red",    to = "yellow"},
            {name = "clear", from = "red",    to = "green" },
            {name = "clear", from = "yellow", to = "green" },
        },

        callbacks = {
            onbeforestart = function(event) self:log("[FSM] STARTING UP") end,
            onstart       = function(event) self:log("[FSM] READY") end,
            onbeforewarn  = function(event) self:log("[FSM] START   EVENT: warn!", true) end,
            onbeforepanic = function(event) self:log("[FSM] START   EVENT: panic!", true) end,
            onbeforecalm  = function(event) self:log("[FSM] START   EVENT: calm!",  true) end,
            onbeforeclear = function(event) self:log("[FSM] START   EVENT: clear!", true) end,
            onwarn        = function(event) self:log("[FSM] FINISH  EVENT: warn!") end,
            onpanic       = function(event) self:log("[FSM] FINISH  EVENT: panic!") end,
            oncalm        = function(event) self:log("[FSM] FINISH  EVENT: calm!") end,
            onclear       = function(event) self:log("[FSM] FINISH  EVENT: clear!") end,
            onleavegreen  = function(event) self:log("[FSM] LEAVE   STATE: green") end,
            onleaveyellow = function(event) self:log("[FSM] LEAVE   STATE: yellow") end,
            onleavered    = function(event)
                self:log("[FSM] LEAVE   STATE: red")
                self:pending(event, 3)
                self:performWithDelay(function()
                    self:pending(event, 2)
                    self:performWithDelay(function()
                        self:pending(event, 1)
                        self:performWithDelay(function()
                            self.pendingLabel_:setString("")
                            event.transition()
                        end, 1)
                    end, 1)
                end, 1)
                return "async"
            end,
            ongreen       = function(event) self:log("[FSM] ENTER   STATE: green") end,
            onyellow      = function(event) self:log("[FSM] ENTER   STATE: yellow") end,
            onred         = function(event) self:log("[FSM] ENTER   STATE: red") end,
            onchangestate = function(event) self:log("[FSM] CHANGED STATE: " .. event.from .. " to " .. event.to) end,
        },
    })

    -- create UI
    display.newColorLayer(ccc4(255, 255, 255, 255))
        :addTo(self)

    ui.newTTFLabel({
        text = "Finite State Machine",
        size = 32,
        align = ui.TEXT_ALIGN_CENTER,
        color = display.COLOR_BLACK,
        x = display.cx,
        y = display.top - 60,
    }):addTo(self)

    self.pendingLabel_ = ui.newTTFLabel({
        text = "",
        size = 32,
        align = ui.TEXT_ALIGN_CENTER,
        color = display.COLOR_BLACK,
        x = display.cx,
        y = display.top - 620,
    }):addTo(self)

    -- preload texture
    self.stateImage_ = display.newSprite("#GreenState.png")
        :pos(display.cx, display.top - 300)
        :scale(1.5)
        :addTo(self)

    self.clearButton_ = ui.newTTFLabelMenuItem({
        text = "clear",
        color = display.COLOR_BLACK,
        size = 32,
        x = display.cx - 150,
        y = display.top - 540,
        listener = function()
            self.fsm_:doEvent("clear")
        end
    })
    self.calmButton_ = ui.newTTFLabelMenuItem({
        text = "calm",
        color = display.COLOR_BLACK,
        size = 32,
        x = display.cx - 50,
        y = display.top - 540,
        listener = function()
            self.fsm_:doEvent("calm")
        end
    })
    self.warnButton_ = ui.newTTFLabelMenuItem({
        text = "warn",
        color = display.COLOR_BLACK,
        size = 32,
        x = display.cx + 50,
        y = display.top - 540,
        listener = function()
            self.fsm_:doEvent("warn")
        end
    })
    self.panicButton_ = ui.newTTFLabelMenuItem({
        text = "panic!",
        color = display.COLOR_BLACK,
        size = 32,
        x = display.cx + 150,
        y = display.top - 540,
        listener = function()
            self.fsm_:doEvent("panic")
        end
    })
    ui.newMenu({self.clearButton_, self.calmButton_, self.warnButton_, self.panicButton_})
        :addTo(self)

    -- debug
    self.logCount_ = 0
end

function MainScene:pending(event, n)
    local msg = event.to .. " in ..." .. n
    self:log("[FSM] PENDING STATE: " .. msg)
    self.pendingLabel_:setString(msg)
end

function MainScene:log(msg, separate)
    if separate then self.logCount_ = self.logCount_ + 1 end
    if separate then print("") end
    printf("%d: %s", self.logCount_, msg)

    local state = self.fsm_:getState()
    if state == "green" then
        self.stateImage_:setDisplayFrame(display.newSpriteFrame("GreenState.png"))
    elseif state == "red" then
        self.stateImage_:setDisplayFrame(display.newSpriteFrame("RedState.png"))
    elseif state == "yellow" then
        self.stateImage_:setDisplayFrame(display.newSpriteFrame("YellowState.png"))
    end

    self.clearButton_:setEnabled(self.fsm_:canDoEvent("clear"))
    self.calmButton_:setEnabled(self.fsm_:canDoEvent("calm"))
    self.warnButton_:setEnabled(self.fsm_:canDoEvent("warn"))
    self.panicButton_:setEnabled(self.fsm_:canDoEvent("panic"))
end

function MainScene:onEnter()
    self.fsm_:doEvent("start")
end

return MainScene
