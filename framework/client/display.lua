--[[

Copyright (c) 2011-2012 qeeplay.com

http://dualface.github.com/quick-cocos2d-x/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

The display module provides access to cocos2d-x core features.

-   Query display screen information.
-   Mange scenes.
-   Creates display objects.

]]

local display = {}

require("framework.client.cocos2dx.CCNodeExtend")
require("framework.client.cocos2dx.CCSpriteExtend")
require("framework.client.cocos2dx.CCLayerExtend")
require("framework.client.cocos2dx.CCSceneExtend")
require("framework.client.cocos2dx.CCShapeNodeExtend")

local sharedDirector         = CCDirector:sharedDirector()
local sharedTextureCache     = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()

-- check device screen size
local glview = sharedDirector:getOpenGLView()
local size = glview:getFrameSize()
display.sizeInPixels = {width = size.width, height = size.height}

local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

local scale = 1
if CONFIG_SCREEN_AUTOSCALE then
    -- set auto scale
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = w / CONFIG_SCREEN_WIDTH;
        CONFIG_SCREEN_HEIGHT = h / scale;
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = h / CONFIG_SCREEN_HEIGHT;
        CONFIG_SCREEN_WIDTH = w / scale;
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT_ON_SMALL_SCREEN" then
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

echoInfo(format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
echoInfo(format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
echoInfo(format("# display.widthInPixels        = %0.2f", display.widthInPixels))
echoInfo(format("# display.heightInPixels       = %0.2f", display.heightInPixels))
echoInfo(format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
echoInfo(format("# display.width                = %0.2f", display.width))
echoInfo(format("# display.height               = %0.2f", display.height))
echoInfo(format("# display.cx                   = %0.2f", display.cx))
echoInfo(format("# display.cy                   = %0.2f", display.cy))
echoInfo(format("# display.left                 = %0.2f", display.left))
echoInfo(format("# display.right                = %0.2f", display.right))
echoInfo(format("# display.top                  = %0.2f", display.top))
echoInfo(format("# display.bottom               = %0.2f", display.bottom))
echoInfo(format("# display.c_left               = %0.2f", display.c_left))
echoInfo(format("# display.c_right              = %0.2f", display.c_right))
echoInfo(format("# display.c_top                = %0.2f", display.c_top))
echoInfo(format("# display.c_bottom             = %0.2f", display.c_bottom))
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

--[[--

]]
function display.setTexturePixelFormat(filename, format)
    display.TEXTURES_PIXEL_FORMAT[filename] = format
end

--[[--

Creates a scene.

A scene (implemented with the CCScene object) is more or less an independent piece of the app workflow. Some people may call them “screens” or “stages”. Your app can have many scenes, but only one of them is active at a given time.

### Example:

    local scene = display.newScene("HelloScene")
    display.replaceScene(scene) -- setup running scene

### Parameters:

-   [_optional string **name**_] name of scene

### Returns:

-   CCScene

]]
function display.newScene(name)
    local scene = CCSceneExtend.extend(CCScene:create())
    scene.name = name or "<unknown-scene>"
    return scene
end

--[[--

]]
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

--[[--

Replaces the running scene with a new one.

### Example:

    display.replaceScene(scene1)
    display.replaceScene(scene2, "CROSSFADE", 0.5)
    display.replaceScene(scene3, "FADE", 0.5, ccc3(255, 255, 255))

### Parameters:

-   CCScene **newScene** scene of want to display

-   [_optional string **transitionType**_] is one of the following:

    Transition Type             | Note
    --------------------------- | -------------------
    CROSSFADE       | Cross fades two scenes using the CCRenderTexture object
    FADE            | Fade out the outgoing scene and then fade in the incoming scene
    FADEBL          | Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner
    FADEDOWN        | Fade the tiles of the outgoing scene from the top to the bottom
    FADETR          | Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner
    FADEUP          | Fade the tiles of the outgoing scene from the bottom to the top
    FLIPANGULAR     | Flips the screen half horizontally and half vertically
    FLIPX           | Flips the screen horizontally
    FLIPY           | Flips the screen vertically
    JUMPZOOM        | Zoom out and jump the outgoing scene, and then jump and zoom in the incoming
    MOVEINB         | Move in from to the bottom the incoming scene
    MOVEINL         | Move in from to the left the incoming scene
    MOVEINR         | Move in from to the right the incoming scene
    MOVEINT         | Move in from to the top the incoming scene
    PAGETURN        | A transition which peels back the bottom right hand corner of a scene to transition to the scene beneath it simulating a page turn
    ROTOZOOM        | Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming
    SHRINKGROW      | Shrink the outgoing scene while grow the incoming scene
    SLIDEINB        | Slide in the incoming scene from the bottom border
    SLIDEINL        | Slide in the incoming scene from the left border
    SLIDEINR        | Slide in the incoming scene from the right border
    SLIDEINT        | Slide in the incoming scene from the top border
    SPLITCOLS       | The odd columns goes upwards while the even columns goes downwards
    SPLITROWS       | The odd rows goes to the left while the even rows goes to the right
    TURNOFFTILES    | Turn off the tiles of the outgoing scene in random order
    ZOOMFLIPANGULAR | Flips the screen half horizontally and half vertically doing a little zooming out/in
    ZOOMFLIPX       | Flips the screen horizontally doing a zoom out/in The front face is the outgoing scene and the back face is the incoming scene
    ZOOMFLIPY       | Flips the screen vertically doing a little zooming out/in The front face is the outgoing scene and the back face is the incoming scene

-   [_optional float **time**_] duration of the transition

-   [_optional mixed **more**_] parameter for the transition

]]
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

--[[--

Get current running scene.

### Returns:

-   CCScene

]]
function display.getRunningScene()
    return sharedDirector:getRunningScene()
end

--[[--

Pauses the running scene.

]]
function display.pause()
    sharedDirector:pause()
end

--[[--

Resumes the paused scene.

]]
function display.resume()
    sharedDirector:resume()
end

--[[--

Creates CCLayer object.

CCLayer is a subclass of CCNode. all features from CCNode are valid, plus the following new features:

-   It can receive touches
-   It can receive Accelerometer input
-   It can receive device hardward keypad input

### Example:

    local function onTouch(event, x, y)
        printf("touch %s, x = %0.2f, y = %0.2f", event, x, y)
    end

    local layer = display.newLayer()
    layer:addTouchEventListener(onTouch)
    layer:setTouchEnabled(true)

### Returns:

-   CCLayer

]]
function display.newLayer()
    return CCLayerExtend.extend(CCLayer:create())
end

--[[--

Creates a node object.

Anything thats gets drawn or contains things that get drawn is a CCNode. The most popular CCNodes are: CCScene, CCLayer, CCSprite, CCMenu.

A CCNode is a "void" object. It doesn't have a texture

The main features of a CCNode are:

-   They can contain other CCNode nodes (addChild, getChildByTag, removeChild, etc)
-   They can schedule periodic callback (schedule, unschedule, etc)
-   They can execute actions (runAction, stopAction, etc)

Features of CCNode:

-   position
-   scale (x, y)
-   rotation (in degrees, clockwise)
-   CCGridBase (to do mesh transformations)
-   anchor point
-   size
-   visible
-   z-order

### Example:

    local group = display.newNode()     -- create container
    group:addChild(sprite1)             -- add sprites to container
    group:addChild(sprite2)             -- add sprites to container
    transition.moveBy(group, {time = 2.0, x = 100})

### Returns:

-   CCNode

]]
function display.newNode()
    return CCNodeExtend.extend(CCNode:create())
end

--[[--

Creates a CCSprite object.

CCSprite can be created with an image, or with a sprite frame.

### Example:

    -- create with an image
    local sprite1 = display.newSprite("hello1.png")

    -- create with a sprite frame
    local sprite2 = display.newSprite("#frame0001.png")

### Parameters:

-   string **filename** image filename or sprite frame name. sprite frame name have prefix character '#'.

-   [_optional float **x**, float **y**_] initial position or the sprite

### Returns:

-   CCSprite

]]
function display.newSprite(filename, x, y)
    local sprite, autoCleanupFilename
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
        autoCleanupFilename = filename
    end

    if sprite then
        CCSpriteExtend.extend(sprite)
        if x and y then sprite:setPosition(x, y) end
        if autoCleanupFilename then
            sprite.IMAGE_FILENAME = autoCleanupFilename
        end
    else
        echoError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
    end

    return sprite
end

--[[--

Creates a sprite, set position to screen center.

### Parameters:

-   string **filename** image filename or sprite frame name.

### Returns:

-   CCSprite

]]
function display.newBackgroundSprite(filename)
    return display.newSprite(filename, display.cx, display.cy)
end

--[[--

Creates a sprite, repeat sprite's texture to fill whole rect.

### Parameters:

-   string **filename** image filename or sprite frame name.

### Returns:

-   CCSprite

]]
function display.newBackgroundTilesSprite(filename)
    local rect = CCRectMake(0, 0, display.width, display.height)
    local sprite = CCSprite:create(filename, rect)
    if not sprite then
        echoError("display.newBackgroundTilesSprite() - create sprite failure, filename %s", tostring(filename))
        return
    end

    local tp = ccTexParams()
    tp.minFilter = 9729
    tp.magFilter = 9729
    tp.wrapS = 10497
    tp.wrapT = 10497
    sprite:getTexture():setTexParameters(tp)

    display.align(sprite, display.LEFT_BOTTOM, 0, 0)

    return sprite
end

--[[--

Creates a CCCircleShape object, draw a circle on screen.

CCCircleShape is a subclass of CCShapeNode.

CCShapeNode is a subclass of CCNode. all features from CCNode are valid, plus the following new features:

-   draw shape to screen
-   set shape line color
-   set shape line width

CCShapeNode have the following new methods:

-   ccColor4F getColor()
-   setColor(ccColor4F color)
-   int getLineWidth()
-   setLineWidth(int width)

CCCircleShape have the following new methods:

-   float getRadius()
-   setRadius(float radius)
-   float getAngle()
-   setAngle(float angle)
-   int getSegments()
-   setSegments(int segments)
-   bool isDrawLineToCenter()
-   setDrawLineToCenter(bool drawLineToCenter)
-   float getScaleX()
-   setScaleX(float scaleX)
-   float getScaleY()
-   setScaleY(float scaleY)

### Example:

    local circle = display.newCircle(100) -- raidus = 100 points
    circle:setColor(255, 255, 255)        -- RGB = 0xffffff, white color
    circle:setSegments(128)               -- more segments appear smoother, default 32
    circle:setScaleY(0.8)                 -- Draw an ellipse

### Parameters:

-   float **radius**

### Returns:

-   CCCircleShape

]]
function display.newCircle(radius)
    return CCShapeNodeExtend.extend(CCCircleShape:create(radius))
end

--[[--

Creates a CCRectShape object, draw a rectangle on screen.

CCRectShape is a subclass of CCShapeNode, see [display.newCircle()](#anchor_display_newCircle) .

CCRectShape have the following new methods:

-   setSize(const CCSize& size)
-   bool isFill()
-   setFill(bool isFill)

### Example:

    local rect = display.newRect(200, 100)
    rect:setFill(true)

### Parameters:

-   float **width**, float **height** size of rectangle

### Returns:

-   CCRectShape

]]
function display.newRect(width, height)
    return CCShapeNodeExtend.extend(CCRectShape:create(CCSize(width, height)))
end

--[[--

Creates a CCPolygon object, draw a polygon on screen.

CCPolygon is a subclass of CCShapeNode, see [display.newCircle()](#anchor_display_newCircle) .

CCPolygon have the following new methods:

-   bool isFill()
-   setFill(bool isFill)
-   bool isClose()
-   setClose(bool isClose)

### Example:

    local points = {
        {10, 10},  -- point 1
        {50, 50},  -- point 2
        {100, 10}, -- point 3
    }
    local polygon = display.newPolygon(points) -- draw a triangle
    polygon:setClose(true) -- draw line from last point to first point

### Parameters:

-   table **points** array of points

-   [_optional float **scale**_]

### Returns:

-   CCPolygonShape

]]
function display.newPolygon(points, scale)
    if type(scale) ~= "number" then scale = 1 end
    local arr = CCPointArray:create(#points)
    for i, p in ipairs(points) do
        p = ccp(p[1] * scale, p[2] * scale)
        arr:add(p)
    end

    return CCShapeNodeExtend.extend(CCPolygonShape:create(arr))
end

--[[--

]]
function display.align(target, anchorPoint, x, y)
    target:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then target:setPosition(x, y) end
end

local round = math.round

--[[--

]]
function display.pixels(x, y)
    local scale = 1 / display.contentScaleFactor
    if x then x = round(x / scale) * scale end
    if y then y = round(y / scale) * scale end
    return x, y
end

--[[--

Adds multiple Sprite Frames from image and plist file.

Creates sprite sheet tools:

-   [Texture Packer](http://www.codeandweb.com/texturepacker)
-   [Zwoptex](http://www.zwopple.com/zwoptex/)

### Example:

    display.addSpriteFramesWithFile("sprites.plist", "sprites.png")
    local sprite1 = display.newSprite("#sprite0001.png")

### Parameters:

-   string **plistFilename** filename of plist file

-   string **image** filename of image

]]
function display.addSpriteFramesWithFile(plistFilename, image)
    if display.TEXTURES_PIXEL_FORMAT[image] then
        CCTexture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
        CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    else
        sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
    end
end

--[[--

Removes multiple Sprite Frames from a plist file.

Sprite Frames stored in this file will be removed. It is convinient to call this method when a specific texture needs to be removed.

### Parameters:

-   string **plistFilename** filename of plist file

]]
function display.removeSpriteFramesWithFile(plistFilename, imageName)
    sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
    if imageName then
        display.removeSpriteFrameByImageName(imageName)
    end
end

--[[--

]]
function display.removeSpriteFrameByImageName(imageName)
    sharedSpriteFrameCache:removeSpriteFrameByName(imageName)
    CCTextureCache:sharedTextureCache():removeTextureForKey(imageName)
end

--[[--

Creates CCSpriteBatchNode object from an image.

CCSpriteBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call (often known as "batch draw").

A CCSpriteBatchNode can reference one and only one texture (one image file, one texture atlas). Only the CCSprites that are contained in that texture can be added to the CCSpriteBatchNode. All CCSprites added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call. If the CCSprites are not added to a CCSpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.

Limitations:

-   The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is CCSprite or any subclass of CCSprite. eg: particles, labels and layer can't be added to a CCSpriteBatchNode.
-   Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.

### Example:

    local imageName = "sprites.png"
    display.addSpriteFramesWithFile("sprites.plist", imageName) -- load sprite frames

    -- it will draw them in 1 single OpenGL call
    local batch = display.newBatch(imageName)
    for i = 1, 100 do
        local sprite = display.newSprite("#sprite0001.png")
        batch:addChild(sprite)
    end

    --

    -- it will draw them use 100 OpenGL call
    local group = display.newNode()
    for i = 1, 100 do
        local sprite = display.newSprite("#sprite0001.png")
        group:addChild(sprite)
    end

### Parameters:

-   string **image** filename of image

-   [_optional int **capacity**_] estimated capacity of batch

### Returns:

-   CCSpriteBatchNode

]]
function display.newBatchNode(image, capacity)
    return CCNodeExtend.extend(CCSpriteBatchNode:create(image, capacity or 29))
end

--[[--

Returns an Sprite Frame that was previously added.

### Example:

    display.addSpriteFramesWithFile("sprites.plist", "sprites.png")
    local sprite = display.newSprite("#sprite0001")

    local frame2 = display.newSpriteFrame("sprite0002.png")
    local frame3 = display.newSpriteFrame("sprite0003.png")

    ....

    sprite:setDisplayFrame(frame2)  -- change sprite texture without recreate
    -- or
    sprite:setDisplayFrame(frame3)

### Parameters:

-   string **frameName** name of sprite frame, without prefix character '#'.

### Returns:

-   CCSpriteFrame

]]
function display.newSpriteFrame(frameName)
    local frame = sharedSpriteFrameCache:spriteFrameByName(frameName)
    if not frame then
        echoError("display.newSpriteFrame() - invalid frame, name %s", tostring(frameName))
    end
    return frame
end

--[[--



### Example:

### Parameters:

### Returns:

]]
function display.newSpriteWithFrame(frame, x, y)
    local sprite = CCSprite:createWithSpriteFrame(frame)
    if sprite then CCSpriteExtend.extend(sprite) end
    if x and y then sprite:setPosition(x, y) end
    return sprite
end

--[[--

Creates multiple frames by pattern.

### Example:

    -- create array of CCSpriteFrame [walk0001.png -> walk0020.png]
    local frames = display.newFrames("walk%04d.png", 1, 20)

### Parameters:

-   string **pattern**

-   int **begin**

-   int **length**

-   [_optional bool **isReversed**_]

### Returns:

-   table

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
        if not frame then
            echoError("display.newFrames() - invalid frame, name %s", tostring(frameName))
            return
        end

        frames[#frames + 1] = frame
    end
    return frames
end

--[[--

create animation

### Example:

    display.newAnimation(frames, time)

### Example:

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
    return CCAnimation:createWithSpriteFrames(array, time)
end

--[[

create animate

### Example:

    display.newAnimate(animation, isRestoreOriginalFrame)

### Example:

    local frames = display.newFrames("walk_%02d.png", 1, 20)
    local sprite = display.newSpriteWithFrame(frames[1])

    local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames
    local animate = display.newAnimate(animation)

]]
function display.newAnimate(animation)
    return CCAnimate:create(animation)
end

return display
