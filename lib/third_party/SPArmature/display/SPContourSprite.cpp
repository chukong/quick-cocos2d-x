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

#include "SPContourSprite.h"
#include "SPBatchNodeManager.h"

namespace sp{

ContourSprite *ContourSprite::create()
{
	ContourSprite *pContourSprite = new ContourSprite();
	if (pContourSprite && pContourSprite->init())
	{
		pContourSprite->autorelease();
		return pContourSprite;
	}
	CC_SAFE_DELETE(pContourSprite);
	return NULL;
}


ContourSprite::ContourSprite()
    :m_pContourList(NULL)
    ,m_fLineWidth(2)
    ,m_Color(ccc4f(0, 0, 255, 255))
{
}


ContourSprite::~ContourSprite()
{
    m_pContourList->removeAllObjects();
    CC_SAFE_DELETE(m_pContourList);
}
    
bool ContourSprite::init()
{
    m_pContourList = CCArray::create();
    CCAssert(m_pContourList, "create m_pContourList failed!");
    m_pContourList->retain();
    
    setVisible(false);
    
    return true;
}

void ContourSprite::addContourData(ContourData *_contourData)
{
    m_pContourList->addObject(_contourData);
}
    
void ContourSprite::addContourDataList(CCArray *_contourDataList)
{
    m_pContourList->addObjectsFromArray(_contourDataList);
}

void ContourSprite::removeContourData(ContourData *_contourData)
{
    m_pContourList->removeObject(_contourData);
}
    
void ContourSprite::setDrawLineWidth(float _width)
{
    m_fLineWidth = _width;
}


float ContourSprite::getDrawLineWidth()
{
    return m_fLineWidth;
}


void ContourSprite::setDrawLineColor( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
    m_Color = ccc4f(r, g, b, a);
}
    
ccColor4F ContourSprite::getDrawLineColor()
{
    return m_Color;
} 


void ContourSprite::update(float dt)
{
}
    
void ContourSprite::draw()
{
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pContourList, _object)
    {
        ContourData *_contourData = (ContourData*)_object;
        
        const CCArray *_vertexList = _contourData->getVertexList();
        
        int _length = _vertexList->data->num;
        CCPoint **x = (CCPoint**)_vertexList->data->arr;
        int _nextIndex = 0;
        
        for (int i=0; i<_length; i++)
        {
            _nextIndex = i+1;
            if (_nextIndex >= _length)
            {
                _nextIndex = 0;
            }
            
            ccDrawLine(*x[i], *x[_nextIndex]);
        }
    }
}
    

}