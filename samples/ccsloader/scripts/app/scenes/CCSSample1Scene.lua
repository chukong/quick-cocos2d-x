
local CCSSample1Scene = class("CCSSample1Scene", function()
    return display.newScene("CCSSample1Scene")
end)

function CCSSample1Scene:ctor()
	app:createTitle(self, "CCS Sample1")
	app:createNextButton(self)

	app:loadCCSJsonFile(self, "DemoHead_UI.ExportJson")
	-- app:loadCCSJsonFile(self, "Cocostudio1_5_1.ExportJson")
end


return CCSSample1Scene
