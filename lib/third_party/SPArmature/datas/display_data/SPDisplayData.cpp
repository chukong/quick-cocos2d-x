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

#include "SPDisplayData.h"
#include "SPConstValue.h"

namespace sp{
//
//INIT_JS_CLASS_ROOT(DisplayData)
//
//JS_FUNCTION_BEGIN(DisplayData)
//JS_FUNCTION_BIND(setDisplayType, 1)
//JS_FUNCTION_BIND(getDisplayType, 0)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(DisplayData)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(DisplayData)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(DisplayData)
//JS_PROPERTY_END

DisplayData *DisplayData::createWithJson(const char *_pszDescription)
{
    DisplayData *pDisplayData = new DisplayData();
    if (pDisplayData && pDisplayData->initWithJson(_pszDescription))
    {
        pDisplayData->autorelease();
        return pDisplayData;
    }
    CC_SAFE_DELETE(pDisplayData);
    return NULL;
}
    
DisplayData *DisplayData::create()
{
	DisplayData *pDisplayData = new DisplayData();
	if (pDisplayData && pDisplayData->init()){
		pDisplayData->autorelease();
		return pDisplayData;
	}
	CC_SAFE_DELETE(pDisplayData);
	return NULL;
}
    
const char *DisplayData::changeDisplayToTexture(const char * displayName)
{
    // remove .xxx
    std::string _textureName = displayName;
    size_t startPos = _textureName.find_last_of(".");
    
    if(startPos != std::string::npos)
    {
        _textureName = _textureName.erase(startPos);
    }
    
    return _textureName.c_str();
}

DisplayData::DisplayData(void)
    :m_eDisplayType(SP_DISPLAY_SPRITE)
{
//    CREATE_JS_OBJECT(DisplayData);
}


DisplayData::~DisplayData(void)
{
//    DELETE_JS;
}
    
bool DisplayData::init()
{
    return initWithJson(NULL);
}
 
void DisplayData::updateJson()
{
    JsonData::updateJson();
    
    m_JsonDic.insertItem(A_DISPLAY_TYPE, m_eDisplayType);
}
    
bool DisplayData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        
        
        JsonData::initWithJson(_pszDescription);
        
        m_eDisplayType = (DisplayType)m_JsonDic.getItemIntValue(A_DISPLAY_TYPE, SP_DISPLAY_SPRITE);
        
        ret = true;
    } while (0);
    
    
    return ret;
}
    

}