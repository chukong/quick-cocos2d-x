
#ifndef __CCHUE_FILTER__
#define __CCHUE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== CCHueFilter

class CCHueFilter : public CCSingleFloatParamFilter
{

public:
	static CCHueFilter* create();
	static CCHueFilter* create(float $param);

	CCHueFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCHUE_FILTER__
