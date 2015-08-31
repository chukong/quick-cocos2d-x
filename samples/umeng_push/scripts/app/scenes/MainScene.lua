
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if device.platform == "android" then
        self:showPushView()
    else
        self:noPushView()
    end
end

function MainScene:showPushView()
    print("htl, showPushView entry")

    self.innerSpace = 80

    cc.ui.UILabel.new({text = "UmengPush demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*1)
        :align(display.CENTER)
        :addTo(self)

    -- result show
    local resultLabel = cc.ui.UILabel.new({text = "result: -", size = 20, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*2)
        :align(display.CENTER)
        :addTo(self)
    self.resultLabel = resultLabel

    -- enable btn
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Enable Push", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            cc.push:doCommand({command = "startPush"})
        end)
        :pos(100, display.top - self.innerSpace*3)
        :addTo(self)

    -- disabel btn
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "Disable Push", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            cc.push:doCommand{command = "stopPush"}
        end)
        :pos(300, display.top - self.innerSpace*3)
        :addTo(self)

    -- set tag
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "set tag", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            local text = self.textSetTag:getText()
            if string.utf8len(text) < 1 then
                return
            end
            cc.push:doCommand{command = "setTags", args = string.split(text, ",")}
        end)
        :pos(100, display.top - self.innerSpace*4)
        :addTo(self)

    -- tag input
    local inputSetTagEdit = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(300, 50),
        x = 350,
        y = display.top - self.innerSpace*4,
        listener = function()end})
    :addTo(self)
    inputSetTagEdit:setText("tag1,tag2")
    self.textSetTag = inputSetTagEdit

    -- del tag
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "del tag", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            local text = self.textDelTag:getText()
            if string.utf8len(text) < 1 then
                return
            end
            cc.push:doCommand{command = "delTags", args = string.split(text, ",")}
        end)
        :pos(100, display.top - self.innerSpace*5)
        :addTo(self)

    -- tag input
    local inputDelTagEdit = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(300, 50),
        x = 350,
        y = display.top - self.innerSpace*5,
        listener = function()end})
    :addTo(self)
    inputDelTagEdit:setText("tag1,tag2")
    self.textDelTag = inputDelTagEdit

    -- set alial
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "set alias", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            local text = self.textAlias:getText()
            if string.utf8len(text) < 1 then
                return
            end
            cc.push:doCommand{command = "setAlias", args = text .. "," .. cc.push.umengAliasType.SINA_WEIBO}
        end)
        :pos(100, display.top - self.innerSpace*6)
        :addTo(self)

    -- tag input
    local inputSetAliasEdit = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(300, 50),
        x = 350,
        y = display.top - self.innerSpace*6,
        listener = function()end})
    :addTo(self)
    inputSetAliasEdit:setText("aliasname")
    self.textAlias = inputSetAliasEdit

    -- del alias
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "del alias", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(180, 50)
        :onButtonClicked(function()
            local text = self.textAliasDel:getText()
            if string.utf8len(text) < 1 then
                return
            end
            cc.push:doCommand{command = "delAlias", args = text .. "," .. cc.push.umengAliasType.SINA_WEIBO}
        end)
        :pos(100, display.top - self.innerSpace*7)
        :addTo(self)

    -- tag input
    local inputSetAliasEditDel = ui.newEditBox({
        image = "EditBoxBg.png",
        size = CCSize(300, 50),
        x = 350,
        y = display.top - self.innerSpace*7,
        listener = function()end})
    :addTo(self)
    inputSetAliasEditDel:setText("aliasname")
    self.textAliasDel = inputSetAliasEditDel

    -- use EventProxy, ensure remove the listener when leave current the scene
    local proxy = cc.EventProxy.new(cc.push, self)
    proxy:addEventListener(cc.push.events.LISTENER, function(event)
        --event = 
        --{ provider,
        --  command,   返回类型 有setTags,delTags,setAlias,delAlias,startPush,stopPush,customMsg,notifyMsg
        --  ecode,  0为成功，其它为失败
        --  text,收到的自定义消息内容
        --  }

        local info
        if event.command == "customMsg" or event.command == "notifyMsg" then
            info = event.command .. " msg:" .. event.text
        else
            info = event.command .. " code:" .. event.code
        end

        print("htl info:" .. info)
        self.resultLabel:setString("result: " .. info)
    end)

end

function MainScene:noPushView()
    cc.ui.UILabel.new({text = "UmengPush demo\n\nPlease run this demo on Android device.",
            size = 24,
            align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.cy)
        :align(display.CENTER)
        :addTo(self)
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
