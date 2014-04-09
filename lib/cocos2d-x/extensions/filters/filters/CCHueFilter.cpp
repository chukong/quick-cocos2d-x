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
	CCLOG("CCHueFilter::loadShader, program:%d", __p);
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
	CCLOG("CCHueFilter::setAttributes");
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
