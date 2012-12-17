
local network = {}

function network.isLocalWiFiAvailable()
    return CCNetwork:isLocalWiFiAvailable()
end

function network.isInternetConnectionAvailable()
    return CCNetwork:isInternetConnectionAvailable()
end

function network.isHostNameReachable(hostname)
    if type(hostname) ~= "string" then
        echoError("[network] ERR, isHostNameReachable() invalid hostname")
        return false
    end
    return CCNetwork:isHostNameReachable(hostname)
end

function network.getInternetConnectionStatus()
    return CCNetwork:getInternetConnectionStatus()
end

function network.sendHttpRequest(url, method, callback)
    echoNotice("HTTP REQUEST: [%s] %s", os.date("%Y-%m-%d %H:%I:%S"), url)

    method = string.upper(method)
    if method == "GET" then
        method = CCHttpRequestMethodGET
    else
        method = CCHttpRequestMethodPOST
    end

    return CCHttpRequest:createWithUrlLua(callback, url, method)
end

return network
