
local display = {}

require(__FRAMEWORK_PACKAGE_NAME__ .. ".cocos2dx.CCNodeExtend")
require(__FRAMEWORK_PACKAGE_NAME__ .. ".cocos2dx.CCSceneExtend")
require(__FRAMEWORK_PACKAGE_NAME__ .. ".cocos2dx.CCSpriteExtend")
require(__FRAMEWORK_PACKAGE_NAME__ .. ".cocos2dx.CCLayerExtend")

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

local function checkScale(w, h)
    local scale = 1
    local wscale, hscale = w / CONFIG_SCREEN_WIDTH, h / CONFIG_SCREEN_HEIGHT
    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = wscale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH_PRIOR" then
        if wscale > hscale then
            scale = wscale
        else
            scale = hscale
        end
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = hscale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT_PRIOR" then
        if wscale < hscale then
            scale = wscale
        else
            scale = hscale
        end
    end
    return scale, wscale, hscale
end

local scale, wscale, hscale = 1, 1, 1
if type(CONFIG_SCREEN_AUTOSCALE) == "function" then
    CONFIG_SCREEN_AUTOSCALE(w, h)
    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, kResolutionNoBorder)
elseif CONFIG_SCREEN_AUTOSCALE then
    scale, wscale, hscale = checkScale(w, h)

    if type(CONFIG_RESOURCE_SIZE) == "table" then
        local selectedSize, lastSize
        for i, size in ipairs(CONFIG_RESOURCE_SIZE) do
            local maxContentScale = size.scale or 99999
            if scale <= maxContentScale then
                selectedSize = size
                break
            end
            lastSize = size
        end

        if not selectedSize and lastSize then selectedSize = lastSize end
        CCFileUtils:sharedFileUtils():addSearchPath(selectedSize.path)

        w = w / scale * selectedSize.scale
        h = h / scale * selectedSize.scale
        scale, wscale, hscale = checkScale(w, h)
    end

    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        CONFIG_SCREEN_HEIGHT = h / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH_PRIOR" then
        if wscale > hscale then
            CONFIG_SCREEN_HEIGHT = h / scale
        else
            CONFIG_SCREEN_WIDTH = w / scale
        end
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        CONFIG_SCREEN_WIDTH = w / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT_PRIOR" then
        if wscale < hscale then
            CONFIG_SCREEN_HEIGHT = h / scale
        else
            CONFIG_SCREEN_WIDTH = w / scale
        end
    else
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

function display.newNode()
    return CCNodeExtend.extend(CCNode:create())
end

function display.newClippingRegionNode(rect)
    return CCNodeExtend.extend(CCClippingRegionNode:create(rect))
end

function display.newSprite(filename, x, y)
    local t = typen(filename)
    if t == LUA_TUSERDATA then t = tolua.type(filename) end
    local sprite

    if not filename then
        sprite = CCSprite:create()
    elseif t == LUA_TSTRING then
        if string.byte(filename) == 35 then -- first char is #
            local frame = display.newSpriteFrame(string.sub(filename, 2))
            if frame then
                sprite = CCSprite:createWithSpriteFrame(frame)
            end
        else
            if display.TEXTURES_PIXEL_FORMAT[filename] then
                CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
                sprite = CCSprite:create(filename)
                CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            else
                sprite = CCSprite:create(filename)
            end
        end
    elseif t == "CCSpriteFrame" then
        sprite = CCSprite:createWithSpriteFrame(filename)
    else
        echoError("display.newSprite() - invalid filename value type")
        return
    end

    if sprite then
        CCSpriteExtend.extend(sprite)
        if x and y then sprite:setPosition(x, y) end
    else
        echoError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
    end

    return sprite
end

function display.newScale9Sprite(filename, x, y, size)
    local t = typen(filename)
    if t ~= LUA_TSTRING then
        echoError("display.newScale9Sprite() - invalid filename type")
        return
    end

    local sprite
    if string.byte(filename) == 35 then -- first char is #
        local frame = display.newSpriteFrame(string.sub(filename, 2))
        if frame then
            sprite = CCScale9Sprite:createWithSpriteFrame(frame)
        end
    else
        if display.TEXTURES_PIXEL_FORMAT[filename] then
            CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
            sprite = CCScale9Sprite:create(filename)
            CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
        else
            sprite = CCScale9Sprite:create(filename)
        end
    end

    if sprite then
        CCSpriteExtend.extend(sprite)
        if x and y then sprite:setPosition(x, y) end
        if size then sprite:setContentSize(size) end
    else
        echoError("display.newScale9Sprite() - create sprite failure, filename %s", tostring(filename))
    end

    return sprite
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

function display.newCircle(radius)
    return CCNodeExtend.extend(CCCircleShape:create(radius))
end

function display.newRect(width, height)
    local x, y = 0, 0
    if typen(width) == LUA_TUSERDATA then
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
    rect:setPosition(x, y)
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

function display.addSpriteFramesWithFile(plistFilename, image)
    if display.TEXTURES_PIXEL_FORMAT[image] then
        CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
        CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    else
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
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
    if typen(image) == LUA_TSTRING then
        image = display.newSprite(image)
    end

    local progress = CCNodeExtend.extend(CCProgressTimer:create(image))
    progress:setType(progresssType)
    return progress
end

return display
