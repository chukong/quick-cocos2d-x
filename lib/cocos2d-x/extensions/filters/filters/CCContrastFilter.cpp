
#include "CCContrastFilter.h"

NS_CC_EXT_BEGIN
//================== CCContrastFilter

CCContrastFilter* CCContrastFilter::create()
{
	CCContrastFilter* __filter = new CCContrastFilter();
	__filter->autorelease();
	return __filter;
}

CCContrastFilter* CCContrastFilter::create(float $brightness)
{
	CCContrastFilter* __filter = CCContrastFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCContrastFilter::CCContrastFilter()
{
	this->shaderName = kCCFilterShader_contrast;
	_param = 1.f;
}

CCGLProgram* CCContrastFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCContrastFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_contrast_frag);
	return __p;
}

void CCContrastFilter::setParameter(float $param)
{
	_param = MIN(4.f, MAX($param, 0.f));
	initProgram();
}

void CCContrastFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCContrastFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCContrastFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_contrast = $cgp->getUniformLocationForName("u_contrast");
	//CCLOG("CCContrastFilter::setUniforms %d", u_contrast);
	$cgp->setUniformLocationWith1f(u_contrast, _param);
	//CCLOG("CCContrastFilter::setUniforms _param:%.2f", _param);
}

NS_CC_EXT_END