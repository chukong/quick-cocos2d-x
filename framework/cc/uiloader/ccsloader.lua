
local ccsloader = class("ccsloader")

function ccsloader:load(jsonFile)
	local fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(jsonFile)
	local jsonStr = fileUtil:getStringFromFile(fullPath)
	local jsonVal = json.decode(jsonStr)

	self:loadTexture(jsonVal)
	-- for i,v in ipairs(jsonVal.textures) do
	-- 	display.addSpriteFrames(v, jsonVal.texturesPng[i])
	-- end

	return self:parserJson(jsonVal)
end

function ccsloader:parserJson(jsonVal)
	local root = jsonVal.nodeTree
	if not root then
		root = jsonVal.widgetTree
	end
	if not root then
		printInfo("ccsloader - parserJson havn't found root noe")
		return
	end
	local uiRoot = self:generateUINode(root)

	return uiRoot
end

-- generate a ui node and invoke self to generate child ui node
function ccsloader:generateUINode(jsonNode, transX, transY)
	transX = transX or 0
	transY = transY or 0

	local clsName = jsonNode.classname
	local options = jsonNode.options

	options.x = options.x or 0
	options.y = options.y or 0
	options.x = options.x + transX
	options.y = options.y + transY

	local uiNode = self:createUINode(clsName, options)
	if not uiNode then
		return
	end

	-- ccs中父节点的原点在父节点的锚点位置，这里用posTrans作转换
	local posTrans = uiNode:getAnchorPoint()
	local parentSize = uiNode:getContentSize()
	posTrans.x = posTrans.x * parentSize.width
	posTrans.y = posTrans.y * parentSize.height

	uiNode.name = options.name or "unknow node"

	-- print("ccsloader set node params:" .. uiNode.name)

	if options.fileName then
		uiNode:setSpriteFrame(options.fileName)
	end

	if options.flipX then
		uiNode:setFlippedX(options.flipX)
	end
	if options.flipY then
		uiNode:setFlippedY(options.flipY)
	end
	uiNode:setRotation(options.rotation or 0)

	uiNode:setScaleX(options.scaleX or 1)
	uiNode:setScaleY(options.scaleY or 1)
	uiNode:setVisible(options.visible)
	uiNode:setLocalZOrder(options.ZOrder or 0)
	uiNode:setTag(options.tag or 0)

	local emptyNode
	if "ScrollView" == clsName then
		emptyNode = cc.Node:create()
		emptyNode:setPosition(options.x, options.y)
		uiNode:addScrollNode(emptyNode)
	end

	local children = jsonNode.children
	for i,v in ipairs(children) do
		local childrenNode = self:generateUINode(v, posTrans.x, posTrans.y)
		if childrenNode then
			if "ScrollView" == clsName then
				emptyNode:addChild(childrenNode)
			elseif "ListView" == clsName then
				local item = uiNode:newItem()
				item:addContent(childrenNode)
				local size = childrenNode:getContentSize()
				local layoutParameter = self:getChildOptionJson(v)
				if layoutParameter then
					item:setMargin({left = layoutParameter.marginLeft,
						right = layoutParameter.marginRight,
						top = layoutParameter.marginTop,
						bottom = layoutParameter.marginDown})
				end
				item:setItemSize(size.width, size.height)
				uiNode:addItem(item)
			elseif "PageView" == clsName then
				local item = uiNode:newItem()
				childrenNode:setPosition(0, 0)
				item:addChild(childrenNode)
				item:setTag(10001)
				uiNode:addItem(item)
			else
				uiNode:addChild(childrenNode)
			end
		end
	end

	if "ListView" == clsName or "PageView" == clsName then
		uiNode:reload()
	elseif "ScrollView" == clsName then
		uiNode:resetPosition()
	end

	return uiNode
end

function ccsloader:createUINode(clsName, options)
	if not clsName then
		return
	end

	local node

	if clsName == "Node" then
		node = self:createNode(options)
	elseif clsName == "Sprite" or clsName == "Scale9Sprite" then
		node = self:createSprite(options)
	elseif clsName == "ImageView" then
		node = self:createImage(options)
	elseif clsName == "Button" then
		node = self:createButton(options)
	elseif clsName == "LoadingBar" then
		node = self:createLoadingBar(options)
	elseif clsName == "Slider" then
		node = self:createSlider(options)
	elseif clsName == "CheckBox" then
		node = self:createCheckBox(options)
    elseif clsName == "LabelBMFont" then
    	node = self:createBMFontLabel(options)
    elseif clsName == "Label" then
    	node = self:createLabel(options)
    elseif clsName == "LabelAtlas" then
    	node = self:createLabelAtlas(options)
	elseif clsName == "TextField" then
		node = self:createEditBox(options)
	elseif clsName == "Panel" then
		node = self:createPanel(options)
	elseif clsName == "ScrollView" then
		node = self:createScrollView(options)
	elseif clsName == "ListView" then
		node = self:createListView(options)
	elseif clsName == "PageView" then
		node = self:createPageView(options)
	else
		-- printError("ccsloader not support node:" .. clsName)
		printInfo("ccsloader not support node:" .. clsName)
	end

	return node
end

function ccsloader:getChildOptionJson(json)
	return json.options.layoutParameter
end

function ccsloader:newWapperNode(oldNode, layoutParameter)
	local newNode = display.newNode()
	local size = oldNode:getContentSize()
	size.width = size.width + layoutParameter.marginLeft + layoutParameter.marginRight
	size.height = size.height + layoutParameter.marginTop + layoutParameter.marginDown
	newNode:setContentSize(size)
	newNode:addChild(oldNode)
	oldNode:setPosition()
end

function ccsloader:getButtonStateImages(options)
	local images = {}
	if options.normalData and options.normalData.path then
		images.normal = self:transResName(options.normalData.path)
	end
	if options.pressedData and options.pressedData.path then
		images.pressed = self:transResName(options.pressedData.path)
	end
	if options.disabledData and options.disabledData.path then
		images.disabled = self:transResName(options.disabledData.path)
	end

	return images
end

function ccsloader:getAnchorType(anchorX, anchorY)
	if 1 == anchorX then
		if 1 == anchorY then
			return display.RIGHT_TOP
		elseif 0.5 == anchorY then
			return display.RIGHT_CENTER
		else
			return display.RIGHT_BOTTOM
		end
	elseif 0.5 == anchorX then
		if 1 == anchorY then
			return display.CENTER_TOP
		elseif 0.5 == anchorY then
			return display.CENTER
		else
			return display.CENTER_BOTTOM
		end
	else
		if 1 == anchorY then
			return display.LEFT_TOP
		elseif 0.5 == anchorY then
			return display.LEFT_CENTER
		else
			return display.LEFT_BOTTOM
		end
	end
end


function ccsloader:getCheckBoxImages(options)
	local images = {}

	local getBackgroundImage = function(state)
		local image = options.backGroundBoxData.path
		if "pressed" == state then
			image = options.backGroundBoxSelectedData.path
		end
		if "disabled" == state then
			image = options.backGroundBoxDisabledData.path
		end

		return image
	end

	-- local getFrontgroundImage = function(state)
	-- 	local image = options.backGroundBoxData.path
	-- 	if "pressed" == state then
	-- 		image = options.backGroundBoxSelectedData.path
	-- 	end
	-- 	if "disabled" == state then
	-- 		image = options.backGroundBoxDisabledData.path
	-- 	end

	-- 	return image
	-- end

	images.off = self:transResName(getBackgroundImage("normal"))
	images.off_pressed = self:transResName(getBackgroundImage("pressed"))
	images.off_disabled = self:transResName(getBackgroundImage("disabled"))
	images.on = {images.off, self:transResName(options.frontCrossData.path)}
	images.on_pressed = images.on
	images.on_disabled = {images.off_disabled,
		self:transResName(options.frontCrossDisabledData.path)}

	return images
end

function ccsloader:loadTexture(json)
	-- cc.FileUtils:getInstance():addSearchPath("res/")

	for i,v in ipairs(json.textures) do
		self.bUseTexture = true
		display.addSpriteFrames(v, json.texturesPng[i])
	end

end

function ccsloader:transResName(name)
	if not name then
		return name
	end

	-- local pathInfo = io.pathinfo(path)
	-- local name = pathInfo.filename

	if self.bUseTexture then
		return "#" .. name
	else
		return name
	end
end

function ccsloader:createNode(options)
	local node = cc.Node:create()
	if not options.ignoreSize then
		node:setContentSize(cc.size(options.width, options.height))
	end
	node:setPositionX(options.x or 0)
	node:setPositionY(options.y or 0)
	node:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

	return node
end

function ccsloader:createSprite(options)
	local node = cc.Sprite:create()
	if not options.ignoreSize then
		node:setContentSize(cc.size(options.width, options.height))
	end
	node:setPositionX(options.x or 0)
	node:setPositionY(options.y or 0)
	node:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

	return node
end

function ccsloader:createImage(options)
	local node = cc.ui.UIImage.new(
		self:transResName(options.fileNameData.path),
		{scale9 = not options.ignoreSize})

	if not options.ignoreSize then
		node:setLayoutSize(options.width, options.height)
	end
	node:setPositionX(options.x or 0)
	node:setPositionY(options.y or 0)
	node:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

	return node
end

function ccsloader:createButton(options)
	local node = cc.ui.UIPushButton.new(self:getButtonStateImages(options),
		{scale9 = not options.ignoreSize})
	if not options.ignoreSize then
		node:setButtonSize(options.width, options.height)
	end
	node:align(self:getAnchorType(options.anchorPointX, options.anchorPointY),
		options.x or 0, options.y or 0)

	return node
end

function ccsloader:createLoadingBar(options)
	local params = {}
	params.image = self:transResName(options.textureData.path)
	params.scale9 = options.scale9Enable
	params.capInsets = cc.rect(options.capInsetsX, options.capInsetsY,
		options.capInsetsWidth, options.capInsetsHeight)
	params.direction = options.direction
	params.percent = options.percent
	params.viewRect = cc.rect(options.x, options.y, options.width, options.height)

	local node = cc.ui.UILoadingBar.new(params)

	node:setPositionX(options.x or 0)
	node:setPositionY(options.y or 0)
	node:setContentSize(options.width, options.height)
	node:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

	return node
end

function ccsloader:createSlider(options)
	local node = cc.ui.UISlider.new(display.LEFT_TO_RIGHT,
		{bar = self:transResName(options.barFileNameData.path),
		button = self:transResName(options.ballNormalData.path)},
		{scale9 = not options.ignoreSize})

	if not options.ignoreSize then
		node:setSliderSize(options.width, options.height)
	end
	node:align(self:getAnchorType(options.anchorPointX, options.anchorPointY),
		options.x or 0, options.y or 0)
    node:setSliderValue(options.percent)

	return node
end

function ccsloader:createCheckBox(options)
	local node = cc.ui.UICheckBoxButton.new(
		self:getCheckBoxImages(options),
		{scale9 = not options.ignoreSize})

	if not options.ignoreSize then
		node:setButtonSize(options.width, options.height)
	end
	node:align(self:getAnchorType(options.anchorPointX, options.anchorPointY),
		options.x or 0, options.y or 0)

	return node
end

function ccsloader:createBMFontLabel(options)
	local node = ui.newBMFontLabel({
		text = options.text,
		font = options.fileNameData.path,
		textAlign = ui.TEXT_ALIGN_CENTER,
		x = options.x,
		y = options.y})
	if 1 == options.anchorPointY then
		node:setAlignment(ui.TEXT_ALIGN_RIGHT)
	elseif 0.5 == options.anchorPointY then
	else
		node:setAlignment(ui.TEXT_ALIGN_RIGHT)
	end

	return node
end

function ccsloader:createLabel(options)
	local node = cc.ui.UILabel.new({text = options.text,
		font = options.fontName,
		size = options.fontSize,
		color = cc.c3b(options.colorR, options.colorG, options.colorB),
		align = options.hAlignment,
		valign = options.vAlignment,
		x = options.x, y = options.y})
	if not options.ignoreSize then
		node:setLayoutSize(options.areaWidth, options.areaHeight)
	end

	return node
end

function ccsloader:createLabelAtlas(options)
	local labelAtlas
	if "function" == type(cc.LabelAtlas._create) then
		labelAtlas = cc.LabelAtlas:_create()
		labelAtlas:initWithString(options.stringValue,
			options.charMapFileData.path,
			options.itemWidth,
			options.itemHeight,
			string.byte(options.startCharMap))
	else
		labelAtlas = cc.LabelAtlas:create(
			options.stringValue,
			options.charMapFileData.path,
			options.itemWidth,
			options.itemHeight,
			string.byte(options.startCharMap))
	end

	labelAtlas:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))
	labelAtlas:setPosition(options.x, options.y)
	if not options.ignoreSize then
		labelAtlas:setContentSize(options.width, options.height)
	end
	return labelAtlas
end

function ccsloader:createEditBox(options)
	local editBox = ui.newEditBox({
        size = cc.size(options.width, options.height)
    })
    editBox:setPlaceHolder(options.placeHolder)
    editBox:setFontName(options.fontName)
    editBox:setFontSize(options.fontSize)
    editBox:setText(options.text)
    editBox:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))
    if options.passwordEnable then
    	editBox:setInputFlag(cc.EDITBOX_INPUT_FLAG_PASSWORD)
	end
	if options.maxLengthEnable then
		editBox:setMaxLength(options.maxLength)
	end

	editBox:setPosition(
		options.x - options.width*options.anchorPointX,
		options.y + options.fontSize/2)

	return editBox
end

function ccsloader:createPanel(options)
	local node = cc.Node:create()
	local clrLayer
	local bgLayer

	if 1 == options.colorType then
		-- single color
		clrLayer = cc.LayerColor:create()
		clrLayer:setTouchEnabled(false)
		clrLayer:setColor(cc.c3b(options.bgColorR, options.bgColorG, options.bgColorB))
	elseif 2 == options.colorType then
		-- gradient
		clrLayer = cc.LayerGradient:create()
		clrLayer:setTouchEnabled(false)
		clrLayer:setStartColor(cc.c3b(options.bgStartColorR, options.bgStartColorG, options.bgStartColorB))
		clrLayer:setEndColor(cc.c3b(options.bgEndColorR, options.bgEndColorG, options.bgEndColorB))
		clrLayer:setVector(cc.p(options.vectorX, options.vectorY))
	end

	if clrLayer then
		clrLayer:setAnchorPoint(cc.p(0, 0))
		clrLayer:setOpacity(options.bgColorOpacity)
	end

	-- background layer
	if options.backGroundScale9Enable then
		if options.backGroundImageData and options.backGroundImageData.path then
			local capInsets = cc.rect(options.capInsetsX, options.capInsetsY,
						options.capInsetsWidth, options.capInsetsHeight)
			if self.bUseTexture then
				bgLayer = cc.Scale9Sprite:createWithSpriteFrameName(
					options.backGroundImageData.path, capInsets)
			else
				bgLayer = cc.Scale9Sprite:create(
					capInsets, options.backGroundImageData.path)
			end
		end
	else
		if options.backGroundImageData and options.backGroundImageData.path then
			bgLayer = display.newSprite(
				self:transResName(options.backGroundImageData.path))
		end
	end

	local conSize = cc.size(options.width, options.height)
	if not options.ignoreSize then
		if clrLayer then
			clrLayer:setContentSize(conSize)
		end
	end
	if bgLayer then
		bgLayer:setPosition(conSize.width/2, conSize.height/2)
	end
	node:setContentSize(conSize)
	if clrLayer then
		node:addChild(clrLayer)
	end
	if bgLayer then
		node:addChild(bgLayer)
	end
	node:setPositionX(options.x or 0)
	node:setPositionY(options.y or 0)
	node:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

	-- local setVisibleOrg = node.setVisible
	-- local setVisibleAll
	-- setVisibleAll = function(self, bVisible)
	-- 	if not self then
	-- 		return
	-- 	end

	-- 	print("setvisible:" .. tostring(bVisible))

	-- 	setVisibleOrg(self, bVisible)
	-- 	local children = self:getChildren()
	-- 	if not children then
	-- 		return
	-- 	end
	-- 	for i,v in ipairs(children) do
	-- 		setVisibleAll(v, bVisible)
	-- 	end
	-- end
	-- node.setVisible = setVisibleAll

	return node
end

function ccsloader:createScrollView(options)
	local params =
		{viewRect = cc.rect(options.x, options.y, options.width, options.height)}

	if 1 == options.colorType then
		-- single color
		params.bgColor = cc.c4b(options.bgColorR, options.bgColorG, options.bgColorB, options.bgColorOpacity)
	elseif 2 == options.colorType then
		-- gradient
		params.bgStartColor = cc.c4b(options.bgStartColorR, options.bgStartColorG, options.bgStartColorB, options.bgColorOpacity)
		params.bgEndColor = cc.c4b(options.bgEndColorR, options.bgEndColorG, options.bgEndColorB, options.bgColorOpacity)
		params.bgVector = cc.p(options.vectorX, options.vectorY)
	end

	local node = cc.ui.UIScrollView.new(params)
	local dir = options.direction
	-- ccs中 0:none 1:vertical 2:horizontal 3:vertical and horizontal
	-- quick 0:both 1:vertical 2:horizontal
	if 0 == dir then
		-- 让ccs中的none对应到vertical
		dir = 0
	elseif 3 == dir then
		dir = 0
	end
	node:setDirection(dir)

	return node
end

function ccsloader:createListView(options)
	local params =
		{viewRect = cc.rect(options.x, options.y, options.width, options.height)}

	if 1 == options.colorType then
		-- single color
		params.bgColor = cc.c4b(options.bgColorR, options.bgColorG, options.bgColorB, options.bgColorOpacity)
	elseif 2 == options.colorType then
		-- gradient
		params.bgStartColor = cc.c4b(options.bgStartColorR, options.bgStartColorG, options.bgStartColorB, options.bgColorOpacity)
		params.bgEndColor = cc.c4b(options.bgEndColorR, options.bgEndColorG, options.bgEndColorB, options.bgColorOpacity)
		params.bgVector = cc.p(options.vectorX, options.vectorY)
	end

	local node = cc.ui.UIListView.new(params)
	local dir = options.direction
	-- ccs listView 0:none 1:vertical 2:horizontal 3:vertical and horizontal
	-- quick 0:both 1:vertical 2:horizontal
	if 0 == dir then
		-- 让ccs中的none对应到vertical
		dir = 1
	elseif 3 == dir then
		dir = 0
	end
	node:setDirection(dir)
	node:setAlignment(options.gravity)

	return node
end

function ccsloader:createPageView(options)
	local params = {}
	params.column = 1
	params.row = 1
	params.viewRect = cc.rect(options.x, options.y, options.width, options.height)

	local node = cc.ui.UIPageView.new(params)

	return node
end


return ccsloader
