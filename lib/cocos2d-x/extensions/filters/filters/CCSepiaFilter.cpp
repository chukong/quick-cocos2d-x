#include "CCSepiaFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== CCSepiaFilter

CCSepiaFilter* CCSepiaFilter::create()
{
	CCSepiaFilter* __filter = new CCSepiaFilter();
	__filter->autorelease();
	return __filter;
}

CCSepiaFilter* CCSepiaFilter::create(float $resolation)
{
	CCSepiaFilter* __filter = CCSepiaFilter::create();
	__filter->setParameter();
	return __filter;
}

CCSepiaFilter::CCSepiaFilter()
{
	this->shaderName = kCCFilterShader_sepia;
}

CCGLProgram* CCSepiaFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCSepiaFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTextureColor_vert,
		ccFilterShader_sepia_frag);
	return __p;
}

void CCSepiaFilter::setParameter()
{
	initProgram();
}

void CCSepiaFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCSepiaFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCSepiaFilter::setUniforms(CCGLProgram* $cgp)
{

}

NS_CC_EXT_END
