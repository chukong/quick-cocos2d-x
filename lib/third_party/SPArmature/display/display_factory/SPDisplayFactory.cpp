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

#include "SPDisplayFactory.h"
#include "SPDisplayData.h"
#include "SPBone.h"
#include "SPBatchNodeManager.h"
#include "SPArmature.h"


namespace sp{

void DisplayFactory::changeDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	CCNode *_display = getRenderNode(_bone, _decoDisplay);
	BatchNodeManager::sharedBatchNodeManager()->getCurrentLayer()->addChild(_display);

	setDisplay(_bone, _decoDisplay, _display);
}

void DisplayFactory::updateDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, FrameData *_frameData)
{
	CCNode *_renderNode = getRenderNode(_bone, _decoDisplay);

	if(_renderNode)
	{
		_renderNode->setAdditionalTransform(_bone->m_pGlobalTransformMatrix);
	}
	
}

void DisplayFactory::editAnchorPoint(CCPoint &p, Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    
}

CCNode *DisplayFactory::getRenderNode(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return (CCNode*)_decoDisplay->getDisplay();
}
   
float DisplayFactory::getWidth(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return getContentSize(_bone, _decoDisplay).width;
}

float DisplayFactory::getHeight(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return getContentSize(_bone, _decoDisplay).height;
}

CCRect DisplayFactory::getBoundingBox(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return getRenderNode(_bone, _decoDisplay)->boundingBox();
}

CCSize DisplayFactory::getContentSize(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	return getRenderNode(_bone, _decoDisplay)->getContentSize();
}

CCPoint DisplayFactory::getAnchorPoint(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    return getRenderNode(_bone, _decoDisplay)->getAnchorPoint();
}

CCPoint DisplayFactory::getAnchorPointInPoints(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    return getRenderNode(_bone, _decoDisplay)->getAnchorPointInPoints();
}


void DisplayFactory::setDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, CCNode *_renderNode)
{
	Armature *_armature = _bone->getArmature(); 
	CCNode *_originDisplayRenderNode = _bone->getDisplayManager()->getDisplayRenderNode();

    /*
     *  if already have a display we can just use the display's vertexz, or we should update the armature's children order
     */
    if (_originDisplayRenderNode)
    {
        if (_armature && _armature->getRenderType() == BATCHNODE_VERTEXZ)
        {
            _renderNode->setVertexZ(_bone->getDisplayManager()->getDisplayRenderNode()->getVertexZ());
        }
        else
        {
            _renderNode->_setZOrder(_bone->getDisplayManager()->getDisplayRenderNode()->getZOrder());
        }
    }else{
        if(_armature)
        {
            _armature->setBonesIndexChanged(true);
        }
    }
    
    _bone->getDisplayManager()->setDisplayRenderNode(_renderNode);
}


void DisplayFactory::createContourPoints(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
#if SP_DEBUG_FOR_EDIT

	//! create ContourPoints
	ContourPoints *_contourPoints = new ContourPoints("Armature/BindingBoxBorder.png");
	_contourPoints->setBoundingBox(getBoundingBox(_bone, _decoDisplay));
	BatchNodeManager::sharedBatchNodeManager()->getCurrentLayer()->addChild(_contourPoints->getRenderNode());

	_contourPoints->getRenderNode()->_setZOrder(INT_MAX);
    CCPoint p = getAnchorPoint(_bone, _decoDisplay);
    _contourPoints->setAnchorPoint(p);
    
	_decoDisplay->setContourPoints(_contourPoints);

#endif
}

}