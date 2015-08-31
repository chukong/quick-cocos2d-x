
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	if device.platform == "android" then
		self:showView()
	else
		self:showNotSupport()
	end
end

function MainScene:showView()
	cc.ui.UILabel.new({text = "UmengUpdate demo v1.0", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - 70*1)
        :align(display.CENTER)
        :addTo(self)

	cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
		:setButtonLabel(cc.ui.UILabel.new({text = "update", size = 22, color = display.COLOR_BLACK}))
		:setButtonSize(240, 80)
		:onButtonClicked(function()
			cc.update:doCommand{command = "forceUpdate"}
		end)
		:pos(display.cx, display.cy)
        :addTo(self)

    local proxy = cc.EventProxy.new(cc.update, self)
    proxy:addEventListener(cc.update.events.LISTENER, function(event)
        if event.type == "update" then
        	if event.code == cc.update.errors.HAVE_UPDATE then
        		printInfo("have new update")
        	elseif event.code == cc.update.errors.NO_UPDATE then
        		printInfo("have no update")
        	elseif event.code == cc.update.errors.NO_WIFI then
        		printInfo("no wifi")
        	elseif event.code == cc.update.errors.TIME_OUT then
        		printInfo("timeout")
        	elseif event.code == cc.update.errors.USER_UPDATE then
        		printInfo("user choose update")
        	elseif event.code == cc.update.errors.USER_IGNORE then
        		printInfo("user choose ignore this update")
        	elseif event.code == cc.update.errors.USER_LATER then
        		printInfo("user choose later update")
        	end
        elseif event.type == "download" then
        	if event.code == cc.update.errors.DOWNLOAD_START then
        		printInfo("download start")
        	elseif event.code == cc.update.errors.DOWNLOADING then
        		printInfo("downloading progress %d%%", event.downloadProgress)
        	elseif event.code == cc.update.errors.DOWNLOAD_END then
        		if event.dlCode == cc.update.errors.DOWNLOAD_FAIL then
        			printInfo("download faile")
        		elseif event.dlCode == cc.update.errors.DOWNLOAD_SUC then
        			printInfo("download success file:%s", event.file)
        		elseif event.dlCode == cc.update.errors.DOWNLOAD_NEED_RESTART then
        			printInfo("download need restart")
        		end
        	end
        end
    end)
end

function MainScene:showNotSupport()
	cc.ui.UILabel.new{text = "UmengUpdate Demo\nplease run this demo on Android device",
			size = 24,
            align = cc.ui.TEXT_ALIGN_CENTER}
        :align(display.CENTER)
		:pos(display.cx, display.cy)
		:addTo(self)
end

function MainScene:onEnter()
	if device.platform == "android" then
		cc.update:doCommand{command = "update"}
		-- cc.update:doCommand{command = "silentUpdate"}
	end
end

function MainScene:onExit()
end

return MainScene
