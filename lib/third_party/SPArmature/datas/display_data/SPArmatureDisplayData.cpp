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

#include "SPArmatureDisplayData.h"
#include "SPConstValue.h"
#include "SPDisplayFactory.h"

namespace sp{

//INIT_JS_CLASS(ArmatureDisplayData, DisplayData)
//
//JS_FUNCTION_BEGIN(ArmatureDisplayData)
//JS_FUNCTION_BIND(setParamJS, 1)
//JS_FUNCTION_BIND(getDisplayName, 0)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(ArmatureDisplayData)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(ArmatureDisplayData)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(ArmatureDisplayData)
//JS_PROPERTY_END



ArmatureDisplayData *ArmatureDisplayData::createWithJson(const char *_pszDescription)
{
    ArmatureDisplayData *pDisplayData = new ArmatureDisplayData();
    if (pDisplayData && pDisplayData->initWithJson(_pszDescription))
    {
        pDisplayData->autorelease();
        return pDisplayData;
    }
    CC_SAFE_DELETE(pDisplayData);
    return NULL;
}
    
ArmatureDisplayData *ArmatureDisplayData::create()
{
	ArmatureDisplayData *pDisplayData = new ArmatureDisplayData();
	if (pDisplayData && pDisplayData->init()){
		pDisplayData->autorelease();
		return pDisplayData;
	}
	CC_SAFE_DELETE(pDisplayData);
	return NULL;
}


    
ArmatureDisplayData::ArmatureDisplayData(void)
    :m_strDisplayName("")
{
    m_eDisplayType = SP_DISPLAY_ARMATURE;
    
//    CREATE_JS_OBJECT(ArmatureDisplayData);
}

//ArmatureDisplayData::ArmatureDisplayData(DEFINE_JS obj)
//    :m_strDisplayName("")
//{
//	m_eDisplayType = SP_DISPLAY_ARMATURE;
//}
    
bool ArmatureDisplayData::init()
{
    
    return true;
}
 
void ArmatureDisplayData::updateJson()
{
    JsonData::updateJson();
    
    m_JsonDic.insertItem(A_NAME, m_strDisplayName.c_str());
}
    
bool ArmatureDisplayData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        JsonData::initWithJson(_pszDescription);
        
        const char * str = m_JsonDic.getItemStringValue(A_NAME);
        if(str != NULL)
        {
            m_strDisplayName = str;
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}
    
void ArmatureDisplayData::copy(ArmatureDisplayData *_displayData)
{
    m_strDisplayName = _displayData->m_strDisplayName;
    m_eDisplayType = _displayData->m_eDisplayType;
}
 
}