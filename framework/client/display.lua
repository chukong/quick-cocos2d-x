
function ccsize(width, height)
    return CCSize(width, height)
end

local traceObject = traceObject

local display = {}

local director = CCDirector:sharedDirector()
display.director = director

local sharedTextureCache = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()

-- landscape, landscape_right
-- landscape_left
-- portrait
-- upside_down
display.orientationPortrait       = "portrait"
display.orientationUpsideDown     = "upside_down"
display.orientationLandscapeLeft  = "landscape_left"
display.orientationLandscapeRight = "landscape_right"

local orientation_
if not DEVICE_ORIENTATION then DEVICE_ORIENTATION = "portrait" end

orientation_ = string.lower(DEVICE_ORIENTATION)
if orientation_ == "landscape"
   or orientation_ == "landscape_right"
   or orientation_ == "landscaperight" then
    orientation_ = display.orientationLandscapeRight
elseif orientation_ == "landscape_left" or orientation_ == "landscapeleft" then
    orientation_ = display.orientationLandscapeLeft
elseif orientation_ == "upside_down" or orientation_ == "upsidedown" then
    orientation_ = display.orientationUpsideDown
else
    orientation_ = display.orientationPortrait
end
display.orientation = orientation_

local glview = director:getOpenGLView()
local size = glview:getFrameSize()
display.sizeInPixels = {width = size.width, height = size.height}

local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

local scale = 1
if CONFIG_SCREEN_AUTOSCALE then
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
    if CONFIG_SCREEN_AUTOSCALE == "FULLWIDTH" then
        scale = w / CONFIG_SCREEN_WIDTH;
        CONFIG_SCREEN_HEIGHT = h / scale;
    elseif CONFIG_SCREEN_AUTOSCALE == "FULLHEIGHT" then
        scale = h / CONFIG_SCREEN_HEIGHT;
        CONFIG_SCREEN_WIDTH = w / scale;
    elseif CONFIG_SCREEN_AUTOSCALE == "FULLHEIGHTONSMALLWIDTH" then
        if w < CONFIG_SCREEN_WIDTH then
            scale = w / CONFIG_SCREEN_WIDTH;
            CONFIG_SCREEN_HEIGHT = h / scale;
        else
            CONFIG_SCREEN_WIDTH = w
            CONFIG_SCREEN_HEIGHT = h
        end
    elseif CONFIG_SCREEN_AUTOSCALE == "FULLHEIGHTONSMALLSCREEN" then
        if h < CONFIG_SCREEN_HEIGHT then
            scale = h / CONFIG_SCREEN_HEIGHT;
            CONFIG_SCREEN_WIDTH = w / scale;
        else
            CONFIG_SCREEN_WIDTH = w
            CONFIG_SCREEN_HEIGHT = h
        end
    end

    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH,
                                   CONFIG_SCREEN_HEIGHT,
                                   kResolutionNoBorder)
end

local winSize = director:getWinSize()
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
display.cp_left            = display.c_left * scale
display.cp_right           = display.c_right * scale
display.cp_top             = display.c_top * scale
display.cp_bottom          = display.c_bottom * scale
display.left               = 0
display.right              = display.width
display.top                = display.height
display.bottom             = 0
display.widthInPixels      = display.sizeInPixels.width
display.heightInPixels     = display.sizeInPixels.height

echoWarning(format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
echoWarning(format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
echoWarning(format("# display.widthInPixels        = %0.2f", display.widthInPixels))
echoWarning(format("# display.heightInPixels       = %0.2f", display.heightInPixels))
echoWarning(format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
echoWarning(format("# display.orientation          = %s",    display.orientation))
echoWarning(format("# display.width                = %0.2f", display.width))
echoWarning(format("# display.height               = %0.2f", display.height))
echoWarning(format("# display.cx                   = %0.2f", display.cx))
echoWarning(format("# display.cy                   = %0.2f", display.cy))
echoWarning(format("# display.left                 = %0.2f", display.left))
echoWarning(format("# display.right                = %0.2f", display.right))
echoWarning(format("# display.top                  = %0.2f", display.top))
echoWarning(format("# display.bottom               = %0.2f", display.bottom))
echoWarning(format("# display.c_left               = %0.2f", display.c_left))
echoWarning(format("# display.c_right              = %0.2f", display.c_right))
echoWarning(format("# display.c_top                = %0.2f", display.c_top))
echoWarning(format("# display.c_bottom             = %0.2f", display.c_bottom))
echoWarning(format("# display.cp_left              = %0.2f", display.cp_left))
echoWarning(format("# display.cp_right             = %0.2f", display.cp_right))
echoWarning(format("# display.cp_top               = %0.2f", display.cp_top))
echoWarning(format("# display.cp_bottom            = %0.2f", display.cp_bottom))
echoWarning("#")

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

----------------------------------------
-- scenes
----------------------------------------

local SCENE_TRANSITIONS = {}
SCENE_TRANSITIONS["CROSSFADE"]       = {CCTransitionCrossFade, 2}
SCENE_TRANSITIONS["FADE"]            = {CCTransitionFade, 3, ccc3(0, 0, 0)}
SCENE_TRANSITIONS["FADEBL"]          = {CCTransitionFadeBL, 2}
SCENE_TRANSITIONS["FADEDOWN"]        = {CCTransitionFadeDown, 2}
SCENE_TRANSITIONS["FADETR"]          = {CCTransitionFadeTR, 2}
SCENE_TRANSITIONS["FADEUP"]          = {CCTransitionFadeUp, 2}

SCENE_TRANSITIONS["FLIPANGULAR"]     = {CCTransitionFlipAngular, 3, kOrientationLeftOver}
SCENE_TRANSITIONS["FLIPX"]           = {CCTransitionFlipX, 3, kOrientationLeftOver}
SCENE_TRANSITIONS["FLIPY"]           = {CCTransitionFlipY, 3, kOrientationUpOver}
SCENE_TRANSITIONS["ZOOMFLIPX"]       = {CCTransitionZoomFlipX, 3, kOrientationLeftOver}
SCENE_TRANSITIONS["ZOOMFLIPY"]       = {CCTransitionZoomFlipY, 3, kOrientationUpOver}

SCENE_TRANSITIONS["JUMPZOOM"]        = {CCTransitionJumpZoom, 2}
SCENE_TRANSITIONS["ROTOZOOM"]        = {CCTransitionRotoZoom, 2}

SCENE_TRANSITIONS["MOVEINB"]         = {CCTransitionMoveInB, 2}
SCENE_TRANSITIONS["MOVEINL"]         = {CCTransitionMoveInL, 2}
SCENE_TRANSITIONS["MOVEINR"]         = {CCTransitionMoveInR, 2}
SCENE_TRANSITIONS["MOVEINT"]         = {CCTransitionMoveInT, 2}

SCENE_TRANSITIONS["SLIDEINB"]        = {CCTransitionSlideInB, 2}
SCENE_TRANSITIONS["SLIDEINL"]        = {CCTransitionSlideInL, 2}
SCENE_TRANSITIONS["SLIDEINR"]        = {CCTransitionSlideInR, 2}
SCENE_TRANSITIONS["SLIDEINT"]        = {CCTransitionSlideInT, 2}

SCENE_TRANSITIONS["SHRINKGROW"]      = {CCTransitionShrinkGrow, 2}
SCENE_TRANSITIONS["SPLITCOLS"]       = {CCTransitionSplitCols, 2}
SCENE_TRANSITIONS["SPLITROWS"]       = {CCTransitionSplitRows, 2}
SCENE_TRANSITIONS["TURNOFFTILES"]    = {CCTransitionTurnOffTiles, 2}

SCENE_TRANSITIONS["SCENEORIENTED"]   = {CCTransitionSceneOriented, 3, kOrientationLeftOver}
SCENE_TRANSITIONS["ZOOMFLIPANGULAR"] = {CCTransitionZoomFlipAngular, 2}

SCENE_TRANSITIONS["PAGETURN"]        = {CCTransitionPageTurn, 3, false}
SCENE_TRANSITIONS["RADIALCCW"]       = {CCTransitionRadialCCW, 2}
SCENE_TRANSITIONS["RADIALCW"]        = {CCTransitionRadialCW, 2}

local function newSceneWithTransition(scene, transitionName, time, more)
    local key = string.upper(tostring(transitionName))
    if string.sub(key, 1, 12) == "CCTRANSITION" then
        key = string.sub(key, 13)
    end

    if SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(SCENE_TRANSITIONS[key])
        transitionTime = transitionTime or 0.2

        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end
    end
    return scene
end

function display.newScene(name)
    local scene = CCScene:create()
    scene.name = name or "<none-name>"
    scene.isTouchEnabled = false

    if DEBUG > 1 then traceObject(scene, format("Scene - %s", scene.name)) end
    return display.extendScene(scene)
end

function display.extendScene(scene)
    local function sceneEventHandler(event)
        if event.name == "enter" then
            echoWarning("## Scene \"%s:onEnter()\"", scene.name)
            scene.isTouchEnabled = true
            if scene.onEnter then scene:onEnter() end
        else
            echoWarning("## Scene \"%s:onExit()\"", scene.name)
            scene.isTouchEnabled = false
            if scene.onExit then scene:onExit() end
        end
    end

    scene:registerScriptHandler(sceneEventHandler)
    return scene
end

--[[--

replaces the running scene with a new one.

**Usage:**

    display.replaceScene(newScene, [transition mode, transition time, [more parameter] ])

**Example:**

    display.replaceScene(newScene)
    display.replaceScene(newScene, "crossFade", 0.5)
    display.replaceScene(newScene, "fade", 0.5, ccc3(255, 255, 255))

--]]
function display.replaceScene(nextScene, transition_, transitionTime, more)
    local current = director:getRunningScene()
    if current then
        scheduler.unscheduleAll()
        if current.beforeExit then current:beforeExit() end
        nextScene = newSceneWithTransition(nextScene, transition_, transitionTime, more)
        director:replaceScene(nextScene)
    else
        director:runWithScene(nextScene)
    end
end

function display.getRunningScene()
    return director:getRunningScene()
end

function display.pause()
    director:pause()
end

function display.resume()
    director:resume()
end


----------------------------------------
-- nodes
----------------------------------------

local ANCHOR_POINTS = {
    ccp(0.5, 0.5),  -- CENTER
    ccp(0, 1),      -- TOP_LEFT
    ccp(0.5, 1),    -- TOP_CENTER
    ccp(1, 1),      -- TOP_RIGHT
    ccp(0, 0.5),    -- CENTER_LEFT
    ccp(1, 0.5),    -- CENTER_RIGHT
    ccp(0, 0),      -- BOTTOM_LEFT
    ccp(1, 0),      -- BOTTOM_RIGHT
    ccp(0.5, 0),    -- BOTTOM_CENTER
}

function display.align(node, anchorPoint, x, y)
    node:setAnchorPoint(ANCHOR_POINTS[anchorPoint])
    node:setPosition(x, y)
end

function display.newLayer()
    local layer = display.extendLayer(display.extendNode(CCLayer:create()))
    if DEBUG > 1 then traceObject(layer, "Layer") end
    return layer
end

function display.newGroup()
    local group = display.extendNode(CCNode:create())
    if DEBUG > 1 then traceObject(group, "Group") end
    return group
end

function display.newSprite(filename, x, y)
    local sprite
    if string.sub(filename, 1, 1) == "#" then
        sprite = CCSprite:createWithSpriteFrameName(string.sub(filename, 2))
    else
        sprite = CCSprite:create(filename)
    end

    if sprite == nil then
        local msg = format("[display] ERR, newSprite() not found image: %s", filename)
        echo(debug.traceback(msg, 2))
        echo("")
        return nil
    end

    display.extendSprite(sprite)
    sprite:setPosition(x, y)

    if DEBUG > 1 then traceObject(sprite, format("Sprite - %s", filename)) end
    return sprite
end
display.newImage = display.newSprite

function display.newBackgroundSprite(filename)
    return display.newSprite(filename, display.cx, display.cy)
end
display.newBackgroundImage = display.newBackgroundSprite

function display.newBackgroundTilesSprite(filename)
    local rect = CCRectMake(0, 0, display.width, display.height)
    local sprite = CCSprite:create(filename, rect)
    if sprite == nil then
        local msg = format("[display] ERR, newSprite() not found image: %s", filename)
        echo(debug.traceback(msg, 2))
        echo("")
        return nil
    end

    local tp = ccTexParams()
    tp.minFilter = 9729
    tp.magFilter = 9729
    tp.wrapS = 10497
    tp.wrapT = 10497
    sprite:getTexture():setTexParameters(tp)

    display.extendSprite(sprite)
    sprite:align(display.LEFT_BOTTOM, 0, 0)

    if DEBUG > 1 then traceObject(sprite, format("Sprite - %s", filename)) end
    return sprite
end
display.newBackgroundTilesImage = display.newBackgroundTilesSprite

function display.newCircle(radius, segments)
    if type(segments) ~= "number" then segments = 36 end
    local shape = display.extendShape(CCCircleShape:create(radius, 0, segments))
    if DEBUG > 1 then traceObject(shape, "CircleShape") end
    return shape
end

function display.newRect(width, height)
    local shape = display.extendShape(CCRectShape:create(CCSize(width, height)))
    if DEBUG > 1 then traceObject(shape, "RectShape") end
    return shape
end

function display.newPolygon(points, scale)
    if type(scale) ~= "number" then scale = 1 end
    local arr = CCArray:create()
    for i, p in ipairs(points) do
        p = ccp(p[1] * scale, p[2] * scale)
        p:autorelease()
        arr:addObject(p)
    end
    arr:retain() -- TODO: memory leaks ?!?
    local shape = CCPolygonShape:create(arr)
    display.extendShape(shape)
    if DEBUG > 1 then traceObject(shape, "PolygonShape") end
    return shape
end

display.sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()
function display.addSpriteFramesWithFile(plistFilename, image)
    display.sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
end

function display.removeSpriteFramesWithFile(plistFilename, image)
    display.sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
end

function display.newBatchNode(image, capacity)
    capacity = capacity or 29
    local node
    if type(image) == "string" then
        node = CCSpriteBatchNode:create(image, capacity)
    else
        node = CCSpriteBatchNode:create(image, capacity)
    end
    if DEBUG > 1 then traceObject(node, "BatchNode") end
    return display.extendNode(node)
end

function display.newSpriteFrame(frameName)
    local frame = sharedSpriteFrameCache:spriteFrameByName(frameName)
    if DEBUG > 1 then traceObject(frame, format("SpriteFrame - %s", frameName)) end
    return frame
end

function display.newSpriteWithFrame(frame, x, y)
    if not frame then
        traceback()
    end
    local sprite = CCSprite:createWithSpriteFrame(frame)
    display.extendSprite(sprite)
    sprite:setPosition(x, y)
    if DEBUG > 1 then traceObject(sprite, "Sprite") end
    return sprite
end

local floor = math.floor
local function round(num)
    return floor(num + 0.5)
end

function display.pixels(x, y)
    local scale = 1 / display.contentScaleFactor
    if x then x = round(x / scale) * scale end
    if y then y = round(y / scale) * scale end
    return x, y
end

--[[--

create multiple frames by pattern

**Usage:**

    display.newFrames(pattern, begin, length)

**Example:**

    -- create array [walk_01.png -> walk_20.png]
    display.addSpriteFramesWithFile("walk.plist", "walk.png")
    local frames = display.newFrames("walk_%02d.png", 1, 20)

]]
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
        if not frame then error("Invalid frame") end
        if DEBUG > 1 then traceObject(frame, format("SpriteFrame - %s", frameName)) end
        frames[#frames + 1] = frame
    end
    return frames
end

--[[--

create animation

**Usage:**

    display.newAnimation(frames, time)

**Example:**

    local frames    = display.newFrames("walk_%02d.png", 1, 20)
    local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames

]]
function display.newAnimation(frames, time)
    local count = #frames
    local array = CCArray:create()
    for i = 1, count do
        array:addObject(frames[i])
    end
    time = time or 1.0 / count
    local animation = CCAnimation:createWithSpriteFrames(array, time)
    if DEBUG > 1 then traceObject(animation, "Animation") end
    return animation
end

--[[

create animate

**Usage:**

    display.newAnimate(animation, isRestoreOriginalFrame)

**Example:**

    local frames = display.newFrames("walk_%02d.png", 1, 20)
    local sprite = display.newSpriteWithFrame(frames[1])

    local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames
    local animate = display.newAnimate(animation)

]]
function display.newAnimate(animation, isRestoreOriginalFrame)
    if type(isRestoreOriginalFrame) ~= "boolean" then isRestoreOriginalFrame = false end
    local animate = CCAnimate:create(animation)
    if DEBUG > 1 then traceObject(animate, "Animate") end
    return animate
end

----------------------------------------
-- binding
----------------------------------------

function display.extendNode(node)
    node.removeFromParentAndCleanup_ = node.removeFromParentAndCleanup
    function node:removeFromParentAndCleanup(isCleanup)
        if type(isCleanup) ~= "boolean" then isCleanup = true end
        self:removeFromParentAndCleanup_(isCleanup)
    end

    node.setPosition_ = node.setPosition
    function node:setPosition(x, y)
        if type(x) == "number" and type(y) == "number" then
            node:setPosition_(x, y)
        end
    end

    function node:removeSelf(isCleanup)
        self:removeFromParentAndCleanup(isCleanup)
    end

    function node:align(anchorPoint, x, y)
        display.align(self, anchorPoint, x, y)
    end

    function node:pixels()
        local x, y = node:getPosition()
        node:setPosition(display.pixels(x, y))
    end

    node.insert = node.addChild

    return node
end

function display.extendLayer(node)
    function node:addTouchEventListener(listener, isMultiTouches, priority, swallowsTouches)
        if type(isMultiTouches) ~= "boolean" then isMultiTouches = false end
        if type(priority) ~= "number" then priority = 0 end
        if type(swallowsTouches) ~= "boolean" then swallowsTouches = false end
        self:registerScriptTouchHandler(listener, isMultiTouches, priority, swallowsTouches)
    end

    function node:removeTouchEventListener()
        self:unregisterScriptTouchHandler()
    end

    return node
end

function display.extendSprite(node)
    display.extendNode(node)

    function node:playAnimationOnce(animation, removeWhenFinished, onComplete)
        local animate = display.newAnimate(animation)
        if removeWhenFinished or onComplete then
            self:runAction(transition.sequence({
                animate,
                CCCallFunc:create(function()
                    if removeWhenFinished then
                        self:removeFromParentAndCleanup(true)
                    end
                    if type(onComplete) == "function" then
                        onComplete()
                    end
                end)
            }))
        else
            self:runAction(animate)
        end
    end

    function node:playAnimationForever(animation, isRestoreOriginalFrame)
        local animate = display.newAnimate(animation, isRestoreOriginalFrame)
        self:runAction(CCRepeatForever:create(animate))
    end

    return node
end

function display.extendShape(shape)
    shape = display.extendNode(shape)
    shape.setColor_ = shape.setColor

    function shape:setColor(r, g, b, a)
        r, g, b = _i(r), _i(g), _i(b)
        if type(a) ~= "number" then a = 255 end
        shape:setColor_(ccc4f(r / 255, g / 255, b / 255, a / 255))
    end

    return shape
end

return display
