#ifndef __CCSATURATION_FILTER__
#define __CCSATURATION_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== CCSaturationFilter

class CCSaturationFilter : public CCSingleFloatParamFilter
{

public:
	static CCSaturationFilter* create();
	static CCSaturationFilter* create(float $param);

	CCSaturationFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};


NS_CC_EXT_END

#endif //__CCSATURATION_FILTER__
