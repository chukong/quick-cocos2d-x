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
#include "SPContourData.h"
using namespace cocos2d;

namespace sp{

/*
 *  @brief  ContourSprite used to draw the contour of the display
 */
class ContourSprite : public CCSprite
{
public:
	static ContourSprite *create();
    
public:
	ContourSprite();
	~ContourSprite(void);
    
    virtual bool init();
    
    
    void addContourData(ContourData *_contourData);
    void addContourDataList(CCArray *_contourDataList);
    void removeContourData(ContourData *_contourData);
    
    
    /*
     *  @brief  set the draw line width
     */
    void setDrawLineWidth(float _width);
    
    /*
     *  @brief  get the draw line width
     */
    float getDrawLineWidth();
    
    /*
     *  @brief  set the draw line color
     */
    void setDrawLineColor( GLubyte r, GLubyte g, GLubyte b, GLubyte a );
    
    /*
     *  @brief  get the draw line color
     */
    ccColor4F getDrawLineColor();
    
    void draw();
    
    void update(float dt);
    
private:
    //! a contour list
    CCArray *m_pContourList;
    //! line width
    float m_fLineWidth;
    //! line color
    ccColor4F m_Color;
    
};
		

}
