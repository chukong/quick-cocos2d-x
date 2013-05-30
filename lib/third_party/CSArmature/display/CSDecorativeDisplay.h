/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
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

#ifndef COCOSTUDIO_DECORATIVEDISPLAY_H
#define COCOSTUDIO_DECORATIVEDISPLAY_H

#include "cocos2d.h"

#include "CSDisplayFactory.h"
#include "CSDatas.h"
#include "sigslot.h"


#if CS_DEBUG_FOR_EDIT
#include "CSContourPoints.h"
#endif

#if ENABLE_PHYSICS_DETECT
#include "CSColliderDetector.h"
#endif


namespace cs {

class CS_EXTERN DecorativeDisplay: public cocos2d::CCObject, public sigslot::has_slots<>
{
public:
	static DecorativeDisplay *create();
public:
	DecorativeDisplay(void);
	~DecorativeDisplay(void);

	virtual bool init();

protected:

	CC_SYNTHESIZE_RETAIN(cocos2d::CCNode*, m_pDisplay, Display);
	CC_SYNTHESIZE_RETAIN(DisplayData*, m_pDisplayData, DisplayData);
	
#if CS_DEBUG_FOR_EDIT
	CC_SYNTHESIZE_RETAIN(ContourPoints*, m_pContourPoints, ContourPoints);
	CC_SYNTHESIZE_RETAIN(CCTexture2DMutable*, m_pTextureMutable, TextureMutable);
#endif

#if ENABLE_PHYSICS_DETECT
	CC_SYNTHESIZE_RETAIN(ColliderDetector*, m_pColliderDetector, ColliderDetector);
#endif
public:
	void anchorPointChanged(float pointX, float pointY);
};

}

#endif