/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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
	//CCLOG("CCFilter::initProgram %s, program:%d", shaderName, __pProgram);
	if (!__pProgram)
	{
		__pProgram = loadShader();
		//CCLOG("CCFilter::initProgram %s, after loadShader program:%d", shaderName, __pProgram);
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
		//CCLOG("CCFilter::getProgram %d", __pProgram);
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
	//CCLOG("CCFilter::loadShader");
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