#include "CCDropShadowFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCDropShadowFilter

CCDropShadowFilter* CCDropShadowFilter::create()
{
	CCDropShadowFilter* __filter = new CCDropShadowFilter();
	__filter->autorelease();
	return __filter;
}

CCDropShadowFilter* CCDropShadowFilter::create(float $resolation)
{
	CCDropShadowFilter* __filter = CCDropShadowFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

CCDropShadowFilter::CCDropShadowFilter()
{
	this->shaderName = kCCFilterShader_drop_shadow;
}

CCGLProgram* CCDropShadowFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCDropShadowFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_drop_shadow_vert, 
		ccFilterShader_drop_shadow_frag);
	return __p;
}

void CCDropShadowFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void CCDropShadowFilter::initSprite(CCFilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	CCSize __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void CCDropShadowFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCDropShadowFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCDropShadowFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
	CCLOG("CCDropShadowFilter::setUniforms %d", u_resolution);
	$cgp->setUniformLocationWith2f(u_resolution, _textureWidth, _textureHeight);
	CCLOG("CCDropShadowFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",
		_textureWidth, _textureHeight);
}

NS_CC_EXT_END
