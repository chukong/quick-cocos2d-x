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
#include "SPDecorativeDisplay.h"
#include "SPBoneData.h"

using namespace cocos2d;

namespace sp{
    
class Bone;

//! DisplayManager manages Bone's display
class  DisplayManager : public CCObject
{
public:
    static DisplayManager *create(Bone *_bone);
    
public:
    DisplayManager();
    ~DisplayManager();
    
    bool init(Bone *_bone);
    
    /**
	 *	@brief	Use BoneData to init the display list.
     *          If display is a sprite, and it have texture info in the TexutreData, then use TexutreData to init the display's anchor point
     *          If the display is a Armature, then create a new Armature
     */
	void initDisplayList(BoneData *_boneData);
    
    /**
	 *	@brief	Add display and use  _DisplayData init the display.
     *          If _index already have a display, then replace it.
     *          If _index is current display index, then also change display to _index
     *
	 *	@param 	_DisplayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a SpriteDisplayData param
     *
	 *	@param 	_index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    void addDisplay(DisplayData *_displayData, int _index);
    
    void insertDisplay(DisplayData *_displayData, int _index);
    
    void removeDisplay(int _index);
    
    CCArray *getDecorativeDisplayList();
    
    /**
	 *	@brief	Change display by index. You can just use this method to
	 *          change display in the display list. The display list is just used for this bone,
     *			and it is the displays you may use in every frame.
     *
     *          note : if _index is the same with prev index, the method will not effect
     *
	 *	@param 	_index the index of the display you want to change
     *
     *  @param  _force if true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     */
	void changeDisplayByIndex(int _index, bool _force);
    
    
    void setDisplayRenderNode(CCNode *_displayRenderNode);
    CCNode *getDisplayRenderNode();
    
    int getCurrentDisplayIndex();
    DecorativeDisplay *getCurrentDecorativeDisplay();
    
    void updateDisplay();
    
    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                     Edit Function                              ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////
    
    
    void addEditDisplay(DisplayData *_displayData, int _index);
    
    void insertEditDisplay(DisplayData *_displayData, int _index);
    
    void removeEditDisplay(int _index);
    
    void editAnchorPoint(CCPoint &p);
    
public:
    /**
     *  @brief   check if the position is inside the bone.
     */
    virtual bool containPoint(CCPoint &_point);
    
    /**
     *  @brief   check if the position is inside the bone.
     */
    virtual bool containPoint(float _x, float _y);
    
    /**
     *  @brief   If this bone is be clicked, then test whether the anchor points is clicked.
     *           If anchor points is clicked, then return the point type.
     *           If anchor points is not clicked, then return POINT_MIN
     */
    virtual int getClickedContourPointType();
    
    /**
     *  @brief   Set whether or not the bone is visible.
     */
    virtual void setVisible(bool _visible);
    
    /**
     *  @brief   Get whether or not the bone is visible.
     */
    virtual bool isVisible();
    
    /**
     *  @brief  set whether or not show the contour points and collider points.
     */
    void showContour(bool _show);
    
    /**
     *  @brief  whether or not show the contour points and collider points.
     */
    bool isShowContour();
    
	
	/**
     *  @brief  Convert point to bone's transform space, and this function will modify the input value.
     */
	void convertPointToSpace(CCPoint &p);
    
    
	float getWidth();
	float getHeight();
	CCSize getContentSize();
	CCRect getBoundingBox();
    
    CCPoint getAnchorPoint();
    CCPoint getAnchorPointInPoints();

private:
    //! display render node.
	CCNode *m_pDisplayRenderNode;
    
    CCArray *m_pDecoDisplayList;
    //! include current display information, like contour sprite, etc.
    DecorativeDisplay *m_pCurrentDecoDisplay;
    //! current display index
	int m_iDisplayIndex;
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, m_bForceChangeDisplay, ForceChangeDisplay)
    
    
    //! Whether of not the bone is visible. Default is true
    bool m_bVisible;
    
    Bone *m_pBone;
};
		
}
