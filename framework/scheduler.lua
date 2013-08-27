
local scheduler = {}

local sharedScheduler = CCDirector:sharedDirector():getScheduler()

function scheduler.scheduleUpdateGlobal(listener)
    return sharedScheduler:scheduleScriptFunc(listener, 0, false)
end

function scheduler.scheduleGlobal(listener, interval)
    return sharedScheduler:scheduleScriptFunc(listener, interval, false)
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
