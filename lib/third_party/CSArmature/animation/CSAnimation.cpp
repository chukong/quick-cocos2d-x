#include "CSAnimation.h"
#include "CSArmature.h"
#include "CSBone.h"
#include "CSArmatureDefine.h"
#include "CSUtilMath.h"
#include "CSConstValue.h"
#include "CSDatas.h"

using namespace cocos2d;
using namespace std;

namespace cs {

        
Animation *Animation::create(Armature *armature)
{
    Animation *pARmatureAnimation = new Animation();
    if (pARmatureAnimation && pARmatureAnimation->init(armature))
    {
        pARmatureAnimation->autorelease();
        return pARmatureAnimation;
    }
    CC_SAFE_DELETE(pARmatureAnimation);
    return NULL;
}

    
Animation::Animation()
    :m_pAnimationData(NULL)
    ,m_strMovementID("")
    ,m_pArmature(NULL)
    ,m_iToIndex(0)
{

}

Animation::~Animation(void)
{
	CC_SAFE_RELEASE_NULL(m_pTweenList);
	CC_SAFE_RELEASE_NULL(m_pAnimationData);
}

bool Animation::init(Armature *armature)
{
    bool bRet = false;
    do
    {
        m_pArmature = armature;
        
		m_pTweenList = new CCArray();
		m_pTweenList->init();

        bRet = true;
    }
    while (0);
    
    return bRet;
}


void Animation:: pause()
{
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pTweenList, object)
	{
		((Tween*)object)->pause();
	}
    ProcessBase::pause();
}
  
void Animation::resume()
{
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pTweenList, object)
	{
		((Tween*)object)->resume();
	}
    ProcessBase::resume();
}

void Animation::stop()
{
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pTweenList, object)
	{
		((Tween*)object)->stop();
	}
    m_pTweenList->removeAllObjects();
    ProcessBase::stop();
}

void Animation::setAnimationScale(float animationScale )
{
    if(animationScale == m_fAnimationScale)
    {
        return;
    }

	m_fAnimationScale = animationScale;
    
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pTweenList, object)
	{
		((Tween*)object)->setAnimationScale(m_fAnimationScale);
	}
}


void Animation::play(const char *animationName, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    CCAssert(m_pAnimationData, "m_pAnimationData can not be null");
    
	m_pMovementData = m_pAnimationData->getMovement(animationName);
    CCAssert(m_pMovementData, "m_pMovementData can not be null");
    
	//! Get key frame count
	rawDuration = m_pMovementData->duration;

    m_strMovementID = animationName;
    
	//! Further processing parameters
    durationTo = (durationTo == -1) ? m_pMovementData->durationTo : durationTo;
    
    durationTween = (durationTween == -1) ? m_pMovementData->durationTween : durationTween;
    durationTween = (durationTween == 0) ? m_pMovementData->duration : durationTween;
    
    tweenEasing	= (tweenEasing == TWEEN_EASING_MAX) ? m_pMovementData->tweenEasing : tweenEasing;
    loop = (loop < 0) ? m_pMovementData->loop : loop;
    
    
    ProcessBase::play((void*)animationName, durationTo, durationTween, loop, tweenEasing);
    
    
	if (rawDuration == 1)
	{
		m_eLoopType = SINGLE_FRAME;
	}
	else
	{
		if (loop)
		{
			m_eLoopType = ANIMATION_TO_LOOP_FRONT;
		}
		else
		{
			m_eLoopType = ANIMATION_NO_LOOP;
			rawDuration --;
		}
		m_iDurationTween = durationTween;
	}
    
    MovementBoneData *movementBoneData = NULL;
    m_pTweenList->removeAllObjects();

    CCDictElement *element = NULL;
    CCDictionary *dict = m_pArmature->getBoneDic();

	CCDICT_FOREACH(dict, element)
	{
        Bone *bone = (Bone*)element->getObject();
        movementBoneData = (MovementBoneData*)m_pMovementData->movBoneDataDic.objectForKey(bone->getName());

		Tween *tween = bone->getTween();
		if(movementBoneData && movementBoneData->frameList.count()>0)
        {
			m_pTweenList->addObject(tween);
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);
        }
        else
        {
			if(!bone->getIgnoreMovementBoneData())
			{
				//! this bone is not include in this movement, so hide it
				bone->getDisplayManager()->changeDisplayByIndex(-1, false);
				tween->stop();
			}
            
        }
	}

	//m_pArmature->update(0);
}


void Animation::playByIndex(int animationIndex, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    std::vector<std::string> &movName = m_pAnimationData->movementNames;
    CC_ASSERT((animationIndex > -1) && (animationIndex < movName.size()));
    
    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, durationTween, loop, tweenEasing);
}



int Animation::getMovementCount()
{
    return m_pAnimationData->getMovementCount();
}

void Animation::update(float dt)
{
	ProcessBase::update(dt);
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pTweenList, object)
	{
		((Tween*)object)->update(dt);
	}
}
    
void Animation::updateHandler()
{
	if (m_fCurrentPercent >= 1)
	{
		switch(m_eLoopType)
		{
		case ANIMATION_NO_LOOP:

			m_eLoopType = ANIMATION_MAX;
			m_fCurrentFrame = (m_fCurrentPercent-1) * m_iNextFrameIndex;
			m_fCurrentPercent = m_fCurrentFrame / m_iDurationTween;

			if (m_fCurrentPercent >= 1.0f)
			{
			}
			else
			{
				m_iNextFrameIndex = m_iDurationTween;

				MovementEventSignal.emit(m_pArmature, START, m_strMovementID.c_str());

				break;
			}
		case ANIMATION_MAX:
		case SINGLE_FRAME:
			m_fCurrentPercent = 1;
			m_bIsComplete = true;

			MovementEventSignal.emit(m_pArmature, COMPLETE, m_strMovementID.c_str());

			break;
		case ANIMATION_TO_LOOP_FRONT:
			m_eLoopType = ANIMATION_LOOP_FRONT;
			m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
			m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);
			m_iNextFrameIndex = m_iDurationTween > 0 ? m_iDurationTween : 1;

			MovementEventSignal.emit(m_pArmature, START, m_strMovementID.c_str());

			break;
		default:
			//                m_eLoopType += int(m_fCurrentPercent);
			m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
			m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);
			m_iToIndex = 0;

			MovementEventSignal.emit(m_pArmature, LOOP_COMPLETE, m_strMovementID.c_str());

			break;
		}
	}

	if (m_eLoopType == ANIMATION_LOOP_FRONT || m_eLoopType == ANIMATION_LOOP_BACK)
	{
		updateFrameData(m_fCurrentPercent);
	}
}

    
void Animation::updateFrameData(float currentPercent)
{
	m_iPrevFrameIndex = m_iCurFrameIndex;
    m_iCurFrameIndex = rawDuration * currentPercent;
    m_iCurFrameIndex = m_iCurFrameIndex % rawDuration;
    
    updateMovementFrameData(currentPercent);
}
    
void Animation::updateMovementFrameData(float _currentPercent)
{
//     int length = m_pMovementData->movBoneDataDic.count();
//     
//     if(length == 0){
//         return;
//     }
//     float _played = rawDuration * _currentPercent;
//     
//     if (!m_pCurrentFrameData || _played >= m_pCurrentFrameData->m_iDuration + m_pCurrentFrameData->m_iStart || _played < m_pCurrentFrameData->m_iStart) {
//         while (true) {
//             m_pCurrentFrameData =  m_pMovementData->getMoveFrameData(m_iToIndex);
//             if (++m_iToIndex >= _length) {
//                 m_iToIndex = 0;
//             }
//             if(m_pCurrentFrameData && _played >= m_pCurrentFrameData->m_iStart && _played < m_pCurrentFrameData->m_iDuration + m_pCurrentFrameData->m_iStart){
//                 break;
//             }
//         }
//         if(m_pCurrentFrameData->m_strEvent.length() != 0){
//             m_pArmature->onMovementEvent(MOVEMENT_EVENT_FRAME, m_pCurrentFrameData->m_strEvent.c_str());
//         }
//         if(m_pCurrentFrameData->m_strSound.length() != 0){
//             m_pArmature->onMovementEvent(SOUND_FRAME, m_pCurrentFrameData->m_strSound.c_str());
//         }
//         if(m_pCurrentFrameData->m_strMovement.length() != 0){
//             play(m_pCurrentFrameData->m_strMovement.c_str());
//         }
//     }
}

 
}