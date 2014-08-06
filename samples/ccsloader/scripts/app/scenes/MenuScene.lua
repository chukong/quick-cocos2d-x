
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	print("MenuScen ctor")
	local node = cc.uiloader:load("DemoLogin.ExportJson")
	if node then
		self:addChild(node)

		-- node = findChildByTag(node, 66)
		-- if not node then
		-- 	print("MenuScene node is nil")
		-- end
		dumpUITree(node)
	end
end

function MenuScene:onEnter()
end


depth = 1
function dumpUITree(node)
	if not node then
		return
	end

	-- if node.name then
	-- 	local info = {}
	-- 	table.insert(info, "")
	-- 	table.insert(info, getLinePreSym() .. string.format("Name:%s", node.name))
	-- 	table.insert(info, getLinePreSym() .. string.format("Tag:%d", node:getTag()))
	-- 	table.insert(info, getLinePreSym() .. string.format("Position:(%d, %d)", node:getPositionX(), node:getPositionY()))
	-- 	local size = node:getContentSize()
	-- 	table.insert(info, getLinePreSym() .. string.format("Size:(%d, %d)", size.width, size.height))
	-- 	table.insert(info, getLinePreSym() .. string.format("Scale:(%f, %f)", node:getScaleX(), node:getScaleY()))
	-- 	local anchor = node:getAnchorPoint()
	-- 	table.insert(info, getLinePreSym() .. string.format("Anchor:(%f, %f)", anchor.x, anchor.y))
	-- 	table.insert(info, getLinePreSym() .. "Visible:" .. tostring(node:isVisible()))
	-- 	table.insert(info, getLinePreSym() .. string.format("ChildCount:%d", node:getChildrenCount()))

	-- 	print(table.concat(info, "\n"))
	-- end

	print("")

	printLine(string.format("Name:%s", node.name))
	printLine(string.format("Tag:%d", node:getTag()))
	printLine(string.format("Position:(%d, %d)", node:getPositionX(), node:getPositionY()))
	local size = node:getContentSize()
	printLine(string.format("Size:(%d, %d)", size.width, size.height))
	printLine(string.format("Scale:(%f, %f)", node:getScaleX(), node:getScaleY()))
	local anchor = node:getAnchorPoint()
	printLine(string.format("Anchor:(%f, %f)", anchor.x, anchor.y))
	printLine("Visible:" .. tostring(node:isVisible()))
	printLine(string.format("ChildCount:%d", node:getChildrenCount()))

	depth = depth + 1
	for i,v in ipairs(node:getChildren()) do
		dumpUITree(v)
	end
	depth = depth - 1
end

function printLine(str)
	local t = {"+"}
	for i=1,depth do
		table.insert(t, "----")
	end
	table.insert(t, str)
	print(table.concat(t))
end

function getLinePreSym()
	local t = {"+"}
	for i=1,depth do
		table.insert(t, "----")
	end
	table.insert(t, str)

	return table.concat(t)
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
