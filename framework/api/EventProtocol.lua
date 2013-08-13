
--[[--

Events are the principal way in which you create interactive applications. They are a way of
triggering responses in your program. For example, you can turn any display object into an
interactive object.

]]
local EventProtocol = {}

--[[--

Turn any object into an interactive object.

**Usage:**

    framework.api.EventProtocol.extend(object)

]]
function EventProtocol.extend(object)
    object.listeners = {}

    --[[--

    Adds a listener to the object’s list of listeners, and return handle of listener. When the named event occurs, the listener will be invoked and be supplied with a table representing the event.

    **Usage:**

        -- Create an object that listens to events
        local player = Player.new()
        framework.api.EventProtocol.extend(player)

        -- Setup listener
        local handle
        local function onPlayerDead(event)
            -- event.name   == "PLAYER_DEAD"
            -- event.object == player
            player:removeEventListener("PLAYER_DEAD", handle)
        end
        handle = player:addEventListener("PLAYER_DEAD", onPlayerDead)

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
        end
        local handle = "_LISTENER_HANDLE_" .. tostring(listener)
        object.listeners[eventName][handle] = listener
        return handle
    end

    --[[--

    Dispatches event to object. The event parameter must be a table with a name property which is a string identifying the type of event. Event include a object property to the event so that your listener can know which object
    received the event.

    **Syntax:**

        object:dispatchEvent(event)

    <br />

    @param event
    contains event properties

    ]]
    function object:dispatchEvent(event)
        event.name = string.upper(event.name)
        local eventName = event.name
        if object.listeners[eventName] == nil then return end

        event.target = object
        for _, listener in pairs(object.listeners[eventName]) do
            if listener(event) == false then break end
        end
    end

    --[[--

    Removes the specified listener (or by handle) from the object's list of listeners so that it no longer is notified of events corresponding to the specified event.

    **Syntax:**

        -- key is listener function or handle return by addEventListener()
        object:removeEventListener(eventName, key)

    ]]
    function object:removeEventListener(eventName, key)
        eventName = string.upper(eventName)
        if object.listeners[eventName] == nil then return end

        for handle, listener in pairs(object.listeners[eventName]) do
            if key == listener or key == handle then
                object.listeners[eventName][handle] = nil
                break
            end
        end
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
