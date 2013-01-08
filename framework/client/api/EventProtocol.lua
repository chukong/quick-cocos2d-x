
--[[--

Events are the principal way in which you create interactive applications. They are a way of
triggering responses in your program. For example, you can turn any display object into an
interactive object.

]]
local EventProtocol = {}

--[[--

Turn any object into an interactive object.

**Usage:**

    framework.client.api.EventProtocol.extend(object)

]]
function EventProtocol.extend(object)
    object.listeners = {}

    --[[--

    Adds a listener to the object’s list of listeners. When the named event occurs, the listener will be invoked and be supplied with a table representing the event.

    **Usage:**

        -- Create an object that listens to events
        local player = Player.new()
        framework.client.api.EventProtocol.extend(player)

        -- Setup listener
        local function onPlayerDead(event)
            -- event.name   == "PLAYER_DEAD"
            -- event.object == player
        end
        player:addEventListener("PLAYER_DEAD", onPlayerDead)

        -- Sometime later, create an event and dispatch it
        player:dispatchEvent({name = "PLAYER_DEAD"})

    ~~

    @param eventName
    String specifying the name of the event to listen for.

    @tparam function listener
    If the event's event.name matches this string, listener will be invoked.

    @return Nothing.

    ]]
    function object:addEventListener(eventName, listener)
        eventName = string.upper(eventName)
        if object.listeners[eventName] == nil then
            object.listeners[eventName] = {}
            -- setmetatable(object.listeners[eventName], {__mode = "v"})
        end
        local t = object.listeners[eventName]
        t[#t + 1] = listener
    end

    --[[--

    Dispatches event to object. The event parameter must be a table with a name property which is a
    string identifying the type of event. Event include a object property to the event so that your listener can know which object
    received the event.

    **Syntax:**

        object:dispatchEvent(event)

    <br />

    @param event
    contains event properties

    ]]
    function object:dispatchEvent(event)
        event.name = string.upper(event.name)
        event.target = object
        local eventName = event.name
        if object.listeners[eventName] == nil then return end
        local t = object.listeners[eventName]
        for i = #t, 1, -1 do
            local ret
            local listener = t[i]
            if type(listener) == "table" then
                ret = listener[2](listener[1], event)
            else
                ret = listener(event)
            end
            if ret == false then break end
        end
    end

    --[[--

    Removes the specified listener from the object's list of listeners so that it no longer is
    notified of events corresponding to the specified event.

    **Syntax:**

        object:removeEventListener(eventName, listener)

    ]]
    function object:removeEventListener(eventName, listener)
        eventName = string.upper(eventName)
        if object.listeners[eventName] == nil then return end
        local t = object.listeners[eventName]
        for i = #t, 1, -1 do
            if t[i] == listener then
                table.remove(t, i)
                return
            end
        end
        if #t == 0 then object.listeners[eventName] = nil end
    end

    --[[--

    Removes all listeners for specified event from the object's list of listeners.

    **Syntax:**

        object:removeAllEventListenersForEvent(eventName)

    ]]
    function object:removeAllEventListenersForEvent(eventName)
        object.listeners[string.upper(eventName)] = nil
    end

    --[[--

    Removes all listeners from the object's list of listeners.

    **Syntax:**

        object:removeAllEventListeners()

    ]]
    function object:removeAllEventListeners()
        object.listeners = {}
    end

    return object
end

return EventProtocol
