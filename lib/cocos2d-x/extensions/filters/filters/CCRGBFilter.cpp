/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCRGBFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCRGBFilter

CCRGBFilter* CCRGBFilter::create()
{
	CCRGBFilter* __filter = new CCRGBFilter();
	__filter->autorelease();
	return __filter;
}

CCRGBFilter* CCRGBFilter::create(float $readAdj, float $greenAdj, float $blueAdj)
{
	CCRGBFilter* __filter = CCRGBFilter::create();
	__filter->setParameter($readAdj, $greenAdj, $blueAdj);
	return __filter;
}

CCRGBFilter::CCRGBFilter()
: _redAdj(1.f)
, _greenAdj(1.f)
, _blueAdj(1.f)
{
	this->shaderName = kCCFilterShader_rgb;
}

CCGLProgram* CCRGBFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCRGBFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_rgb_frag);
	return __p;
}

void CCRGBFilter::setParameter(float $redAdj, float $greenAdj, float $blueAdj)
{
	_redAdj = $redAdj;
	_greenAdj = $greenAdj;
	_blueAdj = $blueAdj;
	initProgram();
}

void CCRGBFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCRGBFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCRGBFilter::setUniforms(CCGLProgram* $cgp)
{
	int __redAdj = $cgp->getUniformLocationForName("u_redAdj");
	int __greenAdj = $cgp->getUniformLocationForName("u_greenAdj");
	int __blueAdj = $cgp->getUniformLocationForName("u_blueAdj");
	//CCLOG("CCRGBFilter::setUniforms %d, %d, %d", __redAdj, __greenAdj, __blueAdj);
	$cgp->setUniformLocationWith1f(__redAdj, _redAdj);
	$cgp->setUniformLocationWith1f(__greenAdj, _greenAdj);
	$cgp->setUniformLocationWith1f(__blueAdj, _blueAdj);
	/*CCLOG("CCRGBFilter::setUniforms u_redAdj:%.2f, u_greenAdj:%.5f, u_blueAdj:%.5f",
		_redAdj, _greenAdj, _blueAdj);*/
}

NS_CC_EXT_END