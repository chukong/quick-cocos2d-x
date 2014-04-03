#ifndef __CCCONTRAST_FILTER__
#define __CCCONTRAST_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCContrastFilter

class CCContrastFilter : public CCSingleFloatParamFilter
{

public:
	static CCContrastFilter* create();
	static CCContrastFilter* create(float $param);

	CCContrastFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCCONTRAST_FILTER__