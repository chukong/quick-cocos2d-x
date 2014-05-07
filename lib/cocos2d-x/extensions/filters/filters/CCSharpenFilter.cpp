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

#include "CCSharpenFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCSharpenFilter

CCSharpenFilter* CCSharpenFilter::create()
{
	CCSharpenFilter* __filter = new CCSharpenFilter();
	__filter->autorelease();
	return __filter;
}

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, float $widthFactor, float $heightFactor)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $widthFactor, $heightFactor);
	return __filter;
}

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, int $amount)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $amount);
	return __filter;
}

CCSharpenFilter::CCSharpenFilter()
: _sharpness(0.f)
, _widthFactor(0.f)
, _heightFactor(0.f)
, _amount(0)
{
	this->shaderName = kCCFilterShader_sharpen;
}

CCGLProgram* CCSharpenFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCSharpenFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_sharpen_vert, ccFilterShader_sharpen_frag);
	return __p;
}

void CCSharpenFilter::setParameter(float $sharpness, float $widthFactor, float $heightFactor)
{
	_sharpness = $sharpness;
	_widthFactor = $widthFactor;
	_heightFactor = $heightFactor;
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::setParameter(float $sharpness, int $amount)
{
	_sharpness = $sharpness;
	_amount = $amount;
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::initSprite(CCFilteredSprite* $sprite)
{
	// If _amount is not 0, then calculate the value of the widthFactor and the heightFactor.
	if (_amount != 0)
	{
		CCSize __size = $sprite->getContentSize();
		_widthFactor = 1.0f / __size.width * _amount;
		_heightFactor = 1.0f / __size.height * _amount;
	}
	initProgram();
}

void CCSharpenFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCSharpenFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCSharpenFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_sharpness = $cgp->getUniformLocationForName("u_sharpness");
	int u_widthFactor = $cgp->getUniformLocationForName("u_widthFactor");
	int u_heightFactor = $cgp->getUniformLocationForName("u_heightFactor");
	//CCLOG("CCSharpenFilter::setUniforms %d, %d, %d", u_sharpness, u_widthFactor, u_heightFactor);
	$cgp->setUniformLocationWith1f(u_sharpness, _sharpness);
	$cgp->setUniformLocationWith1f(u_widthFactor, _widthFactor);
	$cgp->setUniformLocationWith1f(u_heightFactor, _heightFactor);
	//CCLOG("CCSharpenFilter::setUniforms u_sharpness:%.2f, u_widthFactor:%.5f, u_heightFctor:%.5f",_sharpness, _widthFactor, _heightFactor);
}

NS_CC_EXT_END