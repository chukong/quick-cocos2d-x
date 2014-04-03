#ifndef __CCMASK_FILTER__
#define __CCMASK_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCMaskFilter

class CCMaskFilter : public CCFilter
{

public:
	static CCMaskFilter* create();
	static CCMaskFilter* create(CCString* $maskImage);
	static CCMaskFilter* createWithSpriteFrameName(CCString* $maskImage);

	CCMaskFilter();

	void setParameter(CCString* $param);
	virtual void initSprite(CCFilteredSprite* $sprite);
	inline void setIsSpriteFrame(bool $isSpriteFrame){ _isSpriteFrame = $isSpriteFrame; };
protected:
	void initProgram();
	CCString* _param;
	bool _isSpriteFrame;

};

NS_CC_EXT_END

#endif //__CCMASK_FILTER__