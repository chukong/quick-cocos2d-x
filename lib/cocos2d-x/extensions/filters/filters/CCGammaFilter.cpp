#include "CCGammaFilter.h"

NS_CC_EXT_BEGIN

//================== CCGammaFilter

CCGammaFilter* CCGammaFilter::create()
{
	CCGammaFilter* __filter = new CCGammaFilter();
	__filter->autorelease();
	return __filter;
}

CCGammaFilter* CCGammaFilter::create(float $brightness)
{
	CCGammaFilter* __filter = CCGammaFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCGammaFilter::CCGammaFilter()
{
	this->shaderName = kCCFilterShader_gamma;
	_param = 1.f;
}

CCGLProgram* CCGammaFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCGammaFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_gamma_frag);
	return __p;
}

void CCGammaFilter::setParameter(float $param)
{
	_param = MIN(3.f, MAX($param, 0.f));
	initProgram();
}

void CCGammaFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCGammaFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCGammaFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_gamma");
	//CCLOG("CCGammaFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	//CCLOG("CCGammaFilter::setUniforms _param:%.2f", _param);
}

NS_CC_EXT_END
