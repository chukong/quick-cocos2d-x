#ifndef __CCFILTER_GRAY_H__
#define __CCFILTER_GRAY_H__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCGrayFilter

class CCGrayFilter : public CCFilter
{
public:
	static CCGrayFilter* create();
	static CCGrayFilter* create(ccColor4F $param);

	CCGrayFilter();
	void setParameter(ccColor4F $param);

protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

private:
	ccColor4F _param;
};

NS_CC_EXT_END

#endif //__CCFILTER_GRAY_H__