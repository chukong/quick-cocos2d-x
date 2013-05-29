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

#include <iostream>
#include "SPContentJsonDictionary.h"
//#include "SPDumpLeak.h"

using namespace sp;

SPJsonDictionary::SPJsonDictionary()
{
    m_cValue.clear();
}


SPJsonDictionary::~SPJsonDictionary()
{
    m_cValue.clear();
}


void SPJsonDictionary::initWithDescription(const char *pszDescription)
{
    Json::Reader cReader;
    m_cValue.clear();
    if (pszDescription && *pszDescription)
    {
        std::string strValue = pszDescription;
        cReader.parse(strValue, m_cValue, false);
    }
}


void SPJsonDictionary::initWithValue(Json::Value& value)
{
    m_cValue = value;
}


void SPJsonDictionary::insertItem(const char *pszKey, int nValue)
{
    m_cValue[pszKey] = nValue;
}


void SPJsonDictionary::insertItem(const char *pszKey, double fValue)
{
    m_cValue[pszKey] = fValue;
}


void SPJsonDictionary::insertItem(const char *pszKey, const char * pszValue)
{
    m_cValue[pszKey] = pszValue;
}

void SPJsonDictionary::insertItem(const char *pszKey, bool bValue)
{
    m_cValue[pszKey] = bValue;
}

void SPJsonDictionary::insertItem(const char *pszKey, SPJsonDictionary * subDictionary)
{
    if (subDictionary)
        m_cValue[pszKey] = subDictionary->m_cValue;
}


bool SPJsonDictionary::deleteItem(const char *pszKey)
{
    if(!m_cValue.isMember(pszKey))
        return false;

    m_cValue.removeMember(pszKey);

    return true;
}


void SPJsonDictionary::cleanUp()
{
    m_cValue.clear();
}


bool SPJsonDictionary::isKeyValidate(const char *pszKey)
{
    return m_cValue.isMember(pszKey);
}


int SPJsonDictionary::getItemIntValue(const char *pszKey, int nDefaultValue)
{
    if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isNumeric())
        return nDefaultValue;
    
    return m_cValue[pszKey].asInt();
}


double SPJsonDictionary::getItemFloatValue(const char *pszKey, double fDefaultValue)
{
    if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isNumeric())
        return fDefaultValue;
    
    return m_cValue[pszKey].asDouble();
}


const char * SPJsonDictionary::getItemStringValue(const char *pszKey)
{
    if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isString())
        return NULL;
    
    return m_cValue[pszKey].asCString();
}

bool SPJsonDictionary::getItemBoolvalue(const char *pszKey, bool bDefaultValue)
{
    if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isBool()) 
        return bDefaultValue;
    
    return m_cValue[pszKey].asBool();
}


SPJsonDictionary * SPJsonDictionary::getSubDictionary(const char *pszKey)
{
    SPJsonDictionary * pNewDictionary;
    if (!isKeyValidate(pszKey, m_cValue) || (!m_cValue[pszKey].isArray() && 
                                            !m_cValue[pszKey].isObject() && 
                                            !m_cValue[pszKey].isConvertibleTo(Json::arrayValue) &&
                                            !m_cValue[pszKey].isConvertibleTo(Json::objectValue)))
    {
        pNewDictionary = NULL;
    }
    else
    {
        pNewDictionary = new SPJsonDictionary();
        pNewDictionary->initWithValue(m_cValue[pszKey]);
    }
    return pNewDictionary;
}


std::string SPJsonDictionary::getDescription()
{
    std::string strReturn = m_cValue.toStyledString();
    return strReturn;
}


bool SPJsonDictionary::insertItemToArray(const char *pszArrayKey, int nValue)
{
    Json::Value array;
    if(m_cValue.isMember(pszArrayKey))
    {
        if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue))
            return false;
        
        array = m_cValue[pszArrayKey];
    }
    
    array.append(nValue);
    m_cValue[pszArrayKey] = array;
    
    return true;
}


bool SPJsonDictionary::insertItemToArray(const char *pszArrayKey, double fValue)
{
    Json::Value array;
    if(m_cValue.isMember(pszArrayKey))
    {
        if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue))
            return false;
        
        array = m_cValue[pszArrayKey];
    }
    
    array.append(fValue);
    m_cValue[pszArrayKey] = array;
    
    return true;
}


bool SPJsonDictionary::insertItemToArray(const char *pszArrayKey, const char * pszValue)
{
    Json::Value array;
    if(m_cValue.isMember(pszArrayKey))
    {
        if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue))
            return false;
        
        array = m_cValue[pszArrayKey];
    }
    
    array.append(pszValue);
    m_cValue[pszArrayKey] = array;
    
    return true;
}


bool SPJsonDictionary::insertItemToArray(const char *pszArrayKey, SPJsonDictionary * subDictionary)
{
    Json::Value array;
    if(m_cValue.isMember(pszArrayKey))
    {
        if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue))
            return false;
        
        array = m_cValue[pszArrayKey];
    }
    
    array.append(subDictionary->m_cValue);
    m_cValue[pszArrayKey] = array;
    
    return true;
}


int SPJsonDictionary::getItemCount()
{
    return m_cValue.size();
}


DicItemType SPJsonDictionary::getItemType(int nIndex)
{
    return (DicItemType)m_cValue[nIndex].type();
}


DicItemType SPJsonDictionary::getItemType(const char *pszKey)
{
    return (DicItemType)m_cValue[pszKey].type();
}

std::vector<std::string> SPJsonDictionary::getAllMemberNames()
{
    return m_cValue.getMemberNames();
}


int SPJsonDictionary::getArrayItemCount(const char *pszArrayKey)
{
    int nRet = 0;
    if (!isKeyValidate(pszArrayKey, m_cValue) ||
        (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isObject() && 
         !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue) && !m_cValue[pszArrayKey].isConvertibleTo(Json::objectValue)))
    {
        nRet = 0;
    }
    else
    {
        Json::Value arrayValue = m_cValue[pszArrayKey];
        nRet = arrayValue.size();
    }
        
    return nRet;
}


int SPJsonDictionary::getIntValueFromArray(const char *pszArrayKey, int nIndex, int nDefaultValue)
{
    int nRet = nDefaultValue;
    Json::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
    if (arrayValue)
    {
        if ((*arrayValue)[nIndex].isNumeric())
            nRet = (*arrayValue)[nIndex].asInt();
    }

    return nRet;
}


double SPJsonDictionary::getFloatValueFromArray(const char *pszArrayKey, int nIndex, double fDefaultValue)
{
    double fRet = fDefaultValue;
    Json::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
    if (arrayValue)
    {
        if ((*arrayValue)[nIndex].isNumeric())
            fRet = (*arrayValue)[nIndex].asDouble();
    }
    
    return fRet;
}


const char * SPJsonDictionary::getStringValueFromArray(const char *pszArrayKey, int nIndex)
{
    Json::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
    if (arrayValue)
    {
        if ((*arrayValue)[nIndex].isString())
            return (*arrayValue)[nIndex].asCString();
    }
    
    return NULL;
}


SPJsonDictionary * SPJsonDictionary::getSubItemFromArray(const char *pszArrayKey, int nIndex)
{
    Json::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
    if (arrayValue)
    {
        if ((*arrayValue)[nIndex].isArray() || (*arrayValue)[nIndex].isObject())
        {
            SPJsonDictionary * pNewDictionary = new SPJsonDictionary();
            pNewDictionary->initWithValue((*arrayValue)[nIndex]);
            return pNewDictionary;
        }
    }
    
    return NULL;
}


DicItemType SPJsonDictionary::getItemTypeFromArray(const char *pszArrayKey, int nIndex)
{
    Json::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
    if (arrayValue)
        return (DicItemType)((*arrayValue)[nIndex].type());
    
    return (DicItemType)Json::nullValue;
}


inline bool SPJsonDictionary::isKeyValidate(const char *pszKey, Json::Value& root)
{
    if (root.isNull() || !root.isMember(pszKey))
        return false;
    
    return true;
}


inline Json::Value * SPJsonDictionary::validateArrayItem(const char *pszArrayKey, int nIndex)
{
    if (!isKeyValidate(pszArrayKey, m_cValue) && !m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(Json::arrayValue))
        return NULL;
    if (!m_cValue[pszArrayKey].isValidIndex(nIndex))
        return NULL;
    
    return &m_cValue[pszArrayKey];
}



