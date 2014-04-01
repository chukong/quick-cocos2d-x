#include "CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCFilteredSprite

CCFilteredSprite::CCFilteredSprite()
: _pFilters(NULL)
{

}

CCFilteredSprite::~CCFilteredSprite()
{
	CC_SAFE_RELEASE(_pFilters);
}

bool CCFilteredSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated)
{
	if (rotated)
	{
		CCSprite* __sp = CCSprite::create();
		__sp->initWithTexture(pTexture, rect, rotated);
		CCRenderTexture* __rTex = CCRenderTexture::create(rect.size.height, rect.size.width);
		__rTex->begin();
		__sp->visit();
		__rTex->end();
		CCTexture2D* __newTex = new CCTexture2D();
		__newTex->initWithImage(__rTex->newCCImage(true));
		__newTex->autorelease();
		return CCSprite::initWithTexture(pTexture, rect, rotated);
	}
	return  CCSprite::initWithTexture(pTexture, rect, rotated);
}

void CCFilteredSprite::draw()
{
	CC_NODE_DRAW_SETUP();
	
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	ccGLBindTexture2D(this->getTexture()->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoods
	diff = offsetof(ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	// draw customer filter, implement in child class.
	drawFilter();

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();

	CC_INCREMENT_GL_DRAWS(1);
}

CCFilter* CCFilteredSprite::getFilter(unsigned int $index)
{
	if (!_pFilters || _pFilters->count() == 0 || $index >= _pFilters->count())
	{
		return NULL;
	}
	return static_cast<CCFilter*>(_pFilters->objectAtIndex($index));
}

CCArray* CCFilteredSprite::getFilters()
{
	return _pFilters;
}

void CCFilteredSprite::setFilters(CCArray* $pFilters)
{
	CC_SAFE_RETAIN($pFilters);
	CC_SAFE_RELEASE(_pFilters);
	_pFilters = $pFilters;
	CCLOG("CCFilteredSprite setFilters:%d", _pFilters->count());
	updateFilters();
}

//================== CCFilteredSpriteWithOne

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::create()
{
	CCFilteredSpriteWithOne *pSprite = new CCFilteredSpriteWithOne();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::create(const char* $pszFileName)
{
	CCFilteredSpriteWithOne *pobSprite = new CCFilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithFile($pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::create(const char* $pszFileName, const CCRect& $rect)
{
	CCFilteredSpriteWithOne *pobSprite = new CCFilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithFile($pszFileName, $rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithTexture(CCTexture2D* $pTexture)
{
	CCSprite *pobSprite = new CCFilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithTexture($pTexture))
	{
		pobSprite->autorelease();
		return static_cast<CCFilteredSpriteWithOne*>(pobSprite);
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithTexture(CCTexture2D* $pTexture, const CCRect& $rect)
{
	CCSprite *pobSprite = new CCFilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithTexture($pTexture, $rect))
	{
		pobSprite->autorelease();
		return static_cast<CCFilteredSpriteWithOne*>(pobSprite);
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithTexture(CCTexture2D* $pTexture, const CCRect& $rect, bool $rotated)
{
	CCFilteredSpriteWithOne *pobSprite = new CCFilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithTexture($pTexture, $rect, $rotated))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCFilteredSpriteWithOne *pobSprite = new CCFilteredSpriteWithOne();
	if ($pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame($pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCFilter* CCFilteredSpriteWithOne::getFilter(unsigned int $index)
{
	return CCFilteredSprite::getFilter(0);
}

void CCFilteredSpriteWithOne::setFilter(CCFilter* $pFilter)
{
	CCArray* __pFilters = CCArray::create($pFilter, NULL);
	CCFilteredSprite::setFilters(__pFilters);
}

void CCFilteredSpriteWithOne::setFilters(CCArray* $pFilters)
{
	CCAssert(false, "setFilters on CCFilteredSpriteWithOne is forbidden!");
}

void CCFilteredSpriteWithOne::drawFilter()
{
	// show custom filter
	if (_pFilters && _pFilters->count() == 1)
	{
		static_cast<CCFilter*>(_pFilters->objectAtIndex(0))->draw();
	}
}

bool CCFilteredSpriteWithOne::updateFilters()
{
	CCAssert(_pFilters || _pFilters->count() != 1, "Invalid CCFilter!");
	do
	{
		unsigned int __count = _pFilters->count();
		CC_BREAK_IF(__count == 0);
		CCFilter* __filter = static_cast<CCFilter*>(_pFilters->objectAtIndex(0));
		__filter->initSprite(this);
		if (__filter->getProgram())
		{
			setShaderProgram(__filter->getProgram());
		}
		CHECK_GL_ERROR_DEBUG();
		return true;
	} while (0);

	return false;
}
//================== CCFilteredSpriteWithMulti

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::create()
{
	CCFilteredSpriteWithMulti *pSprite = new CCFilteredSpriteWithMulti();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::create(const char* $pszFileName)
{
	CCTexture2D* __pTexture = CCTextureCache::sharedTextureCache()->addImage($pszFileName);
	CCRect __rect = CCRectZero;
	__rect.size = __pTexture->getContentSize();
	return createWithTexture(__pTexture, __rect);
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::create(const char* $pszFileName, const CCRect& $rect)
{
	CCTexture2D* __pTexture = CCTextureCache::sharedTextureCache()->addImage($pszFileName);
	return CCFilteredSpriteWithMulti::createWithTexture(__pTexture, $rect);
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithTexture(CCTexture2D* $pTexture)
{
	CCRect __rect = CCRectZero;
	__rect.size = $pTexture->getContentSize();
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::createWithTexture($pTexture, __rect);
	return pobSprite;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithTexture(CCTexture2D* $pTexture, const CCRect& $rect)
{
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::createWithTexture($pTexture, $rect, false);
	return pobSprite;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithTexture(CCTexture2D* $pTexture, const CCRect& $rect, bool $rotated)
{
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::create();
	pobSprite->setTSTexture($pTexture);
	pobSprite->setTSRect($rect);
	pobSprite->setTSRotated($rotated);
	return pobSprite;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::createWithTexture($pSpriteFrame->getTexture(), $pSpriteFrame->getRect(), $pSpriteFrame->isRotated());
	return pobSprite;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCFilteredSpriteWithMulti::CCFilteredSpriteWithMulti()
: _pTexture(NULL)
, _rect(0.f, 0.f, 0.f, 0.f)
{
}

CCFilteredSpriteWithMulti::~CCFilteredSpriteWithMulti()
{
	CC_SAFE_RELEASE(_pTexture);
}

CCTexture2D* CCFilteredSpriteWithMulti::getTSTexture()
{
	return _pTexture;
}

void CCFilteredSpriteWithMulti::setTSTexture(CCTexture2D* $texture)
{
	CC_SAFE_RETAIN($texture);
	CC_SAFE_RELEASE(_pTexture);
	_pTexture = $texture;
}

CCRect CCFilteredSpriteWithMulti::getTSRect()
{
	return _rect;
}

void CCFilteredSpriteWithMulti::setTSRect(const CCRect& $rect)
{
	_rect = $rect;
}

bool CCFilteredSpriteWithMulti::getTSRotated()
{
	return _rotated;
}

void CCFilteredSpriteWithMulti::setTSRotated(bool $rotated)
{
	_rotated = $rotated;
}


void CCFilteredSpriteWithMulti::setFilter(CCFilter* $pFilter)
{
	CCAssert(false, "setFilter on CCFilteredSpriteWithMulti is forbidden!");
}

bool CCFilteredSpriteWithMulti::updateFilters()
{
	CCAssert(_pFilters || _pFilters->count()>1, "Invalid CCFilter!");
	do
	{
		CCFilteredSprite* __sp = NULL;
		CC_BREAK_IF(!_pTexture);
		
		unsigned int __count = _pFilters->count();
		CCTexture2D* __oldTex = NULL;
		CCRenderTexture* __canva = CCRenderTexture::create(_rect.size.width, _rect.size.height);
		for (size_t i = 0; i < __count; i++)
		{
			CCLOG("CCFilteredSpriteWithMulti render %d", i);
			__canva->begin();
			CCFilter* __filter = static_cast<CCFilter*>(_pFilters->objectAtIndex(i));
			if (i == 0)
			{
				__sp = CCFilteredSpriteWithOne::createWithTexture(_pTexture, _rect, _rotated);
				//For subsequent filters, the _rotated is permanent FALSE.
				_rotated = false;
			}
			else
			{
				__sp = CCFilteredSpriteWithOne::createWithTexture(__oldTex, _rect, _rotated);
			}
			__sp->setFilter(__filter);
			__sp->setAnchorPoint(ccp(0, 0));
			__sp->setPosition(ccp(0, 0));
			__sp->getTexture()->setAliasTexParameters();
			__sp->visit();
			__canva->end();
			__oldTex = new CCTexture2D();
			__oldTex->initWithImage(__canva->newCCImage(true));
			__oldTex->autorelease();
			_rect.origin = CCPointZero;
			_rect.size = __oldTex->getContentSize();
		}
		static_cast<CCSprite*>(this)->initWithTexture(__oldTex);
		CHECK_GL_ERROR_DEBUG();
		CCLOG("CCFilteredSpriteWithMulti updateFilters:%d", __count);
		CCLOG("texture %f, %f", __oldTex->getContentSize().width, __oldTex->getContentSize().height);
		return true;
	} while (0);

	return false;
}

void CCFilteredSpriteWithMulti::drawFilter(){}

NS_CC_EXT_END