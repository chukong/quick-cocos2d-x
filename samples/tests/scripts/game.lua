
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")

    game.enterMainScene()
end

function game.createMenu(items, callback)
    local labels = {}
    for _, item in ipairs(items) do
        local label = ui.newTTFLabelMenuItem({
            text = item,
            listener = function() callback(item) end
        })
        labels[#labels + 1] = label
    end

    local menu = ui.newMenu(labels)
    menu:alignItemsVertically()
    menu:setPosition(display.cx, display.cy)
    return menu
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.createSceneClass(name)
    local cls = class(name, function()
        return display.newScene(name)
    end)

    function cls:prepare(args)
        self.menuLayer = display.newLayer()
        self:addChild(self.menuLayer, 30000)

        local label = ui.newTTFLabelMenuItem({
            text = "RETURN",
            color = ccc3(255, 0, 0),
            x = display.right - 80,
            y = display.bottom + 30,
            listener = function()
                display.replaceScene(require("scenes.MainScene").new())
            end
        })
        self.menuLayer:addChild(ui.newMenu({label}))

        local label = ui.newTTFLabel({
            text = "====   " .. cls.__cname .. "   ====",
            size = 24,
            color = ccc3(0, 255, 0),
            x = display.cx,
            y = display.top - 30,
            align = ui.TEXT_ALIGN_CENTER,
        })
        self.menuLayer:addChild(label)

        if args and args.description then
            local label = ui.newTTFLabel({
                text = args.description,
                size = 20,
                color = ccc3(0, 160, 0),
                x = display.cx,
                y = display.top - 60,
                align = ui.TEXT_ALIGN_CENTER,
            })
            self.menuLayer:addChild(label)
        end
    end


    function cls:runTest(name)
        printf("----------------------------------------")
        printf("-- run test %s", name)
        print("--")
        name = string.gsub(name, " ", "_")
        if self.beforeRunTest then self:beforeRunTest() end
        local m = self[name .. "Test"]
        m(self)
    end

    return cls
end

function bin2hex(bin)
    local t = {}
    for i = 1, string.len(bin) do
        local c = string.byte(bin, i, i)
        t[#t + 1] = string.format("%02x", c)
    end
    return table.concat(t, " ")
end
