
local function ctor(self, app)
    self.app = app
end
local ServerAction = class("ServerAction", ctor)

return ServerAction
