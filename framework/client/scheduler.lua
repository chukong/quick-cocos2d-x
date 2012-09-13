
local M = {}

local scheduler = CCDirector:sharedDirector():getScheduler()
local stack = {}

local function push(handle)
    stack[#stack + 1] = handle
    return handle
end

function M.enterFrame(listener, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return push(scheduler:scheduleScriptFunc(listener, 0, isPaused))
end

function M.schedule(listener, interval, isPaused)
    if type(isPaused) ~= "boolean" then isPaused = false end
    return push(scheduler:scheduleScriptFunc(listener, interval, isPaused))
end

function M.unschedule(handle)
    scheduler:unscheduleScriptEntry(handle)
    for i = 1, #stack do
        if stack[i] == handle then
            table.remove(stack, i)
            return
        end
    end
end
M.remove = M.unschedule

function M.unscheduleAll()
    for i = 1, #stack do
        scheduler:unscheduleScriptEntry(stack[i])
    end
    stack = {}
end
M.removeAll = M.unscheduleAll

function M.performWithDelay(time, listener)
    local handle
    handle = scheduler:scheduleScriptFunc(function()
        M.unschedule(handle)
        listener()
    end, time, false)
    return push(handle)
end

return M
