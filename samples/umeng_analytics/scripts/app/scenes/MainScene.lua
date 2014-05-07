
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    self.innerSpace = 80

    cc.ui.UILabel.new({text = "Umeng analytics demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*1)
        :align(display.CENTER)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Pay", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            -- 通过支付宝用 10元钱 购买了 1000 个金币
            MobClickCppForLua:pay(10, 2, 1000)
        end)
        :pos(130, display.top - self.innerSpace*2)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Buy", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            -- 使用金币购买了1个头盔，一个头盔价值 1000 金币
            MobClickCppForLua:buy("helmet", 1, 1000)
        end)
        :pos(130, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Use", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(240, 60)
        :onButtonClicked(function()
            -- 使用了2瓶魔法药水,每个需要50个虚拟币
            MobClickCppForLua:use("magic_bottle", 2, 50)
        end)
        :pos(130, display.top - self.innerSpace*3)
        :addTo(self)

end

function MainScene:onEnter()
    MobClickCppForLua::beginScene("MainScene");

    if device.platform == "android" then
        -- avoid unmeant back
        self:performWithDelay(function()
            -- keypad layer, for android
            local layer = display.newLayer()
            layer:addKeypadEventListener(function(event)
                if event == "back" then app.exit() end
            end)
            self:addChild(layer)

            layer:setKeypadEnabled(true)
        end, 0.5)
    end
end

function MainScene:onExit()
    MobClickCppForLua::endScene("MainScene");
end

return MainScene
