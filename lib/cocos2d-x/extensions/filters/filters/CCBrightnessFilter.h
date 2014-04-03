#ifndef __CCBRIGHTNESS_FILTER__
#define __CCBRIGHTNESS_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN
//================== CCBrightnessFilter

class CCBrightnessFilter : public CCSingleFloatParamFilter
{

public:
	static CCBrightnessFilter* create();
	static CCBrightnessFilter* create(float $brightness);

	CCBrightnessFilter();

	virtual void setParameter(float $brightness);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCBRIGHTNESS_FILTER__