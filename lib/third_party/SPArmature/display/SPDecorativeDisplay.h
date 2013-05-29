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

#include "SPContourPoints.h"
#include "SPContourSprite.h"
#include "cocos2d.h"

#include "SPDisplayFactory.h"
#include "SPDisplayData.h"

using namespace cocos2d;

namespace sp{


class  DecorativeDisplay: public CCObject
{
public:
	static DecorativeDisplay *create();
public:
	DecorativeDisplay(void);
	~DecorativeDisplay(void);
    
    virtual bool init();
    
    
    void setDisplay(CCObject *_display);
    CCObject *getDisplay();
    
    void setContourSprite(ContourSprite *_contourSprite);
    ContourSprite *getContourSprite();

	void setContourPoints(ContourPoints *_contourPoints);
    ContourPoints *getContourPoints();

    void setDisplayData(DisplayData *_displayData);
    DisplayData *getDisplayData();
    
    void setTextureMutable(CCTexture2DMutable *_texture2DMutable);
    CCTexture2DMutable * getTextureMutable();
//public:
//    //! mark which type your display is
//    DisplayType m_eDisplayType;
//    
//    /**
//     *  @brief  If DisplayType is SP_DISPLAY_SPRITE, then Bone will use this image name to create a CCSprite from CCSpriteFrameCache.
//     *          It should note that when use this name to create CCSprite from CCSpriteFrameCache, you should use m_strDisplayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
//     *
//     *          If DisplayType is SP_DISPLAY_ARMATURE, the name is the Armature's name. When Bone init display and type is SP_DISPLAY_ARMATURE, then Bone will create a Armature.
//     */
//    std::string m_strDisplayName;
//    
//    /**
//     *  @brief  m_strImageName is different from m_strDisplayName, it is used for the display with type of DisplayType.
//     *          It is the name of the whole image name.
//     *          Example : we have several pngs named 1.png, 2.png, 3.png, these names are display names. And when use texture packer
//     *          to packer them to all.png, the 'all.png' is the image name.
//     */
//    std::string m_strImageName;
protected:
    CCObject *m_pDisplay;
    
    ContourSprite *m_pContourSprite;
	
    ContourPoints *m_pContourPoints;
    
    DisplayData *m_pDisplayData;
    
    CCTexture2DMutable *m_pTextureMutable;
};

}