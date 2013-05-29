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

#include "SPBoneData.h"
#include "SPDisplayData.h"
#include "SPConstValue.h"
#include "SPDisplayFactoryManager.h"

namespace sp{
    
BoneData *BoneData::createWithJson(const char *_pszDescription)
{
    BoneData *pBoneData = new BoneData();
    if (pBoneData && pBoneData->initWithJson(_pszDescription))
    {
        pBoneData->autorelease();
        return pBoneData;
    }
    CC_SAFE_DELETE(pBoneData);
    return NULL;
}

BoneData *BoneData::create()
{
    BoneData *pBoneData = new BoneData();
    if (pBoneData && pBoneData->init())
    {
        pBoneData->autorelease();
        return pBoneData;
    }
    CC_SAFE_DELETE(pBoneData);
    return NULL;
}

BoneData::BoneData(void)
    :m_pDisplayDataList(NULL)
    ,m_strName("")
    ,m_strParent("")

//    ,m_fPivotX(0)
//    ,m_fPivotY(0)
//    ,m_fWidth(0)
//    ,m_fHeight(0)
{

}


BoneData::~BoneData(void)
{
    CC_SAFE_DELETE( m_pDisplayDataList );
}

bool BoneData::init()
{
    return initWithJson(NULL);
}

//void BoneData::copy(BoneData *_data)
//{
//	Node::copy(_data);
//    
//	m_strName = _data->m_strName;
//	m_strParent = _data->m_strParent;
//
//
//    m_pDisplayDataList->removeAllObjects();
//	CCObject *_object = NULL;
//	CCARRAY_FOREACH(_data->m_pDisplayDataList, _object)
//	{
//        DisplayData *_displayData = (DisplayData*)_object;
//        DisplayData *_newData = DisplayData::create();
//        
//        _newData->m_strImageName = _displayData->m_strImageName;
//        _newData->m_strDisplayName = _displayData->m_strDisplayName;
//        _newData->m_eDisplayType = _displayData->m_eDisplayType;
//        
//		m_pDisplayDataList->addObject(_newData);
//	}
//
//}

void BoneData::updateJson()
{
    Node::updateJson();
    
    m_JsonDic.insertItem(A_NAME, m_strName.c_str());
    m_JsonDic.insertItem(A_PARENT, m_strParent.c_str());
    
    
    if(m_pDisplayDataList->count() <= 0)
    {
        return;
    }
    
    
    CCObject *_object = NULL;
    CCARRAY_FOREACH(m_pDisplayDataList, _object)
    {
        DisplayData *_displayData = (DisplayData*)_object;
        m_JsonDic.insertItemToArray(DISPLAY_DATA, &_displayData->getJsonDic());
    }
    
}

bool BoneData::initWithJson(const char *_pszDescription)
{
    bool ret = false;
    
    do {
        
        m_pDisplayDataList = new CCArray();
        CCAssert(m_pDisplayDataList && m_pDisplayDataList->init(), "");
        
        
        
        JsonData::initWithJson(_pszDescription);
        
        const char * str = m_JsonDic.getItemStringValue(A_NAME);
        if(str != NULL)
        {
            m_strName = str;
        }
        
        str = m_JsonDic.getItemStringValue(A_PARENT);
        if(str != NULL)
        {
            m_strParent = str;
        }
        
        int _length = m_JsonDic.getArrayItemCount(DISPLAY_DATA);
        
        for (int i = 0; i<_length; i++)
        {
            SPJsonDictionary *_dic = m_JsonDic.getSubItemFromArray(DISPLAY_DATA, i);
            
            DisplayType _displayType = (DisplayType)_dic->getItemIntValue(A_DISPLAY_TYPE, SP_DISPLAY_SPRITE);
            addDisplayData(_displayType, _dic->getDescription().c_str());
        }
        
        ret = true;
    } while (0);
    
    
    return ret;
}
    
int BoneData::getDisplayCount()
{
    return m_pDisplayDataList->count();
}

DisplayData *BoneData::addDisplayData(DisplayData *_displayData)
{
    m_pDisplayDataList->addObject(_displayData);
    return _displayData;
}

DisplayData *BoneData::addDisplayData(DisplayType _displayType, const char *_pszDescription)
{
    DisplayData *_displayData = DisplayFactoryManager::createDisplayData(_displayType);
    _displayData->initWithJson(_pszDescription);
    addDisplayData(_displayData);
    return _displayData;
}

DisplayData *BoneData::insertDisplayData(DisplayData *_displayData, int _index)
{
    m_pDisplayDataList->insertObject(_displayData, _index);
    return _displayData;
}

DisplayData *BoneData::getDisplayData(int _index)
{
    return (DisplayData*)m_pDisplayDataList->objectAtIndex(_index);
}

DisplayData *BoneData::removeDisplayData(int _index)
{
    DisplayData *_originData = (DisplayData*)m_pDisplayDataList->objectAtIndex(_index);
    m_pDisplayDataList->removeObjectAtIndex(_index);
    return _originData;
}
    
CCArray *BoneData::getDisplayList()
{
    return m_pDisplayDataList;
}
    
DisplayData *BoneData::changeDisplayDataAtIndex(int _index, DisplayData *_displayData)
{
    DisplayData *_originData = (DisplayData*)m_pDisplayDataList->objectAtIndex(_index);
    m_pDisplayDataList->replaceObjectAtIndex(_index, _displayData, true);
    return _originData;
}
  
}