
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local label1 = ui.newTTFLabelMenuItem({
        text  = "get https://github.com/opensearch.xml source code",
        size  = 32,
        x     = display.left + 20,
        y     = display.top - 40,
        listener = function() self:getSources() end
    })
    label1:align(display.LEFT_CENTER)

    local menu = ui.newMenu({label1})
    self:addChild(menu)
end

function MainScene:getSources()
    function callback(event)
        local ok = (event.name == "completed")
        print("request event.name = " .. event.name)
        local request = event.request

        if not ok then
            -- request failure
            print(request:getErrorCode(), request:getErrorMessage())
            print("---- get source end ----\n")
            return
        end

        local code = request:getResponseStatusCode()
        if code ~= 200 then
            -- code is HTTP response code
            print(code)
            print("---- get source end ----\n")
            return
        end

        local response = request:getResponseString()
        print(response)
        print("---- get source end ----\n")
    end

    print("---- get source begin ----")
    local request = network.createHTTPRequest(callback, "https://github.com/opensearch.xml")
    request:start()
end

function MainScene:onEnter()
    if device.platform ~= "android" then return end

    -- avoid unmeant back
    self:performWithDelay(function()
        -- keypad layer, for android
        local layer = display.newLayer()
        layer:addKeypadEventListener(function(event)
            if event == "back" then game.exit() end
        end)
        self:addChild(layer)

        layer:setKeypadEnabled(true)
    end, 0.5)
end

return MainScene
