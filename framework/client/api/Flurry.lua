
local Flurry = {}

Flurry.ready_ = LuaFlurry ~= nil

function Flurry.logEvent(eventName, parameters, timed)
    eventName = tostring(eventName)
    if type(parameters) ~= "table" then
        timed = parameters
        parameters = nil
    end
    if type(timed) ~= "boolean" then timed = false end

    if not Flurry.ready_ then
        echoWarning("Flurry.logEvent(%s, %s)", eventName, _s(timed))
        dump(parameters, "parameters")
    elseif parameters then
        LuaFlurry:logEventWithParameters(eventName, parameters, timed)
    else
        LuaFlurry:logEvent(eventName, timed)
    end
end

function Flurry.endTimedEvent(eventName)
    eventName = tostring(eventName)

    if not Flurry.ready_ then
        echoWarning("Flurry.endTimedEvent(%s)", eventName)
    else
        LuaFlurry:endTimedEvent(eventName)
    end
end

return Flurry
