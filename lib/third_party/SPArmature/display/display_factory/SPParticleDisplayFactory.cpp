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
#include "SPParticleDisplayFactory.h"
#include "SPDisplayData.h"
#include "SPArmature.h"
#include "SPDisplayFactoryManager.h"
#include "SPParticleDisplayData.h"
#include "SPShaderNode.h"
#include "SPBatchNodeManager.h"

namespace sp{
    
    
CCObject *ParticleDisplayFactory::addDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, DisplayData *_DisplayData)
{
    ParticleDisplayData *_adp = ParticleDisplayData::create(); ;
    _adp->copy((ParticleDisplayData*)_DisplayData);
    
    _decoDisplay->setDisplayData(_adp);
    
    return createDisplay(_bone, _decoDisplay);
}
    
CCObject *ParticleDisplayFactory::createDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    CCObject *_display = NULL;
    
    ParticleDisplayData *_displayData = (ParticleDisplayData*)_decoDisplay->getDisplayData();
    
	CCParticleSystem *_system = CCParticleSystemQuad::create(_displayData->getPlist().c_str());

	_display = _system;

    _decoDisplay->setDisplay(_display);
    
    return _display;
}

void ParticleDisplayFactory::updateDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, FrameData *_frameData)
{
	CCNode *_renderNode = getRenderNode(_bone, _decoDisplay);

	if(_renderNode)
	{
		_renderNode->setPosition(_bone->m_pGlobalTransformMatrix.tx, _bone->m_pGlobalTransformMatrix.ty);
		_renderNode->setScaleX(_frameData->m_fScaleX);
		_renderNode->setScaleY(_frameData->m_fScaleY);
	}

}

    
}