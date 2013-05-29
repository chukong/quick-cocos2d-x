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

#include "SPDisplayManager.h"
#include "SPDisplayFactoryManager.h"
#include "SPBone.h"
#include "SPUtilMath.h"
#include "SPArmature.h"


namespace sp{

DisplayManager *DisplayManager::create(Bone *_bone)
{
    DisplayManager *pDisplayManager = new DisplayManager();
    if (pDisplayManager && pDisplayManager->init(_bone))
    {
        pDisplayManager->autorelease();
        return pDisplayManager;
    }
    CC_SAFE_DELETE(pDisplayManager);
    return NULL;
}
    
    
DisplayManager::DisplayManager()
    :m_pDecoDisplayList(NULL)
    ,m_pCurrentDecoDisplay(NULL)
    ,m_pDisplayRenderNode(NULL)
    ,m_iDisplayIndex(-1)
    ,m_bForceChangeDisplay(false)
    ,m_pBone(NULL)
    ,m_bVisible(true)
{
}
    
DisplayManager::~DisplayManager()
{
    CC_SAFE_DELETE(m_pDecoDisplayList);
    
    if( m_pDisplayRenderNode )
    {
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        m_pDisplayRenderNode->release();
//        CCLOG(" m_pDisplayRenderNode :  %i", m_pDisplayRenderNode->retainCount());
        m_pDisplayRenderNode = NULL;
    }
}
    
bool DisplayManager::init(Bone *_bone)
{
    bool ret = false;
    
    do {
        
        m_pBone = _bone;
        
        initDisplayList(_bone->getBoneData());
        
        ret = true;
    } while (0);
    
    return ret;
}

    
void DisplayManager::addDisplay(DisplayData *_displayData, int _index)
{
    DecorativeDisplay *_decoDisplay = NULL;
    
    if(_index >= 0 && _index < m_pDecoDisplayList->count())
    {
        _decoDisplay = (DecorativeDisplay*)m_pDecoDisplayList->objectAtIndex(_index);
    }
    else
    {
        _decoDisplay = DecorativeDisplay::create();
        m_pDecoDisplayList->addObject(_decoDisplay);
    }
    
    
    DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->addDisplay(m_pBone, _decoDisplay, _displayData);
    
    //! if changed display index is current display index, then change current display to the new display
    if(_index == m_iDisplayIndex)
    {
        m_iDisplayIndex = -1;
        changeDisplayByIndex(_index, false);
    }
}



void DisplayManager::insertDisplay(DisplayData *_displayData, int _index)
{
    DecorativeDisplay *_decoDisplay = NULL;
    
    _decoDisplay = DecorativeDisplay::create();
    m_pDecoDisplayList->insertObject(_decoDisplay, _index);
    
    
    DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->addDisplay(m_pBone, _decoDisplay, _displayData);
    
    //! if changed display index is current display index, then change current display to the new display
    if(_index == m_iDisplayIndex)
    {
        m_iDisplayIndex = -1;
        changeDisplayByIndex(_index, false);
    }
}


void DisplayManager::removeDisplay(int _index)
{
    m_pDecoDisplayList->removeObjectAtIndex(_index);
    
    if(_index == m_iDisplayIndex)
    {
        setDisplayRenderNode(NULL);
    }
    
}
    
void DisplayManager::changeDisplayByIndex(int _index, bool _force)
{
    CCAssert(_index>=-1 && (m_pDecoDisplayList ? _index<(int)m_pDecoDisplayList->count() : true), "the _index value is out of range");
    
    
    m_bForceChangeDisplay = _force;
    
    /*
     *	if _index is equal to current display index,then do nothing
     */
    if ( m_iDisplayIndex == _index)
    {
        return;
    }
    
    
    m_iDisplayIndex = _index;
    
    /*
     *	m_iDisplayIndex == -1, it means you want to hide you display
     */
    if (-1 == m_iDisplayIndex)
    {
        if(m_pDisplayRenderNode)
        {
            m_pDisplayRenderNode->removeFromParentAndCleanup(true);
            setDisplayRenderNode(NULL);
            
        }
        return;
    }
    
    
    DecorativeDisplay *_decoDisplay = (DecorativeDisplay*)m_pDecoDisplayList->objectAtIndex(m_iDisplayIndex);
    
    m_pCurrentDecoDisplay = _decoDisplay;
    
    DisplayFactoryManager::getFactory((DisplayType)_decoDisplay->getDisplayData()->getDisplayType())->changeDisplay(m_pBone, _decoDisplay);
    
}
    
void DisplayManager::setDisplayRenderNode(CCNode *_displayRenderNode)
{
    if (m_pDisplayRenderNode)
    {
        m_pDisplayRenderNode->removeFromParentAndCleanup(true);
        m_pDisplayRenderNode->release();
    }
    
    m_pDisplayRenderNode = _displayRenderNode;
    if(m_pDisplayRenderNode)
    {
        m_pDisplayRenderNode->retain();
    }
}
    
CCNode *DisplayManager::getDisplayRenderNode()
{
    return m_pDisplayRenderNode;
}
    
int DisplayManager::getCurrentDisplayIndex()
{
    return m_iDisplayIndex;
}

DecorativeDisplay *DisplayManager::getCurrentDecorativeDisplay()
{
    return m_pCurrentDecoDisplay;
}

 

void DisplayManager::initDisplayList(BoneData *_boneData)
{
    CC_SAFE_DELETE(m_pDecoDisplayList);
    m_pDecoDisplayList = CCArray::create();
    m_pDecoDisplayList->retain();
    
    if(!_boneData)
    {
        return;
    }
    
    CCObject *_object = NULL;
    CCArray *_displayDataList = _boneData->getDisplayList();
    CCARRAY_FOREACH(_displayDataList, _object)
    {
        DisplayData *_displayData = (DisplayData*)_object;
        
        DecorativeDisplay *_decoDisplay = DecorativeDisplay::create();
        _decoDisplay->setDisplayData(_displayData);
        
        CCObject *_display = NULL;
        _display = DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->createDisplay(m_pBone, _decoDisplay);
        
        m_pDecoDisplayList->addObject(_decoDisplay);
    }
}
    
void DisplayManager::updateDisplay()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->updateDisplay(m_pBone, m_pCurrentDecoDisplay, m_pBone->getCombinedData());
}
    
    
bool DisplayManager::containPoint(CCPoint &_point)
{
#if !SP_DEBUG_FOR_EDIT
    return false;
#endif
    
    if(!m_bVisible)
    {
        return false;
    }
    
    bool ret = false;
    
    switch (m_pCurrentDecoDisplay->getDisplayData()->getDisplayType())
    {
        case SP_DISPLAY_SPRITE:
        {
            /*
             *  First we first check if the point is in the sprite content rect. If false, then we continue to check
             *  the contour point. If this step is also false, then we can say the bone not contain this point.
             *
             */
            
            CCPoint _outPoint = ccp(0, 0);
            
            CCSprite *_sprite = (CCSprite*)m_pCurrentDecoDisplay->getDisplay();
            _sprite = (CCSprite*)_sprite->getChildByTag(0);
            
            ret = SP_SPRITE_CONTAIN_POINT_WITH_RETURN(_sprite, _point, _outPoint);
            
            ContourPoints *_contourPoints = m_pCurrentDecoDisplay->getContourPoints();
            if( _contourPoints && _contourPoints->isVisible())
            {
                //! check whether or not click on a anchor point
                ContourPointType type = _contourPoints->containWorldPoint(_point);
                
                //! If click point is on a kind of contour point, return true
                if(type != POINT_MIN)
                {
                    ret = true;
                    return ret;
                }
            }
            
            //! If ret is false, then click point is neither on the sprite rect and contour point, return false.
            if(!ret)
            {
                return ret;
            }
            
            
            if(m_pCurrentDecoDisplay->getTextureMutable() && m_pCurrentDecoDisplay->getTextureMutable()->pixelAt(_outPoint).a == 0)
            {
                ret = false;
            }
            
            return ret;
        }
            break;
            
        default:
            break;
    }
    return ret;
}

bool DisplayManager::containPoint(float x, float y)
{
    CCPoint p = ccp(x, y);
    return containPoint(p);
}

int DisplayManager::getClickedContourPointType()
{
    ContourPoints *_contourPoints = m_pCurrentDecoDisplay->getContourPoints();
    if(_contourPoints && _contourPoints->isVisible())
    {
        return _contourPoints->getClickedPointType();
    }
    
    return POINT_MIN;
}

void DisplayManager::setVisible(bool _visible)
{
    m_bVisible = _visible;
    
    if(!m_bVisible)
    {
        if(m_pCurrentDecoDisplay->getContourSprite())
        {
            m_pCurrentDecoDisplay->getContourSprite()->setVisible(m_bVisible);
        }
        if(m_pCurrentDecoDisplay->getContourPoints())
        {
            m_pCurrentDecoDisplay->getContourPoints()->setVisible(m_bVisible);
        }
    }
    
    switch (m_pCurrentDecoDisplay->getDisplayData()->getDisplayType())
    {
        case SP_DISPLAY_SPRITE:
        {
            m_pDisplayRenderNode->setVisible(_visible);
        }
            break;
        case SP_DISPLAY_ARMATURE:
        {
            if(m_pBone->getChildArmature())
            {
                m_pBone->getChildArmature()->setVisible(_visible);
            }
        }
            break;
        default:
            break;
    }
    
    
}

bool DisplayManager::isVisible()
{
    return m_bVisible;
}

void DisplayManager::showContour(bool _show)
{
    if (m_pCurrentDecoDisplay->getContourSprite())
    {
        m_pCurrentDecoDisplay->getContourSprite()->setVisible(_show);
    }
    if(m_pCurrentDecoDisplay->getContourPoints())
    {
        m_pCurrentDecoDisplay->getContourPoints()->setVisible(_show);
    }
}

bool DisplayManager::isShowContour()
{
    if (m_pCurrentDecoDisplay->getContourSprite())
    {
        return m_pCurrentDecoDisplay->getContourSprite()->isVisible();
    }
    return false;
}
    

CCSize DisplayManager::getContentSize()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    return DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getContentSize(m_pBone, m_pCurrentDecoDisplay);
}

float DisplayManager::getWidth()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    return DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getWidth(m_pBone, m_pCurrentDecoDisplay);
}

float DisplayManager::getHeight()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    return DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getHeight(m_pBone, m_pCurrentDecoDisplay);
}

CCRect DisplayManager::getBoundingBox()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    return DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getBoundingBox(m_pBone, m_pCurrentDecoDisplay);
}


CCPoint DisplayManager::getAnchorPoint()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    CCPoint p = DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getAnchorPoint(m_pBone, m_pCurrentDecoDisplay);
    
    return p;
}

CCPoint DisplayManager::getAnchorPointInPoints()
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    CCPoint p = DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->getAnchorPointInPoints(m_pBone, m_pCurrentDecoDisplay);
    
    return p;
}

void DisplayManager::convertPointToSpace(CCPoint &p)
{
    
    if(m_pDisplayRenderNode)
    {
        p = m_pDisplayRenderNode->convertToNodeSpace(p);
    }
    else
    {
        CCAffineTransform t = m_pBone->m_pGlobalTransformMatrix;
        
#if SP_DEBUG_FOR_EDIT
        t.a /= m_pBone->getScaleX();
        t.b /= m_pBone->getScaleX();
        t.c /= m_pBone->getScaleY();
        t.d /= m_pBone->getScaleY();
#endif
        
        CCNode *node = CCNode::create();
        node->setAdditionalTransform(t);
        
        p = node->convertToNodeSpace(p);
    }
    
    
}
    

void DisplayManager::editAnchorPoint(CCPoint &p)
{
    DisplayData *_displayData = m_pCurrentDecoDisplay->getDisplayData();
    return DisplayFactoryManager::getFactory((DisplayType)_displayData->getDisplayType())->editAnchorPoint(p, m_pBone, m_pCurrentDecoDisplay);

    //    if(m_pCurrentDecoDisplay->getDisplayData()->getDisplayType() == SP_DISPLAY_SPRITE)
    //    {
    //        CCSprite *_sprite = (CCSprite*)m_pDisplayRenderNode;
    //
    //        std::string &_displayName = ((SpriteDisplayData*)m_pCurrentDecoDisplay->getDisplayData())->getDisplayName();
    //
    //        std::string _textureName = DisplayData::changeDisplayToTexture(_displayName.c_str());
    //
    //        TextureData *_textureData = ArmatureDataManager::sharedArmatureDataManager()->getTextureData(_textureName.c_str());
    //
    //        if(_textureData)
    //        {
    //            _textureData->m_fPivotX = _sprite->getAnchorPointInPoints().x;
    //            _textureData->m_fPivotY = _sprite->getAnchorPointInPoints().y;
    //        }
    //
    //    }
}

void DisplayManager::addEditDisplay(DisplayData *_displayData, int _index)
{
    addDisplay(_displayData, _index);

    if(m_pBone->getBoneData()->getDisplayCount() >0 && m_pBone->getBoneData()->getDisplayData(_index))
    {
        m_pBone->getBoneData()->changeDisplayDataAtIndex(_index, _displayData);
    }
    else{
        m_pBone->getBoneData()->addDisplayData(_displayData);
    }
}



void DisplayManager::insertEditDisplay(DisplayData *_displayData, int _index)
{
    insertDisplay(_displayData, _index);

    m_pBone->getBoneData()->insertDisplayData(_displayData, _index);
}


void DisplayManager::removeEditDisplay(int _index)
{
    removeDisplay(_index);
    
    m_pBone->getBoneData()->removeDisplayData(_index);
}
    

}