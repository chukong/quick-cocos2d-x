
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	print("MenuScen ctor")
	cc.FileUtils:getInstance():addSearchPath("res/NewUi_1/")
	app:loadCCSJsonFile(self, "NewUi_1.ExportJson")
end

function MenuScene:onEnter()
end

function findChildByTag(node, tag)
	if not node then
		return
	end

	if tag == node:getTag() then
		return node
	end

	local findNode
	for i,v in ipairs(node:getChildren()) do
		findNode = findChildByTag(v, tag)
		if findNode then
			return findNode
		end
	end

	return
end

return MenuScene
