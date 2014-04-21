#include "CCMaskFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCMaskFilter

CCMaskFilter* CCMaskFilter::create()
{
	CCMaskFilter* __filter = new CCMaskFilter();
	__filter->autorelease();
	return __filter;
}

CCMaskFilter* CCMaskFilter::create(CCString* $maskImage)
{
	CCMaskFilter* __filter = CCMaskFilter::create();
	__filter->setParameter($maskImage);
	__filter->setIsSpriteFrame(false);
	return __filter;
}

CCMaskFilter* CCMaskFilter::createWithSpriteFrameName(CCString* $maskImage)
{
	CCMaskFilter* __filter = CCMaskFilter::create();
	__filter->setParameter($maskImage);
	__filter->setIsSpriteFrame(true);
	return __filter;
}

CCMaskFilter::CCMaskFilter()
: _param(NULL)
, _isSpriteFrame(false)
{
	this->shaderName = NULL;
}

void CCMaskFilter::initProgram()
{
	//Do nothing in CCMaskFilter
	CCLOG("CCMaskFilter initProgram");
}

void CCMaskFilter::initSprite(CCFilteredSprite* $sprite)
{
	CCLOG("CCMaskFilter initSprite maskImage:%s", _param->getCString());
	ccBlendFunc __maskBF = { GL_ONE, GL_ZERO };
	ccBlendFunc __imgBF = { GL_DST_ALPHA, GL_ZERO };

	CCSprite* __pMask = _isSpriteFrame ?
		CCSprite::create(_param->getCString()) :
		CCSprite::createWithSpriteFrameName(_param->getCString());
	__pMask->setAnchorPoint(ccp(0, 0));
	__pMask->setPosition(ccp(0, 0));

	CCSprite* __pImg = CCSprite::createWithSpriteFrameName("helloworld.png");
	__pImg->setAnchorPoint(ccp(0, 0));
	__pImg->setPosition(ccp(0, 0));

	__pMask->setBlendFunc(__maskBF);
	__pImg->setBlendFunc(__imgBF);

	CCSize __size = __pImg->getContentSize();
	CCRenderTexture* __pRender = CCRenderTexture::create(__size.width, __size.height);
	__pRender->begin();
	__pMask->visit();
	__pImg->visit();
	__pRender->end();

	CCTexture2D* __pTex = new CCTexture2D();
	__pTex->initWithImage(__pRender->newCCImage(true));
	__pTex->autorelease();
	$sprite->setTexture(__pTex);
}

void CCMaskFilter::setParameter(CCString* $maskImage)
{
	_param = $maskImage;
}

NS_CC_EXT_END