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
#include "SPTweenFunction.h"

namespace sp{
    

enum ANIMATION_TYPE
{
	SINGLE = -4,        //! the animation just have one frame
	LIST_START,         //! the animation isn't loop
	LIST_LOOP_START,    //! the animation is loop
	LIST
};



class  ProcessBase : public CCObject
{
public:
	ProcessBase(void);
	~ProcessBase(void);
    
    
    /**
	 *	@brief  start the Process
     *
     *  @param  _animation  it will not used in the ProcessBase Class
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
    virtual void play(void * _animation, int _durationTo, int _durationTween,  int _loop, int _tweenEasing);

    /**
	 *	@brief	pause the Process
     */
	virtual void pause();
    
    /**
	 *	@brief	resume the Process
     */
	virtual void resume();
    
    /**
	 *	@brief	stop the Process
     */
	virtual void stop();
    
	virtual void gotoFrame(int _frameIndex);
    
    /**
     *  @note   you should never call this function, unless you know what you do
     *
	 *	@brief	update the Process, include current process, current frame and son on
     *
     *  @param  the duration since last update
     */
	virtual void update(float dt);
 
    virtual int getCurrentFrameIndex();
    
protected:
    

    /**
	 *	@brief	void update(float dt) will call this handler, you can handle your logic here
     */
	virtual void updateHandler() {};

protected:

	
    /**
     *	@brief	set and get whether the aniamtion is pause 
     */
	CC_SYNTHESIZE_PASS_BY_REF(bool, m_bIsPause, IsPause);
    
    /**
     *	@brief	set and get whether the aniamtion is complete
     */
	CC_SYNTHESIZE_PASS_BY_REF(bool, m_bIsComplete, IsComplete);

	/**
     *	@brief	current percent this process arrived
     */
	CC_SYNTHESIZE_PASS_BY_REF(float, m_fCurrentPercent, CurrentPercent);
	
	/**
     *	@brief	key frame count
     */
	CC_SYNTHESIZE_PASS_BY_REF(int, m_iDuration, Duration);
	
	/**
     *	@brief	the animation whether or not loop
     */
	CC_SYNTHESIZE_PASS_BY_REF(int, m_iLoop, Loop);

	/**
     *	@brief	the tween easing effect
     */
	CC_SYNTHESIZE_PASS_BY_REF(TweenType, m_eTweenEasing, TweenEasing);

    /**
     *	@brief	the animation update speed
     */
	CC_SYNTHESIZE_PASS_BY_REF(float, m_fAnimationInternal, AnimationInternal);

    /**
     *	@brief	scale the animation speed
     */
	CC_SYNTHESIZE_PASS_BY_REF(float, m_fAnimationScale, AnimationScale);
	
protected:
    /**
     *	@brief	the durantion frame count will run
     */
	int m_iDurationTween;

	/**
     *	@brief	current frame this process arrived, this frame is tween frame
     */
	float m_fCurrentFrame;

	/**
     *	@brief	total frame this process need run, diffrent from m_iDurationTween
     *          m_iTotalFrames used for calculate current percent of the animation.
     *          m_iTotalFrames is first setted to durationTo, when the animation changing complete,
     *          it will be setted to durationTween
     */
	int m_iTotalFrames;
    
    
    //! frame index it the time line
    int m_iFrameIndex;
    
    
};


}