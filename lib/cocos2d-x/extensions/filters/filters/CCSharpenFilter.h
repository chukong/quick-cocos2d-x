#ifndef __CCSHARPEN_FILTER__
#define __CCSHARPEN_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCSharpenFilter

class CCSharpenFilter : public CCFilter
{

public:
	static CCSharpenFilter* create();
	static CCSharpenFilter* create(float $sharpness, float $widthFactor, float $heightFactor);
	static CCSharpenFilter* create(float $sharpness, int $amount);

	CCSharpenFilter();

	void setParameter(float $sharpness, float $widthFactor, float $heightFactor);
	void setParameter(float $sharpness, int $amount);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _sharpness;
	float _widthFactor;
	float _heightFactor;
	int _amount;

};

NS_CC_EXT_END

#endif //__CCSHARPEN_FILTER__