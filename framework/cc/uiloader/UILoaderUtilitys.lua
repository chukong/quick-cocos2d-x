
local UILoaderUtilitys = {}

function UILoaderUtilitys.loadTexture(plist, png)
	if UILoaderUtilitys.isNil(plist) then
		return
	end

	local fileUtil
	if cc.FileUtils.getInstance then
		fileUtil = cc.FileUtils:getInstance()
	else
		fileUtil = cc.FileUtils:sharedFileUtils()
	end
	local fullPath = fileUtil:fullPathForFilename(plist)
	fileUtil:addSearchPath(io.pathinfo(fullPath).dirname)
	local spCache
	if cc.SpriteFrameCache.getInstance then
		spCache = cc.SpriteFrameCache:getInstance()
	else
		spCache = cc.SpriteFrameCache:sharedSpriteFrameCache()
	end
	if png then
		spCache:addSpriteFramesWithFile(plist, png)
	else
		spCache:addSpriteFramesWithFile(plist)
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

