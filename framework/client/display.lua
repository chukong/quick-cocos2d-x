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

[BR]

**References:**

-   [cocos2d Programming Guide](http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:index)

]]

local display = {}

local sharedDirector         = CCDirector:sharedDirector()
local sharedTextureCache     = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()

-- check screen orientation
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

local SCENE_TRANSITIONS = {}

SCENE_TRANSITIONS["CROSSFADE"]       = {CCTransitionCrossFade, 2}
SCENE_TRANSITIONS["FADE"]            = {CCTransitionFade, 3, ccc3(0, 0, 0)}
SCENE_TRANSITIONS["FADEBL"]          = {CCTransitionFadeBL, 2}
SCENE_TRANSITIONS["FADEDOWN"]        = {CCTransitionFadeDown, 2}
SCENE_TRANSITIONS["FADETR"]          = {CCTransitionFadeTR, 2}
SCENE_TRANSITIONS["FADEUP"]          = {CCTransitionFadeUp, 2}
SCENE_TRANSITIONS["FLIPANGULAR"]     = {CCTransitionFlipAngular, 3, kCCTransitionOrientationLeftOver}
SCENE_TRANSITIONS["FLIPX"]           = {CCTransitionFlipX, 3, kCCTransitionOrientationLeftOver}
SCENE_TRANSITIONS["FLIPY"]           = {CCTransitionFlipY, 3, kCCTransitionOrientationUpOver}
SCENE_TRANSITIONS["JUMPZOOM"]        = {CCTransitionJumpZoom, 2}
SCENE_TRANSITIONS["MOVEINB"]         = {CCTransitionMoveInB, 2}
SCENE_TRANSITIONS["MOVEINL"]         = {CCTransitionMoveInL, 2}
SCENE_TRANSITIONS["MOVEINR"]         = {CCTransitionMoveInR, 2}
SCENE_TRANSITIONS["MOVEINT"]         = {CCTransitionMoveInT, 2}
SCENE_TRANSITIONS["PAGETURN"]        = {CCTransitionPageTurn, 3, false}
SCENE_TRANSITIONS["ROTOZOOM"]        = {CCTransitionRotoZoom, 2}
SCENE_TRANSITIONS["SHRINKGROW"]      = {CCTransitionShrinkGrow, 2}
SCENE_TRANSITIONS["SLIDEINB"]        = {CCTransitionSlideInB, 2}
SCENE_TRANSITIONS["SLIDEINL"]        = {CCTransitionSlideInL, 2}
SCENE_TRANSITIONS["SLIDEINR"]        = {CCTransitionSlideInR, 2}
SCENE_TRANSITIONS["SLIDEINT"]        = {CCTransitionSlideInT, 2}
SCENE_TRANSITIONS["SPLITCOLS"]       = {CCTransitionSplitCols, 2}
SCENE_TRANSITIONS["SPLITROWS"]       = {CCTransitionSplitRows, 2}
SCENE_TRANSITIONS["TURNOFFTILES"]    = {CCTransitionTurnOffTiles, 2}
SCENE_TRANSITIONS["ZOOMFLIPANGULAR"] = {CCTransitionZoomFlipAngular, 2}
SCENE_TRANSITIONS["ZOOMFLIPX"]       = {CCTransitionZoomFlipX, 3, kCCTransitionOrientationLeftOver}
SCENE_TRANSITIONS["ZOOMFLIPY"]       = {CCTransitionZoomFlipY, 3, kCCTransitionOrientationUpOver}

--[[--
@ignore
]]
local function newSceneWithTransition(scene, transitionName, time, more)
    local key = string.upper(tostring(transitionName))
    if string.sub(key, 1, 12) == "CCTRANSITION" then
        key = string.sub(key, 13)
    end

    if key == "RANDOM" then
        local keys = table.keys(SCENE_TRANSITIONS)
        key = keys[math.random(1, #keys)]
    end

    if SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(SCENE_TRANSITIONS[key])
        time = time or 0.2

        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end
    end
    return scene
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
    local scene = CCScene:create()
    scene.name = name or "<none-name>"
    scene.isTouchEnabled = false
    return display.extendScene(scene)
end

--[[--

Replaces the running scene with a new one.

### Example:

    display.replaceScene(scene1)
    display.replaceScene(scene2, "CCTransitionCrossFade", 0.5)
    display.replaceScene(scene3, "CCTransitionFade", 0.5, ccc3(255, 255, 255))

### Parameters:

-   CCScene **newScene** scene of want to display

-   [_optional string **transitionType**_] is one of the following:

    Transition Type             | Note
    --------------------------- | -------------------
    CCTransitionCrossFade       | Cross fades two scenes using the CCRenderTexture object
    CCTransitionFade            | Fade out the outgoing scene and then fade in the incoming scene
    CCTransitionFadeBL          | Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner
    CCTransitionFadeDown        | Fade the tiles of the outgoing scene from the top to the bottom
    CCTransitionFadeTR          | Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner
    CCTransitionFadeUp          | Fade the tiles of the outgoing scene from the bottom to the top
    CCTransitionFlipAngular     | Flips the screen half horizontally and half vertically
    CCTransitionFlipX           | Flips the screen horizontally
    CCTransitionFlipY           | Flips the screen vertically
    CCTransitionJumpZoom        | Zoom out and jump the outgoing scene, and then jump and zoom in the incoming
    CCTransitionMoveInB         | Move in from to the bottom the incoming scene
    CCTransitionMoveInL         | Move in from to the left the incoming scene
    CCTransitionMoveInR         | Move in from to the right the incoming scene
    CCTransitionMoveInT         | Move in from to the top the incoming scene
    CCTransitionPageTurn        | A transition which peels back the bottom right hand corner of a scene to transition to the scene beneath it simulating a page turn
    CCTransitionRotoZoom        | Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming
    CCTransitionShrinkGrow      | Shrink the outgoing scene while grow the incoming scene
    CCTransitionSlideInB        | Slide in the incoming scene from the bottom border
    CCTransitionSlideInL        | Slide in the incoming scene from the left border
    CCTransitionSlideInR        | Slide in the incoming scene from the right border
    CCTransitionSlideInT        | Slide in the incoming scene from the top border
    CCTransitionSplitCols       | The odd columns goes upwards while the even columns goes downwards
    CCTransitionSplitRows       | The odd rows goes to the left while the even rows goes to the right
    CCTransitionTurnOffTiles    | Turn off the tiles of the outgoing scene in random order
    CCTransitionZoomFlipAngular | Flips the screen half horizontally and half vertically doing a little zooming out/in
    CCTransitionZoomFlipX       | Flips the screen horizontally doing a zoom out/in The front face is the outgoing scene and the back face is the incoming scene
    CCTransitionZoomFlipY       | Flips the screen vertically doing a little zooming out/in The front face is the outgoing scene and the back face is the incoming scene

-   [_optional float **time**_]

-   [_optional mixed **more**_]

]]
function display.replaceScene(newScene, transitionType, time, more)
    local current = sharedDirector:getRunningScene()
    if current then
        if current.beforeExit then current:beforeExit() end
        newScene = newSceneWithTransition(newScene, transitionType, time, more)
        sharedDirector:replaceScene(newScene)
    else
        sharedDirector:runWithScene(newScene)
    end
end

--[[--

Get current running Scene.

### Returns:

-   CCScene

]]
function display.getRunningScene()
    return display.extendNode(sharedDirector:getRunningScene())
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

--[[--

Set node object anchorPoint and position.

### Example:

    display.align(sprite, display.LEFT_TOP, 100, 100)
    -- or
    sprite:align(display.LEFT_TOP, 100, 100)

### Parameters:

-   CCNode **node**

-   enum **anchorPoint** is one of the following:

    enum                                            | Value
    ----------------------------------------------- | ----------------------
    display.CENTER                                  | CCPoint(0.5, 0.5)
    display.TOP_LEFT,[BR]display.LEFT_TOP           | CCPoint(  0,   1)
    display.TOP_CENTER,[BR]display.CENTER_TOP       | CCPoint(0.5,   1)
    display.TOP_RIGHT,[BR]display.RIGHT_TOP         | CCPoint(  1,   1)
    display.CENTER_LEFT,[BR]display.LEFT_CENTER     | CCPoint(  0, 0.5)
    display.CENTER_RIGHT,[BR]display.RIGHT_CENTER   | CCPoint(  1, 0.5)
    display.BOTTOM_LEFT,[BR]display.LEFT_BOTTOM     | CCPoint(  0,   0)
    display.BOTTOM_RIGHT,[BR]display.RIGHT_BOTTOM   | CCPoint(  1,   0)
    display.BOTTOM_CENTER,[BR]display.CENTER_BOTTOM | CCPoint(0.5,   0)

-   [_optional float **x**, float **y**_]

]]
function display.align(node, anchorPoint, x, y)
    node:setAnchorPoint(ANCHOR_POINTS[anchorPoint])
    if x and y then node:setPosition(x, y) end
end

--[[--

Creates CCLayer object.

CCLayer is a subclass of CCNode. all features from CCNode are valid, plus the following new features:

-   It can receive touches
-   It can receive Accelerometer input
-   It can receive device hardward keypad input

CCLayer object created by display have more methods, see [display.extendLayer()](#anchor_display_extendLayer) .

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
    return display.extendLayer(display.extendNode(CCLayer:create()))
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

CCNode object created by display have more methods, see [display.extendNode()](#anchor_display_extendNode) .

### Example:

    local group = display.newNode()    -- create container
    group:addChild(sprite1)             -- add sprites to container
    group:addChild(sprite2)             -- add sprites to container
    transition.moveBy(group, {time = 2.0, x = 100})

### Returns:

-   CCNode

]]
function display.newNode()
    return display.extendNode(CCNode:create())
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

-   [_optional float **x**, float **y**_] sprite initial position

### Returns:

-   CCSprite

]]
function display.newSprite(filename, x, y)
    local sprite
    if string.byte(filename) == 35 then -- #
        local frame = display.newSpriteFrame(string.sub(filename, 2))
        if not frame then return end

        sprite = CCSprite:createWithSpriteFrame(frame)
    else
        sprite = CCSprite:create(filename)
        if not sprite then
            local msg = format("display.newSprite() - not found image: %s", filename)
            echo(debug.traceback(msg, 2))
            echo("")
            return
        end
    end

    display.extendSprite(sprite)
    sprite:setPosition(x, y)

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
    return display.extendShape(CCCircleShape:create(radius))
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
    return display.extendShape(CCRectShape:create(CCSize(width, height)))
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
    local arr = CCArray:create()
    for i, p in ipairs(points) do
        p = ccp(p[1] * scale, p[2] * scale)
        p:autorelease()
        arr:addObject(p)
    end
    arr:retain() -- TODO: memory leaks ?!?
    local shape = CCPolygonShape:create(arr)
    display.extendShape(shape)
    return shape
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
    sharedSpriteFrameCache:addSpriteFramesWithFile(plistFilename, image)
end

--[[--

Removes multiple Sprite Frames from a plist file.

Sprite Frames stored in this file will be removed. It is convinient to call this method when a specific texture needs to be removed.

### Parameters:

-   string **plistFilename** filename of plist file

]]
function display.removeSpriteFramesWithFile(plistFilename)
    sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
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
    capacity = capacity or 29
    local node
    if type(image) == "string" then
        node = CCSpriteBatchNode:create(image, capacity)
    else
        node = CCSpriteBatchNode:create(image, capacity)
    end
    return display.extendNode(node)
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
    if frame then return frame end

    local msg = format("display.newSpriteFrame() - not found sprite frame: %s", frameName)
    echo(debug.traceback(msg, 2))
    echo("")
end

--[[--



### Example:

### Parameters:

### Returns:

]]
function display.newSpriteWithFrame(frame, x, y)
    if not frame then
        echo(debug.traceback())
    end
    local sprite = CCSprite:createWithSpriteFrame(frame)
    display.extendSprite(sprite)
    sprite:setPosition(x, y)
    return sprite
end

local floor = math.floor
--[[--
@ignore
]]
local function round(num)
    return floor(num + 0.5)
end

--[[--

### Example:

### Parameters:

### Returns:

]]
function display.pixels(x, y)
    local scale = 1 / display.contentScaleFactor
    if x then x = round(x / scale) * scale end
    if y then y = round(y / scale) * scale end
    return x, y
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
        if not frame then error("Invalid frame") end
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
function display.newAnimate(animation, isRestoreOriginalFrame)
    if type(isRestoreOriginalFrame) ~= "boolean" then isRestoreOriginalFrame = false end
    return CCAnimate:create(animation)
end

----------------------------------------

--[[--

### Example:

### Parameters:

### Returns:

]]
function display.extendScene(scene)
    display.extendNode(scene)

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

### Example:

### Parameters:

### Returns:

]]
function display.extendNode(node)
    node.removeFromParentAndCleanup_ = node.removeFromParentAndCleanup
    function node:removeFromParentAndCleanup(isCleanup)
        if type(isCleanup) ~= "boolean" then isCleanup = true end
        if not tolua.isnull(self) then
            self:removeFromParentAndCleanup_(isCleanup)
        end
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

    function node:scheduleUpdate(callback, priority)
        node:scheduleUpdateWithPriorityLua(callback, _i(priority))
    end

    function node:schedule(callback, interval)
        local seq = transition.sequence({
            CCDelayTime:create(interval),
            CCCallFunc:create(callback),
        })
        local action = CCRepeatForever:create(seq)
        self:runAction(action)
        return action
    end

    function node:performWithDelay(callback, delay)
        local action = transition.sequence({
            CCDelayTime:create(delay),
            CCCallFunc:create(callback),
        })
        self:runAction(action)
        return action
    end

    function node:removeAction(action)
        transition.removeAction(action)
    end

    function node:stopAllActions()
        transition.stopTarget(self)
    end

    return node
end

--[[--

### Example:

### Parameters:

### Returns:

]]
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

-- --[[--

-- Create new layer, used for setting up Android hardware keys.

-- Note: This only works on Android devices (not iOS or simulators).

-- @param function callback
-- @return CCLayer

-- ]]
-- function device.newKeypadLayer(callback)
--     local keypadLayer = CCLayer:create()

--     keypadLayer:registerScriptKeypadHandler(function(keycode)
--         if keycode == kTypeBackClicked then
--             callback({target = keypadLayer, name = "keypad", key = "back"})
--         elseif keycode == kTypeMenuClicked then
--             callback({target = keypadLayer, name = "keypad", key = "menu"})
--         else
--             callback({target = keypadLayer, name = "keypad", key = keycode})
--         end
--     end)

--     function keypadLayer:enable()
--         keypadLayer:setKeypadEnabled(true)
--     end

--     function keypadLayer:disable()
--         keypadLayer:setKeypadEnabled(false)
--     end

--     return keypadLayer
-- end


    return node
end

--[[--

### Example:

### Parameters:

### Returns:

]]
function display.extendSprite(node)
    display.extendNode(node)

    function node:playAnimationOnce(animation, removeWhenFinished, onComplete, delay)
        local actions = {}
        if type(delay) == "number" and delay > 0 then
            self:setVisible(false)
            actions[#actions + 1] = CCDelayTime:create(delay)
            actions[#actions + 1] = CCShow:create()
        end

        actions[#actions + 1] = display.newAnimate(animation)

        if removeWhenFinished or onComplete then
            actions[#actions + 1] = CCCallFunc:create(function()
                if removeWhenFinished then
                    self:removeFromParentAndCleanup(true)
                end
                if type(onComplete) == "function" then
                    onComplete()
                end
            end)
        end

        local action
        if #actions > 1 then
            action = transition.sequence(actions)
        else
            action = actions[1]
        end
        self:runAction(action)
        return action
    end

    function node:playAnimationForever(animation, isRestoreOriginalFrame, delay)
        local animate = display.newAnimate(animation, isRestoreOriginalFrame)
        local action
        if type(delay) == "number" and delay > 0 then
            self:setVisible(false)
            local sequence = transition.sequence({
                CCDelayTime:create(delay),
                CCShow:create(),
                animate,
            })
            action = CCRepeatForever:create(sequence)
        else
            action = CCRepeatForever:create(animate)
        end
        self:runAction(action)
        return action
    end

    return node
end

--[[--

### Example:

### Parameters:

### Returns:

]]
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

--[[--

### Example:

### Parameters:

### Returns:

]]
function ccsize(width, height)
    return CCSize(width, height)
end

return display
