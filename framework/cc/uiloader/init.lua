
local uiloader = class("uiloader")
local CCSUILoader = import(".CCSUILoader")
local CCSSceneLoader = import(".CCSSceneLoader")

function uiloader:ctor()
end

function uiloader:load(jsonFile)
	local json = self:loadFile_(jsonFile)
	if not json then
		print("uiloader - load file fail:" .. jsonFile)
		return
	end

	local node
	local w
	local h
	
	if self:isScene_(json) then
		node, w, h = CCSSceneLoader:load(json)
	else
		node, w, h = CCSUILoader:load(json)
	end

	return node, w, h
end

function uiloader:seekNodeByTag(parent, tag)
	if not parent then
		return
	end

	if tag == parent:getTag() then
		return parent
	end

	local findNode
	local children = parent:getChildren()
	local childCount = parent:getChildrenCount()
	if childCount < 1 then
		return
	end
	for i=1, childCount do
		if "table" == type(children) then
			parent = children[i]
		elseif "userdata" == type(children) then
			parent = children:objectAtIndex(i - 1)
		end

		if parent then
			findNode = self:seekNodeByTag(parent, tag)
			if findNode then
				return findNode
			end
		end
	end

	return
end

function uiloader:seekNodeByName(parent, name)
	if not parent or parent.getChildren == nil then
		return
	end

	if name == parent.name then
		return parent
	end

	local findNode
	local children = parent:getChildren()
	local childCount = parent:getChildrenCount()
	if childCount < 1 then
		return
	end
	for i=1, childCount do
		if "table" == type(children) then
			parent = children[i]
		elseif "userdata" == type(children) then
			parent = children:objectAtIndex(i - 1)
		end

		if parent then
			findNode = self:seekNodeByName(parent, name)
			if findNode then
				return findNode
			end
		end
	end

	return
end


function uiloader:seekComponents(parent, nodeName, componentIdx)
	local node = self:seekNodeByName(parent, nodeName)
	if not node then
		return
	end
	node = self:seekNodeByName(node, "Component" .. componentIdx)
	return node
end






-- private
function uiloader:loadFile_(jsonFile)
	local fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(jsonFile)
	local jsonStr = fileUtil:getStringFromFile(fullPath)
	local jsonVal = json.decode(jsonStr)

	return jsonVal
end

function uiloader:isScene_(json)
	if json.components then
		return true
	else
		return false
	end
end

return uiloader
