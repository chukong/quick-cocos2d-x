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

#include "SPBone.h"
#include "SPUtilMath.h"
#include "SPArmature.h"
#include "SPArmatureDataManager.h"
#include "SPBatchNodeManager.h"

#include "SPArmatureDisplayFactory.h"
#include "SPDisplayManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#endif

//using namespace SP_JSBind;

namespace sp{
 
//INIT_JS_CLASS_ROOT(Bone)
// 
// 
//JS_FUNCTION_BEGIN(Bone)
//JS_FUNCTION_BIND(init, 1)
//    
//JS_FUNCTION_BIND(setPosition, 2)
//JS_FUNCTION_BIND(setPositionX, 1)
//JS_FUNCTION_BIND(setPositionY, 1)
//JS_FUNCTION_BIND(setRotation, 1)
//JS_FUNCTION_BIND(setScale, 1)
//JS_FUNCTION_BIND(setScaleX, 1)
//JS_FUNCTION_BIND(setScaleY, 1)
//
//
//JS_FUNCTION_BIND(setName, 1)
//JS_FUNCTION_BIND(getName, 0)
//
//JS_FUNCTION_BIND(setIgnoreMovementBoneData, 1)
//    
//JS_FUNCTION_BIND(addDisplay, 2)
//JS_FUNCTION_BIND(changeDisplayByIndex, 2)
//
//JS_FUNCTION_BIND(getPositionX, 0)
//JS_FUNCTION_BIND(getPositionY, 0)
//JS_FUNCTION_BIND(getRotation, 0)
//JS_FUNCTION_BIND(getScaleX, 0)
//JS_FUNCTION_BIND(getScaleY, 0)
//JS_FUNCTION_BIND(getParentBone, 0)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(Bone)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(Bone)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(Bone)
//JS_PROPERTY_END

    
Bone* Bone::create()
{

    Bone *pBone = new Bone();
    if (pBone && pBone->init())
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return NULL;

}
    
Bone* Bone::create(const char *_name)
{
    
    Bone *pBone = new Bone();
    if (pBone && pBone->init(_name))
    {
        pBone->autorelease();
        return pBone;
    }
    CC_SAFE_DELETE(pBone);
    return NULL;
}
//
//Bone::Bone(DEFINE_JS obj)
//{
//    m_pUserData = NULL;
//    m_pTweenData = NULL;
//	m_pCombinedData = NULL;
//    m_pParent = NULL;
//    m_pArmature = NULL;
//    m_pChildArmature = NULL;
//    m_pBoneData = NULL;
//    m_pTween = NULL;
//    m_pTween = NULL;
//    m_pChildren = NULL;
//    m_pDisplayManager = NULL;
//    m_iZOrder = 0;
//	m_bIgnoreMovementBoneData = false;
//	m_pGlobalTransformMatrix = CCAffineTransformMake(1, 0, 0, 1, 0, 0);
//}
    
Bone::Bone()
{
//    CREATE_JS_OBJECT(Bone)
    
    m_pUserData = NULL;
    m_pTweenData = NULL;
	m_pCombinedData = NULL;
    m_pParent = NULL;
    m_pArmature = NULL;
    m_pChildArmature = NULL;
    m_pBoneData = NULL;
    m_pTween = NULL;
    m_pTween = NULL;
    m_pChildren = NULL;
    m_pDisplayManager = NULL;
    m_iZOrder = 0;
	m_bIgnoreMovementBoneData = false;
	m_pGlobalTransformMatrix = CCAffineTransformMake(1, 0, 0, 1, 0, 0);
	m_bRootBone = false;
}


Bone::~Bone(void)
{

   
    CC_SAFE_DELETE(m_pChildren);
    CC_SAFE_DELETE(m_pTween);
    CC_SAFE_DELETE(m_pUserData);
	CC_SAFE_DELETE(m_pCombinedData);
    CC_SAFE_DELETE(m_pDisplayManager);
    
    if(m_pBoneData)
    {
        m_pBoneData->release();
    }

//	DELETE_JS;
}

bool Bone::init()
{
    return Bone::init(NULL);
}


bool Bone::init(const char *_name)
{
    bool bRet = false;
    do
    {
        
        if(NULL != _name)
        {
            m_strName = _name;
        }

		// init m_pUserData
        CC_SAFE_DELETE(m_pUserData);
        m_pUserData = FrameData::create();
        m_pUserData->retain();
        
        CC_SAFE_DELETE(m_pCombinedData);
        m_pCombinedData = FrameData::create();
        m_pCombinedData->retain();

        CC_SAFE_DELETE(m_pTween);
		m_pTween = Tween::create(this);
		m_pTween->retain();
		m_pTweenData = m_pTween->getTweenNode();
        
        CC_SAFE_DELETE(m_pDisplayManager);
        m_pDisplayManager = DisplayManager::create(this);
        m_pDisplayManager->retain();
        
        
        bRet = true;
    }
    while (0);

    return bRet;
}

void Bone::setBoneData(BoneData *_boneData)
{
    CCAssert(NULL != _boneData, "_boneData must not be NULL");
	
    m_pBoneData = _boneData;
    
    m_pBoneData->retain();
    
    //! init m_strName
    m_strName = m_pBoneData->m_strName;
    //! init zorder
    m_iZOrder = m_pBoneData->m_iZOrder;
    
    m_pDisplayManager->initDisplayList(_boneData);
}
    
BoneData *Bone::getBoneData()
{
    return m_pBoneData;
}
    
    
void Bone::update(float dt)
{
	do 
	{
		if (m_pArmature)
		{
            m_pTween->update(dt);
            
			//! if current have no display or the bone is not visible, then return.
			if((-1 == m_pDisplayManager->getCurrentDisplayIndex() || !m_pDisplayManager->isVisible()))
			{
				break;
			}

            updateTransform();
        
			m_pDisplayManager->updateDisplay();
        
		}
	} while (0);
    

    
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pChildren, _object)
    {
        Bone *_bone = (Bone*)_object;
        _bone->update(dt);
    }

}
    
void Bone::updateTransform()
{
    m_pCombinedData->m_fX = m_pUserData->m_fX + m_pTweenData->m_fX;
    m_pCombinedData->m_fY = m_pUserData->m_fY + m_pTweenData->m_fY;
    
    m_pCombinedData->m_fSkewX = m_pUserData->m_fSkewX + m_pTweenData->m_fSkewX;
    m_pCombinedData->m_fSkewY = m_pUserData->m_fSkewY + m_pTweenData->m_fSkewY;
    
    m_pCombinedData->m_fScaleX = m_pUserData->m_fScaleX + m_pTweenData->m_fScaleX - 1;
    m_pCombinedData->m_fScaleY = m_pUserData->m_fScaleY + m_pTweenData->m_fScaleY - 1;
    
    MovementBoneData *_moveBoneData = getTween()->getMoveBoneData();
    if(_moveBoneData && _moveBoneData->getUseColorInfo())
    {
        m_pCombinedData->m_iAlpha = m_pUserData->m_iAlpha + m_pTweenData->m_iAlpha - 255;
        m_pCombinedData->m_iRed = m_pUserData->m_iRed + m_pTweenData->m_iRed - 255;
        m_pCombinedData->m_iGreen = m_pUserData->m_iGreen + m_pTweenData->m_iGreen - 255;
        m_pCombinedData->m_iBlue = m_pUserData->m_iBlue + m_pTweenData->m_iBlue - 255;
    }
    
    
    float cosX = cos(m_pCombinedData->m_fSkewX);
    float sinX = sin(m_pCombinedData->m_fSkewX);
    float cosY = cos(m_pCombinedData->m_fSkewY);
    float sinY = sin(m_pCombinedData->m_fSkewY);
    
    if (m_pDisplayManager->getCurrentDecorativeDisplay())
    {
        m_pSlefTransformMatrix.a = m_pCombinedData->m_fScaleX * cosY;
        m_pSlefTransformMatrix.b = m_pCombinedData->m_fScaleX * sinY;
        m_pSlefTransformMatrix.c = m_pCombinedData->m_fScaleY * sinX;
        m_pSlefTransformMatrix.d = m_pCombinedData->m_fScaleY * cosX;
        m_pSlefTransformMatrix.tx = m_pCombinedData->m_fX;
        m_pSlefTransformMatrix.ty = m_pCombinedData->m_fY;
    }

    
    if (m_pChildren && m_pChildren->count() > 0)
    {
		if(m_bRootBone)
		{
			m_pTransformMatrixForChildren = m_pSlefTransformMatrix;
		}
		else
		{
			
			/*
			 *  m_pTransformMatrixForChildren is used for children, and it don't contain
			 *  the parent scale value
			 */
			m_pTransformMatrixForChildren.a = cosY;
			m_pTransformMatrixForChildren.b = sinY;
			m_pTransformMatrixForChildren.c = sinX;
			m_pTransformMatrixForChildren.d = cosX;
			m_pTransformMatrixForChildren.tx = m_pCombinedData->m_fX;
			m_pTransformMatrixForChildren.ty = m_pCombinedData->m_fY;
		}



        
    }
    
    if(m_pParent)
    {
        m_pGlobalTransformMatrix = CCAffineTransformConcat(m_pSlefTransformMatrix, m_pParent->m_pTransformMatrixForChildren);
        
        if (m_pChildren && m_pChildren->count() > 0)
        {
            m_pTransformMatrixForChildren = CCAffineTransformConcat(m_pTransformMatrixForChildren, m_pParent->m_pTransformMatrixForChildren);
        }
    }
    else
    {
        m_pGlobalTransformMatrix = m_pSlefTransformMatrix;
    }
    
}


void Bone::addChildBone(Bone* _child)
{
	CCAssert( NULL != _child, "Argument must be non-nil");
	CCAssert( NULL == _child->m_pParent, "child already added. It can't be added again");
    
	if(!m_pChildren)
	{
		childrenAlloc();
	}

	if (m_pChildren->indexOfObject(_child) == UINT_MAX)
    {
        m_pChildren->addObject(_child);
        _child->setParentBone(this);
    }
}

void Bone::removeChildBone(Bone *_bone, bool _cleanup)
{
    if ( m_pChildren->indexOfObject(_bone) != UINT_MAX )
    {
        
        CCArray *_ccbones = _bone->m_pChildren;
        CCObject *_object = NULL;
        CCARRAY_FOREACH(_ccbones, _object)
        {
            Bone *_ccBone = (Bone*)_object;
            _bone->removeChildBone(_ccBone, _cleanup);
        }
        
        _bone->RemoveFromParentSignal.emit(_bone->getName().c_str(), NULL);
        
        _bone->setParentBone(NULL);
        
        if(_cleanup)
        {
            _bone->getDisplayManager()->setDisplayRenderNode(NULL);
        }
        
        m_pChildren->removeObject(_bone);
 
    }
}

void Bone::removeFromParent(bool _cleanup)
{
    if (NULL != m_pParent)
    {
        m_pParent->removeChildBone(this, _cleanup);
    }
}

void Bone::setParentBone(Bone *_parent)
{
    m_pParent = _parent;
    
//    if(NULL == m_pParent)
//    {
//        if(NULL != m_pArmature)
//        {
//            m_pArmature->removeBone(this);
//            m_pArmature = NULL;
//        }
//    }
}

Bone *Bone::getParentBone()
{
    return m_pParent;
}

void Bone::childrenAlloc(void)
{
	CC_SAFE_DELETE(m_pChildren);
	m_pChildren = CCArray::createWithCapacity(4);
	m_pChildren->retain();
}


void Bone::setChildArmature(Armature *_armature)
{
	if(m_pChildArmature)
	{
		
        /*
         *  remove child armature from armature's bone list
         */
        m_pChildArmature->getRootBone()->removeFromParent(true);

		m_pChildArmature->getRootBone()->getDisplayManager()->setVisible(false);

		m_pChildArmature->setArmature(NULL);
	}

	m_pChildArmature = _armature;

	if (m_pChildArmature)
	{
		m_pChildArmature->getRootBone()->getDisplayManager()->setVisible(true);
		m_pChildArmature->setArmature(m_pArmature);
	}
	
}

Armature *Bone::getChildArmature()
{
	return m_pChildArmature;
}

    
void Bone::setZOrder(int _zorder)
{
    /*
	 *	if _zorder is equal to m_iZOrder,then do nothing
	 */
    if (_zorder == m_iZOrder) {
        return;
    }
    
    m_iZOrder = _zorder;
    
    m_pArmature->setBonesIndexChanged(true);
}
    
int Bone::getZOrder()
{
    return m_iZOrder;
}
    
void Bone::setPosition(float x, float y)
{
    m_pUserData->m_fX = x;
    m_pUserData->m_fY = y;
}
    
void Bone::setPositionX(float x)
{
    m_pUserData->m_fX = x;
}
    
void Bone::setPositionY(float y)
{
    m_pUserData->m_fY = y;
}

void Bone::setRotation(float r)
{
    m_pUserData->m_fSkewX = CC_DEGREES_TO_RADIANS(r);
    m_pUserData->m_fSkewY = CC_DEGREES_TO_RADIANS(-r);
}


void Bone::setScale(float scale)
{
    m_pUserData->m_fScaleX = scale;
    m_pUserData->m_fScaleY = scale;
}
    
void Bone::setScaleX(float scaleX)
{
    m_pUserData->m_fScaleX = scaleX;
}
    
void Bone::setScaleY(float scaleY)
{
    m_pUserData->m_fScaleY = scaleY;
}

CCPoint Bone::getPosition()
{
	return ccp(m_pUserData->m_fX, m_pUserData->m_fY);
}

float Bone::getPositionX()
{
    return m_pUserData->m_fX;
}
    
float Bone::getPositionY()
{
    return m_pUserData->m_fY;
}

float Bone::getRotation()
{
    return m_pUserData->m_fSkewX;
}

float Bone::getScaleX()
{
    return m_pUserData->m_fScaleX;
}


float Bone::getScaleY()
{
    return m_pUserData->m_fScaleY;
}
    
void Bone::setName(const char *_name)
{
    m_strName = _name;
}
    
std::string &Bone::getName()
{
    return m_strName;
}

    
CCArray *Bone::getChildren()
{
    return m_pChildren;
}

FrameData *Bone::getCombinedData()
{
    return m_pCombinedData;
}

void Bone::addDisplay(DisplayData *_displayData, int _index)
{
    m_pDisplayManager->addDisplay(_displayData, _index);
}

void Bone::changeDisplayByIndex(int _index, bool _force)
{
    m_pDisplayManager->changeDisplayByIndex(_index, _force);
}
    
    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                     Edit Function                              ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////

    

void Bone::editName(const char *_name)
{
    
    NameChanedSignal.emit(this, _name);

    setName(_name);
    
    m_pBoneData->m_strName = _name;
    
    CCObject *_object = NULL;
    
    CCARRAY_FOREACH(m_pChildren, _object)
    {
        Bone *_bone = (Bone*)_object;
        _bone->getBoneData()->m_strParent = _name;
    }
    
}

}
