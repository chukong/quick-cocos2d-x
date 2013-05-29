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

#include "SPMovementData.h"
#include "SPConstValue.h"
#include "SPBone.h"

using namespace std;

namespace sp{

MovementData *MovementData::createWithJson(const char *_pszDescription)
{
    MovementData *pMovementData = new MovementData();
    if (pMovementData->initWithJson(_pszDescription))
    {
        pMovementData->autorelease();
        return pMovementData;
    }
    CC_SAFE_DELETE(pMovementData);
    return NULL;
}

MovementData *MovementData::create()
{
    MovementData *pMovementData = new MovementData();
    if (pMovementData->init())
    {
        pMovementData->autorelease();
        return pMovementData;
    }
    CC_SAFE_DELETE(pMovementData);
    return NULL;
}

MovementData::MovementData(void)
    :m_pMovBoneDataDic(NULL)
    ,m_pMovFrameDataArr(NULL)
    ,m_strName("")
    ,m_iDuration(0)
    ,m_iDurationTo(0)
    ,m_iDurationTween(0)
    ,m_bLoop(true)
    ,m_eTweenEasing(Sine_EaseInOut)
{
}


MovementData::~MovementData(void)
{
    CC_SAFE_DELETE( m_pMovBoneDataDic );
    CC_SAFE_DELETE( m_pMovFrameDataArr );
}

bool MovementData::init()
{
    return initWithJson(NULL);
}

void MovementData::updateJson()
{
    JsonData::updateJson();
    
    
    m_JsonDic.insertItem(A_LOOP, m_bLoop);
    m_JsonDic.insertItem(A_DURATION_TWEEN, m_iDurationTween);
    m_JsonDic.insertItem(A_DURATION_TO, m_iDurationTo);
    m_JsonDic.insertItem(A_DURATION, m_iDuration);
    m_JsonDic.insertItem(A_TWEEN_EASING, m_eTweenEasing);
    m_JsonDic.insertItem(A_NAME, m_strName.c_str());
    
    if(m_pMovBoneDataDic->count() <= 0)
    {
        return;
    }
    
    Json::Value array;
    
    CCDictElement *_element = NULL;
    CCDICT_FOREACH(m_pMovBoneDataDic, _element)
    {
        MovementBoneData *_movBoneData = (MovementBoneData*)_element->getObject();
        m_JsonDic.insertItemToArray(MOVEMENT_BONE_DATA, &_movBoneData->getJsonDic());
    }
    
}

bool MovementData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        CC_SAFE_DELETE(m_pMovBoneDataDic);
        m_pMovBoneDataDic = new CCDictionary();
        CCAssert(m_pMovBoneDataDic, "create MovementData::m_pMovBoneDataDic fail!");
        
        CC_SAFE_DELETE(m_pMovFrameDataArr);
        m_pMovFrameDataArr = new CCArray();
        CCAssert(m_pMovFrameDataArr, "create MovementData::m_pMovFrameDataArr fail!");
        
        
        JsonData::initWithJson(_pszDescription);
        
        
        m_bLoop = m_JsonDic.getItemBoolvalue(A_LOOP, true);
        m_iDurationTween = m_JsonDic.getItemIntValue(A_DURATION_TWEEN, 0);
        m_iDurationTo = m_JsonDic.getItemIntValue(A_DURATION_TO, 0);
        m_iDuration = m_JsonDic.getItemIntValue(A_DURATION, 0);
        m_eTweenEasing = (TweenType)m_JsonDic.getItemIntValue(A_TWEEN_EASING, Sine_EaseInOut);
        
        const char * str = m_JsonDic.getItemStringValue(A_NAME);
        if(str != NULL)
        {
            m_strName = str;
        }
        
        
        int _length = m_JsonDic.getArrayItemCount(MOVEMENT_BONE_DATA);
        
        for (int i = 0; i<_length; i++)
        {
            SPJsonDictionary *_dic = m_JsonDic.getSubItemFromArray(MOVEMENT_BONE_DATA, i);
            
            MovementBoneData *_movBoneData = MovementBoneData::createWithJson(_dic->getDescription().c_str());
            
            m_pMovBoneDataDic->setObject(_movBoneData, _movBoneData->getName().c_str());
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}
    
void MovementData::setName(const std::string &var)
{
    m_strName = var;
    NameChanedSignal.emit(this, m_strName.c_str());
}

const std::string &MovementData::getName()
{
    return m_strName;
}
    
MovementBoneData *MovementData::addMovementBoneData(Bone *_bone, MovementBoneData *_movBoneData)
{
    
    if (_movBoneData->getName().compare("") == 0 &&  _bone)
    {
        _movBoneData->setName(_bone->getName());
    }
    
    m_pMovBoneDataDic->setObject(_movBoneData, _movBoneData->getName());
    
    m_MovBoneDataVec.push_back(_movBoneData);
    movBoneDataDurationChanged();
    
    connectBoneSignal(_bone, _movBoneData);
    connectMovBoneDataSignal(_movBoneData);
    
    return _movBoneData;
}
    
MovementBoneData *MovementData::addMovementBoneData(Bone *_bone, const char *_pszDescription)
{
    MovementBoneData *_movBoneData = MovementBoneData::createWithJson(_pszDescription);
   
    addMovementBoneData(_bone, _movBoneData);
    
    return _movBoneData;
}
    
MovementBoneData *MovementData::removeMovementBoneData(const char *_boneName)
{
    MovementBoneData *_movBoneData = getMovementBoneData(_boneName);
    if(!_movBoneData)
    {
        return NULL;
    }
    m_pMovBoneDataDic->removeObjectForKey(_boneName);
    
    std::vector<MovementBoneData*>::iterator it;
    
    for ( it= m_MovBoneDataVec.begin(); it != m_MovBoneDataVec.end(); it++)
    {
        if (*it == _movBoneData)
        {
            break;
        }
    }
    m_MovBoneDataVec.erase(it);
    
    movBoneDataDurationChanged();
    
    
    return _movBoneData;
}

MovementBoneData *MovementData::getMovementBoneData(const char *_boneName)
{
    return (MovementBoneData*)(m_pMovBoneDataDic->objectForKey(_boneName));
}

void MovementData::addMovFrameData(MovementFrameData *_movFrameData)
{
	m_pMovFrameDataArr->addObject(_movFrameData);
}

MovementFrameData *MovementData::getMoveFrameData(int _index)
{
	return (MovementFrameData*)m_pMovFrameDataArr->objectAtIndex(_index);
}
    
CCDictionary *MovementData::getMovBoneDataDic()
{
    return m_pMovBoneDataDic;
}
    
CCArray *MovementData::getMovFrameDataArr()
{
    return m_pMovFrameDataArr;
}
    
void MovementData::connectMovBoneDataSignal(MovementBoneData *_movBoneData)
{
    _movBoneData->DurationChangedSignal.connect(this, &MovementData::movBoneDataDurationChanged);
    
}

void MovementData::disconnectMovBoneDataSignal(MovementBoneData *_movBoneData)
{
    _movBoneData->DurationChangedSignal.disconnect(this);
}

void MovementData::movBoneDataDurationChanged()
{
    
    if(m_MovBoneDataVec.size() > 0)
    {
        qsort(&m_MovBoneDataVec[0], m_MovBoneDataVec.size(), sizeof(MovementBoneData*), &MovementData::biggerDuration);
        m_iDuration = m_MovBoneDataVec.back()->getDuration();
    }
    else
    {
        m_iDuration = 0;
    }
    
    
}
    
void MovementData::connectBoneSignal(Bone *_bone, MovementBoneData *_movBoneData)
{
    if(!_bone || !_movBoneData)
    {
        return;
    }
    
    _bone->NameChanedSignal.connect(this, &MovementData::boneNameChanged);
}

void MovementData::disconnectBoneSignal(Bone *_bone)
{
    
}

void MovementData::boneNameChanged(Bone *_bone, const char *_boneName)
{
    const char *_originBoneName = _bone->getName().c_str();
    MovementBoneData *_movBoneData = (MovementBoneData*)m_pMovBoneDataDic->objectForKey(_originBoneName);
    _movBoneData->setName(_boneName);
    m_pMovBoneDataDic->removeObjectForKey(_originBoneName);
    m_pMovBoneDataDic->setObject(_movBoneData, _boneName);
    
}

int MovementData::biggerDuration(const void *a, const void *b)
{
    MovementBoneData *_aMovBoneData = *((MovementBoneData**)a);
    MovementBoneData *_bMovBoneData = *((MovementBoneData**)b);
    
    int _aDuration = _aMovBoneData->getDuration();
    int _bDuration = _bMovBoneData->getDuration();
    
    if(_aDuration > _bDuration)
        return 1;
    else if(_aDuration < _bDuration)
        return -1;
    return 0;
        
}

}