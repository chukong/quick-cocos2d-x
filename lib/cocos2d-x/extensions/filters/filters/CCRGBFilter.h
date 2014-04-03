
#ifndef __CCRGB_FILTER__
#define __CCRGB_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCRGBFilter

class CCRGBFilter : public CCFilter
{

public:
	static CCRGBFilter* create();
	static CCRGBFilter* create(float $redAdj, float $greenAdj, float $blueAdj);

	CCRGBFilter();

	void setParameter(float $redAdj, float $greenAdj, float $blueAdj);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _redAdj;
	float _greenAdj;
	float _blueAdj;
};


NS_CC_EXT_END

#endif //__CCRGB_FILTER__