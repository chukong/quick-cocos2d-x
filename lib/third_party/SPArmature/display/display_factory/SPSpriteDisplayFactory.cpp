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

#include "SPArmatureDefine.h"
#include "SPTextureData.h"
#include "SPSpriteDisplayFactory.h"
#include "SPDisplayData.h"
#include "SPArmatureDataManager.h"
#include "SPDisplayFactoryManager.h"
#include "SPBatchNodeManager.h"
#include "SPSpriteDisplayData.h"

namespace sp{

    
CCObject *SpriteDisplayFactory::addDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, DisplayData *_DisplayData)
{
    
    SpriteDisplayData *_sdp = SpriteDisplayData::create();
    _sdp->copy((SpriteDisplayData*)_DisplayData);
    
    _decoDisplay->setDisplayData(_sdp);
    
    return createDisplay(_bone, _decoDisplay);
}

CCObject *SpriteDisplayFactory::createDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    CCSprite *_display = NULL;
    
    do {
        
        SpriteDisplayData *_displayData = (SpriteDisplayData*)_decoDisplay->getDisplayData();
        
        // remove .xxx
        std::string _textureName = _displayData->getDisplayName();
        size_t startPos = _textureName.find_last_of(".");
        
        if(startPos != std::string::npos)
        {
            _textureName = _textureName.erase(startPos);
        }


#if SP_DEBUG_FOR_EDIT

		_display = CCSprite::create();
		CCSprite *_sprite = NULL;

		if(_textureName.compare("") != 0)
		{
			_sprite = CCSprite::create((_textureName + ".png").c_str());
		}
		else
		{
			_decoDisplay->setDisplay(_display);
			break;
		}
		_display->addChild(_sprite, 0, 0);
        
#else
		if(_textureName.compare("") == 0)
		{
			_display = CCSprite::create();
		}
		else
		{
			_display = CCSprite::createWithSpriteFrameName((_textureName + ".png").c_str());
		}
#endif

		_decoDisplay->setDisplay(_display);
		
   
        TextureData *_textureData = ArmatureDataManager::sharedArmatureDataManager()->getTextureData(_textureName.c_str());
        
        if(_textureData)
        {
            /*
             *  init display anchorPoint， every Texture have a anchor point
             */
            float _anchorPointX = _textureData->m_fPivotX / _textureData->m_fWidth;
            float _anchorPointY = (_textureData->m_fHeight - _textureData->m_fPivotY) / _textureData->m_fHeight;
#if SP_DEBUG_FOR_EDIT
            ((CCSprite*)_sprite)->setAnchorPoint(ccp(_anchorPointX, _anchorPointY));
#else
            ((CCSprite*)_display)->setAnchorPoint(ccp(_anchorPointX, _anchorPointY));
#endif
        }
        
        
        
#if SP_DEBUG_FOR_EDIT

		//! create CCTexture2DMutable
		CCSize _size = ((CCSprite*)_sprite)->getContentSize();

		CCTexture2DMutable *_textureMutable = createTexture2DMutable(_size.width, _size.height, (_textureName + ".png").c_str());
		_textureMutable->autorelease();

		_decoDisplay->setTextureMutable(_textureMutable);


		//! create ContourSprite
        ContourSprite *_contourSprite = _decoDisplay->getContourSprite();
        
        if(_contourSprite)
        {
            _contourSprite->removeFromParentAndCleanup(true);
        }
        
        _contourSprite = ContourSprite::create();
        
        
        if (_textureData && _textureData->getContourCount() > 0)
        {
            _contourSprite->addContourDataList(_textureData->getContourDatas());
        }
        
        _contourSprite->_setZOrder(INT_MAX);
        
        _decoDisplay->setContourSprite(_contourSprite);
        
#endif
        
        createContourPoints(_bone, _decoDisplay);

    } while (0);
    
    return _display;
}
    
void SpriteDisplayFactory::changeDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    CCSprite *_renderNode = (CCSprite*)getRenderNode(_bone, _decoDisplay);
    
    
#if SP_DEBUG_FOR_EDIT
    BatchNodeManager::sharedBatchNodeManager()->getCurrentLayer()->addChild(_renderNode);
#else
    SpriteDisplayData *_displayData = (SpriteDisplayData*)_decoDisplay->getDisplayData();
    
    // remove .xxx
    std::string _textureName = _displayData->getDisplayName();
    size_t startPos = _textureName.find_last_of(".");
    
    if(startPos != std::string::npos)
    {
        _textureName = _textureName.erase(startPos);
    }
    
    _textureName += ".png";
    
    if(_textureName.compare(".png") == 0)
    {
        //BatchNodeManager::sharedBatchNodeManager()->getCurrentLayer()->addChild(_renderNode);
    }
    else
    {
        std::string imagePath =  ArmatureDataManager::sharedArmatureDataManager()->getDisplayImagePath(_textureName.c_str());
        
        CCSpriteBatchNode *_batchNode = BatchNodeManager::sharedBatchNodeManager()->getBatchNode(imagePath);
        _batchNode->addChild(_renderNode);
    }
#endif
    
    
#if SP_DEBUG_FOR_EDIT
    ContourSprite *_contourSprite = _decoDisplay->getContourSprite();
    //CCLOG("change display %s", m_strName.c_str());
    
    if(_contourSprite)
    {
        _contourSprite->removeFromParentAndCleanup(true);
        BatchNodeManager::sharedBatchNodeManager()->getCurrentLayer()->addChild(_contourSprite);
    }
#endif
    
    _bone->setChildArmature(NULL);
    

	setDisplay(_bone, _decoDisplay, _renderNode);
}

CCNode *SpriteDisplayFactory::getRenderNode(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return (CCNode*)_decoDisplay->getDisplay();
}

void SpriteDisplayFactory::updateDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, FrameData *_frameData)
{
	CCSprite *_renderNode = (CCSprite*)getRenderNode(_bone, _decoDisplay);

    CCAffineTransform t = _bone->m_pGlobalTransformMatrix;
    
#if SP_DEBUG_FOR_EDIT
	t.a /= _bone->getTween()->getScaleX();
	t.b /= _bone->getTween()->getScaleX();
	t.c /= _bone->getTween()->getScaleY();
	t.d /= _bone->getTween()->getScaleY();
#endif

    _renderNode->setAdditionalTransform(t);
    _renderNode->setDirty(true);
	

#if SP_DEBUG_FOR_EDIT
	if(_decoDisplay)
	{
		ContourSprite *_contourSprite = _decoDisplay->getContourSprite();
		_contourSprite->translateFormOtherNode(t);
        
        _contourSprite->setScaleX(_bone->getTween()->getScaleX());
		_contourSprite->setScaleY(_bone->getTween()->getScaleY());
         
		_renderNode = (CCSprite*)_renderNode->getChildByTag(0);

		_renderNode->setScaleX(_bone->getTween()->getScaleX());
		_renderNode->setScaleY(_bone->getTween()->getScaleY());

        
		ContourPoints *_contourPoints = _decoDisplay->getContourPoints();
		_contourPoints->getRenderNode()->translateFormOtherNode(t);
		_contourPoints->setBoundingBox(_renderNode->boundingBox());
        
	}
#endif
    
    MovementBoneData *_moveBoneData = _bone->getTween()->getMoveBoneData();
    if(_moveBoneData && _moveBoneData->getUseColorInfo())
    {
        _renderNode->setColor(ccc3(_frameData->m_iRed, _frameData->m_iGreen, _frameData->m_iBlue));
        _renderNode->setOpacity(_frameData->m_iAlpha);
    }
}

void SpriteDisplayFactory::editAnchorPoint(CCPoint &p, Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    
    CCSprite *_renderNode = (CCSprite*)getRenderNode(_bone, _decoDisplay);

#if SP_DEBUG_FOR_EDIT
    _renderNode = (CCSprite*)_renderNode->getChildByTag(0);
#endif
    
    CCPoint oldAnchorPoint = _renderNode->getAnchorPoint();
    
    CCRect boundingBox = _renderNode->boundingBox();
    
    float deltaX, deltaY = 0;
    float deltaX2, deltaY2 = 0;
    float tempX, tempY = 0;
    
    
    CCRect rect = _renderNode->getTextureRect();
    tempX = rect.size.width * (p.x - oldAnchorPoint.x);
    tempY = rect.size.height * (p.y - oldAnchorPoint.y);
    
    
    CCAffineTransform t = _bone->m_pSlefTransformMatrix;
    
    deltaX = (float)((double)t.a * tempX + (double)t.c * tempY);
    deltaY = (float)((double)t.b * tempX + (double)t.d * tempY);
    
    _bone->getTween()->editRelativePosition(deltaX, deltaY);
    
    
    
    deltaX2 = boundingBox.size.width * (p.x - oldAnchorPoint.x);
    deltaY2 = boundingBox.size.height * (p.y - oldAnchorPoint.y);
    
    CCArray *_children = _bone->getChildren();
    CCObject *_object = NULL;
    CCARRAY_FOREACH(_children, _object)
    {
        Bone *_bone = (Bone*)_object;
        
        _bone->getTween()->editRelativePosition(-deltaX2, -deltaY2);
    }
    
    _renderNode->setAnchorPoint(ccp(p.x, p.y));
    
    _decoDisplay->getContourPoints()->setAnchorPoint(p);
}
    
CCTexture2DMutable *SpriteDisplayFactory::createTexture2DMutable(float _width, float _height, const char *_imageFile)
{
    CCTexture2DMutable *_textureMutable = new CCTexture2DMutable();
    _textureMutable->initWithImageFile(_imageFile);
    
    return _textureMutable;
}


CCRect SpriteDisplayFactory::getBoundingBox(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	CCRect boundingBox;
	CCNode *_renderNode = getRenderNode(_bone, _decoDisplay);
#if SP_DEBUG_FOR_EDIT
	boundingBox = _renderNode->getChildByTag(0)->boundingBox();
	boundingBox = CCRectApplyAffineTransform(boundingBox, _renderNode->nodeToParentTransform());
#else
	boundingBox = _renderNode->boundingBox();
#endif

	return boundingBox;
}

CCSize SpriteDisplayFactory::getContentSize(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
#if SP_DEBUG_FOR_EDIT
	return getRenderNode(_bone, _decoDisplay)->getChildByTag(0)->getContentSize();
#else
	return getRenderNode(_bone, _decoDisplay)->getContentSize();
#endif
	
}
    
CCPoint SpriteDisplayFactory::getAnchorPoint(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
#if SP_DEBUG_FOR_EDIT
	return getRenderNode(_bone, _decoDisplay)->getChildByTag(0)->getAnchorPoint();
#else
	return getRenderNode(_bone, _decoDisplay)->getAnchorPoint();
#endif
    
}

CCPoint SpriteDisplayFactory::getAnchorPointInPoints(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
#if SP_DEBUG_FOR_EDIT
	return getRenderNode(_bone, _decoDisplay)->getChildByTag(0)->getAnchorPointInPoints();
#else
	return getRenderNode(_bone, _decoDisplay)->getAnchorPointInPoints();
#endif
    
}


}