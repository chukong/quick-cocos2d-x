
local display = {}

local sharedDirector         = CCDirector:sharedDirector()
local sharedTextureCache     = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()
local sharedAnimationCache   = CCAnimationCache:sharedAnimationCache()

-- check device screen size
local glview = sharedDirector:getOpenGLView()
local size = glview:getFrameSize()
display.sizeInPixels = {width = size.width, height = size.height}

local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

if CONFIG_SCREEN_WIDTH == nil or CONFIG_SCREEN_HEIGHT == nil then
    CONFIG_SCREEN_WIDTH = w
    CONFIG_SCREEN_HEIGHT = h
end

if not CONFIG_SCREEN_AUTOSCALE then
    if w > h then
        CONFIG_SCREEN_AUTOSCALE = "FIXED_HEIGHT"
    else
        CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"
    end
else
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
end

local scale, scaleX, scaleY

if CONFIG_SCREEN_AUTOSCALE then
    if type(CONFIG_SCREEN_AUTOSCALE_CALLBACK) == "function" then
        scaleX, scaleY = CONFIG_SCREEN_AUTOSCALE_CALLBACK(w, h, device.model)
    end

    if not scaleX or not scaleY then
        scaleX, scaleY = w / CONFIG_SCREEN_WIDTH, h / CONFIG_SCREEN_HEIGHT
    end

    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = scaleX
        CONFIG_SCREEN_HEIGHT = h / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = scaleY
        CONFIG_SCREEN_WIDTH = w / scale
    else
        scale = 1.0
        echoError(string.format("display - invalid CONFIG_SCREEN_AUTOSCALE \"%s\"", CONFIG_SCREEN_AUTOSCALE))
    end

    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, kResolutionNoBorder)
end

local winSize = sharedDirector:getWinSize()
display.contentScaleFactor = scale
display.size               = {width = winSize.width, height = winSize.height}
display.width              = display.size.width
display.height             = display.size.height
display.cx                 = display.width / 2
display.cy                 = display.height / 2
display.c_left             = -display.width / 2
display.c_right            = display.width / 2
display.c_top              = display.height / 2
display.c_bottom           = -display.height / 2
display.left               = 0
display.right              = display.width
display.top                = display.height
display.bottom             = 0
display.widthInPixels      = display.sizeInPixels.width
display.heightInPixels     = display.sizeInPixels.height

echoInfo(string.format("# CONFIG_SCREEN_AUTOSCALE      = %s", CONFIG_SCREEN_AUTOSCALE))
echoInfo(string.format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
echoInfo(string.format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
echoInfo(string.format("# display.widthInPixels        = %0.2f", display.widthInPixels))
echoInfo(string.format("# display.heightInPixels       = %0.2f", display.heightInPixels))
echoInfo(string.format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
echoInfo(string.format("# display.width                = %0.2f", display.width))
echoInfo(string.format("# display.height               = %0.2f", display.height))
echoInfo(string.format("# display.cx                   = %0.2f", display.cx))
echoInfo(string.format("# display.cy                   = %0.2f", display.cy))
echoInfo(string.format("# display.left                 = %0.2f", display.left))
echoInfo(string.format("# display.right                = %0.2f", display.right))
echoInfo(string.format("# display.top                  = %0.2f", display.top))
echoInfo(string.format("# display.bottom               = %0.2f", display.bottom))
echoInfo(string.format("# display.c_left               = %0.2f", display.c_left))
echoInfo(string.format("# display.c_right              = %0.2f", display.c_right))
echoInfo(string.format("# display.c_top                = %0.2f", display.c_top))
echoInfo(string.format("# display.c_bottom             = %0.2f", display.c_bottom))
echoInfo("#")

display.COLOR_WHITE = ccc3(255, 255, 255)
display.COLOR_BLACK = ccc3(0, 0, 0)
display.COLOR_RED   = ccc3(255, 0, 0)
display.COLOR_GREEN = ccc3(0, 255, 0)
display.COLOR_BLUE  = ccc3(0, 0, 255)

display.AUTO_SIZE      = 0
display.FIXED_SIZE     = 1
display.LEFT_TO_RIGHT  = 0
display.RIGHT_TO_LEFT  = 1
display.TOP_TO_BOTTOM  = 2
display.BOTTOM_TO_TOP  = 3

display.CENTER        = 1
display.LEFT_TOP      = 2; display.TOP_LEFT      = 2
display.CENTER_TOP    = 3; display.TOP_CENTER    = 3
display.RIGHT_TOP     = 4; display.TOP_RIGHT     = 4
display.CENTER_LEFT   = 5; display.LEFT_CENTER   = 5
display.CENTER_RIGHT  = 6; display.RIGHT_CENTER  = 6
display.BOTTOM_LEFT   = 7; display.LEFT_BOTTOM   = 7
display.BOTTOM_RIGHT  = 8; display.RIGHT_BOTTOM  = 8
display.BOTTOM_CENTER = 9; display.CENTER_BOTTOM = 9

display.ANCHOR_POINTS = {
    CCPoint(0.5, 0.5),  -- CENTER
    CCPoint(0, 1),      -- TOP_LEFT
    CCPoint(0.5, 1),    -- TOP_CENTER
    CCPoint(1, 1),      -- TOP_RIGHT
    CCPoint(0, 0.5),    -- CENTER_LEFT
    CCPoint(1, 0.5),    -- CENTER_RIGHT
    CCPoint(0, 0),      -- BOTTOM_LEFT
    CCPoint(1, 0),      -- BOTTOM_RIGHT
    CCPoint(0.5, 0),    -- BOTTOM_CENTER
}

display.SCENE_TRANSITIONS = {
    CROSSFADE       = {CCTransitionCrossFade, 2},
    FADE            = {CCTransitionFade, 3, ccc3(0, 0, 0)},
    FADEBL          = {CCTransitionFadeBL, 2},
    FADEDOWN        = {CCTransitionFadeDown, 2},
    FADETR          = {CCTransitionFadeTR, 2},
    FADEUP          = {CCTransitionFadeUp, 2},
    FLIPANGULAR     = {CCTransitionFlipAngular, 3, kCCTransitionOrientationLeftOver},
    FLIPX           = {CCTransitionFlipX, 3, kCCTransitionOrientationLeftOver},
    FLIPY           = {CCTransitionFlipY, 3, kCCTransitionOrientationUpOver},
    JUMPZOOM        = {CCTransitionJumpZoom, 2},
    MOVEINB         = {CCTransitionMoveInB, 2},
    MOVEINL         = {CCTransitionMoveInL, 2},
    MOVEINR         = {CCTransitionMoveInR, 2},
    MOVEINT         = {CCTransitionMoveInT, 2},
    PAGETURN        = {CCTransitionPageTurn, 3, false},
    ROTOZOOM        = {CCTransitionRotoZoom, 2},
    SHRINKGROW      = {CCTransitionShrinkGrow, 2},
    SLIDEINB        = {CCTransitionSlideInB, 2},
    SLIDEINL        = {CCTransitionSlideInL, 2},
    SLIDEINR        = {CCTransitionSlideInR, 2},
    SLIDEINT        = {CCTransitionSlideInT, 2},
    SPLITCOLS       = {CCTransitionSplitCols, 2},
    SPLITROWS       = {CCTransitionSplitRows, 2},
    TURNOFFTILES    = {CCTransitionTurnOffTiles, 2},
    ZOOMFLIPANGULAR = {CCTransitionZoomFlipAngular, 2},
    ZOOMFLIPX       = {CCTransitionZoomFlipX, 3, kCCTransitionOrientationLeftOver},
    ZOOMFLIPY       = {CCTransitionZoomFlipY, 3, kCCTransitionOrientationUpOver},
}

display.TEXTURES_PIXEL_FORMAT = {}

function display.newScene(name)
    local scene = CCSceneExtend.extend(CCScene:create())
    scene.name = name or "<unknown-scene>"
    return scene
end

function display.wrapSceneWithTransition(scene, transitionType, time, more)
    local key = string.upper(tostring(transitionType))
    if string.sub(key, 1, 12) == "CCTRANSITION" then
        key = string.sub(key, 13)
    end

    if key == "RANDOM" then
        local keys = table.keys(display.SCENE_TRANSITIONS)
        key = keys[math.random(1, #keys)]
    end

    if display.SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(display.SCENE_TRANSITIONS[key])
        time = time or 0.2

        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end
    else
        echoError("display.wrapSceneWithTransition() - invalid transitionType %s", tostring(transitionType))
    end
    return scene
end

function display.replaceScene(newScene, transitionType, time, more)
    if sharedDirector:getRunningScene() then
        if transitionType then
            newScene = display.wrapSceneWithTransition(newScene, transitionType, time, more)
        end
        sharedDirector:replaceScene(newScene)
    else
        sharedDirector:runWithScene(newScene)
    end
end

function display.getRunningScene()
    return sharedDirector:getRunningScene()
end

function display.pause()
    sharedDirector:pause()
end

function display.resume()
    sharedDirector:resume()
end

function display.newLayer()
    return CCLayerExtend.extend(CCLayer:create())
end

function display.newColorLayer(color)
    return CCLayerExtend.extend(CCLayerColor:create(color))
end

function display.newNode()
    return CCNodeExtend.extend(CCNode:create())
end

function display.newClippingRegionNode(rect)
    return CCNodeExtend.extend(CCClippingRegionNode:create(rect))
end

-- 2014-04-10 zrong modified 
-- Add a parameter named 'params' to provide 'class' and 'size'.
-- The filtname parameter can be a CCTexture2D.
-- 2014-04-10 zrong modify end
function display.newSprite(filename, x, y, params)
	local spriteClass = nil
	local size = nil
	if params then
		spriteClass = params.class
		size = params.size
	end
	if not spriteClass then spriteClass = CCSprite end
    local t = type(filename)
    if t == "userdata" then t = tolua.type(filename) end
    local sprite

    if not filename then
        sprite = spriteClass:create()
    elseif t == "string" then
        if string.byte(filename) == 35 then -- first char is #
            local frame = display.newSpriteFrame(string.sub(filename, 2))
            if frame then
                sprite = spriteClass:createWithSpriteFrame(frame)
            end
        else
            if display.TEXTURES_PIXEL_FORMAT[filename] then
                CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
                sprite = spriteClass:create(filename)
                CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            else
                sprite = spriteClass:create(filename)
            end
        end
    elseif t == "CCSpriteFrame" then
        sprite = spriteClass:createWithSpriteFrame(filename)
	elseif t == "CCTexture2D" then
		sprite = spriteClass:createWithTexture(filename)
    else
        echoError("display.newSprite() - invalid filename value type")
        sprite = spriteClass:create()
    end

    if sprite then
        CCSpriteExtend.extend(sprite)
        if x and y then sprite:setPosition(x, y) end
        if size then sprite:setContentSize(size) end
    else
        echoError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
        sprite = spriteClass:create()
    end

    return sprite
end

-- 2014-04-10 zrong modified 
-- The display.newSprite can adopt a class parameter, so I simplified the newScale9Sprite.
-- 2014-04-10 zrong modify end
function display.newScale9Sprite(filename, x, y, size)
	return display.newSprite(filename, x, y, {class=CCScale9Sprite,size=size})
end

function display.newTilesSprite(filename, rect)
    if not rect then
        rect = CCRect(0, 0, display.width, display.height)
    end
    local sprite = CCSprite:create(filename, rect)
    if not sprite then
        echoError("display.newTilesSprite() - create sprite failure, filename %s", tostring(filename))
        return
    end

    local tp = ccTexParams()
    tp.minFilter = 9729
    tp.magFilter = 9729
    tp.wrapS = 10497
    tp.wrapT = 10497
    sprite:getTexture():setTexParameters(tp)
    CCSpriteExtend.extend(sprite)

    display.align(sprite, display.LEFT_BOTTOM, 0, 0)

    return sprite
end

--- create a tiled CCSpriteBatchNode, the image can not a POT file.
-- @author zrong(zengrong.net)
-- Creation: 2014-01-21
-- Modification: 2014-04-10
-- @param filename As same a the first parameter for display.newSprite
-- @param plistFile Texture(plist) image filename, filename must be a part of the texture.
-- @param size The tiled node size, use cc.size create it please.
-- @param hPadding Horizontal padding, it will display 1 px gap on moving the node, set padding for fix it.
-- @param vPadding Vertical padding.
-- @return A CCSpriteBatchNode
function display.newTiledBatchNode(filename, plistFile, size, hPadding, vPadding)
	size = size or cc.size(display.width, display.height)
	hPadding = hPadding or 0
	vPadding = vPadding or 0
	local __sprite = display.newSprite(filename)
	local __sliceSize = __sprite:getContentSize()
	__sliceSize.width = __sliceSize.width - hPadding
	__sliceSize.height = __sliceSize.height - vPadding
	local __xRepeat = math.ceil(size.width/__sliceSize.width)
	local __yRepeat = math.ceil(size.height/__sliceSize.height)
	-- How maney sprites we need to fill in tiled node?
	local __capacity = __xRepeat * __yRepeat
	local __batch = display.newBatchNode(plistFile, __capacity)
	local __newSize = cc.size(0,0)
	--printf("newTileNode xRepeat:%u, yRepeat:%u", __xRepeat, __yRepeat)
	for y=0,__yRepeat-1 do
		for x=0,__xRepeat-1 do
			__newSize.width = __newSize.width + __sliceSize.width
			__sprite = display.newSprite(filename)
				:align(display.LEFT_BOTTOM,x*__sliceSize.width, y*__sliceSize.height)
				:addTo(__batch)
				--print("newTileNode:", x*__sliceSize.width, y*__sliceSize.height)
		end
		__newSize.height = __newSize.height + __sliceSize.height
	end
	__batch:setContentSize(__newSize)
	return __batch, __newSize.width, __newSize.height
end

--- Create a masked sprite
-- @author zrong(zengrong.net)
-- Creation: 2014-01-21
function display.newMaskedSprite(__mask, __pic)
	local __mb = ccBlendFunc:new()
	__mb.src = GL_ONE
	__mb.dst = GL_ZERO

	local __pb = ccBlendFunc:new()
	__pb.src = GL_DST_ALPHA
	__pb.dst = GL_ZERO

	local __maskSprite = display.newSprite(__mask):align(display.LEFT_BOTTOM, 0, 0)
	__maskSprite:setBlendFunc(__mb)

	local __picSprite = display.newSprite(__pic):align(display.LEFT_BOTTOM, 0, 0)
	__picSprite:setBlendFunc(__pb)

	local __maskSize = __maskSprite:getContentSize()
	local __canva = CCRenderTexture:create(__maskSize.width,__maskSize.height)
	__canva:begin()
	__maskSprite:visit()
	__picSprite:visit()
	__canva:endToLua()

	local __resultSprite = CCSpriteExtend.extend(
		CCSprite:createWithTexture(
			__canva:getSprite():getTexture()
		))
		:flipY(true)
	return __resultSprite
end

--- Create a Filtered Sprite
-- @author zrong(zengrong.net)
-- Creation: 2014-04-10
-- @param filename As same a the first parameter for display.newSprite
-- @param filters One of the following:
-- 		A CCFilter name;
-- 		More CCFilter names(in a table);
-- 		An instance of CCFilter;
-- 		Some instances of CCFilter(in a table);
-- 		A CCArray inclueds some instances of CCFilter.
-- @param params A or some parameters for CCFilter.
-- @return An instance of CCFilteredSprite
function display.newFilteredSprite(filename, filters, params)
	local __one = {class=CCFilteredSpriteWithOne}
	local __multi = {class=CCFilteredSpriteWithMulti}
	if not filters then return display.newSprite(filtename, nil,nil , __one) end
	local __sp = nil
	local __type = type(filters)
    if __type == "userdata" then __type = tolua.type(filters) end
	--print("display.newFSprite type:", __type)
	if __type == "string" then
		__sp = display.newSprite(filename, nil, nil, __one)
		filters = filter.newFilter(filters, params)
		__sp:setFilter(filters)
	elseif __type == "table" then
		assert(#filters > 1, "display.newFilteredSprite() - Please give me 2 or more filters!")
		__sp = display.newSprite(filename, nil, nil, __multi)
		-- treat filters as {"FILTER_NAME", "FILTER_NAME"}
		if type(filters[1]) == "string" then
			__sp:setFilters(filter.newFilters(filters, params))
		else
			-- treat filters as {CCFilter, CCFilter , ...}
			local __filters = CCArray:create()
			for i in ipairs(filters) do
				__filters:addObject(filters[i])
			end
			__sp:setFilters(__filters)
		end
	elseif __type == "CCArray" then
		-- treat filters as CCArray(CCFilter, CCFilter, ...)
		__sp = display.newSprite(filename, nil, nil, __multi)
		__sp:setFilters(filters)
	else
		-- treat filters as CCFilter
		__sp = display.newSprite(filename, nil, nil, __one)
		__sp:setFilter(filters)
	end
	return __sp
end
display.newFSprite = display.newFilteredSprite

--- Create a Gray Sprite by CCFilteredSprite
-- @author zrong(zengrong.net)
-- Creation: 2014-04-10
-- @param filename As same a the first parameter for display.newSprite
-- @param params As same as the third parameter for display.newFilteredSprite
-- @return An instance of CCFilteredSprite
function display.newGraySprite(filename, params)
	return display.newFilteredSprite(filename, "GRAY", params)
end

function display.newDrawNode()
	return CCDrawNodeExtend.extend(CCDrawNode:create())
end

--- Create a circle or a sector or a pie by CCDrawNode
-- @author zrong(zengrong.net)
-- Creation: 2014-03-11
function display.newSolidCircle(radius, params)
	local circle = display.newDrawNode()
	circle:drawCircle(radius, params)
	local x,y = 0,0
	if params then
		x = params.x or x
		y = params.y or y
	end
	circle:pos(x,y)
	return circle
end

function display.newCircle(radius, params)
    local circle = CCNodeExtend.extend(CCCircleShape:create(radius))
	local x,y = 0,0
	local align=display.CENTER
	if params then
		x = params.x or x
		y = params.y or y
		align = params.align or align
		if params.fill then circle:setFill(params.fill) end
		if params.color then circle:setLineColor(params.color) end
		if params.strippleEnabled then circle:setLineStippleEnabled(params.strippleEnabled) end
		if params.lineStripple then circle:setLineStipple(params.lineStripple) end
		local lineWidth = params.lineWidth or params.borderWidth 
		if lineWidth then circle:setLineWidth(lineWidth) end
	end
	circle:setContentSize(cc.size(radius*2,radius*2))
	circle:align(align, x,y)
	return circle
end

function display.newRect(width, height, params)
    local x, y = 0, 0
    if type(width) == "userdata" then
        local t = tolua.type(width)
        if t == "CCRect" then
            x = width.origin.x
            y = width.origin.y
            height = width.size.height
            width = width.size.width
        elseif t == "CCSize" then
            height = width.height
            width = width.width
        else
            echoError("display.newRect() - invalid parameters")
            return
        end
    end

    local rect = CCNodeExtend.extend(CCRectShape:create(CCSize(width, height)))
	local align=display.CENTER
	if type(height) == "table" then params = hight end
	if type(params) == "table" then
		x = params.x or x
		y = params.y or y
		align = params.align or align
		if params.color then rect:setLineColor(params.color) end
		if params.strippleEnabled then rect:setLineStippleEnabled(params.strippleEnabled) end
		if params.lineStripple then rect:setLineStipple(params.lineStripple) end
		if params.fill then rect:setFill(params.fill) end
		local lineWidth = params.lineWidth or params.borderWidth 
		if lineWidth then rect:setLineWidth(lineWidth) end
	end
	rect:setContentSize(cc.size(width, height))
	rect:align(align, x,y)
    return rect
end

function display.newPolygon(points, scale)
    if type(scale) ~= "number" then scale = 1 end
    local arr = CCPointArray:create(#points)
    for i, p in ipairs(points) do
        p = CCPoint(p[1] * scale, p[2] * scale)
        arr:add(p)
    end

    return CCNodeExtend.extend(CCPolygonShape:create(arr))
end

function display.align(target, anchorPoint, x, y)
    target:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then target:setPosition(x, y) end
end

function display.addImageAsync(imagePath, callback)
    sharedTextureCache:addImageAsync(imagePath, callback)
end

function display.addSpriteFramesWithFile(plistFilename, image, handler)
	local async = type(handler) == "function"
	local asyncHandler = nil
	if async then
		asyncHandler = function()
			-- printf("%s, %s async done.", plistFilename, image)
			local texture = sharedTextureCache:textureForKey(image)
			assert(texture, string.format("The texture %s, %s is unavailable.", plistFilename, image))
			sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, texture)
			handler(plistFilename, image)
		end
	end
    if display.TEXTURES_PIXEL_FORMAT[image] then
        CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
		if async then
			sharedTextureCache:addImageAsync(image, asyncHandler)
		else
			sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
		end
        CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    else
		if async then
			sharedTextureCache:addImageAsync(image, asyncHandler)
		else
			sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
		end
    end
end

function display.removeSpriteFramesWithFile(plistFilename, imageName)
    sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
    if imageName then
        display.removeSpriteFrameByImageName(imageName)
    end
end

function display.setTexturePixelFormat(filename, format)
    display.TEXTURES_PIXEL_FORMAT[filename] = format
end

function display.removeSpriteFrameByImageName(imageName)
    sharedSpriteFrameCache:removeSpriteFrameByName(imageName)
    CCTextureCache:sharedTextureCache():removeTextureForKey(imageName)
end

function display.newBatchNode(image, capacity)
    return CCNodeExtend.extend(CCSpriteBatchNode:create(image, capacity or 100))
end

function display.newSpriteFrame(frameName)
    local frame = sharedSpriteFrameCache:spriteFrameByName(frameName)
    if not frame then
        echoError("display.newSpriteFrame() - invalid frameName %s", tostring(frameName))
    end
    return frame
end

function display.newFrames(pattern, begin, length, isReversed)
    local frames = {}
    local step = 1
    local last = begin + length - 1
    if isReversed then
        last, begin = begin, last
        step = -1
    end

    for index = begin, last, step do
        local frameName = string.format(pattern, index)
        local frame = sharedSpriteFrameCache:spriteFrameByName(frameName)
        if not frame then
            echoError("display.newFrames() - invalid frame, name %s", tostring(frameName))
            return
        end

        frames[#frames + 1] = frame
    end
    return frames
end

function display.newAnimation(frames, time)
    local count = #frames
    local array = CCArray:create()
    for i = 1, count do
        array:addObject(frames[i])
    end
    time = time or 1.0 / count
    return CCAnimation:createWithSpriteFrames(array, time)
end

function display.setAnimationCache(name, animation)
    sharedAnimationCache:addAnimation(animation, name)
end

function display.getAnimationCache(name)
    return sharedAnimationCache:animationByName(name)
end

function display.removeAnimationCache(name)
    sharedAnimationCache:removeAnimationByName(name)
end

function display.removeUnusedSpriteFrames()
    sharedSpriteFrameCache:removeUnusedSpriteFrames()
    sharedTextureCache:removeUnusedTextures()
end

display.PROGRESS_TIMER_BAR = kCCProgressTimerTypeBar
display.PROGRESS_TIMER_RADIAL = kCCProgressTimerTypeRadial

function display.newProgressTimer(image, progresssType)
    if type(image) == "string" then
        image = display.newSprite(image)
    end

    local progress = CCNodeExtend.extend(CCProgressTimer:create(image))
    progress:setType(progresssType)
    return progress
end

-- Get a screenshot of a CCNode
-- @author zrong(zengrong.net)
-- Creation: 2014-04-10
-- @param node A node to print.
-- @param args 
-- @return An instance of CCSprite or CCFilteredSprite.
function display.printscreen(node, args)
	local sp = true
	local file = nil
	local filters = nil
	local filterParams = nil
	if args then
		if args.sprite ~= nil then sp = args.sprite end
		file = args.file
		filters = args.filters
		filterParams = args.filterParams
	end
	local size = node:getContentSize()
	local canvas = CCRenderTexture:create(size.width,size.height)
	canvas:begin()
	node:visit()
	canvas:endToLua()

	if sp then
		local texture = canvas:getSprite():getTexture()
		if filters then
			sp = display.newFSprite(texture, filters, filterParams)
		else
			sp = display.newSprite(texture)
		end
		sp:flipY(true)
	end
	if file and device.platform ~= "mac" then
		canvas:saveToFile(file)
	end
	return sp, file
end

return display
