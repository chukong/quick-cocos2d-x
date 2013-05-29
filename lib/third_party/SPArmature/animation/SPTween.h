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

#include "SPProcessBase.h"
#include "SPMovementData.h"
#include "SPTweenFunction.h"

using namespace cocos2d;

namespace sp{

class Bone;
class  Tween : public ProcessBase
{
public:
    /**
	 *	@brief	create with a Bone
     *
     *  @param  _bone the Bone Tween will bind to
     */
	static Tween* create(Bone *_bone);
public:
	Tween(void);
	~Tween(void);

    /**
	 *	@brief	init  with a Bone
     *
     *  @param  _bone the Bone Tween will bind to
     */
	virtual bool init(Bone *_bone);
	
    /**
	 *	@brief  start the Process
     *
     *  @param  _movementBoneData  the MovementBoneData include all frame datas
     *
     *  @param  _durationTo the frames between two animation changing-over.
     *          It's meaning is changing to this animation need how many frames
     *
     *          -1 : use the value from MovementData get from flash design panel
     *
     *  @param  _durationTween  the frame count you want to play in the game.
     *          if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *          -1 : use the value from MovementData get from flash design panel
     *
     *  @param  _loop   whether the animation is loop
     *
     *          _loop < 0 : use the value from MovementData get from flash design panel
     *          _loop = 0 : this animation is not loop
     *          _loop > 0 : this animation is loop
     *
     *  @param  _tweenEasing    tween easing is used for calculate easing effect
     *
     *          TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *          -1 : fade out
     *          0  : line
     *          1  : fade in
     *          2  : fade in and out
     *
     */
	void play(MovementBoneData *_movementBoneData, int _durationTo, int _durationTween,  int _loop, int _tweenEasing);
	
    
    void setMoveBoneData(MovementBoneData *_movBoneData);
    
    MovementBoneData *getMoveBoneData();
    
    virtual void gotoFrame(int _frameIndex);
	
	FrameData *getTweenNode(){ return m_pTweenData; }
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativePosition(float x, float y);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editPosition(float x, float y);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativePositionX(float x);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editPositionX(float x);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativePositionY(float y);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editPositionY(float y);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativeRotation(float r);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editRotation(float r);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativeScale(float scaleX, float scaleY);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editScale(float scaleX, float scaleY);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativeScaleX(float scaleX);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editScaleX(float scaleX);
    
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is relative value
     */
    void editRelativeScaleY(float scaleY);
    /*
     *  @brief  Used for editor, this function will modify the data in the data pool
     *          The param is absolute value
     */
    void editScaleY(float scaleY);
    
    
    
    CCPoint getPosition();
	float	getPositionX();
	float	getPositionY();
	float	getRotation();
	float	getScaleX();
	float	getScaleY();
protected:
    
    /**
	 *	@brief	void update(float dt) will call this handler, you can handle your logic here
     */
	void updateHandler();
    
    /**
	 *	@brief	calculate which frame arrived, and if current frame have event, then call the event listener
     */
    float updateFrameData(float _currentPrecent, bool _activeFrame = false);
    

private:
    /**
	 *	@brief	calculate the between value of _from and _to, and give it to m_pBetween
     */
	void setBetween(FrameData *_from, FrameData *_to);
    
    /**
	 *	@brief	according to the _percent to calculate current FrameData
     */
	FrameData *tweenNodeTo(float _percent, FrameData *_node = NULL);
    
    /**
	 *	@brief	get the ease effect. It can make the curve more smooth
     *
     *  @param  _percent percent arrived
     *
     *  @param  _easing which easing effect you want to use
     */
	static float getEaseValue(float _percent, float _easing);
    
    
private:
	FrameData *m_pTweenData;
    //! from data, used for calculate between value
	FrameData *m_pFrom;
    FrameData *m_pTo;
    
    //! between data, used for calculate current FrameData(m_pNode) value
	FrameData *m_pBetween;

    //! a weak reference to the current MovementBoneData. The data is in the data pool
	MovementBoneData *m_pMovementBoneData;
    
    //! a weak reference to the current FrameData. The data is in the data pool
    FrameData *m_pCurrentKeyFrame;
	
    //! a weak reference to the next FrameData. The data is in the data pool
    FrameData *m_pNextKeyFrame;
    
    FrameData *m_pEditKeyFrame;

    //! a weak reference to the Bone
	Bone *m_pBone;

    
	TweenType m_eFrameTweenEasing;

	
	bool m_bIsTweenKeyFrame;
    
    
    //! this key frame will last m_iBetweenDuration frames
	int m_iBetweenDuration;
    
	int m_iTotalDuration;
    
    /**
     *	the next frame index in MovementBoneData->m_pFrameList
     *  it's different from m_iFrameIndex
     */
	int m_iToIndex;
    
    /**
     *	the current frame index in MovementBoneData->m_pFrameList
     *  it's different from m_iFrameIndex
     */
    int m_iFromIndex;
    
    //! whether or not current state is a key frame state, or it's a tween state
    bool m_bIsAtKeyFrame;
};



}