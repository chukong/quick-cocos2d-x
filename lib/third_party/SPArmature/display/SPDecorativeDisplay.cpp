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

#include "SPDecorativeDisplay.h"
#include "SPConstValue.h"

namespace sp{

    
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
    :m_pContourSprite(NULL)
    ,m_pTextureMutable(NULL)
    ,m_pDisplay(NULL)
    ,m_pDisplayData(NULL)
	,m_pContourPoints(NULL)
{
    
}


DecorativeDisplay::~DecorativeDisplay(void)
{
    if(NULL != m_pDisplay)
    {
        m_pDisplay->release();
    }
    
    m_pDisplay = NULL;
    
    if (NULL != m_pContourSprite)
    {
        m_pContourSprite->release();
    }
    
    m_pContourSprite = NULL;

	if (NULL != m_pContourPoints)
    {
        m_pContourPoints->release();
    }
    
    m_pContourPoints = NULL;
    
    if(NULL != m_pTextureMutable)
    {
        m_pTextureMutable->release();
    }
    
    m_pTextureMutable = NULL;
}
    
bool DecorativeDisplay::init()
{
    
    return true;
}

void DecorativeDisplay::setDisplay(CCObject *_display)
{
    if (NULL != m_pDisplay)
    {
        m_pDisplay->release();
    }
    
    m_pDisplay = _display;
    m_pDisplay->retain();
}
    
CCObject *DecorativeDisplay::getDisplay()
{
    return m_pDisplay;
}
    
void DecorativeDisplay::setContourSprite(ContourSprite *_contourSprite)
{
    if(m_pContourSprite != NULL)
    {
        m_pContourSprite->release();
    }
    
    m_pContourSprite = _contourSprite;
    m_pContourSprite->retain();
}
    
ContourSprite *DecorativeDisplay::getContourSprite()
{
    return m_pContourSprite;
}

void DecorativeDisplay::setContourPoints(ContourPoints *_contourPoints)
{
	if(m_pContourPoints != NULL)
    {
        m_pContourPoints->release();
    }
    
    m_pContourPoints = _contourPoints;
    m_pContourPoints->retain();
}

ContourPoints *DecorativeDisplay::getContourPoints()
{
	return m_pContourPoints;
}


void DecorativeDisplay::setDisplayData(DisplayData *_displayData)
{
    if(m_pDisplayData != NULL)
    {
        m_pDisplayData->release();
    }
    
    m_pDisplayData = _displayData;
//    
//    m_strDisplayName = _displayData->m_strDisplayName;
//    m_strImageName = _displayData->m_strImageName;
//    m_eDisplayType = _displayData->m_eDisplayType;
    
    m_pDisplayData->retain();
}

DisplayData *DecorativeDisplay::getDisplayData()
{
    return m_pDisplayData;
}
    
void DecorativeDisplay::setTextureMutable(CCTexture2DMutable *_texture2DMutable)
{
    if(m_pTextureMutable != NULL)
    {
        m_pTextureMutable->release();
    }
    
    m_pTextureMutable = _texture2DMutable;
    m_pTextureMutable->retain();
}

CCTexture2DMutable * DecorativeDisplay::getTextureMutable()
{
    return m_pTextureMutable;
}
    

}