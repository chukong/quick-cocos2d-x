/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SPShaderDisplayData.h"
#include "SPConstValue.h"
#include "SPDisplayFactory.h"

namespace sp{

    
//    
//INIT_JS_CLASS(ShaderDisplayData, DisplayData)
//
//JS_FUNCTION_BEGIN(ShaderDisplayData)
//JS_FUNCTION_BIND(setParamJS, 2)
//JS_FUNCTION_BIND(getVert, 0)
//JS_FUNCTION_BIND(getFrag, 0)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(ShaderDisplayData)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(ShaderDisplayData)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(ShaderDisplayData)
//JS_PROPERTY_END




ShaderDisplayData *ShaderDisplayData::createWithJson(const char *_pszDescription)
{
    ShaderDisplayData *pDisplayData = new ShaderDisplayData();
    if (pDisplayData && pDisplayData->initWithJson(_pszDescription))
    {
        pDisplayData->autorelease();
        return pDisplayData;
    }
    CC_SAFE_DELETE(pDisplayData);
    return NULL;
}
    
ShaderDisplayData *ShaderDisplayData::create()
{
	ShaderDisplayData *pDisplayData = new ShaderDisplayData();
	if (pDisplayData && pDisplayData->init()){
		pDisplayData->autorelease();
		return pDisplayData;
	}
	CC_SAFE_DELETE(pDisplayData);
	return NULL;
}
    


ShaderDisplayData::ShaderDisplayData(void)
    :m_strVert("")
    ,m_strFrag("")
{
    m_eDisplayType = SP_DISPLAY_SHADER;
    
//    CREATE_JS_OBJECT(ShaderDisplayData);
}

//ShaderDisplayData::ShaderDisplayData(DEFINE_JS obj)
//    :m_strVert("")
//    ,m_strFrag("")
//{
//	 m_eDisplayType = SP_DISPLAY_SHADER;
//}

    
bool ShaderDisplayData::init()
{
    return true;
}
 
void ShaderDisplayData::updateJson()
{
    DisplayData::updateJson();
    
    m_JsonDic.insertItem(A_VERT, m_strVert.c_str());
	m_JsonDic.insertItem(A_FRAG, m_strFrag.c_str());
}

bool ShaderDisplayData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!DisplayData::initWithJson(_pszDescription));
        
        const char * str = m_JsonDic.getItemStringValue(A_VERT);
        if(str != NULL)
        {
            m_strVert = str;
        }

		str = m_JsonDic.getItemStringValue(A_FRAG);
        if(str != NULL)
        {
            m_strFrag = str;
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}

void ShaderDisplayData::copy(ShaderDisplayData *_displayData)
{
    m_strVert = _displayData->m_strVert;
    m_strFrag = _displayData->m_strFrag;
    m_eDisplayType = _displayData->m_eDisplayType;
}

  
}