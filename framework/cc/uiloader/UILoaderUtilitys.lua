
local UILoaderUtilitys = {}

function UILoaderUtilitys.loadTexture(plist, png)
	if UILoaderUtilitys.isNil(plist) then
		return
	end

	local fileUtil
	fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(plist)
	fileUtil:addSearchPath(io.pathinfo(fullPath).dirname)
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

return UILoaderUtilitys

