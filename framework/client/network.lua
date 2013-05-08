
local network = {}

function network.isLocalWiFiAvailable()
    return CCNetwork:isLocalWiFiAvailable()
end

function network.isInternetConnectionAvailable()
    return CCNetwork:isInternetConnectionAvailable()
end

function network.isHostNameReachable(hostname)
    if type(hostname) ~= "string" then
        echoError("network.isHostNameReachable() - invalid hostname %s", tostring(hostname))
        return false
    end
    return CCNetwork:isHostNameReachable(hostname)
end

function network.getInternetConnectionStatus()
    return CCNetwork:getInternetConnectionStatus()
end

--[[--

~~~ lua

function callback(event)
    local ok = (event.name == "completed")
    local request = event.request

    if not ok then
        -- request failure
        print(request:getErrorCode(), request:getErrorMessage())
        return
    end

    local code = request:getResponseStatusCode()
    if code ~= 200 then
        -- code is HTTP response code
        print(code)
        return
    end

    local response = request:getResponseString()
    print(response)
end

local request = network.createHTTPRequest(callback, url, "POST")
request:addPOSTValue("KEY", "VALUE")
request:start()

~~~

]]
function network.createHTTPRequest(callback, url, method)
    if not method then method = "GET" end
    if string.upper(tostring(method)) == "GET" then
        method = kCCHTTPRequestMethodGET
    else
        method = kCCHTTPRequestMethodPOST
    end
    return CCHTTPRequest:createWithUrlLua(callback, url, method)
end

return network
