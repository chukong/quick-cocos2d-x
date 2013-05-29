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


#include "reader.h"
#include "SPNode.h"
#include "sigslot.h"
#include "SPArmatureDefine.h"
#include "SPTweenFunction.h"

namespace sp{

class  FrameData : public Node
{
public:
    static FrameData *createWithJson(const char *_pszDescription);
    static FrameData *create();
public:
    FrameData();
    ~FrameData();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
    
protected:
    //! the frame will last m_iDuration frames
    CC_PROPERTY(int, m_iDuration, Duration)
    
    //! every frame's tween easing effect
    CC_PROPERTY(TweenType, m_eTweenEasing, TweenEasing)

    /**
     *  @brief  The current display index when change to this frame.
     *  If value is -1, then display will not show.
     */
    CC_PROPERTY(int, m_iDisplayIndex, DisplayIndex)
    
    /**
     *  @brief  m_strMovement, m_strEvent, m_strSound, m_strSoundEffect do not support yet
     */
	std::string m_strMovement;
	std::string m_strEvent;
	std::string m_strSound;
	std::string m_strSoundEffect;

//! signal
public:
    sigslot::signal2<int, int> DurationChangedSignal;
    sigslot::signal2<TweenType, TweenType> TweenEasingChangedSignal;
    sigslot::signal2<int, int> DisplayIndexChangedSignal;

};


}
