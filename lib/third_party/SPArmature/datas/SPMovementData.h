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

#include "SPMovementBoneData.h"
#include "SPMovementFrameData.h"

#include "sigslot.h"
#include "SPArmatureDefine.h"


namespace sp{

class Bone;
    
class  MovementData : public CCObject, public JsonData, public sigslot::has_slots<> {
public:
    static MovementData *createWithJson(const char *_pszDescription);
    static MovementData *create();
public:

    MovementData(void);
    ~MovementData(void);

    virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    void updateJson();
    
    

    MovementBoneData *addMovementBoneData(Bone *_bone, MovementBoneData *_movBoneData);
    MovementBoneData *addMovementBoneData(Bone *_bone, const char *_pszDescription);
    MovementBoneData *removeMovementBoneData(const char *_boneName);
    
    MovementBoneData *getMovementBoneData(const char *_boneName);
    
    
    

    //! not used yet
	void addMovFrameData(MovementFrameData *_movFrameData);
	MovementFrameData *getMoveFrameData(int _index);

    /**
     *	@brief	get a CCDictionary* include all MovementBoneData infomation
	 *
	 *  @return	CCDictionary* include all MovementBoneData infomation
     */
	CCDictionary *getMovBoneDataDic();
    
    /**
     *	@brief	get a CCArray* include all MovementBoneData infomation
	 *
	 *  @return	CCArray* include all MovementBoneData infomation
     */
	CCArray *getMovFrameDataArr();
    
public:
    
    
    //! the frames this movement will last
    CC_SYNTHESIZE(int, m_iDuration, Duration)
    
    /**
     *  @brief  Change to this movement will last m_iDurationTo frames. Use this effect can avoid too suddenly changing.
     *
     *          Example : current movement is "stand", we want to change to "run", then we fill m_iDurationTo frames before
     *          change to "run" instead of changing to "run" directly.
     */
    CC_SYNTHESIZE(int, m_iDurationTo, DurationTo)
    
    /*
     *  @brief  this is different from m_iDuration, m_iDurationTween contain tween effect.
     *
     *          Example : If we edit 10 frames in the flash, then m_iDuration is 10. When we set m_iDurationTween to 50, the movement will last 50 frames, the extra 40 frames will auto filled with tween effect
     */
    CC_SYNTHESIZE(int, m_iDurationTween, DurationTween)
    
    //! whether the movement is looped
    CC_SYNTHESIZE(bool, m_bLoop, Loop)
    
    /**
     *  @brief  which tween easing effect the movement use
     *          TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *          -1 : fade out
     *          0  : line
     *          1  : fade in
     *          2  : fade in and out
     */
    CC_SYNTHESIZE(TweenType, m_eTweenEasing, TweenEasing)
    
private:
	/**
	 *	@brief	save movment bone datas
	 *  @key	std::string
	 *  @value	MovementBoneData *
     */
    CCDictionary *m_pMovBoneDataDic;
    

	/**
	 *	@brief	save movment bone datas
	 *
	 *  @value	MovementFrameData *
     */
	CCArray	*m_pMovFrameDataArr;
    
    std::vector<MovementBoneData*> m_MovBoneDataVec;
    
    static int biggerDuration(const void *a, const void *b);
    
    CC_PROPERTY_PASS_BY_REF(std::string, m_strName, Name);

//!signal
public:
    sigslot::signal2<MovementData*, const char*> NameChanedSignal;

//!slot
public:
    void connectMovBoneDataSignal(MovementBoneData *_movBoneData);
    void disconnectMovBoneDataSignal(MovementBoneData *_movBoneData);
    
    void connectBoneSignal(Bone *_bone, MovementBoneData *_movBoneData);
    void disconnectBoneSignal(Bone *_bone);

    void movBoneDataDurationChanged();
    void boneNameChanged(Bone *_bone, const char *_boneName);
    
};


}