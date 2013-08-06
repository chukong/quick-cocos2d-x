#include "CSProcessBase.h"
#include "CSUtilMath.h"

using namespace cocos2d;

namespace cs {

ProcessBase::ProcessBase(void)
    :m_fAnimationScale(1)
    ,m_bIsComplete(true)
    ,m_bIsPause(true)
	,m_bIsPlaying(false)
    ,m_fCurrentFrame(0)
	,m_fCurrentPercent(0.0f)
    ,m_iDurationTween(0)
    ,rawDuration(0)
	,m_eLoopType(ANIMATION_LOOP_BACK)
	,m_eTweenEasing(Linear)
	,m_iCurFrameIndex(0)
	,m_bIsLoopBack(false)
{
    /*
     *  set m_fAnimationInternal defualt value to CCDirector::sharedDirector()
     *  ->getAnimationInterval(), in line with game update speed
     */
    m_fAnimationInternal = CCDirector::sharedDirector()->getAnimationInterval();
}


ProcessBase::~ProcessBase(void)
{
}


void ProcessBase::pause()
{
    m_bIsPause = true;
}


void ProcessBase::resume()
{
    m_bIsPause = false;
}

void ProcessBase::stop()
{
    m_bIsComplete = true;
    m_fCurrentFrame = 0;
    m_fCurrentPercent = 0;
}

void ProcessBase::play(void * animation, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    m_bIsComplete = false;
    m_bIsPause = false;
	m_bIsPlaying = true;
    m_fCurrentFrame = 0;
    
    /*
     *  Set m_iTotalFrames to durationTo, it is used for change tween between two animation. 
     *  When changing end, m_iTotalFrames will be setted to _durationTween
     */
    m_iNextFrameIndex = durationTo;
    m_eTweenEasing = (TweenType)tweenEasing;
    
}
  
void ProcessBase::update(float dt)
{ 
    
    if (m_bIsComplete || m_bIsPause)
    {
        return;
    }
    
    /*
     *  Fileter the m_iDuration <=0 and dt >1
     *  If dt>1, generally speaking  the reason is the device is stuck.
     */
    if(rawDuration<=0 || dt>1)
    {
        return;
    }
    
	if (m_iNextFrameIndex <= 0) {
		m_fCurrentFrame = m_iNextFrameIndex = 1;
	}

    /*
     *  update m_fCurrentFrame, every update add the frame passed. 
     *  dt/m_fAnimationInternal determine it is not a frame animation. If frame speed changed, it will not make our 
     *  animation speed slower or quicker.
     */
    m_fCurrentFrame += m_fAnimationScale * (dt/m_fAnimationInternal);
    

	m_fCurrentPercent = m_fCurrentFrame / m_iNextFrameIndex;

	/*
	 *	if m_fCurrentFrame is bigger or equal than m_iTotalFrames, then reduce it util m_fCurrentFrame is 
     *  smaller than m_iTotalFrames
	 */
    m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);
    
	updateHandler();
}


    
void ProcessBase::gotoFrame(int frameIndex)
{
    m_iCurFrameIndex = frameIndex;
    stop();
}
    
int ProcessBase::getCurrentFrameIndex()
{
    return m_iCurFrameIndex;
}


}