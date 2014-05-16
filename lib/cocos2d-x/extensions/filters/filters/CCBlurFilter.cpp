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

#include "CCBlurFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCBlurBaseFilter

CCBlurBaseFilter::CCBlurBaseFilter()
: _param(0.1f)
{
}

void CCBlurBaseFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCBlurBaseFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCBlurBaseFilter::setUniforms(CCGLProgram* $cgp)
{
	int __radius = $cgp->getUniformLocationForName("u_radius");
	//CCLOG("CCFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__radius, _param);
	//CCLOG("CCBlurBaseFilter::setUniforms radius:%d, param:%f", __radius, _param);
}

void CCBlurBaseFilter::setParameter(float $param)
{
	_param = $param;
	//CCLOG("CCBlurBaseFilter::setParameter %f", _param);
	initProgram();
}

//================== CCHBlurFilter

CCHBlurFilter* CCHBlurFilter::create()
{
	CCHBlurFilter* __filter = new CCHBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCHBlurFilter* CCHBlurFilter::create(float $param)
{
	CCHBlurFilter* __filter = CCHBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCHBlurFilter::CCHBlurFilter()
{
	this->shaderName = kCCFilterShader_hblur;
}

CCGLProgram* CCHBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
	//CCLOG("CCHBlurFilter::loadShader %f", _param);
	return __p;
}

//================== CCVBlurFilter

CCVBlurFilter* CCVBlurFilter::create()
{
	CCVBlurFilter* __filter = new CCVBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCVBlurFilter* CCVBlurFilter::create(float $param)
{
	CCVBlurFilter* __filter = CCVBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCVBlurFilter::CCVBlurFilter()
{
	this->shaderName = kCCFilterShader_vblur;
}

CCGLProgram* CCVBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);
	//CCLOG("CCVBlurFilter::loadShader %f", _param);
	return __p;
}

//================== CCGaussianHBlurFilter

CCGaussianHBlurFilter* CCGaussianHBlurFilter::create()
{
	CCGaussianHBlurFilter* __filter = new CCGaussianHBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCGaussianHBlurFilter* CCGaussianHBlurFilter::create(float $param)
{
	CCGaussianHBlurFilter* __filter = CCGaussianHBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCGaussianHBlurFilter::CCGaussianHBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_hblur;
}

CCGLProgram* CCGaussianHBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCGaussianHBlurFilter::loadShader %f, program:%d", _param, __p);
	__p->initWithVertexShaderByteArray(ccPositionTextureColor_vert,
		ccFilterShader_gaussian_hblur_frag);
	return __p;
}

void CCGaussianHBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	CCBlurBaseFilter::setUniforms($cgp);

	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
	$cgp->setUniformLocationWith1f(u_resolution, _resolation);
	//CCLOG("CCGaussianHBlurFilter::setUniforms u_resolution:%f", _resolation);
}

void CCGaussianHBlurFilter::initSprite(CCFilteredSprite* $sprite)
{
	//_resolation = $sprite->getContentSize().width;
	_resolation = 1024;
	//CCLOG("CCGaussianHBlurFilter.initSprite resulation:%f", _resolation);
}

//================== CCGaussianVBlurFilter

CCGaussianVBlurFilter* CCGaussianVBlurFilter::create()
{
	CCGaussianVBlurFilter* __filter = new CCGaussianVBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCGaussianVBlurFilter* CCGaussianVBlurFilter::create(float $param)
{
	CCGaussianVBlurFilter* __filter = CCGaussianVBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCGaussianVBlurFilter::CCGaussianVBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_vblur;
}

CCGLProgram* CCGaussianVBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCGaussianVBlurFilter::loadShader %f, program:%d", _param, __p);
	__p->initWithVertexShaderByteArray(ccPositionTextureColor_vert,
		ccFilterShader_gaussian_vblur_frag);
	return __p;
}

void CCGaussianVBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	CCBlurBaseFilter::setUniforms($cgp);

	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
	$cgp->setUniformLocationWith1f(u_resolution, _resolation);
	//CCLOG("CCGaussianVBlurFilter::setUniforms u_resolution:%f", _resolation);
}

void CCGaussianVBlurFilter::initSprite(CCFilteredSprite* $sprite)
{
	//_resolation = $sprite->getContentSize().height;
	_resolation = 1024;
	//CCLOG("CCGaussianVBlurFilter.initSprite resulation:%f", _resolation);
}

//================== CCZoomBlurFilter

CCZoomBlurFilter* CCZoomBlurFilter::create()
{
	CCZoomBlurFilter* __filter = new CCZoomBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCZoomBlurFilter* CCZoomBlurFilter::create(float $blurSize, float $centerX, float $centerY)
{
	CCZoomBlurFilter* __filter = CCZoomBlurFilter::create();
	__filter->setParameter($blurSize, $centerX, $centerY);
	return __filter;
}

CCZoomBlurFilter::CCZoomBlurFilter()
: _blurSize(1.f)
, _centerX(0.5f)
, _centerY(0.5f)
{
	this->shaderName = kCCFilterShader_zoom_blur;
}

CCGLProgram* CCZoomBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCZoomBlurFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_zoom_blur_frag);
	return __p;
}

void CCZoomBlurFilter::setParameter(float $blurSize, float $centerX, float $centerY)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	//_blurSize = MIN(10.f, MAX($blurSize, 0.f));
	//_centerX = MIN(1.f, MAX($centerX, 0.f));
	//_centerY = MIN(1.f, MAX($centerY, 0.f));
	_blurSize = $blurSize;
	_centerX = $centerX;
	_centerY = $centerY;
	initProgram();
}

void CCZoomBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCZoomBlurFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCZoomBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __blurSize = $cgp->getUniformLocationForName("u_blurSize");
	int __blurCenter = $cgp->getUniformLocationForName("u_blurCenter");
	//CCLOG("CCZoomBlurFilter::setUniforms %d, %d", __blurSize, __blurCenter);
	$cgp->setUniformLocationWith1f(__blurSize, _blurSize);
	$cgp->setUniformLocationWith2f(__blurCenter, _centerX, _centerY);
	//CCLOG("CCZoomBlurFilter::setUniforms _blurSize:%.5f, _centerX:%.5f, _centerY:%.5f", _blurSize, _centerX, _centerY);
}

//================== CCMotionBlurFilter

CCMotionBlurFilter* CCMotionBlurFilter::create()
{
	CCMotionBlurFilter* __filter = new CCMotionBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCMotionBlurFilter* CCMotionBlurFilter::create(float $blurSize, float $blurAngle)
{
	CCMotionBlurFilter* __filter = CCMotionBlurFilter::create();
	__filter->setParameter($blurSize, $blurAngle);
	return __filter;
}

CCMotionBlurFilter::CCMotionBlurFilter()
: _blurSize(1.f)
, _blurAngle(0.f)
, _texelOffsetX(0.f)
, _texelOffsetY(0.f)
{
	this->shaderName = kCCFilterShader_motion_blur;
}

CCGLProgram* CCMotionBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCMotionBlurFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
	return __p;
}

void CCMotionBlurFilter::setParameter(float $blurSize, float $blurAngle)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	_blurAngle = $blurAngle;
	//The initProgram() will perform in initSprite()
}

void CCMotionBlurFilter::initSprite(CCFilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	CCSize __size = $sprite->getContentSize();
	__aspectRatio = __size.height / __size.width;
	_texelOffsetX = _blurSize*cos(_blurAngle*M_PI / 180.0f) / __size.width;
	_texelOffsetY = _blurSize*sin(_blurAngle*M_PI / 180.0f) / __size.width;
	initProgram();
}

void CCMotionBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCMotionBlurFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCMotionBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __directionalTexelStep = $cgp->getUniformLocationForName("u_directionalTexelStep");
	//CCLOG("CCMotionBlurFilter::setUniforms %d", __directionalTexelStep);
	$cgp->setUniformLocationWith2f(__directionalTexelStep, _texelOffsetX, _texelOffsetY);
	//CCLOG("CCMotionBlurFilter::setUniforms _blurSize:%.5f,_blurAngle:%.5f, _texelOffsetX:%.5f, _texelOffsetY:%.5f",	_blurSize, _blurAngle, _texelOffsetX, _texelOffsetY);
}

NS_CC_EXT_END