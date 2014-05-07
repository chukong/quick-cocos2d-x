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

#include "CCHueFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCHueFilter

CCHueFilter* CCHueFilter::create()
{
	CCHueFilter* __filter = new CCHueFilter();
	__filter->autorelease();
	return __filter;
}

CCHueFilter* CCHueFilter::create(float $brightness)
{
	CCHueFilter* __filter = CCHueFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCHueFilter::CCHueFilter()
{
	this->shaderName = kCCFilterShader_hue;
	_param = 0.f;
}

CCGLProgram* CCHueFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCHueFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_hue_frag);
	return __p;
}

void CCHueFilter::setParameter(float $param)
{
	_param = fmodf($param, 360.f)*M_PI / 180;
	initProgram();
}

void CCHueFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCHueFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCHueFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_hueAdjust = $cgp->getUniformLocationForName("u_hueAdjust");
	//CCLOG("CCHueFilter::setUniforms %d", u_hueAdjust);
	$cgp->setUniformLocationWith1f(u_hueAdjust, _param);
	//CCLOG("CCHueFilter::setUniforms _param:%.2f", _param);
}

NS_CC_EXT_END
