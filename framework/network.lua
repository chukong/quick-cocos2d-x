
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

function network.createHTTPRequest(callback, url, method)
    if not method then method = "GET" end
    if string.upper(tostring(method)) == "GET" then
        method = kCCHTTPRequestMethodGET
    else
        method = kCCHTTPRequestMethodPOST
    end
    return CCHTTPRequest:createWithUrl(callback, url, method)
end

function network.uploadFile(callback, url, datas)
	assert(datas or datas.fileFieldName or datas.filePath, "Need file datas!")
	local request = network.createHTTPRequest(callback, url, "POST")
	local fileFieldName = datas.fileFiledName
	local filePath = datas.filePath
	local contentType = datas.contentType
	-- request:setUploadFile(file)
	-- ="application/octet-stream"
	if contentType then
		request:addFormFile(fileFieldName, filePath, contentType)
	else
		request:addFormFile(fileFieldName, filePath)
	end
	if datas.extra then
		for i in ipairs(datas.extra) do
			local data = datas.extra[i]
			request:addFormContents(data[1], data[2])
		end
	end
	request:start()
	return request
end

local function parseTrueFalse(t)
    t = string.lower(tostring(t))
    if t == "yes" or t == "true" then return true end
    return false
end

function network.makeCookieString(cookie)
    local arr = {}
    for name, value in pairs(cookie) do
        if type(value) == "table" then
            value = tostring(value.value)
        else
            value = tostring(value)
        end

        arr[#arr + 1] = tostring(name) .. "=" .. string.urlencode(value)
    end

    return table.concat(arr, "; ")
end

function network.parseCookie(cookieString)
    local cookie = {}
    local arr = string.split(cookieString, "\n")
    for _, item in ipairs(arr) do
        item = string.trim(item)
        if item ~= "" then
            local parts = string.split(item, "\t")
            -- ".amazon.com" represents the domain name of the Web server that created the cookie and will be able to read the cookie in the future
            -- TRUE indicates that all machines within the given domain can access the cookie
            -- "/" denotes the path within the domain for which the variable is valid
            -- "FALSE" indicates that the connection is not secure
            -- "2082787601" represents the expiration date in UNIX time (number of seconds since January 1, 1970 00:00:00 GMT)
            -- "ubid-main" is the name of the cookie
            -- "002-2904428-3375661" is the value of the cookie

            local c = {
                domain = parts[1],
                access = parseTrueFalse(parts[2]),
                path = parts[3],
                secure = parseTrueFalse(parts[4]),
                expire = toint(parts[5]),
                name = parts[6],
                value = string.urldecode(parts[7]),
            }

            cookie[c.name] = c
        end
    end

    return cookie
end

return network
