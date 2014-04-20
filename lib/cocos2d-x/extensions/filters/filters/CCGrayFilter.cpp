#include "CCGrayFilter.h"

NS_CC_EXT_BEGIN

//================== CCGrayFilter

CCGrayFilter* CCGrayFilter::create()
{
	CCGrayFilter* __filter = new CCGrayFilter();
	__filter->autorelease();
	__filter->initProgram();
	return __filter;
}

CCGrayFilter* CCGrayFilter::create(ccColor4F $param)
{
	CCGrayFilter* __filter = CCGrayFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCGrayFilter* CCGrayFilter::create(float $r, float $g, float $b, float $a)
{
	CCGrayFilter* __filter = CCGrayFilter::create();
	__filter->setParameter($r, $a, $b, $a);
	return __filter;
}


CCGrayFilter::CCGrayFilter()
: _param(ccc4f(0.299f, 0.587f, 0.114f, 0.0f))
{
	this->shaderName = kCCFilterShader_gray;
}

void CCGrayFilter::setParameter(ccColor4F $param)
{
	_param = $param;
	initProgram();
}

void CCGrayFilter::setParameter(float $r, float $g, float $b, float $a)
{
	setParameter(ccc4f($r, $a, $b, $a));
}

CCGLProgram* CCGrayFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccFilterShader_gray_frag);
	return __p;
}

void CCGrayFilter::setAttributes(CCGLProgram* $cgp)
{
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCGrayFilter::setUniforms(CCGLProgram* $cgp)
{
	int __grayParam = $cgp->getUniformLocationForName("u_grayParam");
	//CCLOG("CCGrayFilter::setUniforms, u_grayParam:%d", __grayParam);
	$cgp->setUniformLocationWith4f(__grayParam, _param.r, _param.g, _param.b, _param.a);
}

NS_CC_EXT_END