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

#include "SPTextureData.h"
#include "SPConstValue.h"

namespace sp{

    
TextureData *TextureData::createWithJson(const char *_pszDescription)
{
    TextureData *pTextureData = new TextureData();
    if (pTextureData && pTextureData->initWithJson(_pszDescription))
    {
        pTextureData->autorelease();
        return pTextureData;
    }
    CC_SAFE_DELETE(pTextureData);
    return NULL;
}
    
TextureData *TextureData::create()
{
	TextureData *pTextureData = new TextureData();
	if (pTextureData && pTextureData->init())
	{
		pTextureData->autorelease();
		return pTextureData;
	}
	CC_SAFE_DELETE(pTextureData);
	return NULL;
}

TextureData::TextureData()
	:m_fHeight(0.0f)
	,m_fWidth(0.0f)
	,m_fPivotX(0.0f)
	,m_fPivotY(0.0f)
	,m_strName("")
{

}


TextureData::~TextureData()
{
    CC_SAFE_DELETE(m_pContourDataList);
}
    
bool TextureData::init()
{
    m_pContourDataList = CCArray::createWithCapacity(3);
    CCAssert(m_pContourDataList, "create m_pContourDataList failed!");
    m_pContourDataList->retain();
    
    return true;
}
    
void TextureData::addContourData(ContourData *_contourData)
{
    m_pContourDataList->addObject(_contourData);
}


void TextureData::removeContourData(ContourData *_contourData)
{
    m_pContourDataList->removeObject(_contourData);
}


ContourData *TextureData::getContourData(int _index)
{
    return (ContourData*)m_pContourDataList->objectAtIndex(_index);
}

CCArray *TextureData::getContourDatas()
{
    return m_pContourDataList;
}
    
int TextureData::getContourCount()
{
    return m_pContourDataList->count();
}
    
void TextureData::updateJson()
{
    JsonData::updateJson();
    
    
    m_JsonDic.insertItem(A_NAME, m_strName.c_str());
    m_JsonDic.insertItem(A_WIDTH, m_fWidth);
    m_JsonDic.insertItem(A_HEIGHT, m_fHeight);
    m_JsonDic.insertItem(A_PIVOT_X, m_fPivotX);
    m_JsonDic.insertItem(A_PIVOT_Y, m_fPivotY);
    
    if(m_pContourDataList->count() <= 0)
    {
        return;
    }
    
    Json::Value array;
    
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pContourDataList, _object)
    {
        ContourData *_contourData = (ContourData*)_object;
        m_JsonDic.insertItemToArray(CONTOUR_DATA, &_contourData->getJsonDic());
    }
    
}
    
bool TextureData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        JsonData::initWithJson(_pszDescription);
        CC_BREAK_IF(!TextureData::init());
        
        
        const char * str = m_JsonDic.getItemStringValue(A_NAME);
        if(str != NULL)
        {
            m_strName = str;
        }
        
        m_fWidth = m_JsonDic.getItemFloatValue(A_WIDTH, 0);
        m_fHeight = m_JsonDic.getItemFloatValue(A_HEIGHT, 0);
        m_fPivotX = m_JsonDic.getItemFloatValue(A_PIVOT_X, 0);
        m_fPivotY = m_JsonDic.getItemFloatValue(A_PIVOT_Y, 0);
        
        int _length = m_JsonDic.getArrayItemCount(CONTOUR_DATA);
        
        for (int i = 0; i<_length; i++)
        {
            SPJsonDictionary *_dic = m_JsonDic.getSubItemFromArray(CONTOUR_DATA, i);
            
            ContourData *_contourData = ContourData::createWithJson(_dic->getDescription().c_str());
            m_pContourDataList->addObject(_contourData);
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}


}