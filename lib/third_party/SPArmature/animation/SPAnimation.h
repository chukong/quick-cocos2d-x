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
#include "SPAnimationData.h"
#include "sigslot.h"


namespace sp{


class Armature;


class  Animation : public ProcessBase
{
public:
    /**
	 *	@brief	create with a Armature
     *
     *  @param  _armature the Armature Animation will bind to 
     */
    static Animation *create(Armature *_armature);
public:
//    Animation(DEFINE_JS obj);
    Animation();
    ~Animation(void);

    /**
	 *	@brief	init with a Armature
     *
     *  @param  _armature the Armature Animation will bind to
     */
    virtual bool init(Armature *_armature);

    /**
	 *	@brief	Set animation data, Animation will use the data when play animation
     *
     *  @param  _aniData AnimationData you want to set to this Animation
     */
    void setAnimationData(AnimationData* _aniData);
    
    AnimationData *getAnimationData();
    
    /**
	 *	@brief	scale animation play speed. value is bigger, speed is slower.
     *
     *  @param  _animationScale scale value
     */
	void setAnimationScale(float _animationScale);
    
    /**
	 *	@brief  start play the specified Animation
     *
     *  @param  _animationName  the animation name you want to play
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
	void play(const char *_animationName, int _durationTo = -1, int _durationTween = -1,  int _loop = -1, int _tweenEasing = TWEEN_EASING_MAX);
    
    /**
	 *	@brief	play animation by index, the other param is the same to play.
     *
     *  @param  _animationIndex  the animation index you want to play
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
    void playByIndex(int _animationIndex,  int _durationTo = -1, int _durationTween = -1,  int _loop = -1, int _tweenEasing = TWEEN_EASING_MAX);
    
    
    
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
	 *	@brief	get movement count
     */
    int getMovementCount();
    
    
    void editMovement(const char *_animationName);
    void editMovementByIndex(int _index);
    
protected:
    
    /**
	 *	@brief	void update(float dt) will call this handler, you can handle your logic here
     */
    void updateHandler();
    
    /**
	 *	@brief	update current key frame, and process auto stop, pause
     */
    void updateFrameData(float _currentPercent);
    
    /**
	 *	@brief	calculate which frame arrived, and if current frame have event, then call the event listener
     */
    void updateMovementFrameData(float _currentPercent);
protected:
    /**
	 *	@brief	AnimationData save all MovementDatas this animation used.
     */
    AnimationData *m_pAnimationData;
    
    /**
	 *	@brief	MovementData save all MovementFrameDatas this animation used.
     */
    MovementData *m_pMovementData;
    
    /**
	 *	@brief	MovementFrameData save a whole frame datas, it is different from FrameData, FrameData save a single bone's data for every frame.
     */
	MovementFrameData *m_pCurrentFrameData;
    
    /**
	 *	@brief	current movment's name 
     */
	std::string m_strMovementID;
    
private:
    /**
	 *	@brief	weak reference
     */
	Armature *m_pArmature;
    
    //! Prev key frame index
    int m_iPrevFrameIndex;
    
    /**
     *	the frame index in MovementData->m_pMovFrameDataArr
     *  it's different from m_iFrameIndex
     */
	int m_iToIndex;

public:
	/**
	 *	@brief	MovementEvent signal. This will emit a signal when trigger a event. 
	 *			The 1st param is the Armature. The 2nd param is Event Type, like START, COMPLETE. The 3rd param is Movement ID, also called Movement Name.
     */
	sigslot::signal3<Armature*, const char*, const char*> MovementEventSignal;

public:
//    CREATE_JS_CLASS_ROOT(Animation)
//    
//    JS_NO_RETURN_FUNCTION_5(Animation, play, const char*, int, int, int, int);
//    JS_NO_RETURN_FUNCTION_5(Animation, playByIndex, int, int, int, int, int);
//    JS_NO_RETURN_FUNCTION_1(Animation, setAnimationScale, float);
//    JS_NO_RETURN_FUNCTION_0(Animation, stop)
//    JS_NO_RETURN_FUNCTION_0(Animation, pause)
//    JS_NO_RETURN_FUNCTION_0(Animation, resume)
//    JS_NO_RETURN_FUNCTION_1(Animation, gotoFrame, int)
//    JS_FUNCTION_0(Animation, getMovementCount)
//    JS_FUNCTION_0(Animation, getDuration)
};

}