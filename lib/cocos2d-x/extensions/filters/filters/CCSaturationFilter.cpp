#include "CCSaturationFilter.h"

NS_CC_EXT_BEGIN

//================== CCSaturationFilter

CCSaturationFilter* CCSaturationFilter::create()
{
	CCSaturationFilter* __filter = new CCSaturationFilter();
	__filter->autorelease();
	return __filter;
}

CCSaturationFilter* CCSaturationFilter::create(float $brightness)
{
	CCSaturationFilter* __filter = CCSaturationFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCSaturationFilter::CCSaturationFilter()
{
	this->shaderName = kCCFilterShader_saturation;
	_param = 1.f;
}

CCGLProgram* CCSaturationFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCSaturationFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_saturation_frag);
	return __p;
}

void CCSaturationFilter::setParameter(float $param)
{
	_param = MIN(2.f, MAX($param, 0.f));
	initProgram();
}

void CCSaturationFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCSaturationFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCSaturationFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_saturation");
	//CCLOG("CCSaturationFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	//CCLOG("CCSaturationFilter::setUniforms _param:%.2f", _param);
}


NS_CC_EXT_END
