
local uiloader = class("uiloader")
local ccsloader = import(".ccsloader")

function uiloader:ctor()
end

function uiloader:load(jsonFile)
	return ccsloader:load(jsonFile)
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
	if not parent then
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

return uiloader
