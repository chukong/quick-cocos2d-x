#ifndef __CCBLUR_FILTER__
#define __CCBLUR_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCBlurFilter

class CCBlurBaseFilter : public CCSingleFloatParamFilter
{

public:
	CCBlurBaseFilter();
	virtual void setParameter(float $param);
protected:
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

class CCHBlurFilter : public CCBlurBaseFilter
{
public:
	static CCHBlurFilter* create();
	static CCHBlurFilter* create(float $param);

	CCHBlurFilter();
protected:
	virtual CCGLProgram* loadShader();

};

class CCVBlurFilter : public CCBlurBaseFilter
{
public:
	static CCVBlurFilter* create();
	static CCVBlurFilter* create(float $param);

	CCVBlurFilter();
protected:
	virtual CCGLProgram* loadShader();
};

class CCGaussianHBlurFilter : public CCBlurBaseFilter
{
public:
	static CCGaussianHBlurFilter* create();
	static CCGaussianHBlurFilter* create(float $param);

	CCGaussianHBlurFilter();
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setUniforms(CCGLProgram* $glp);
private:
	float _resolation;
};

class CCGaussianVBlurFilter : public CCBlurBaseFilter
{
public:
	static CCGaussianVBlurFilter* create();
	static CCGaussianVBlurFilter* create(float $param);

	CCGaussianVBlurFilter();
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setUniforms(CCGLProgram* $glp);
private:
	float _resolation;
};

//================== CCZoomBlurFilter

class CCZoomBlurFilter : public CCFilter
{

public:
	static CCZoomBlurFilter* create();
	static CCZoomBlurFilter* create(float $blurSize, float $centerX, float $centerY);

	CCZoomBlurFilter();

	void setParameter(float $blurSize, float $centerX, float $centerY);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _blurSize;
	float _centerX;
	float _centerY;
};

//================== CCMotionBlurFilter

class CCMotionBlurFilter : public CCFilter
{

public:
	static CCMotionBlurFilter* create();
	static CCMotionBlurFilter* create(float $blurSize, float $blurAngle);

	CCMotionBlurFilter();

	void setParameter(float $blurSize, float $blurAngle);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _blurSize;
	float _blurAngle;
	float _texelOffsetX;
	float _texelOffsetY;
};

NS_CC_EXT_END
#endif //__CCBLUR_FILTER__