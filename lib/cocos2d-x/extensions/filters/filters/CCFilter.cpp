#include "CCFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== CCFilter

CCFilter::CCFilter()
: shaderName(NULL)
, _pProgram(NULL)
{
}


CCFilter::~CCFilter()
{
	CC_SAFE_RELEASE(_pProgram);
}

CCGLProgram* CCFilter::getProgram()
{
	return _pProgram;
}

void CCFilter::initProgram()
{
	CCGLProgram* __pProgram = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	CCLOG("CCFilter::initProgram %s, program:%d", shaderName, __pProgram);
	if (!__pProgram)
	{
		__pProgram = loadShader();
		CCLOG("CCFilter::initProgram %s, after loadShader program:%d", shaderName, __pProgram);
		this->setAttributes(__pProgram);
		CHECK_GL_ERROR_DEBUG();

		__pProgram->link();
		CHECK_GL_ERROR_DEBUG();

		__pProgram->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		//this->setUniforms(__pProgram);
		//CHECK_GL_ERROR_DEBUG();

		CCShaderCache::sharedShaderCache()->addProgram(__pProgram, this->shaderName);
		__pProgram->release();
		CCLOG("CCFilter::getProgram %d", __pProgram);
	}
	//CCLOG("CCFilter::getProgram2 %d", __pProgram);
	if (!_pProgram)
	{
		_pProgram = __pProgram;
		_pProgram->retain();
	}
}

void CCFilter::initSprite(CCFilteredSprite* $sprite)
{
}

void CCFilter::draw()
{
	setUniforms(getProgram());
}

CCGLProgram* CCFilter::loadShader()
{
	CCLOG("CCFilter::loadShader");
	return NULL;
}

void CCFilter::setAttributes(CCGLProgram* $glp)
{
}

void CCFilter::setUniforms(CCGLProgram* $glp)
{
}

//================== CCSingleFloatParamFilter

CCSingleFloatParamFilter::CCSingleFloatParamFilter()
: _param(0.f)
{
}


void CCSingleFloatParamFilter::setParameter(float $param)
{
	_param = $param;
	initProgram();
}

NS_CC_EXT_END