
local PunchBox_Android = class("PunchBox_Android")

local SDK_CLASS_NAME = "com.quick2dx.sdk.PunchBoxSDK"

function PunchBox_Android:start(interface, options)
    self.interface_ = interface
    self.options_ = options

    local ok, ret = luaj.callStaticMethod(SDK_CLASS_NAME, "start")
    if not ok then
        echoError("PunchBox_Android:ctor() - init SDK failed.")
        return
    end

    -- local function callback(event)
    --     event = json.decode(event)
    --     echoInfo("## PunchBox_Android CALLBACK, event %s", tostring(event.name))
    --     self.interface_:dispatchEvent({name = interface.RECEIVED_EVENT})
    -- end
    -- luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {callback})
end

function PunchBox_Android:show(command, options)
    if type(options) ~= "table" then options = {} end
    local id = options.id or ""
    local position = options.position or "default"
    luaj.callStaticMethod(SDK_CLASS_NAME, "show", {command, id, position})
end

function PunchBox_Android:remove(command)
    luaj.callStaticMethod(SDK_CLASS_NAME, "remove")
end

return PunchBox_Android
