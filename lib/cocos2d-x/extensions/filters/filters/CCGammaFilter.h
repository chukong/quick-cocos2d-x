#ifndef __CCGAMMA_FILTER__
#define __CCGAMMA_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCGammaFilter

class CCGammaFilter : public CCSingleFloatParamFilter
{

public:
	static CCGammaFilter* create();
	static CCGammaFilter* create(float $param);

	CCGammaFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

};

NS_CC_EXT_END

#endif //__CCGAMMA_FILTER__
