#include "SPTween.h"
#include "SPBone.h"
#include "SPArmature.h"
#include "SPUtilMath.h"
#include "SPTweenFunction.h"
#include "cocos2d.h"

namespace sp{


Tween* Tween::create(Bone *_bone)
{
    Tween *pTween = new Tween();
    if (pTween && pTween->init(_bone))
    {
        pTween->autorelease();
        return pTween;
    }
    CC_SAFE_DELETE(pTween);
    return NULL;

}



Tween::Tween()
    :m_pFrom(NULL)
    ,m_pTweenData(NULL)
    ,m_pBetween(NULL)
    ,m_pBone(NULL)
	,m_pCurrentKeyFrame(NULL)
	,m_pNextKeyFrame(NULL)
	,m_pMovementBoneData(NULL)
	,m_eFrameTweenEasing(Sine_EaseInOut)
    ,m_iFromIndex(0)
    ,m_iToIndex(0)
    ,m_pEditKeyFrame(NULL)
{

}


Tween::~Tween(void)
{
    CC_SAFE_DELETE( m_pFrom );
    CC_SAFE_DELETE( m_pTweenData );
    CC_SAFE_DELETE( m_pBetween );
}


bool Tween::init(Bone *_bone)
{
    bool bRet = false;
    do
    {

        m_pFrom = FrameData::create();
        m_pFrom->retain();
        
		m_pTweenData = FrameData::create();
        m_pTweenData->retain();

        m_pBetween = FrameData::create();
        m_pBetween->retain();
        
        m_pBone = _bone;

        bRet = true;
    }
    while (0);

    return bRet;
}


void Tween::play(MovementBoneData *_movementBoneData, int _durationTo, int _durationTween,  int _loop, int _tweenEasing)
{
    
    ProcessBase::play(NULL, _durationTo, _durationTween, _loop, _tweenEasing);
   

    m_pCurrentKeyFrame = NULL;
    m_pNextKeyFrame = NULL;
    m_pEditKeyFrame = NULL;
    m_bIsTweenKeyFrame = false;
    
    m_iTotalDuration = 0;
    m_iBetweenDuration = 0;
    m_iToIndex = 0;
    
    m_pMovementBoneData = _movementBoneData;
    

    if (m_pMovementBoneData->getFrameDatas()->count() == 1)
    {
        m_iLoop = SINGLE;
        m_pNextKeyFrame = m_pMovementBoneData->getFrameData(0);
        if(_durationTo == 0)
        {
            setBetween(m_pNextKeyFrame, m_pNextKeyFrame);
        }else{
            setBetween(m_pTweenData, m_pNextKeyFrame);
        }
        m_bIsTweenKeyFrame = true;
        m_eFrameTweenEasing = Linear;
        m_iDuration = m_pMovementBoneData->getDuration();
        m_iFromIndex = m_iToIndex =0;
    }
    else if (m_pMovementBoneData->getFrameDatas()->count() > 1)
    {
        if (_loop)
        {
            m_iLoop = LIST_LOOP_START;
            m_iDuration = m_pMovementBoneData->getDuration();
        }
        else
        {
            m_iLoop = LIST_START;
            m_iDuration = m_pMovementBoneData->getDuration() - 1;
        }

        m_iDurationTween = _durationTween * m_pMovementBoneData->getScale();

        if (_loop && m_pMovementBoneData->getDelay() != 0)
        {
            setBetween(m_pTweenData, tweenNodeTo(updateFrameData(1 - m_pMovementBoneData->getDelay()), m_pBetween));
            
        }
        else
        {
            m_pNextKeyFrame = m_pMovementBoneData->getFrameData(0);
            setBetween(m_pTweenData, m_pNextKeyFrame);
            m_bIsTweenKeyFrame = true;
        }
    }
}
    
void Tween::setMoveBoneData(MovementBoneData *_movBoneData)
{
    m_pMovementBoneData = _movBoneData;
}
    
MovementBoneData *Tween::getMoveBoneData()
{
    return m_pMovementBoneData; 
}

void Tween::gotoFrame(int _frameIndex)
{
    
    if(!m_pMovementBoneData)
    {
        return;
    }
    m_iDuration = m_pMovementBoneData->getDuration();
    
    if(_frameIndex > m_iDuration)
    {
        m_pBone->getDisplayManager()->changeDisplayByIndex(-1, false);
        stop();
        return;
    }
    
    ProcessBase::gotoFrame(_frameIndex);
    
    
    float _p = (float)m_iFrameIndex / m_iDuration;
    
    m_pEditKeyFrame = NULL;
    
    m_iTotalDuration = 0;
    m_iBetweenDuration = 0;
    m_iToIndex = 0;
    
    
    _p = updateFrameData(_p);
    
    if(m_bIsAtKeyFrame)
    {
        m_pEditKeyFrame = m_pMovementBoneData->getFrameData(m_iFromIndex);
        m_pBone->getDisplayManager()->changeDisplayByIndex(m_pEditKeyFrame->getDisplayIndex(), false);
    }
    else
    {
        m_pEditKeyFrame = NULL;
    }
    
    tweenNodeTo(_p);
}

    
void Tween::updateHandler()
{
	
    if (m_fCurrentPercent >= 1)
    {
        switch(m_iLoop)
        {
        case SINGLE:
            m_pCurrentKeyFrame = m_pNextKeyFrame;
            m_fCurrentPercent = 1;
            m_bIsComplete = true;
            break;
        case LIST_START:
            m_iLoop = LIST;
            if (m_iDurationTween <= 0)
            {
                m_fCurrentPercent = 1;
            }
            else
            {
                m_fCurrentPercent = (m_fCurrentPercent - 1) * m_iTotalFrames / m_iDurationTween;
            }
            if (m_fCurrentPercent >= 1)
            {
                m_fCurrentPercent = 1;
                m_bIsComplete = true;
                break;
            }
            else
            {
                m_iTotalFrames = m_iDurationTween;
                m_iTotalDuration = 0;
                break;
            }
        case LIST:
            m_fCurrentPercent = 1;
            m_bIsComplete = true;
            break;
        case LIST_LOOP_START:
            m_iLoop = 0;
            
			m_iTotalFrames = m_iDurationTween > 0 ? m_iDurationTween : 1;
                
			if (m_pMovementBoneData->getDelay() != 0)
            {
                //
                m_fCurrentFrame = (1 - m_pMovementBoneData->getDelay()) * (float)m_iTotalFrames;
                m_fCurrentPercent = m_fCurrentFrame / m_iTotalFrames;
                
                
            }else
            {
				m_fCurrentPercent = 0;
                m_fCurrentFrame = 0;
			}
                
            m_iTotalDuration = 0;
            m_iBetweenDuration = 0;
            m_iToIndex = 0;
            
            break;
        default:
            m_iLoop += int(m_fCurrentPercent);
            m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
            m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iTotalFrames);
 
            m_iTotalDuration = 0;
            m_iBetweenDuration = 0;
            m_iToIndex = 0;
            break;
        }
    }
    else if (m_iLoop < LIST)
    {
        m_fCurrentPercent = sin(m_fCurrentPercent * SP_HALF_PI);
    }

    if (m_iLoop >= LIST)
    {
        m_fCurrentPercent = updateFrameData(m_fCurrentPercent, true);
    }
	
    if(m_eFrameTweenEasing != TWEEN_EASING_MAX)
	{
		tweenNodeTo(m_fCurrentPercent);
	}
    else if(m_pCurrentKeyFrame)
    {
        tweenNodeTo(0);
    }
	
    if(m_pCurrentKeyFrame)
    {
        
        int _displayIndex = m_pCurrentKeyFrame->getDisplayIndex();

// 		if ( m_pCurrentKeyFrame->getDisplayIndex() == -1 || m_pNextKeyFrame->getDisplayIndex() == -1 )
// 		{
// 			_displayIndex = -1;
// 		}

        if (!m_pBone->getDisplayManager()->getForceChangeDisplay())
        {
            m_pBone->getDisplayManager()->changeDisplayByIndex(_displayIndex, false);
        }
		
        
        m_pBone->setZOrder(m_pCurrentKeyFrame->m_iZOrder);
        
//		if (m_pBone->getArmature())
//		{
//			m_pBone->getArmature()->setBonesIndexChanged(true);
//		}

//         Armature *_childAramture = m_pBone->childArmature;
//         m_pBone->changeDisplay(_displayIndex);
//         if(_childAramture)
//         {
//             _childAramture.origin.z = m_pCurrentKeyFrame->z;
//             if(m_pCurrentKeyFrame->m_strMovement)
//             {
//                 _childAramture.animation.play(m_pCurrentKeyFrame->m_strMovement);
//             }
//         }
        
        Armature *_childAramture = m_pBone->getChildArmature();
        
        if(_childAramture)
        {
            if(m_pCurrentKeyFrame->m_strMovement.compare("") != 0)
            {
                _childAramture->getAnimation()->play(m_pCurrentKeyFrame->m_strMovement.c_str());
            }
        }

        if(m_pCurrentKeyFrame->m_strEvent.length() != 0)
        {
            //m_pBone->dispatchEventWith(Event.BONE_EVENT_FRAME, m_pCurrentKeyFrame->event);
        }
        if(m_pCurrentKeyFrame->m_strSound.length() != 0)
        {
            //soundManager.dispatchEventWith(Event.SOUND_FRAME, m_pCurrentKeyFrame->sound);
        }
        m_pCurrentKeyFrame = NULL;
    }

//    if(m_bIsTweenKeyFrame)
//    {
//        //to
//        /*if(m_pNextKeyFrame.displayIndex < 0){
//        	//m_pBone->changeDisplay(m_pNextKeyFrame.displayIndex);
//        	if(m_pBone->armature){
//        		//m_pBone->armature.bonesIndexChanged = true;
//        	}
//        }*/
//        m_bIsTweenKeyFrame = false;
//    }
}

void Tween::setBetween(FrameData *_from, FrameData *_to)
{
	m_pFrom->copy(_from);
	if(_to->getDisplayIndex() < 0)
	{
		m_pBetween->subtract(_to, _to);
		return;
	}
	m_pBetween->subtract(_from, _to);
	
//     if(_from->getDisplayIndex() == -1 && _to->getDisplayIndex() == -1)
//     {
//         return;
//     }
//     else if (_from->getDisplayIndex() == -1)
//     {
//         m_pFrom->copy(_from);
//         m_pBetween->subtract(_to, _to);
//     }
//     else if(_to->getDisplayIndex() == -1)
//     {
//         m_pFrom->copy(_to);
//         m_pBetween->subtract(_from, _from);
//     }
//     else
//     {
//         m_pFrom->copy(_from);
//         m_pBetween->subtract(_from, _to);
//     }


}

FrameData *Tween::tweenNodeTo(float _percent, FrameData *_node)
{
	_node = _node == NULL ? m_pTweenData : _node;
    
    _node->m_fX = m_pFrom->m_fX + _percent * m_pBetween->m_fX;
    _node->m_fY = m_pFrom->m_fY + _percent * m_pBetween->m_fY;
    
//    CCPoint p1 = ccp(m_pFrom->m_fX, m_pFrom->m_fY);
//    CCPoint p2 = ccp(100, 0);
//    CCPoint p3 = ccp(200, 400);
//    CCPoint p4 = ccp(m_pFrom->m_fX + m_pBetween->m_fX, m_pFrom->m_fY + m_pBetween->m_fY);
//    
//    CCPoint p = bezierTo(_percent, p1, p2, p3, p4);
//    _node->m_fX = p.x;
//    _node->m_fY = p.y;
    
    _node->m_fScaleX = m_pFrom->m_fScaleX + _percent * m_pBetween->m_fScaleX;
    _node->m_fScaleY = m_pFrom->m_fScaleY + _percent * m_pBetween->m_fScaleY;
    
    _node->m_fSkewX = m_pFrom->m_fSkewX + _percent * m_pBetween->m_fSkewX;
    _node->m_fSkewY = m_pFrom->m_fSkewY + _percent * m_pBetween->m_fSkewY;
    
    
    if(m_pMovementBoneData && m_pMovementBoneData->getUseColorInfo())
    {
        _node->m_iAlpha = m_pFrom->m_iAlpha + _percent * m_pBetween->m_iAlpha;
        _node->m_iRed = m_pFrom->m_iRed + _percent * m_pBetween->m_iRed;
        _node->m_iGreen = m_pFrom->m_iGreen + _percent * m_pBetween->m_iGreen;
        _node->m_iBlue = m_pFrom->m_iBlue + _percent * m_pBetween->m_iBlue;
    }

    return _node;
}

float Tween::updateFrameData(float _currentPrecent, bool _activeFrame)
{

    float _played = (float)m_iDuration * _currentPrecent;
    
    
    FrameData *_from;
    FrameData *_to;
    bool _isListEnd;

    // if play to current frame's front or back, then find current frame again
    if (_played >= m_iTotalDuration || _played < m_iTotalDuration - m_iBetweenDuration)
    {
        m_bIsAtKeyFrame = false;
        
        
        /*
         *  get frame length, if m_iToIndex >= _length, then set m_iToIndex to 0, start anew.
         *  m_iToIndex is next index will play
         */
        int _length = m_pMovementBoneData->getFrameCount();
        do
        {
            if(_played == m_iTotalDuration)
            {
                m_bIsAtKeyFrame = true;
            }
            m_iBetweenDuration = m_pMovementBoneData->getFrameData(m_iToIndex)->getDuration();
            m_iTotalDuration += m_iBetweenDuration;
            m_iFromIndex = m_iToIndex;
            
            if (++m_iToIndex >= _length)
            {
                m_iToIndex = 0;
            }
        }
        while (_played >= m_iTotalDuration);
        
        
        _isListEnd = m_iLoop == LIST && m_iToIndex == 0;
        
        if(_isListEnd)
        {
            _to = _from = m_pMovementBoneData->getFrameData(m_iFromIndex);
        }
        else
        {
            _from = m_pMovementBoneData->getFrameData(m_iFromIndex);
            _to = m_pMovementBoneData->getFrameData(m_iToIndex);
        }
        
        m_eFrameTweenEasing = _from->getTweenEasing();
        
        if (_activeFrame)
        {
            m_pCurrentKeyFrame = m_pNextKeyFrame;

            if(!_isListEnd)
            {
                m_pNextKeyFrame = _to;
                m_bIsTweenKeyFrame = true;
            }
        }
        
        setBetween(_from, _to);
        
    }
    _currentPrecent = 1 - (m_iTotalDuration - _played) / (float)m_iBetweenDuration;

    
	/*
     *  If frame tween easing equal to TWEEN_EASING_MAX, then it will not do tween.
     */
    
    TweenType _tweenType;
    
 	if ( m_eFrameTweenEasing != TWEEN_EASING_MAX)
    {
        _tweenType = (m_eTweenEasing == TWEEN_EASING_MAX) ? m_eFrameTweenEasing : m_eTweenEasing;
        if (_tweenType != TWEEN_EASING_MAX)
        {
            _currentPrecent = TweenFunction::tweenTo(0, 1, _currentPrecent, 1, _tweenType);
        }
    }
// 	int _tweenEasing = 0.0f;
// 	if ( m_eFrameTweenEasing != TWEEN_EASING_MAX)
//     {
//         _tweenEasing = (int)(m_eTweenEasing == TWEEN_EASING_MAX) ? m_eFrameTweenEasing : m_eTweenEasing;
//         if (_tweenEasing)
//         {
//             _currentPrecent = getEaseValue(_currentPrecent, _tweenEasing);
//         }
//     }
    return _currentPrecent;
}

float Tween::getEaseValue(float _percent, float _easing)
{
    if (_easing > 1)
    {
        _percent = 0.5 * (1 - cos(_percent * SP_PI ));
        _easing -= 1;
    }
    else if (_easing > 0)
    {
        _percent = sin(_percent * SP_HALF_PI);
    }
    else
    {
        _percent = 1 - cos(_percent * SP_HALF_PI);
        _percent = -_easing;
    }
    return _percent * _easing + (1 - _easing);
}

    

void Tween::editRelativePosition(float x, float y)
{
    editRelativePositionX(x); 
    editRelativePositionY(y);
}


void Tween::editPosition(float x, float y)
{
    editPositionX(x);
    editPositionY(y);
}

void Tween::editRelativePositionX(float x)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fX += x;
    
    m_pTweenData->m_fX = m_pEditKeyFrame->m_fX;
}
    
void Tween::editPositionX(float x)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fX = x;
    
    m_pTweenData->m_fX = m_pEditKeyFrame->m_fX;
}

void Tween::editRelativePositionY(float y)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fY += y;
    
    m_pTweenData->m_fY = m_pEditKeyFrame->m_fY;
}
        
void Tween::editPositionY(float y)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fY = y;
    
    m_pTweenData->m_fY = m_pEditKeyFrame->m_fY;
}

void Tween::editRelativeRotation(float r)
{
    
    CCLOG("rotation : %f", CC_RADIANS_TO_DEGREES(r));
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fSkewX += r;
    m_pEditKeyFrame->m_fSkewY -= r;
    
    m_pEditKeyFrame->m_fSkewX = fmodf(m_pEditKeyFrame->m_fSkewX, 2 * SP_PI);
    m_pEditKeyFrame->m_fSkewY = fmodf(m_pEditKeyFrame->m_fSkewY, 2 * SP_PI);
    
    m_pTweenData->m_fSkewX = m_pEditKeyFrame->m_fSkewX;
    m_pTweenData->m_fSkewY = m_pEditKeyFrame->m_fSkewY;
}
    
void Tween::editRotation(float r)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fSkewX = r;
    m_pEditKeyFrame->m_fSkewY = -r;
    
    m_pEditKeyFrame->m_fSkewX = fmodf(m_pEditKeyFrame->m_fSkewX, 2 * SP_PI);
    m_pEditKeyFrame->m_fSkewY = fmodf(m_pEditKeyFrame->m_fSkewY, 2 * SP_PI);
    
    m_pTweenData->m_fSkewX = m_pEditKeyFrame->m_fSkewX;
    m_pTweenData->m_fSkewY = m_pEditKeyFrame->m_fSkewY;
}

void Tween::editRelativeScale(float scaleX, float scaleY)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fScaleX += scaleX;
    m_pEditKeyFrame->m_fScaleY += scaleY;
    
    m_pTweenData->m_fScaleX = m_pEditKeyFrame->m_fScaleX;
    m_pTweenData->m_fScaleY = m_pEditKeyFrame->m_fScaleY;
}
    
void Tween::editScale(float scaleX, float scaleY)
{
    editScaleX(scaleX);
    editScaleY(scaleY);
}

void Tween::editRelativeScaleX(float scaleX)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fScaleX += scaleX;
    
    m_pTweenData->m_fScaleX = m_pEditKeyFrame->m_fScaleX;
}
    
void Tween::editScaleX(float scaleX)
{
    if(!m_pEditKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fScaleX = scaleX;
    
    m_pTweenData->m_fScaleX = m_pEditKeyFrame->m_fScaleX;
}

void Tween::editRelativeScaleY(float scaleY)
{
    if(!m_pNextKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fScaleY += scaleY;
    
    m_pTweenData->m_fScaleY = m_pEditKeyFrame->m_fScaleY;
}
    
void Tween::editScaleY(float scaleY)
{
    if(!m_pNextKeyFrame)
    {
        return;
    }
    
    m_pEditKeyFrame->m_fScaleY = scaleY;
    
    m_pTweenData->m_fScaleY = m_pEditKeyFrame->m_fScaleY;
}
    
CCPoint Tween::getPosition()
{
    return ccp(m_pTweenData->m_fX, m_pTweenData->m_fY);
}

float Tween::getPositionX()
{
    return m_pTweenData->m_fX;
}

float Tween::getPositionY()
{
    return m_pTweenData->m_fY;
}

float Tween::getRotation()
{
    return m_pTweenData->m_fSkewX;
}

float Tween::getScaleX()
{
    return m_pTweenData->m_fScaleX;
}


float Tween::getScaleY()
{
    return m_pTweenData->m_fScaleY;
}
    

}