#include "CCHazeFilter.h"

NS_CC_EXT_BEGIN

//================== CCHazeFilter

CCHazeFilter* CCHazeFilter::create()
{
	CCHazeFilter* __filter = new CCHazeFilter();
	__filter->autorelease();
	return __filter;
}

CCHazeFilter* CCHazeFilter::create(float $hazeDistance, float $slope)
{
	CCHazeFilter* __filter = CCHazeFilter::create();
	__filter->setParameter($hazeDistance, $slope);
	return __filter;
}

CCHazeFilter::CCHazeFilter()
: _hazeDistance(0.f)
, _slope(0.f)
{
	this->shaderName = kCCFilterShader_haze;
}

CCGLProgram* CCHazeFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("CCHazeFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_haze_frag);
	return __p;
}

void CCHazeFilter::setParameter(float $hazeDistance, float $slope)
{
	_hazeDistance = MIN(0.5f, MAX($hazeDistance, -0.5f));
	_slope = MIN(0.5f, MAX($slope, -0.5f));
	initProgram();
}

void CCHazeFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("CCHazeFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCHazeFilter::setUniforms(CCGLProgram* $cgp)
{
	int __hazeDistance = $cgp->getUniformLocationForName("u_hazeDistance");
	int __slope = $cgp->getUniformLocationForName("u_slope");
	//CCLOG("CCHazeFilter::setUniforms %d, %d", __hazeDistance, __slope);
	$cgp->setUniformLocationWith1f(__hazeDistance, _hazeDistance);
	$cgp->setUniformLocationWith1f(__slope, _slope);
	//CCLOG("CCHazeFilter::setUniforms _hazeDistance:%.5f, _slope:%.5f", _hazeDistance, _slope);
}
NS_CC_EXT_END
