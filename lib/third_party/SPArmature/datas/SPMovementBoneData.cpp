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

#include "SPMovementBoneData.h"
#include "SPConstValue.h"

namespace sp{

MovementBoneData *MovementBoneData::createWithJson(const char *_pszDescription)
{
    MovementBoneData *pMovementBoneData = new MovementBoneData();
    if (pMovementBoneData && pMovementBoneData->initWithJson(_pszDescription))
    {
        pMovementBoneData->autorelease();
        return pMovementBoneData;
    }
    CC_SAFE_DELETE(pMovementBoneData);
    return NULL;
}
    
MovementBoneData *MovementBoneData::create()
{
    MovementBoneData *pFrameNodeList = new MovementBoneData();
    if (pFrameNodeList && pFrameNodeList->init())
    {
        pFrameNodeList->autorelease();
        return pFrameNodeList;
    }
    CC_SAFE_DELETE(pFrameNodeList);
    return NULL;
}

MovementBoneData::MovementBoneData()
    :m_fDelay(0.0f)
    ,m_fScale(1.0f)
    ,m_iDuration(0)
    ,m_pFrameList(NULL)
    ,m_strName("")
{
    m_bUseColorInfo = false;
    m_bUsePositionInfo = true;
    m_bUseRotationInfo = true;
    m_bUseScaleInfo = true;
}


MovementBoneData::~MovementBoneData(void)
{
    CC_SAFE_DELETE(m_pFrameList);
}

bool MovementBoneData::init()
{
    return initWithJson(NULL);
}


void MovementBoneData::updateJson()
{
    JsonData::updateJson();
    
    
    m_JsonDic.insertItem(A_MOVEMENT_DELAY, m_fDelay);
    m_JsonDic.insertItem(A_MOVEMENT_SCALE, m_fScale);
    //    m_JsonDic.insertItem(A_DURATION, m_iDuration);
    m_JsonDic.insertItem(A_NAME, m_strName.c_str());
    
    
    if(m_pFrameList->count() <= 0)
    {
        return;
    }
    
    Json::Value array;
    
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pFrameList, _object)
    {
        FrameData *_frameData = (FrameData*)_object;
        m_JsonDic.insertItemToArray(FRAME_DATA, &_frameData->getJsonDic());
    }
    
}


bool MovementBoneData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        
        m_pFrameList = new CCArray();
        CCAssert(m_pFrameList->init(), "create MovementBoneData::m_pFrameList fail!");
        
        if(_pszDescription == NULL)
        {
            return true;
        }
        
        JsonData::initWithJson(_pszDescription);
        
        m_fDelay = m_JsonDic.getItemFloatValue(A_MOVEMENT_DELAY, 0);
        m_fScale = m_JsonDic.getItemFloatValue(A_MOVEMENT_SCALE, 1);
        //        m_iDuration = m_JsonDic.getItemFloatValue(A_DURATION, 0);
        
        const char * str = m_JsonDic.getItemStringValue(A_NAME);
        if(str != NULL)
        {
            m_strName = str;
        }
        
        
        int _length = m_JsonDic.getArrayItemCount(FRAME_DATA);
        
        for (int i = 0; i<_length; i++)
        {
            SPJsonDictionary *_dic = m_JsonDic.getSubItemFromArray(FRAME_DATA, i);
            
            FrameData *_frameData = FrameData::createWithJson(_dic->getDescription().c_str());
            
            addFrameData(_frameData);
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}

FrameData *MovementBoneData::addFrameData(FrameData* _frameData)
{
    m_pFrameList->addObject(_frameData);
    connectFrameDataSignal(_frameData);
    
    m_iDuration += _frameData->getDuration();
    
    judgeColorChanged(_frameData);
    
    DurationChangedSignal.emit();
    
    return _frameData;
}
    
FrameData *MovementBoneData::addFrameData(const char *_pszDescription)
{
    FrameData *_frameData = FrameData::createWithJson(_pszDescription);
    addFrameData(_frameData);
    
    return _frameData;
}

FrameData *MovementBoneData::insertFrameDataAtIndex(int _index, FrameData* _frameData)
{
    m_pFrameList->insertObject(_frameData, _index);
    
    connectFrameDataSignal(_frameData);
    
    m_iDuration += _frameData->getDuration();
    
    DurationChangedSignal.emit();
    
    return _frameData;
}
    
FrameData *MovementBoneData::insertFrameDataAtIndex(int _index, const char *_pszDescription)
{
    FrameData *_frameData = FrameData::createWithJson(_pszDescription);
    insertFrameDataAtIndex(_index, _frameData);
    
    return _frameData;
}

FrameData *MovementBoneData::removeFrameData(int _index)
{
    FrameData *_frameData = getFrameData(_index);
    
    disconnectFrameDataSignal(_frameData);
    m_pFrameList->removeObjectAtIndex(_index);
    
    m_iDuration -= _frameData->getDuration();
    
    DurationChangedSignal.emit();
    
    return _frameData;
}

void MovementBoneData::exchangeFrameData(int _index, int _index2)
{
    m_pFrameList->exchangeObjectAtIndex(_index, _index2);
}

FrameData* MovementBoneData::getFrameData(int _index)
{
    return (FrameData*)m_pFrameList->objectAtIndex(_index);
}

CCArray *MovementBoneData::getFrameDatas()
{
    return m_pFrameList;
}

int MovementBoneData::getFrameCount()
{
    return m_pFrameList->count();
}

void MovementBoneData::judgeColorChanged(FrameData *_data)
{
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pFrameList, _object)
    {
        FrameData *_frameData = (FrameData*)_object;
        
        
        if(_data->m_iRed != _frameData->m_iRed || _data->m_iGreen != _frameData->m_iGreen || 
           _data->m_iBlue != _frameData->m_iBlue || _data->m_iAlpha != _frameData->m_iAlpha)
        {
            m_bUseColorInfo = true;
            return;
        }
    }
}
 
void MovementBoneData::connectFrameDataSignal(FrameData *_frameData)
{
    _frameData->DurationChangedSignal.connect(this, &MovementBoneData::frameDataDurationChanged);
}
    
void MovementBoneData::disconnectFrameDataSignal(FrameData *_frameData)
{
    _frameData->DurationChangedSignal.disconnect(this);
}
    
void MovementBoneData::frameDataDurationChanged(int _preDurantion, int _duration)
{
    m_iDuration = m_iDuration - _preDurantion + _duration;
    DurationChangedSignal.emit();
}
    

}