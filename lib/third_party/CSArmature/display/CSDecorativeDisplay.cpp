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

#include "CSDecorativeDisplay.h"
#include "CSConstValue.h"

namespace cs {


DecorativeDisplay *DecorativeDisplay::create()
{
	DecorativeDisplay *pDisplay = new DecorativeDisplay();
	if (pDisplay && pDisplay->init()){
		pDisplay->autorelease();
		return pDisplay;
	}
	CC_SAFE_DELETE(pDisplay);
	return NULL;
}

DecorativeDisplay::DecorativeDisplay()
	:m_pDisplay(NULL)
	,m_pDisplayData(NULL)

{
#if ENABLE_PHYSICS_DETECT
    m_pColliderDetector = NULL;
#endif

#if CS_DEBUG_FOR_EDIT
	m_pTextureMutable = NULL;
	m_pContourPoints = NULL;
#endif
}


DecorativeDisplay::~DecorativeDisplay(void)
{
	CC_SAFE_RELEASE_NULL(m_pDisplayData);
	CC_SAFE_RELEASE_NULL(m_pDisplay);
    
#if CS_DEBUG_FOR_EDIT
	CC_SAFE_RELEASE_NULL(m_pContourPoints);
	CC_SAFE_RELEASE_NULL(m_pTextureMutable);
#endif

#if ENABLE_PHYSICS_DETECT
	CC_SAFE_RELEASE_NULL(m_pColliderDetector);
#endif
}

bool DecorativeDisplay::init()
{
	return true;
}


void DecorativeDisplay::anchorPointChanged(float pointX, float pointY)
{
#if CS_DEBUG_FOR_EDIT
	if(m_pDisplay)
	{
		CCSprite *sprite = (CCSprite*)((CCNode*)m_pDisplay)->getChildByTag(0);
		sprite->setAnchorPoint(ccp(pointX, pointY));
	}
#endif
}

}