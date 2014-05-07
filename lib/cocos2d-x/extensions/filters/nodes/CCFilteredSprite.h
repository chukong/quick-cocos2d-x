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

#ifndef __CCFILTERED_SPRITE_H__
#define __CCFILTERED_SPRITE_H__

#include "cocos2d.h"
#include "filters/filters/CCFilter.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class CCFilteredSprite : public CCSprite
{
public:

	CCFilteredSprite();
	~CCFilteredSprite();

	virtual void draw(void);

	virtual CCFilter* getFilter(unsigned int $index = 0);
	virtual void setFilter(CCFilter* $pFilter)=0;

	virtual CCArray* getFilters();
	virtual void setFilters(CCArray* $pFilters);

    virtual void clearFilter() = 0;

protected:
	virtual void drawFilter()=0;
	virtual bool updateFilters()=0;
	CCArray* _pFilters;
};

class CCFilteredSpriteWithOne : public CCFilteredSprite
{
public:
	static CCFilteredSpriteWithOne* create();
	static CCFilteredSpriteWithOne* create(const char* $pszFileName);
	static CCFilteredSpriteWithOne* create(const char* $pszFileName, const CCRect& $rect);

	static CCFilteredSpriteWithOne* createWithTexture(CCTexture2D* $pTexture);
	static CCFilteredSpriteWithOne* createWithTexture(CCTexture2D* $pTexture, const CCRect& rect);

	static CCFilteredSpriteWithOne* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame);

	static CCFilteredSpriteWithOne* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual CCFilter* getFilter(unsigned int $index = 0);
	virtual void setFilters(CCArray* $pFilters);
	virtual void setFilter(CCFilter* $pFilter);
    virtual void clearFilter();

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
};

class CCFilteredSpriteWithMulti : public CCFilteredSprite
{
public:
	static CCFilteredSpriteWithMulti* create();
	static CCFilteredSpriteWithMulti* create(const char* $pszFileName);
	static CCFilteredSpriteWithMulti* create(const char* $pszFileName, const CCRect& $rect);

	static CCFilteredSpriteWithMulti* createWithTexture(CCTexture2D* $pTexture);
	static CCFilteredSpriteWithMulti* createWithTexture(CCTexture2D* $pTexture, const CCRect& rect);

	static CCFilteredSpriteWithMulti* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame);

	static CCFilteredSpriteWithMulti* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual void setFilter(CCFilter* $pFilter);
    virtual void clearFilter();

	CCFilteredSpriteWithMulti();
	~CCFilteredSpriteWithMulti();

	// ts = Temporary Storage
	CCTexture2D* getTSTexture();
	void setTSTexture(CCTexture2D* $texture);
	CCSpriteFrame* getTSFrame();
	void setTSFrame(CCSpriteFrame* $frame);

	CCRect getTSRect();
	void setTSRect(const CCRect& $rect);

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
private:
	CCTexture2D* _pTexture;
	CCSpriteFrame* _pFrame;
	CCRect _rect;
};

NS_CC_EXT_END

#endif /* __CCFILTERED_SPRITE_H__ */