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

#include "SPParticleDisplayData.h"
#include "SPConstValue.h"
#include "SPDisplayFactory.h"

namespace sp{

    
//    
//INIT_JS_CLASS(ParticleDisplayData, DisplayData)
//
//JS_FUNCTION_BEGIN(ParticleDisplayData)
//JS_FUNCTION_BIND(setParamJS, 1)
//JS_FUNCTION_BIND(getPlist, 0)
//JS_FUNCTION_END
//
//JS_PROPERTY_GET_BEGIN(ParticleDisplayData)
//JS_PROPERTY_GET_END
//
//JS_PROPERTY_SET_BEGIN(ParticleDisplayData)
//JS_PROPERTY_SET_END
//
//JS_PROPERTY_BEGIN(ParticleDisplayData)
//JS_PROPERTY_END
//



ParticleDisplayData *ParticleDisplayData::createWithJson(const char *_pszDescription)
{
    ParticleDisplayData *pDisplayData = new ParticleDisplayData();
    if (pDisplayData && pDisplayData->initWithJson(_pszDescription))
    {
        pDisplayData->autorelease();
        return pDisplayData;
    }
    CC_SAFE_DELETE(pDisplayData);
    return NULL;
}
    
ParticleDisplayData *ParticleDisplayData::create()
{
	ParticleDisplayData *pDisplayData = new ParticleDisplayData();
	if (pDisplayData && pDisplayData->init()){
		pDisplayData->autorelease();
		return pDisplayData;
	}
	CC_SAFE_DELETE(pDisplayData);
	return NULL;
}
    


ParticleDisplayData::ParticleDisplayData(void)
    :m_strPlist("")
{
    m_eDisplayType = SP_DISPLAY_PARTICLE;
    
//    CREATE_JS_OBJECT(ParticleDisplayData);
}
//
//ParticleDisplayData::ParticleDisplayData(DEFINE_JS obj)
//    :m_strPlist("")
//{
//	 m_eDisplayType = SP_DISPLAY_PARTICLE;
//}

    
bool ParticleDisplayData::init()
{
    return true;
}
 
void ParticleDisplayData::updateJson()
{
    DisplayData::updateJson();
    
    m_JsonDic.insertItem(A_PLIST, m_strPlist.c_str());
}

bool ParticleDisplayData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!DisplayData::initWithJson(_pszDescription));
        
        const char * str = m_JsonDic.getItemStringValue(A_PLIST);
        if(str != NULL)
        {
            m_strPlist = str;
        }

        
        ret = true;
    } while (0);
    
    
    return ret;
}

void ParticleDisplayData::copy(ParticleDisplayData *_displayData)
{
    m_strPlist = _displayData->m_strPlist;
    m_eDisplayType = _displayData->m_eDisplayType;
}

    

}