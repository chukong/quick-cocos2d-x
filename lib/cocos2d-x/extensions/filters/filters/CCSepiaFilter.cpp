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

#include "CCSepiaFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== CCSepiaFilter

CCSepiaFilter* CCSepiaFilter::create()
{
	CCSepiaFilter* __filter = new CCSepiaFilter();
	__filter->autorelease();
	return __filter;
}

CCSepiaFilter* CCSepiaFilter::create(float $resolation)
{
	CCSepiaFilter* __filter = CCSepiaFilter::create();
	__filter->setParameter();
	return __filter;
}

CCSepiaFilter::CCSepiaFilter()
{
	this->shaderName = kCCFilterShader_sepia;
}

CCGLProgram* CCSepiaFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCSepiaFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTextureColor_vert,
		ccFilterShader_sepia_frag);
	return __p;
}

void CCSepiaFilter::setParameter()
{
	initProgram();
}

void CCSepiaFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCSepiaFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCSepiaFilter::setUniforms(CCGLProgram* $cgp)
{

}

NS_CC_EXT_END
