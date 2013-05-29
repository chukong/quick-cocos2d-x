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

#include "SPNode.h"
#include "SPBoneData.h"
#include "SPTween.h"
#include "SPDisplayData.h"
#include "SPContourSprite.h"
#include "SPArmatureDefine.h"
#include "CCTexture2DMutable.h"
#include "SPDisplayData.h"
#include "SPDecorativeDisplay.h"
#include "sigslot.h"
#include "SPDisplayManager.h"

using namespace cocos2d;

namespace sp{


class Armature;

class  Bone : public CCObject
{
public:
    /**
	 *	@brief	create a Bone
     */
    static Bone *create();
    /**
	 *	@brief	create a Bone with specified name
     *
	 *	@param 	_name Bone's name.
     *
     */
	static Bone *create(const char *_name);

public:
//	Bone(DEFINE_JS obj);
    Bone();
	virtual ~Bone(void);
    
    virtual bool init();
    /**
	 *	@brief	init a Bone with specified name
     *
	 *	@param 	_name Bone's name.
     *
     */
	virtual bool init(const char *_name);

    /**
	 *	@brief	Add a child to this bone, and it will let this child call setParent(Bone *_parent) function to set self to it's parent
     *
	 *	@param 	_child  the child you want to add
     */
	void addChildBone(Bone* _child);
    
    /**
	 *	@brief	set parent bone. 
     *          If _parent is NUll, then also remove this bone from armature.
     *          It will not set the Armature, if you want to add the bone to a Armature, you should use Armature::addBone(Bone *_bone, const char* _parentName).
     *
	 *	@param 	_parent  the parent bone.
     *          NULL : remove this bone from armature
     */
    void setParentBone(Bone *_parent);
    
    /**
	 *	@brief	get parent bone
     *
	 *	@return parent bone
     */
    Bone *getParentBone();
    
    
    /**
	 *	@brief	Remove itself from its parent Bone.
     *
	 *	@param 	_cleanup    whether or not cleanup display
     */
    void removeFromParent(bool _cleanup);
    
    /**
	 *	@brief	Removes a child Bone
     *
	 *	@param 	_bone   the bone you want to remove
     */
	void removeChildBone(Bone *_bone, bool _cleanup);

    /**
	 *	@brief	set the bone's zorder. the zorder is different to cocos2dx's zorder, it used to calculate the vertexz
     *
	 *	@param 	_zorder zorder you want to set
     */
    void setZOrder(int _zorder);
    
    /**
     *  @brief   Get current bone's zorder
     *
     *  @return Current bone's zorder
     *
     */
    int getZOrder();
    
    void update(float dt);
    
    void updateTransform();
    

    /**
     *  @brief  set bone's property, used for users, this won't change data in the data pool
     */
    void setPosition(float x, float y);
    void setPositionX(float x);
    void setPositionY(float y);
    void setRotation(float r);
    void setScale(float scale);
	void setScaleX(float scaleX);
    void setScaleY(float scaleY);
   
	/**
     *  @brief  get bone's user property
     */
	CCPoint getPosition();
	float	getPositionX();
	float	getPositionY();
	float	getRotation();
	float	getScaleX();
	float	getScaleY();

	void setName(const char *_name);
    std::string &getName();


    CCArray *getChildren();
    
    FrameData *getCombinedData();
    
    /**
	 *	@brief	Add display and use  _DisplayData init the display.
     *          If _index already have a display, then replace it.
     *          If _index is current display index, then also change display to _index
     *
	 *	@param 	_displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a SpriteDisplayData param
     *
	 *	@param 	_index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    void addDisplay(DisplayData *_displayData, int _index);
    
    void changeDisplayByIndex(int _index, bool _force);
    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                     Edit Function                              ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////
    
    
    
    void editName(const char *_name);
    

public:
    /*
     *  the origin state of the Bone. Display's state is effected by m_pBoneData, m_pNode, m_pTweenData
     *  when call setData function, it will copy from the BoneData.
     */
	CC_PROPERTY(BoneData *, m_pBoneData, BoneData);
    
    //! A weak reference to the Armature
	CC_SYNTHESIZE(Armature *, m_pArmature, Armature);
    
    //! A weak reference to the child Armature
    CC_PROPERTY(Armature *, m_pChildArmature, ChildArmature);
    
	CC_SYNTHESIZE(Tween *, m_pTween, Tween);
    CC_SYNTHESIZE(DisplayManager*, m_pDisplayManager, DisplayManager)

	/*
	 *	When Armature play a animation, if there is not a MovementBoneData of this bone in this MovementData, this bone will hide.
	 *	Set IgnoreMovementBoneData to true, then this bone will also show.
	 */
	CC_SYNTHESIZE_PASS_BY_REF(bool, m_bIgnoreMovementBoneData, IgnoreMovementBoneData)
    
	CC_SYNTHESIZE(bool, m_bRootBone, RootBone);
	
public:
    CCAffineTransform m_pSlefTransformMatrix;
	//! self Transform, use this to change display's state
	CCAffineTransform m_pGlobalTransformMatrix;
    //! Transform for children
	CCAffineTransform m_pTransformMatrixForChildren;

private:
    //! used for make tween effect between every frame, it's a weak reference of Tween's tweenData
	FrameData *m_pTweenData;
    //! used for users to change the m_pDisplay's transform
    FrameData *m_pUserData;
	//! combine TweenData and UserData, then it's the final data
	FrameData *m_pCombinedData;

    /*
     *  the zorder in the Armature, when chane zorder, you need to change Armature's m_bBonesIndexChanged to 
     *  true. It is used for Armature calculate Bone's vertexz
     */
    int m_iZOrder;

    
	//! lazy allocs
	void childrenAlloc(void);
    CCArray *m_pChildren;
    
    //! a weak reference to it's parent
    Bone *m_pParent;
    
    
    std::string m_strName;
    
public:
    sigslot::signal2<Bone*, const char*> NameChanedSignal;
    sigslot::signal2<const char*, CCDictionary*> RemoveFromParentSignal;
public:
//    CREATE_JS_CLASS_ROOT(Bone)
//    JS_NO_RETURN_FUNCTION_1(Bone, init, const char*)
//    JS_NO_RETURN_FUNCTION_2(Bone, setPosition, float, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setPositionX, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setPositionY, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setRotation, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setScale, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setScaleX, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setScaleY, float)
//    JS_NO_RETURN_FUNCTION_1(Bone, setName, const char*)
//	JS_NO_RETURN_FUNCTION_1(Bone, setIgnoreMovementBoneData, bool)
//    
//    JS_NO_RETURN_FUNCTION_2(Bone, addDisplay, DisplayData*, int)
//    JS_NO_RETURN_FUNCTION_2(Bone, changeDisplayByIndex, int, bool)
//    
//    JS_FUNCTION_0(Bone, getName)
//    JS_FUNCTION_0(Bone, getPositionX);
//    JS_FUNCTION_0(Bone, getPositionY);
//    JS_FUNCTION_0(Bone, getRotation);
//    JS_FUNCTION_0(Bone, getScaleX);
//    JS_FUNCTION_0(Bone, getScaleY);
//    JS_FUNCTION_0(Bone, getParentBone)
    
    
};

}