--- DragonBones
-- @author zrong(zengrong.net)
-- Creation 2014-07-24
local db = {}

local dbManager = CCDBManager:getInstance()

--- Create a CCDragonBones object.
-- @author zrong(zengrong.net)
-- Creation：2014-07-17
-- @param params
-- {
--		skeleton="dragon/skeleton.xml",
--		texture="dragon/texture.xml",
--		armatureName="Dragon",
--		animationName="walk",
--		skeletonName="Dragon",
--		skinName=""
--	}
--	or find skeleton.xml and texture.xml in a dictionary path.
-- {
--		path="dragon",
--		armatureName="Dragon",
--		animationName="",
--		skeletonName="Dragon",
--	}
--	or create a armature directory if Skeleton data and texture data is in cache.
-- {
--		armatureName="Dragon",
--		animationName="walk",
--		skeletonName="Dragon",
--		skinName = ""
--	}
--	or create a 
function db.new(params)
	print("db.new:", vardump(params))
	local path = params.path
	local skeFile = params.skeleton
	local texFile = params.texture
	local armName = params.armatureName
	local aniName = params.animationName or ""
	local skeName = params.skeletonName or armName
	local texName = params.textureName or skeName
	local skinName = params.skinName or ""
	assert(armName and skeName, "armatureName and skeletonName are necessary!")
	local async = type(params.handler) == "function" 
	if async then
		local newDBHandler = function()
			params.handler(
				db.new({
					armatureName=armName, 
					animationName=aniName, 
					skeletonName=skeName, 
					textureName = texName,
					skinName = skinName,
			}))
		end
		db.loadData(
			{
				path = path,
				skeleton = skeFile,
				texture = texFile,
				armatureName=armName, 
				animationName=aniName, 
				skeletonName=skeName, 
				textureName = texName,
				skinName = skinName,
				handler = newDBHandler,
			})
		return nil
	end
	if path then
		return CCDragonBonesExtend.extend(
			CCDragonBones:createByDir(
				path, 
				armName, aniName, 
				skeName, texName, 
				skinName)
		)
	end
	if skeFile and texFile then
		return CCDragonBonesExtend.extend(
			CCDragonBones:createByFiles(
				skeFile, texFile, 
				armName, aniName, 
				skeName, texName, 
				skinName)
		)
	end
	printf("-----db armName:%s, aniName:%s, skeName:%s, texName:%s, skinName:%s", 
		armName, aniName, 
		skeName, texName, 
		skinName)
	local db = CCDragonBones:createByName(
		armName, aniName, 
		skeName, texName,
		skinName)
	print("-----db:", db)
	return CCDragonBonesExtend.extend(db)
	--return CCDragonBonesExtend.extend(
	--	CCDragonBones:createByName(
	--		armName, aniName, 
	--		skeName, texName,
	--		skinName)
	--)
end

function db.loadData(params)
	dump(params)
	local path = params.path
	local skeFile = params.skeleton
	local texFile = params.texture
	local armName = params.armatureName
	local aniName = params.animationName or ""
	local skeName = params.skeletonName or armName
	local texName = params.textureName or skeName
	local skinName = params.skinName or ""

	local async = params.handler and type(params.handler) == "function"
	if path then
		if async then
			dbManager:loadDataByDirAsync(
				path, 
				skeName, texName, 
				params.handler)
		else
			dbManager:loadDataByDir(path, skeName, texName)
		end
	else
		assert(skeFile and texFile, "Please provide skeleton and texture file!")
		if async then
			dbManager:loadDataAsync(
				skeFile, texFile, 
				skeName, texName, 
				params.handler)
		else
			dbManager:loadData(
				skeFile, texFile, 
				skeName, texName)
		end
	end
end

function db.loadDataList(fileList, handler)
	local amount = #fileList
	local aHandler = nil
	if type(handler) == "function" then
		aHandler = function(evt)
			amount = amount - 1
			if amount <= 0 then
				handler()
			end
		end
	end
	for __, adb in ipairs(fileList) do
		if aHandler then
			local param = clone(adb)
			param.handler = aHandler
			db.loadData(param)
		else
			db.loadData(adb)
		end
	end
end

function db.unloadData(params)
	local skeName = params.skeletonName
	local texName = params.textureName or skeName

	dbManager:unloadData(skeName, texName)
end

function db.unloadDataList(fileList)
	for __, v in ipairs(fileList) do
		db.unloadData(v.skeletonName, v.textureName)
	end
end

return db
