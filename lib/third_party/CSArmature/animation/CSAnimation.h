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


#ifndef COCOSTUDIO_CSANIMATION_H
#define COCOSTUDIO_CSANIMATION_H

#include "CSProcessBase.h"
#include "CSDatas.h"
#include "CSArmatureDefine.h"
#include "sigslot.h"

namespace cs {


class Armature;
class Bone;


class CS_EXTERN Animation : public ProcessBase
{
public:
    /**
	 * Create with a Armature
     * @param armature The Armature Animation will bind to 
     */
    static Animation *create(Armature *armature);
public:
    Animation();
    virtual ~Animation(void);

    /**
	 * Init with a Armature
     * @param armature The Armature Animation will bind to
     */
    virtual bool init(Armature *armature);
    
    /**
	 * Scale animation play speed. value is bigger, speed is slower.
     * @param animationScale Scale value
     */
	virtual void setAnimationScale(float animationScale);
    
	/**
	 * Play animation by animation name.
     *
     * @param  animationName  The animation name you want to play
     * @param  durationTo The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @param  durationTween  The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from MovementData get from flash design panel
     *
     * @param  loop   Whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing Tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
	void play(const char *animationName, int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);
    
    /**
	 * Play animation by index, the other param is the same to play.
     * @param  _animationIndex  the animation index you want to play
     */
    void playByIndex(int animationIndex,  int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);
    
    /**
	 * Pause the Process
     */
	virtual void pause();
    /**
	 * Resume the Process
     */
	virtual void resume();
    /**
	 * Stop the Process
     */
	virtual void stop();
    
    
    /**
	 * Get movement count
     */
    int getMovementCount();
    
    void update(float dt);
protected:
    
    /**
	 * Update(float dt) will call this handler, you can handle your logic here
     */
    void updateHandler();
    
    /**
	 * Update current key frame, and process auto stop, pause
     */
    void updateFrameData(float _currentPercent);
    
    /**
	 * Calculate which frame arrived, and if current frame have event, then call the event listener
     */
    void updateMovementFrameData(float _currentPercent);
protected:
	//! AnimationData save all MovementDatas this animation used.
	CC_SYNTHESIZE_RETAIN(AnimationData*, m_pAnimationData, AnimationData);
    

    MovementData *m_pMovementData;				//! MovementData save all MovementFrameDatas this animation used.

	Armature *m_pArmature;						//! A weak reference of armature

	std::string m_strMovementID;				//! Current movment's name 

    int m_iPrevFrameIndex;						//! Prev key frame index
	int m_iToIndex;								//! The frame index in MovementData->m_pMovFrameDataArr, it's different from m_iFrameIndex.

	cocos2d::CCArray *m_pTweenList;
public:
	/**
	 * MovementEvent signal. This will emit a signal when trigger a event. 
	 * The 1st param is the Armature. The 2nd param is Event Type, like START, COMPLETE. The 3rd param is Movement ID, also called Movement Name.
     */
	sigslot::signal3<Armature*, const char*, const char*> MovementEventSignal;

	sigslot::signal2<Bone*, const char*> FrameEventSignal;
};

}


#endif