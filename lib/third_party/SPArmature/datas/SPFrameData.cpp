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

#include "SPFrameData.h"
#include "SPProcessBase.h"
#include "SPConstValue.h"

namespace sp{
    
FrameData *FrameData::createWithJson(const char *_pszDescription)
{
    FrameData *pFrameData = new FrameData();
    if (pFrameData && pFrameData->initWithJson(_pszDescription))
    {
        pFrameData->autorelease();
        return pFrameData;
    }
    CC_SAFE_DELETE(pFrameData);
    return NULL;
}

FrameData *FrameData::create()
{
    FrameData *pFrameData = new FrameData();
    if (pFrameData)
    {
        pFrameData->autorelease();
        return pFrameData;
    }
    CC_SAFE_DELETE(pFrameData);
    return NULL;
}

FrameData::FrameData(void)
    :m_iDuration(1)
    ,m_eTweenEasing(Sine_EaseInOut)
    ,m_iDisplayIndex(0)

    ,m_strMovement("")
    ,m_strEvent("")
    ,m_strSound("")
    ,m_strSoundEffect("")
{

}


FrameData::~FrameData(void)
{

}

void FrameData::updateJson()
{
    Node::updateJson();
    
    m_JsonDic.insertItem(A_DURATION, m_iDuration);
    m_JsonDic.insertItem(A_TWEEN_EASING, m_eTweenEasing);
    m_JsonDic.insertItem(A_DISPLAY_INDEX, m_iDisplayIndex);
}

    
bool FrameData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!Node::initWithJson(_pszDescription));
        
        m_iDuration = m_JsonDic.getItemIntValue(A_DURATION, 1);
        m_eTweenEasing = (TweenType)m_JsonDic.getItemIntValue(A_TWEEN_EASING, Sine_EaseInOut);
        m_iDisplayIndex = m_JsonDic.getItemIntValue(A_DISPLAY_INDEX, 0);
        
        
        ret = true;
    } while (0);
    
    
    return ret;
}
    
    
void FrameData::setDuration(int var)
{
    DurationChangedSignal.emit(m_iDuration, var);
    
    m_iDuration = var;
}

int FrameData::getDuration()
{
    return m_iDuration;
}

void FrameData::setDisplayIndex(int var)
{
    DisplayIndexChangedSignal.emit(m_iDisplayIndex, var);
    
    m_iDisplayIndex = var;
}

int FrameData::getDisplayIndex()
{
    return m_iDisplayIndex;
}
    
void FrameData::setTweenEasing(TweenType var)
{
    TweenEasingChangedSignal.emit(m_eTweenEasing, var);
    
    m_eTweenEasing = var;
}

TweenType FrameData::getTweenEasing()
{
    return m_eTweenEasing;
}


}