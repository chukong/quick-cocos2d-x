
local NetworkTestScene = game.createSceneClass("NetworkTestScene")

function NetworkTestScene:ctor()
    self.requestCount = 0

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "createHTTPRequest",
        "createHTTPRequestBadDomain",
        "send data to server",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function NetworkTestScene:onResponse(event, index, dumpResponse)
    local request = event.request
    printf("REQUEST %d - event.name = %s", index, event.name)
    if event.name == "completed" then
        printf("REQUEST %d - getResponseStatusCode() = %d", index, request:getResponseStatusCode())
        printf("REQUEST %d - getResponseHeadersString() =\n%s", index, request:getResponseHeadersString())

        if request:getResponseStatusCode() ~= 200 then
        else
            printf("REQUEST %d - getResponseDataLength() = %d", index, request:getResponseDataLength())
            if dumpResponse then
                printf("REQUEST %d - getResponseString() =\n%s", index, request:getResponseString())
            end
        end
    else
        printf("REQUEST %d - getErrorCode() = %d, getErrorMessage() = %s", index, request:getErrorCode(), request:getErrorMessage())
    end

    print("----------------------------------------")
end

function NetworkTestScene:createHTTPRequestTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        self:onResponse(event, index)
    end, "http://quick-x.com/feed/", "GET")
    printf("REQUEST START %d", index)
    request:start()
end

function NetworkTestScene:createHTTPRequestBadDomainTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        self:onResponse(event, index)
    end, "http://quick-x.com.x.y.z.not/", "GET")
    printf("REQUEST START %d", index)
    request:start()
end



function NetworkTestScene:send_data_to_serverTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        self:onResponse(event, index, true)
        local cookie = network.parseCookie(event.request:getCookieString())
        dump(cookie, "GET COOKIE FROM SERVER")
    end, "http://quick-x.com/tests/http_request_tests.php", "POST")
    request:addPOSTValue("username", "dualface")
    request:setCookieString(network.makeCookieString({C1 = "V1", C2 = "V2"}))
    printf("REQUEST START %d", index)
    request:start()
end

return NetworkTestScene
