/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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
	//CCLOG("CCFilteredSprite setFilters:%d", _pFilters->count());
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

CCFilteredSpriteWithOne* CCFilteredSpriteWithOne::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCFilteredSpriteWithOne *pobSprite = new CCFilteredSpriteWithOne();
	if ($pSpriteFrame && pobSprite)
	{
		if ($pSpriteFrame->isRotated())
		{
			CCSprite* __sp = CCSprite::createWithSpriteFrame($pSpriteFrame);
			CCSize __size = __sp->getContentSize();
			__sp->setAnchorPoint(ccp(0,0));
			__sp->setPosition(ccp(0,0));
			CCRenderTexture* __rTex = CCRenderTexture::create(__size.width, __size.height);
			__rTex->begin();
			__sp->visit();
			__rTex->end();
			CCTexture2D* __newTex = new CCTexture2D();
			__newTex->initWithImage(__rTex->newCCImage(true));
			__newTex->autorelease();
			pobSprite->initWithTexture(__newTex);
			//CCLOG("==== CCFilteredSprite::initWithTexture, rotated true texture wh(%f,%f)", __newTex->getContentSize().width, __newTex->getContentSize().height);
		}
		else
		{
			pobSprite->initWithSpriteFrame($pSpriteFrame);
		}
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

void CCFilteredSpriteWithOne::clearFilter()
{
    CC_SAFE_RELEASE_NULL(_pFilters);
    //CCLOG("CCFilteredSpriteWithOne::clearFilter");
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
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
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::create();
	pobSprite->setTSTexture($pTexture);
	pobSprite->setTSRect($rect);
	return pobSprite;
}

CCFilteredSpriteWithMulti* CCFilteredSpriteWithMulti::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCFilteredSpriteWithMulti *pobSprite = CCFilteredSpriteWithMulti::create();
	pobSprite->setTSFrame($pSpriteFrame);
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
, _pFrame(NULL)
, _rect(0.f, 0.f, 0.f, 0.f)
{
}

CCFilteredSpriteWithMulti::~CCFilteredSpriteWithMulti()
{
	CC_SAFE_RELEASE(_pTexture);
	CC_SAFE_RELEASE(_pFrame);
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

CCSpriteFrame* CCFilteredSpriteWithMulti::getTSFrame()
{
	return _pFrame;
}

void CCFilteredSpriteWithMulti::setTSFrame(CCSpriteFrame* $pFrame)
{
	CC_SAFE_RETAIN($pFrame);
	CC_SAFE_RELEASE(_pFrame);
	_pFrame = $pFrame;
}

CCRect CCFilteredSpriteWithMulti::getTSRect()
{
	return _rect;
}

void CCFilteredSpriteWithMulti::setTSRect(const CCRect& $rect)
{
	_rect = $rect;
}

void CCFilteredSpriteWithMulti::setFilter(CCFilter* $pFilter)
{
	CCAssert(false, "setFilter on CCFilteredSpriteWithMulti is forbidden!");
}

void CCFilteredSpriteWithMulti::clearFilter()
{
    //CCLOG("CCFilteredSpriteWithMulti::clearFilter");
    CC_SAFE_RELEASE_NULL(_pFilters);
    CCSprite* sprite = static_cast<CCSprite*>(this);
    if (_pTexture)
    {
        sprite->initWithTexture(_pTexture, _rect);
    }
    else if (_pFrame)
    {
        sprite->initWithSpriteFrame(_pFrame);
    }
}

bool CCFilteredSpriteWithMulti::updateFilters()
{
	CCAssert(_pFilters || _pFilters->count()>1, "Invalid CCFilter!");
	do
	{
		CCFilteredSprite* __sp = NULL;
		CCSize __size;
		if (_pTexture)
		{
			__size = _pTexture->getContentSize();
		}
		else if (_pFrame)
		{
			__size = _pFrame->getRect().size;
		}
		else
		{
			break;
		}

		unsigned int __count = _pFilters->count();
		CCTexture2D* __newTex = NULL;
		CCRenderTexture* __canva = CCRenderTexture::create(__size.width, __size.height);
		//CCLOG("CCFilteredSpriteWithMulti::updateFilters %f, %f", __size.width, __size.height);
		for (size_t i = 0; i < __count; i++)
		{
			//CCLOG("CCFilteredSpriteWithMulti render %d", i);
			
			__canva->begin();
			CCFilter* __filter = static_cast<CCFilter*>(_pFilters->objectAtIndex(i));
			if (i == 0)
			{
				__sp = _pTexture ?
					CCFilteredSpriteWithOne::createWithTexture(_pTexture) :
					CCFilteredSpriteWithOne::createWithSpriteFrame(_pFrame);
			}
			else
			{
				__sp = CCFilteredSpriteWithOne::createWithTexture(__newTex);
			}
			__sp->setFilter(__filter);
			__sp->setAnchorPoint(ccp(0, 0));
			//__sp->setPosition(ccp(0, 0));
			//__sp->getTexture()->setAliasTexParameters();
			__sp->visit();
			__canva->end();
			__newTex = new CCTexture2D();
			__newTex->initWithImage(__canva->newCCImage(true));
			__newTex->autorelease();

			//CCLOG("__sp (%u, %u)", __newTex->getPixelsWide(), __newTex->getPixelsHigh());
		}
		static_cast<CCSprite*>(this)->initWithTexture(__newTex);
		CHECK_GL_ERROR_DEBUG();
		//CCLOG("CCFilteredSpriteWithMulti updateFilters:%d", __count);
		//CCLOG("==== CCFilteredSpriteWithMulti updateFilters texture %f, %f", __newTex->getContentSize().width, __newTex->getContentSize().height);
		return true;
	} while (0);

	return false;
}

void CCFilteredSpriteWithMulti::drawFilter(){}

NS_CC_EXT_END