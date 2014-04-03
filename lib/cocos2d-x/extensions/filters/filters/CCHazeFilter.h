
#ifndef __CCHAZE_FILTER__
#define __CCHAZE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCHazeFilter

class CCHazeFilter : public CCFilter
{

public:
	static CCHazeFilter* create();
	static CCHazeFilter* create(float $hazeDistance, float $slope);

	CCHazeFilter();

	void setParameter(float $hazeDistance, float $slope);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _hazeDistance;
	float _slope;
};

NS_CC_EXT_END

#endif //__CCHAZE_FILTER__
