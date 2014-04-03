
#ifndef __CCSEPIA_FILTER__
#define __CCSEPIA_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCSepiaFilter

class CCSepiaFilter : public CCFilter
{

public:
	static CCSepiaFilter* create();
	static CCSepiaFilter* create(float $resolation);

	CCSepiaFilter();

	void setParameter();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCSEPIA_FILTER__
