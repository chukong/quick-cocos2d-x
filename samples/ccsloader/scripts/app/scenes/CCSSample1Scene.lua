
local CCSSample1Scene = class("CCSSample1Scene", function()
    return display.newScene("CCSSample1Scene")
end)

function CCSSample1Scene:ctor()
	app:createTitle(self, "CCS Sample1")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/DemoHead_UI/")
	app:loadCCSJsonFile(self, "DemoHead_UI/DemoHead_UI.ExportJson")

	local progress = cc.uiloader:seekNodeByTag(self, 4)
	progress:setPercent(50)
end


return CCSSample1Scene
