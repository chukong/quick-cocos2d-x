/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "cocos2d.h"
#include "SPFrameData.h"


using namespace cocos2d;

namespace sp{
    
class Bone;
class DecorativeDisplay;
class DisplayData;
    
/**
 *  @brief  DisplayType distinguish which type you display is.
 */
enum DisplayType{
    SP_DISPLAY_SPRITE,          //! display is a single CCSprite
    SP_DISPLAY_ARMATURE,        //! display is a Armature
    SP_DISPLAY_PARTICLE,        //! display is a CCParticle.
	SP_DISPLAY_SHADER,          //! display is a shader
    
    SP_DISPLAY_MAX
};



class DisplayFactory : public CCObject
{
public:
    virtual CCObject *addDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, DisplayData *_DisplayData) = 0;
    virtual CCObject *createDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay) = 0;

    virtual void changeDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay);
	virtual void updateDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, FrameData *_frameData);

	virtual void editAnchorPoint(CCPoint &p, Bone *_bone, DecorativeDisplay *_decoDisplay);
	
	virtual CCNode *getRenderNode(Bone *_bone, DecorativeDisplay *_decoDisplay);

	virtual float getWidth(Bone *_bone, DecorativeDisplay *_decoDisplay);
	virtual float getHeight(Bone *_bone, DecorativeDisplay *_decoDisplay);

	virtual CCRect getBoundingBox(Bone *_bone, DecorativeDisplay *_decoDisplay);
	virtual CCSize getContentSize(Bone *_bone, DecorativeDisplay *_decoDisplay);
    
    virtual CCPoint getAnchorPoint(Bone *_bone, DecorativeDisplay *_decoDisplay);
    virtual CCPoint getAnchorPointInPoints(Bone *_bone, DecorativeDisplay *_decoDisplay);

protected:
	virtual void setDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, CCNode *_renderNode);
	virtual void createContourPoints(Bone *_bone, DecorativeDisplay *_decoDisplay);
};
		

}
