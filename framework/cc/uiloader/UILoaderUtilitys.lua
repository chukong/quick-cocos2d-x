
local UILoaderUtilitys = {}

function UILoaderUtilitys.loadTexture(plist, png)
	if UILoaderUtilitys.isNil(plist) then
		return
	end

	local fileUtil
	fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(plist)
	UILoaderUtilitys.addSearchPathIf(io.pathinfo(fullPath).dirname, fileUtil)
	local spCache
	spCache = cc.SpriteFrameCache:getInstance()
	-- print("UILoaderUtilitys - loadTexture plist:" .. plist)
	if png then
		spCache:addSpriteFrames(plist, png)
	else
		spCache:addSpriteFrames(plist)
	end
end

function UILoaderUtilitys.isNil(str)
	if not str or 0 == string.utf8len(str) then
		return true
	else
		return false
	end
end

function UILoaderUtilitys.addSearchPathIf(dir, fileUtil)
	if not UILoaderUtilitys.searchDirs then
		UILoaderUtilitys.searchDirs = {}
	end

	if not UILoaderUtilitys.isSearchExist(dir) then
		table.insert(UILoaderUtilitys.searchDirs, dir)
		if not fileUtil then
			fileUtil = cc.FileUtils:getInstance()
		end
		fileUtil:addSearchPath(dir)
	end
end

function UILoaderUtilitys.isSearchExist(dir)
	local bExist = false
	for i,v in ipairs(UILoaderUtilitys.searchDirs) do
		if v == dir then
			bExist = true
			break
		end
	end

	return bExist
end

return UILoaderUtilitys

