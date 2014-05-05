#ifndef __CCEXPOSURE_FILTER__
#define __CCEXPOSURE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCExposureFilter

class CCExposureFilter : public CCSingleFloatParamFilter
{

public:
	static CCExposureFilter* create();
	static CCExposureFilter* create(float $param);

	CCExposureFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCEXPOSURE_FILTER__