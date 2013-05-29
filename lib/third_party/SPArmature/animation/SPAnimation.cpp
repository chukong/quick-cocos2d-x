#include "SPAnimation.h"
#include "SPArmature.h"
#include "SPBone.h"
#include "SPArmatureDefine.h"
#include "SPUtilMath.h"
#include "SPConstValue.h"


using namespace std;

namespace sp{

//INIT_JS_CLASS_ROOT(Animation)
//    
//JS_FUNCTION_BEGIN(Animation)
//JS_FUNCTION_BIND(play, 5)
//JS_FUNCTION_BIND(playByIndex, 5)
//JS_FUNCTION_BIND(setAnimationScale, 1)
//JS_FUNCTION_BIND(getMovementCount, 0)
//JS_FUNCTION_BIND(getDuration, 0)
//JS_FUNCTION_BIND(stop, 0)
//JS_FUNCTION_BIND(pause, 0)
//JS_FUNCTION_BIND(resume, 0)
//JS_FUNCTION_BIND(gotoFrame, 1)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(Animation)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(Animation)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(Animation)
//JS_PROPERTY_END
    
        
Animation *Animation::create(Armature *_armature)
{
    Animation *pARmatureAnimation = new Animation();
    if (pARmatureAnimation && pARmatureAnimation->init(_armature))
    {
        pARmatureAnimation->autorelease();
        return pARmatureAnimation;
    }
    CC_SAFE_DELETE(pARmatureAnimation);
    return NULL;
}
//
//Animation::Animation(DEFINE_JS obj)
//    :m_pAnimationData(NULL)
//    ,m_pCurrentFrameData(NULL)
//    ,m_strMovementID("")
//    ,m_pArmature(NULL)
//    ,m_iToIndex(0)
//{
//    
//}

    
Animation::Animation()
    :m_pAnimationData(NULL)
    ,m_pCurrentFrameData(NULL)
    ,m_strMovementID("")
    ,m_pArmature(NULL)
    ,m_iToIndex(0)
{
//    CREATE_JS_OBJECT(Animation)
}

Animation::~Animation(void)
{
//    DELETE_JS;
}

bool Animation::init(Armature *_armature)
{
    bool bRet = false;
    do
    {
        m_pArmature = _armature;
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}


void Animation:: pause()
{
    
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone *_bone = (Bone*)_element->getObject();
        if (_bone->getTween())
        {
            _bone->getTween()->pause();
        }
    }
    
    ProcessBase::pause();
    
}
  
void Animation::resume()
{
    
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone* _bone = (Bone*)_element->getObject();
        if (_bone->getTween())
        {
            _bone->getTween()->resume();
        }
    }
    
    ProcessBase::resume();
}

void Animation::stop()
{
    
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone *_bone = (Bone*)_element->getObject();
        if (_bone->getTween())
        {
            _bone->getTween()->stop();
        }
    }
    
    ProcessBase::stop();
}

void Animation::gotoFrame(int _frameIndex)
{
    if(!m_pMovementData)
    {
        return;
    }
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone *_bone = (Bone*)_element->getObject();
        MovementBoneData *_movementBoneData = m_pMovementData->getMovementBoneData(_bone->getName().c_str());
        
        if(_movementBoneData && _movementBoneData->getFrameCount()>0 && _bone->getTween())
        {
            _bone->getTween()->gotoFrame(_frameIndex);
        }
    }
    
    ProcessBase::gotoFrame(_frameIndex);
}


void Animation::setAnimationData(AnimationData* _aniData)
{
    stop();
    m_pAnimationData = _aniData;
}
    
AnimationData *Animation::getAnimationData()
{
    return m_pAnimationData;
}

void Animation::setAnimationScale(float _animationScale )
{
    if(_animationScale == m_fAnimationScale)
    {
        return;
    }
    
    /*
     *  when calculate m_fCurrentFrame, we will do a processing of m_fCurrentFrame += m_fAnimationScale * (dt/m_fAnimationInternal);
     *  then if m_fAnimationScale is bigger, the m_fCurrentFrame grow quicker, animation 
     *  scale up.
     *  We want animation slower when m_fAnimationScale is bigger, so do 1/_animationScale.
     */
    m_fAnimationScale = 1/_animationScale;
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone *_bone = (Bone*)_element->getObject();
        if (_bone->getTween())
        {
            _bone->getTween()->setAnimationScale(m_fAnimationScale);
        }
    }
}


void Animation::play(const char *_animationName, int _durationTo, int _durationTween,  int _loop, int _tweenEasing)
{
    CCAssert(m_pAnimationData, "m_pAnimationData can not be null");
    
    m_pMovementData = m_pAnimationData->getMovement( _animationName );
    CCAssert(m_pMovementData, "m_pMovementData can not be null");
    
    m_strMovementID		= _animationName;
    
    _durationTo		= (_durationTo == -1) ? m_pMovementData->getDurationTo() : _durationTo;
    
    _durationTween	= (_durationTween == -1) ? m_pMovementData->getDurationTween() : _durationTween;
    _durationTween  = (_durationTween == 0) ? m_pMovementData->getDuration() : _durationTween;
    
    _tweenEasing	= (_tweenEasing == TWEEN_EASING_MAX) ? m_pMovementData->getTweenEasing() : _tweenEasing;
    _loop			= (_loop < 0) ? m_pMovementData->getLoop() : _loop;
    
    
    
    ProcessBase::play((void*)_animationName, _durationTo, _durationTween, _loop, _tweenEasing);
    
    //! get key frame count
    m_iDuration = m_pMovementData->getDuration();
    
    if (m_iDuration == 1)
    {
        m_iLoop = SINGLE;
    }
    else
    {
        if (_loop)
        {
            m_iLoop = LIST_LOOP_START;
        }
        else
        {
            m_iLoop = LIST_START;
            m_iDuration --;
        }
        m_iDurationTween = _durationTween;
    }
    
    MovementBoneData *_movementBoneData = NULL;
    
    CCDictElement *_element = NULL;
    CCDictionary *_dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(_dict, _element)
    {
        Bone *_bone = (Bone*)_element->getObject();
        _movementBoneData = m_pMovementData->getMovementBoneData(_bone->getName().c_str());

        if(_movementBoneData && _movementBoneData->getFrameCount()>=0)
        {
            _bone->getTween()->play(_movementBoneData, _durationTo, _durationTween, _loop, _tweenEasing);
        }
        else
        {
			if(!_bone->getIgnoreMovementBoneData())
			{
				//! this bone is not include in this movement, so hide it
				_bone->getDisplayManager()->changeDisplayByIndex(-1, false);
				if (_bone->getTween())
				{
					_bone->getTween()->stop();
				}
			}
            
        }
    }
    
}


void Animation::playByIndex(int _animationIndex, int _durationTo, int _durationTween,  int _loop, int _tweenEasing)
{
    std::vector<std::string> &movName = m_pAnimationData->getMovNames();
    CCAssert((_animationIndex > -1) && (_animationIndex < movName.size()), "");
    
    std::string _animationName = movName.at(_animationIndex);
    play(_animationName.c_str(), _durationTo, _durationTween, _loop, _tweenEasing);
}



int Animation::getMovementCount()
{
    return m_pAnimationData->getMovementCount();
}
    
void Animation::updateHandler()
{
    
    if (m_fCurrentPercent >= 1)
    {
        switch(m_iLoop)
        {
            case LIST_START:
                
                m_iLoop = LIST;
                m_fCurrentFrame = (m_fCurrentPercent-1) * m_iTotalFrames;
                m_fCurrentPercent = m_fCurrentFrame / m_iDurationTween;
                
                if (m_fCurrentPercent >= 1.0f)
                {
                }
                else
                {
                    m_iTotalFrames = m_iDurationTween;
                    
                    m_pArmature->onMovementEvent(START, m_strMovementID.c_str());
                    MovementEventSignal.emit(m_pArmature, START, m_strMovementID.c_str());

					break;
                }
            case LIST:
            case SINGLE:
                m_fCurrentPercent = 1;
                m_bIsComplete = true;
                
                m_pArmature->onMovementEvent(COMPLETE, m_strMovementID.c_str());
				MovementEventSignal.emit(m_pArmature, COMPLETE, m_strMovementID.c_str());

                break;
            case LIST_LOOP_START:
                m_iLoop = 0;
                m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
                m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iTotalFrames);
                m_iTotalFrames = m_iDurationTween > 0 ? m_iDurationTween : 1;

                m_pArmature->onMovementEvent(START, m_strMovementID.c_str());
				MovementEventSignal.emit(m_pArmature, START, m_strMovementID.c_str());

                break;
            default:
                m_iLoop += int(m_fCurrentPercent);
                m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
                m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iTotalFrames);
                m_iToIndex = 0;
                
                m_pArmature->onMovementEvent(LOOP_COMPLETE, m_strMovementID.c_str());
				MovementEventSignal.emit(m_pArmature, LOOP_COMPLETE, m_strMovementID.c_str());

                break;
        }
    }
    
    
    if (m_iLoop >= LIST )
    {
        updateFrameData(m_fCurrentPercent);
    }
}

    
void Animation::updateFrameData(float _currentPercent)
{
    m_iPrevFrameIndex = m_iFrameIndex;
    m_iFrameIndex = m_iDuration * _currentPercent;
    m_iFrameIndex = m_iFrameIndex % m_iDuration;

// 	if (m_iPrevFrameIndex != m_iFrameIndex)
// 	{
// 
// 	}
    
//    updateMovementFrameData(_currentPercent);
}
    
void Animation::updateMovementFrameData(float _currentPercent)
{
    int _length = m_pMovementData->getMovFrameDataArr()->count();
    
    if(_length == 0){
        return;
    }
    float _played = m_iDuration * _currentPercent;
    
    if (!m_pCurrentFrameData || _played >= m_pCurrentFrameData->m_iDuration + m_pCurrentFrameData->m_iStart || _played < m_pCurrentFrameData->m_iStart) {
        while (true) {
            m_pCurrentFrameData =  m_pMovementData->getMoveFrameData(m_iToIndex);
            if (++m_iToIndex >= _length) {
                m_iToIndex = 0;
            }
            if(m_pCurrentFrameData && _played >= m_pCurrentFrameData->m_iStart && _played < m_pCurrentFrameData->m_iDuration + m_pCurrentFrameData->m_iStart){
                break;
            }
        }
        if(m_pCurrentFrameData->m_strEvent.length() != 0){
            m_pArmature->onMovementEvent(MOVEMENT_EVENT_FRAME, m_pCurrentFrameData->m_strEvent.c_str());
        }
        if(m_pCurrentFrameData->m_strSound.length() != 0){
            m_pArmature->onMovementEvent(SOUND_FRAME, m_pCurrentFrameData->m_strSound.c_str());
        }
        if(m_pCurrentFrameData->m_strMovement.length() != 0){
            play(m_pCurrentFrameData->m_strMovement.c_str());
        }
    }
}
    
void Animation::editMovement(const char *_animationName)
{
    play(_animationName);
    stop();
}

void Animation::editMovementByIndex(int _index)
{
    std::vector<std::string> &movName = m_pAnimationData->getMovNames();
    CCAssert((_index > -1) && (_index < movName.size()), "");
    
    std::string _animationName = movName.at(_index);
    editMovement(_animationName.c_str());
}
 
}