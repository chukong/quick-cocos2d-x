#include "CCSharpenFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCSharpenFilter

CCSharpenFilter* CCSharpenFilter::create()
{
	CCSharpenFilter* __filter = new CCSharpenFilter();
	__filter->autorelease();
	return __filter;
}

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, float $widthFactor, float $heightFactor)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $widthFactor, $heightFactor);
	return __filter;
}

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, int $amount)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $amount);
	return __filter;
}

CCSharpenFilter::CCSharpenFilter()
: _sharpness(0.f)
, _widthFactor(0.f)
, _heightFactor(0.f)
, _amount(0)
{
	this->shaderName = kCCFilterShader_sharpen;
}

CCGLProgram* CCSharpenFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCSharpenFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_sharpen_vert, ccFilterShader_sharpen_frag);
	return __p;
}

void CCSharpenFilter::setParameter(float $sharpness, float $widthFactor, float $heightFactor)
{
	_sharpness = $sharpness;
	_widthFactor = $widthFactor;
	_heightFactor = $heightFactor;
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::setParameter(float $sharpness, int $amount)
{
	_sharpness = $sharpness;
	_amount = $amount;
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::initSprite(CCFilteredSprite* $sprite)
{
	// If _amount is not 0, then calculate the value of the widthFactor and the heightFactor.
	if (_amount != 0)
	{
		CCSize __size = $sprite->getContentSize();
		_widthFactor = 1.0f / __size.width * _amount;
		_heightFactor = 1.0f / __size.height * _amount;
	}
	initProgram();
}

void CCSharpenFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCSharpenFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCSharpenFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_sharpness = $cgp->getUniformLocationForName("u_sharpness");
	int u_widthFactor = $cgp->getUniformLocationForName("u_widthFactor");
	int u_heightFactor = $cgp->getUniformLocationForName("u_heightFactor");
	//CCLOG("CCSharpenFilter::setUniforms %d, %d, %d", u_sharpness, u_widthFactor, u_heightFactor);
	$cgp->setUniformLocationWith1f(u_sharpness, _sharpness);
	$cgp->setUniformLocationWith1f(u_widthFactor, _widthFactor);
	$cgp->setUniformLocationWith1f(u_heightFactor, _heightFactor);
	//CCLOG("CCSharpenFilter::setUniforms u_sharpness:%.2f, u_widthFactor:%.5f, u_heightFctor:%.5f",_sharpness, _widthFactor, _heightFactor);
}

NS_CC_EXT_END