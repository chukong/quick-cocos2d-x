
#ifndef __CCDROP_SHADOW_FILTER__
#define __CCDROP_SHADOW_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCDropShadowFilter

class CCDropShadowFilter : public CCFilter
{

public:
	static CCDropShadowFilter* create();
	static CCDropShadowFilter* create(float $resolation);

	CCDropShadowFilter();

	void setParameter(float $resolation);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _textureWidth;
	float _textureHeight;
};


NS_CC_EXT_END

#endif //__CCDROP_SHADOW_FILTER__
