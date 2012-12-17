
local scheduler = {}

local sharedScheduler = CCDirector:sharedDirector():getScheduler()

function scheduler.scheduleUpdateGlobal(listener, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return sharedScheduler:scheduleScriptFunc(listener, 0, isPaused)
end

function scheduler.scheduleGlobal(listener, interval, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return sharedScheduler:scheduleScriptFunc(listener, interval, isPaused)
end

function scheduler.unscheduleGlobal(handle)
    sharedScheduler:unscheduleScriptEntry(handle)
end

function scheduler.performWithDelayGlobal(listener, time)
    local handle
    handle = sharedScheduler:scheduleScriptFunc(function()
        scheduler.unscheduleGlobal(handle)
        listener()
    end, time, false)
    return handle
end

return scheduler
