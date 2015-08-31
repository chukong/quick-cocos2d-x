-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp" "Cocos2d.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

local CCObjectTypes = {
    "CCAccelAmplitude",
    "CCAccelDeccelAmplitude",
    "CCAction",
    "CCActionCamera",
    "CCActionEase",
    "CCActionInstant",
    "CCActionInterval",
    "CCActionManager",
    "CCAnimate",
    "CCAnimation",
    "CCAnimationCache",
    "CCAnimationData",
    "CCAnimationFrame",
    "CCArmature",
    "CCArmatureAnimation",
    "CCArmatureData",
    "CCArmatureDataManager",
    "CCArmatureDisplayData",
    "CCArray",
    "CCAtlasNode",
    "CCBatchNode",
    "CCBezierBy",
    "CCBezierTo",
    "CCBlink",
    "CCBone",
    "CCBoneData",
    "CCBool",
    "CCCallFunc",
    "CCCallFuncN",
    "CCCamera",
    "CCCardinalSplineBy",
    "CCCardinalSplineTo",
    "CCCatmullRomBy",
    "CCCatmullRomTo",
    "CCCircleShape",
    "CCClippingNode",
    "CCClippingRegionNode",
    "CCComponent",
    "CCConfiguration",
    "CCControl",
    "CCControlButton",
    "CCControlColourPicker",
    "CCControlHuePicker",
    "CCControlPotentiometer",
    "CCControlSaturationBrightnessPicker",
    "CCControlSlider",
    "CCControlStepper",
    "CCControlSwitch",
    "CCDeccelAmplitude",
    "CCDelayTime",
    "CCDictionary",
    "CCDirector",
    "CCDisplayData",
    "CCDouble",
    "CCDrawNode",
    "CCEaseBackIn",
    "CCEaseBackInOut",
    "CCEaseBackOut",
    "CCEaseBounce",
    "CCEaseBounceIn",
    "CCEaseBounceInOut",
    "CCEaseBounceOut",
    "CCEaseElastic",
    "CCEaseElasticIn",
    "CCEaseElasticInOut",
    "CCEaseElasticOut",
    "CCEaseExponentialIn",
    "CCEaseExponentialInOut",
    "CCEaseExponentialOut",
    "CCEaseIn",
    "CCEaseInOut",
    "CCEaseOut",
    "CCEaseRateAction",
    "CCEaseSineIn",
    "CCEaseSineInOut",
    "CCEaseSineOut",
    "CCEditBox",
    "CCFadeIn",
    "CCFadeOut",
    "CCFadeOutBLTiles",
    "CCFadeOutDownTiles",
    "CCFadeOutTRTiles",
    "CCFadeOutUpTiles",
    "CCFadeTo",
    "CCFiniteTimeAction",
    "CCFlipX",
    "CCFlipX3D",
    "CCFlipY",
    "CCFlipY3D",
    "CCFloat",
    "CCFollow",
    "CCFrameData",
    "CCGLProgram",
    "CCGraySprite",
    "CCGrid3DAction",
    "CCGridAction",
    "CCGridBase",
    "CCHide",
    "CCImage",
    "CCInteger",
    "CCJumpBy",
    "CCJumpTiles3D",
    "CCJumpTo",
    "CCKeypadDispatcher",
    "CCLabelAtlas",
    "CCLabelBMFont",
    "CCLabelTTF",
    "CCLayer",
    "CCLayerColor",
    "CCLayerGradient",
    "CCLayerMultiplex",
    "CCLens3D",
    "CCLinkPosition",
    "CCLiquid",
    "CCMenu",
    "CCMenuItem",
    "CCMenuItemAtlasFont",
    "CCMenuItemFont",
    "CCMenuItemImage",
    "CCMenuItemLabel",
    "CCMenuItemSprite",
    "CCMenuItemToggle",
    "CCMotionStreak",
    "CCMoveBy",
    "CCMovementBoneData",
    "CCMovementData",
    "CCMoveTo",
    "CCNode",
    "CCNotificationCenter",
    "CCObject",
    "CCOrbitCamera",
    "CCPageTurn3D",
    "CCParallaxNode",
    "CCParticleBatchNode",
    "CCParticleDisplayData",
    "CCParticleExplosion",
    "CCParticleFire",
    "CCParticleFireworks",
    "CCParticleFlower",
    "CCParticleGalaxy",
    "CCParticleMeteor",
    "CCParticleRain",
    "CCParticleSmoke",
    "CCParticleSnow",
    "CCParticleSpiral",
    "CCParticleSun",
    "CCParticleSystem",
    "CCParticleSystemQuad",
    "CCPlace",
    "CCPointArray",
    "CCPointShape",
    "CCPolygonShape",
    "CCProfiler",
    "CCProfilingTimer",
    "CCProgressFromTo",
    "CCProgressTimer",
    "CCProgressTo",
    "CCRectShape",
    "CCRemoveSelf",
    "CCRenderTexture",
    "CCRepeat",
    "CCRepeatForever",
    "CCReuseGrid",
    "CCReverseTime",
    "CCRipple3D",
    "CCRotateBy",
    "CCRotateTo",
    "CCScale9Sprite",
    "CCScaleBy",
    "CCScaleTo",
    "CCScene",
    "CCScheduler",
    "CCScrollView",
    "CCSequence",
    "CCSet",
    "CCShaky3D",
    "CCShakyTiles3D",
    "CCShapeNode",
    "CCShatteredTiles3D",
    "CCShow",
    "CCShuffleTiles",
    "CCSkewBy",
    "CCSkewTo",
    "CCSpawn",
    "CCSpeed",
    "CCSplitCols",
    "CCSplitRows",
    "CCSprite",
    "CCSpriteBatchNode",
    "CCSpriteDisplayData",
    "CCSpriteFrame",
    "CCSpriteFrameCache",
    "CCStopGrid",
    "CCString",
    "CCTableView",
    "CCTableViewCell",
    "CCTargetedAction",
    "CCTextFieldTTF",
    "CCTexture2D",
    "CCTextureAtlas",
    "CCTextureCache",
    "CCTiledGrid3DAction",
    "CCTileMapAtlas",
    "CCTintBy",
    "CCTintTo",
    "CCTMXLayer",
    "CCTMXLayerInfo",
    "CCTMXMapInfo",
    "CCTMXObjectGroup",
    "CCTMXTiledMap",
    "CCTMXTilesetInfo",
    "CCToggleVisibility",
    "CCTouchDispatcher",
    "CCTransitionCrossFade",
    "CCTransitionFade",
    "CCTransitionFadeBL",
    "CCTransitionFadeDown",
    "CCTransitionFadeTR",
    "CCTransitionFadeUp",
    "CCTransitionFlipAngular",
    "CCTransitionFlipX",
    "CCTransitionFlipY",
    "CCTransitionJumpZoom",
    "CCTransitionMoveInB",
    "CCTransitionMoveInL",
    "CCTransitionMoveInR",
    "CCTransitionMoveInT",
    "CCTransitionPageTurn",
    "CCTransitionProgress",
    "CCTransitionProgressHorizontal",
    "CCTransitionProgressInOut",
    "CCTransitionProgressOutIn",
    "CCTransitionProgressRadialCCW",
    "CCTransitionProgressRadialCW",
    "CCTransitionProgressVertical",
    "CCTransitionRotoZoom",
    "CCTransitionScene",
    "CCTransitionSceneOriented",
    "CCTransitionShrinkGrow",
    "CCTransitionSlideInB",
    "CCTransitionSlideInL",
    "CCTransitionSlideInR",
    "CCTransitionSlideInT",
    "CCTransitionSplitCols",
    "CCTransitionSplitRows",
    "CCTransitionTurnOffTiles",
    "CCTransitionZoomFlipAngular",
    "CCTransitionZoomFlipX",
    "CCTransitionZoomFlipY",
    "CCTurnOffTiles",
    "CCTwirl",
    "CCWaves",
    "CCWaves3D",
    "CCWavesTiles3D",
}

-- register CCObject types
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]],
      [[/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

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
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;]])

    replace([[/* Exported function */
TOLUA_API int  tolua_Cocos2d_open (lua_State* tolua_S);]], [[]])

    replace([[*((LUA_FUNCTION*)]], [[(]])

    replace([[tolua_usertype(tolua_S,"LUA_FUNCTION");]], [[]])

    replace([[toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret]],
        [[int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret]])

    replace([[int tolua_ret = (int)  self->getFileData(pszFileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);]],
        [[unsigned long size = 0;
    unsigned char* buffer = self->getFileData(pszFileName, "rb", &size);
    if (buffer && size)
    {
        lua_pushlstring(tolua_S, (char*)buffer, size);
    }
    else
    {
        lua_pushnil(tolua_S);
    }
    if (buffer) delete[] buffer;]])

    replace([[int tolua_ret = (int)  self->getFileDataFromZip(pszZipFilePath,pszFileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);]],
        [[unsigned long size = 0;
    unsigned char* buffer = self->getFileDataFromZip(pszZipFilePath, pszFileName, &size);
    if (buffer && size)
    {
        lua_pushlstring(tolua_S, (char*)buffer, size);
    }
    else
    {
        lua_pushnil(tolua_S);
    }
    if (buffer) delete[] buffer;]])

    replace('\t', '    ')

    result = string.gsub(result,
        [[tolua_usertype%(tolua_S,"([%a%d]+)"%);]],
        [[tolua_usertype(tolua_S,"%1");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(%1)), "%1");]])

    WRITE(result)
end
