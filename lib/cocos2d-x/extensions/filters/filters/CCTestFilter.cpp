#include "CCTestFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN


//================== CCTestFilter

CCTestFilter* CCTestFilter::create()
{
	CCTestFilter* __filter = new CCTestFilter();
	__filter->autorelease();
	return __filter;
}

CCTestFilter* CCTestFilter::create(float $resolation)
{
	CCTestFilter* __filter = CCTestFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

CCTestFilter::CCTestFilter()
{
	this->shaderName = kCCFilterShader_test;
}

CCGLProgram* CCTestFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCTestFilter::loadShader, program: %p", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_test_vert,
		ccFilterShader_test_frag);
	return __p;
}

void CCTestFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void CCTestFilter::initSprite(CCFilteredSprite* $sprite)
{
	CCSize __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void CCTestFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCTestFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCTestFilter::setUniforms(CCGLProgram* $cgp)
{
	CCTexture2D* __maskTex = CCTextureCache::sharedTextureCache()->addImage("mask10.png");
	__maskTex->setAntiAliasTexParameters();

	CCTexture2D* __tex1 = CCTextureCache::sharedTextureCache()->addImage("dirt.png");
	__tex1->setAntiAliasTexParameters();


	int u_mask = $cgp->getUniformLocationForName("u_mask");
	int u_texture1 = $cgp->getUniformLocationForName("u_texture1");
	int u_cctexture = $cgp->getUniformLocationForName("CC_Texture0");

	CCLOG("CCTestFilter::setUniforms u_mask:%d, u_texture1:%d, CC_Texture0:%d", u_mask, u_texture1, u_cctexture);
	$cgp->setUniformLocationWith1i(u_mask, 2);
	$cgp->setUniformLocationWith1i(u_texture1, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, __maskTex->getName());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, __tex1->getName());
	glActiveTexture(GL_TEXTURE0);

	CCLOG("CCTestFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",
		_textureWidth, _textureHeight);
}

NS_CC_EXT_END
