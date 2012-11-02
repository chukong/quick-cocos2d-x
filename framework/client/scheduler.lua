
local scheduler = {}

local sharedScheduler = CCDirector:sharedDirector():getScheduler()
local stack = {}

local function push(handle)
    stack[#stack + 1] = handle
    return handle
end

function scheduler.enterFrame(listener, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return push(sharedScheduler:scheduleScriptFunc(listener, 0, isPaused))
end

function scheduler.schedule(listener, interval, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return push(sharedScheduler:scheduleScriptFunc(listener, interval, isPaused))
end

function scheduler.unschedule(handle)
    sharedScheduler:unscheduleScriptEntry(handle)
    for i = 1, #stack do
        if stack[i] == handle then
            table.remove(stack, i)
            return
        end
    end
end
scheduler.remove = scheduler.unschedule

function scheduler.unscheduleAll()
    for i = 1, #stack do
        sharedScheduler:unscheduleScriptEntry(stack[i])
    end
    stack = {}
end
scheduler.removeAll = scheduler.unscheduleAll

function scheduler.performWithDelay(time, listener)
    local handle
    handle = sharedScheduler:scheduleScriptFunc(function()
        scheduler.unschedule(handle)
        listener()
    end, time, false)
    return push(handle)
end

return scheduler
