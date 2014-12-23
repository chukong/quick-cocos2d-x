--[[--

针对quick的DragonBones支持，封装了 DragonBonesCPP 的常用操作。

@author zrong(zengrong.net)
Creation 2014-07-24

用法可参考 samples/dragonbones

]]
if CCDBManager==nil then return nil end

local db = {}

local dbManager = CCDBManager:getInstance()

--[[--
创建一个 DragonBonesNode 对象

@author zrong(zengrong.net)

Creation：2014-07-17

@param table params 一个包含所有参数的table

@return DragonBonesNode


params 参数的值较为丰富，如下：

* path 可选。素材文件所在目录，这个目录下应该包含三个文件：
	* texture.xml
	* texture.png
	* skeleton.xml
* skeleton 可选。skeleton.xml的路径；
* texture 可选。texture.xml的路径；
* armatureName 必选。skeleton.xml 中的主 Armature 元素的 name；
* animationName 要默认播放的动作，不提供则为空字符串；
* skeletonName skeleton.xml 中的root元素的 name 值，若不提供则与armatureName相同；
* textureName texture.xml 中的root元素的 name 值，不提供则与skeletonName相同；
* skinName 不提供则为空字符串。
* handler 一个异步函数。
	* 若不提供，则代表同步加载资源，并立即返回新建的 DragonBonesNode 对象；
	* 若提供，则代表资源进行异步加载，并在 handler 调用的时候提供 DragonBonesNode 对象。

举例如下：

一个提供完整的xml配置文件路径的同步载入：

	```lua
	{
		skeleton="dragon/skeleton.xml",
		texture="dragon/texture.xml",
		armatureName="Dragon",
		animationName="walk",
		skeletonName="Dragon",
	}
	```

在 path 指定的目录中自动查找 skeleton.xml 和 texture.xml：

	```lua
	{
		path="dragon",
		armatureName="Dragon",
		animationName="",
		skeletonName="Dragon",
	}
	```

素材已经在缓存中了，那么可以直接提供armatureName：

	```lua
	{
		armatureName="Dragon",
		skeletonName="Dragon",
	}
	```

异步载入素材，这个方法会返回nil，在handler中提供一个DragonBonesNode对象。

	```lua
	{
		path="dragon",
		armatureName="Dragon",
		handler=function(db)
			db:addTo(self, 10)
			db:gotoAndPlay("walk")
		end
	}
	```
]]
function db.new(params)
	dump(params)
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
		return cc.DragonBonesNode:createByDir(
				path, 
				armName, aniName, 
				skeName, texName, 
				skinName)
	end
	if skeFile and texFile then
		return cc.DragonBonesNode:createByFiles(
				skeFile, texFile, 
				armName, aniName, 
				skeName, texName, 
				skinName)
	end
	return cc.DragonBonesNode:createByName(
		armName, aniName, 
		skeName, texName,
		skinName)
end

--[[--

载入外部素材，支持同步或异步载入。

@param table params

params 的参数与 new 相同。但 handler 的参数与new的不同。因为只是异步载入资源，不会创建一个 DragonBonesNode 对象。
]]
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


--[[--

对 loadData 的进一步封装，接受一个列表，批量载入素材。

@param table fileList 一个列表，其中的每一项与 loadData 的 params 参数相同；
@param function handler 不提供代表同步载入，提供代表异步载入。若为异步载入，所有资源载入完成后，会调用这个方法。

]]
function db.loadDataList(fileList, handler)
	local total = #fileList
	local cur = total 
	local aHandler = nil
	if type(handler) == "function" then
		aHandler = function(evt)
			cur = cur - 1
			if cur <= 0 then
				handler(true, cur, total)
			else
				--handler(false, cur, total)
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

--[[--

卸载一个素材。

@param table params 包含 skeletonName 和 textureName 的一个table

]]
function db.unloadData(params)
	local skeName = params.skeletonName
	local texName = params.textureName or skeName

	dbManager:unloadData(skeName, texName)
end

--[[--

批量卸载一个素材。

@param table fileList 一个列表，其中的每一项与 unloadData 的 params 参数相同。

]]
function db.unloadDataList(fileList)
	for __, v in ipairs(fileList) do
		db.unloadData(v.skeletonName, v.textureName)
	end
end

return db
