#include "CCRGBFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCRGBFilter

CCRGBFilter* CCRGBFilter::create()
{
	CCRGBFilter* __filter = new CCRGBFilter();
	__filter->autorelease();
	return __filter;
}

CCRGBFilter* CCRGBFilter::create(float $readAdj, float $greenAdj, float $blueAdj)
{
	CCRGBFilter* __filter = CCRGBFilter::create();
	__filter->setParameter($readAdj, $greenAdj, $blueAdj);
	return __filter;
}

CCRGBFilter::CCRGBFilter()
: _redAdj(1.f)
, _greenAdj(1.f)
, _blueAdj(1.f)
{
	this->shaderName = kCCFilterShader_rgb;
}

CCGLProgram* CCRGBFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCRGBFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_rgb_frag);
	return __p;
}

void CCRGBFilter::setParameter(float $redAdj, float $greenAdj, float $blueAdj)
{
	_redAdj = $redAdj;
	_greenAdj = $greenAdj;
	_blueAdj = $blueAdj;
	initProgram();
}

void CCRGBFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCRGBFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCRGBFilter::setUniforms(CCGLProgram* $cgp)
{
	int __redAdj = $cgp->getUniformLocationForName("u_redAdj");
	int __greenAdj = $cgp->getUniformLocationForName("u_greenAdj");
	int __blueAdj = $cgp->getUniformLocationForName("u_blueAdj");
	//CCLOG("CCRGBFilter::setUniforms %d, %d, %d", __redAdj, __greenAdj, __blueAdj);
	$cgp->setUniformLocationWith1f(__redAdj, _redAdj);
	$cgp->setUniformLocationWith1f(__greenAdj, _greenAdj);
	$cgp->setUniformLocationWith1f(__blueAdj, _blueAdj);
	/*CCLOG("CCRGBFilter::setUniforms u_redAdj:%.2f, u_greenAdj:%.5f, u_blueAdj:%.5f",
		_redAdj, _greenAdj, _blueAdj);*/
}

NS_CC_EXT_END