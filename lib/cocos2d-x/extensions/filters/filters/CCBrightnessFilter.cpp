#include "CCBrightnessFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== CCBrightnessFilter

CCBrightnessFilter* CCBrightnessFilter::create()
{
	CCBrightnessFilter* __filter = new CCBrightnessFilter();
	__filter->autorelease();
	return __filter;
}

CCBrightnessFilter* CCBrightnessFilter::create(float $brightness)
{
	CCBrightnessFilter* __filter = CCBrightnessFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCBrightnessFilter::CCBrightnessFilter()
{
	this->shaderName = kCCFilterShader_brightness;
	_param = 0.f;
}

CCGLProgram* CCBrightnessFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCBrightnessFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_brightness_frag);
	return __p;
}

void CCBrightnessFilter::setParameter(float $brightness)
{
	_param = MIN(1.f, MAX($brightness, -1.f));
	initProgram();
}

void CCBrightnessFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCRGBFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCBrightnessFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_brightness = $cgp->getUniformLocationForName("u_brightness");
	//CCLOG("CCBrightnessFilter::setUniforms %d", u_brightness);
	$cgp->setUniformLocationWith1f(u_brightness, _param);
	//CCLOG("CCBrightnessFilter::setUniforms _param:%.2f", _param);
}
NS_CC_EXT_END