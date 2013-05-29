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

#ifndef SPII_SPContourPoints_h
#define SPII_SPContourPoints_h

#include "cocos2d.h"
#include "CCTexture2DMutable.h"

using namespace cocos2d;

namespace sp{
    
enum ContourPointType{
    POINT_MIN,
    
    POINT_LEFTDOWN,
    POINT_LEFTUP,
    POINT_RIGHTDOWN,
    POINT_RIGHTUP,
    POINT_CENTER,
    POINT_ROTATION,
    
    POINT_MAX
};
    
class  ContourPoints : public CCObject
{
private:
    cocos2d::CCNode* m_pRenderNode;
    
    cocos2d::CCSprite* m_pLeftUp;
    cocos2d::CCSprite* m_pRightUp;
    cocos2d::CCSprite* m_pLeftDown;
    cocos2d::CCSprite* m_pRightDown;
    cocos2d::CCSprite* m_pCenter;
    cocos2d::CCSprite* m_pRotation;
    

    float m_Height;
    float m_Width;

    const char* m_pPointFile;
    
    ContourPointType m_eContourPointType;
    
    cocos2d::CCPoint m_AnchorPoint;

    static CCTexture2DMutable *m_pTextureMutable;
public:
    ContourPoints( const char* file );
    ~ContourPoints();

    void setPointFile(const char* file);

    /**
    *	@brief set the position of each anchor point.
    *
    *	@param 	width 	width of the sprite.
    *	@param 	height 	height of the sprite.
    */
    void setSize(float width, float height );

    /**
    *	@brief set visibility of these anchor points.
    *
    *	@param 	isVisible 	is viible.
    */
    void setVisible( bool isVisible );

	bool isVisible();

    /**
    *	@brief whether clicked an anchor point.
    *
    *	@param  x x position
    *	@param  y y position
    *	@return return the index of the clicked anchor point.
    */
    int isClickAnchorPoint( float x, float y );

    cocos2d::CCNode* getRenderNode();

    //void setPositionWithoutCenter( float x, float y );

    void setBoundingBox(cocos2d::CCRect box);
    
    
    void scalePointPosition(float scaleX, float scaleY);
    
    ContourPointType containWorldPoint(cocos2d::CCPoint &point);
    
    ContourPointType getClickedPointType();
    
    void setAnchorPoint(cocos2d::CCPoint &p);
};


}

#endif