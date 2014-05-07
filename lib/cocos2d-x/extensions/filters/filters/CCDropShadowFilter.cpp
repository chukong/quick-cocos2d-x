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

#include "CCDropShadowFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCDropShadowFilter

CCDropShadowFilter* CCDropShadowFilter::create()
{
	CCDropShadowFilter* __filter = new CCDropShadowFilter();
	__filter->autorelease();
	return __filter;
}

CCDropShadowFilter* CCDropShadowFilter::create(float $resolation)
{
	CCDropShadowFilter* __filter = CCDropShadowFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

CCDropShadowFilter::CCDropShadowFilter()
{
	this->shaderName = kCCFilterShader_drop_shadow;
}

CCGLProgram* CCDropShadowFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCDropShadowFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_drop_shadow_vert, 
		ccFilterShader_drop_shadow_frag);
	return __p;
}

void CCDropShadowFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void CCDropShadowFilter::initSprite(CCFilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	CCSize __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void CCDropShadowFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCDropShadowFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCDropShadowFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
	//CCLOG("CCDropShadowFilter::setUniforms %d", u_resolution);
	$cgp->setUniformLocationWith2f(u_resolution, _textureWidth, _textureHeight);
	//CCLOG("CCDropShadowFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",_textureWidth, _textureHeight);
}

NS_CC_EXT_END
