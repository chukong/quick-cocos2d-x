#include "CCExposureFilter.h"

NS_CC_EXT_BEGIN

//================== CCExposureFilter

CCExposureFilter* CCExposureFilter::create()
{
	CCExposureFilter* __filter = new CCExposureFilter();
	__filter->autorelease();
	return __filter;
}

CCExposureFilter* CCExposureFilter::create(float $brightness)
{
	CCExposureFilter* __filter = CCExposureFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCExposureFilter::CCExposureFilter()
{
	this->shaderName = kCCFilterShader_exposure;
	_param = 0.f;
}

CCGLProgram* CCExposureFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCExposureFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_exposure_frag);
	return __p;
}

void CCExposureFilter::setParameter(float $param)
{
	_param = MIN(10.f, MAX($param, -10.f));
	initProgram();
}

void CCExposureFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCExposureFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCExposureFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_exposure");
	//CCLOG("CCExposureFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	//CCLOG("CCExposureFilter::setUniforms _param:%.2f", _param);
}

NS_CC_EXT_END