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

#pragma  once

#include "cocos2d.h"
#include <stack>

namespace cs{
    
typedef enum
{
    SAX_NONE = 0,
    SAX_KEY,
    SAX_DICT,
    SAX_INT,
    SAX_REAL,
    SAX_STRING,
    SAX_ARRAY
}CSSAXState;

typedef enum
{
    SAX_RESULT_NONE = 0,
    SAX_RESULT_DICT,
    SAX_RESULT_ARRAY
}CSSAXResult;
    
class CSDictMaker : public cocos2d::CCSAXDelegator
{
public:
    CSSAXResult m_eResultType;
    cocos2d::CCArray* m_pRootArray;
    cocos2d::CCDictionary *m_pRootDict;
    cocos2d::CCDictionary *m_pCurDict;
    std::stack<cocos2d::CCDictionary*> m_tDictStack;
    std::string m_sCurKey;   ///< parsed key
    std::string m_sCurValue; // parsed value
    CSSAXState m_tState;
    cocos2d::CCArray* m_pArray;
    
    std::stack<cocos2d::CCArray*> m_tArrayStack;
    std::stack<CSSAXState>  m_tStateStack;
    
public:
    CSDictMaker()
    : m_eResultType(SAX_RESULT_NONE),
    m_pRootArray(NULL),
    m_pRootDict(NULL),
    m_pCurDict(NULL),
    m_tState(SAX_NONE),
    m_pArray(NULL)
    {
    }
    
    ~CSDictMaker()
    {
    }
    
    cocos2d::CCDictionary* dictionaryWithContentsOfCache(const char *pContentCache, unsigned int uDataLength)
    {
        m_eResultType = SAX_RESULT_DICT;
        cocos2d::CCSAXParser parser;
        
        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);
        
        if (pContentCache != NULL && uDataLength > 0)
        {
            parser.parse(pContentCache, uDataLength);
        }
        
        return m_pRootDict;
    }
    
    
    cocos2d::CCDictionary* dictionaryWithContentsOfFile(const char *pFileName)
    {
        m_eResultType = SAX_RESULT_DICT;
        cocos2d::CCSAXParser parser;
        
        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);
        
        parser.parse(pFileName);
        return m_pRootDict;
    }
    
    cocos2d::CCArray* arrayWithContentsOfFile(const char* pFileName)
    {
        m_eResultType = SAX_RESULT_ARRAY;
        cocos2d::CCSAXParser parser;
        
        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);
        
        parser.parse(pFileName);
        return m_pArray;
    }
    
    void startElement(void *ctx, const char *name, const char **atts)
    {
        CC_UNUSED_PARAM(ctx);
        CC_UNUSED_PARAM(atts);
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            m_pCurDict = new cocos2d::CCDictionary();
            if(m_eResultType == SAX_RESULT_DICT && m_pRootDict == NULL)
            {
                // Because it will call m_pCurDict->release() later, so retain here.
                m_pRootDict = m_pCurDict;
                m_pRootDict->retain();
            }
            m_tState = SAX_DICT;
            
            CSSAXState preState = SAX_NONE;
            if (! m_tStateStack.empty())
            {
                preState = m_tStateStack.top();
            }
            
            if (SAX_ARRAY == preState)
            {
                // add the dictionary into the array
                m_pArray->addObject(m_pCurDict);
            }
            else if (SAX_DICT == preState)
            {
                // add the dictionary into the pre dictionary
                CCAssert(! m_tDictStack.empty(), "The state is wrong!");
                cocos2d::CCDictionary* pPreDict = m_tDictStack.top();
                pPreDict->setObject(m_pCurDict, m_sCurKey.c_str());
            }
            
            m_pCurDict->release();
            
            // record the dict state
            m_tStateStack.push(m_tState);
            m_tDictStack.push(m_pCurDict);
        }
        else if(sName == "key")
        {
            m_tState = SAX_KEY;
        }
        else if(sName == "integer")
        {
            m_tState = SAX_INT;
        }
        else if(sName == "real")
        {
            m_tState = SAX_REAL;
        }
        else if(sName == "string")
        {
            m_tState = SAX_STRING;
        }
        else if (sName == "array")
        {
            m_tState = SAX_ARRAY;
            m_pArray = new cocos2d::CCArray();
            if (m_eResultType == SAX_RESULT_ARRAY && m_pRootArray == NULL)
            {
                m_pRootArray = m_pArray;
                m_pRootArray->retain();
            }
            CSSAXState preState = SAX_NONE;
            if (! m_tStateStack.empty())
            {
                preState = m_tStateStack.top();
            }
            
            if (preState == SAX_DICT)
            {
                m_pCurDict->setObject(m_pArray, m_sCurKey.c_str());
            }
            else if (preState == SAX_ARRAY)
            {
                CCAssert(! m_tArrayStack.empty(), "The state is worng!");
                cocos2d::CCArray* pPreArray = m_tArrayStack.top();
                pPreArray->addObject(m_pArray);
            }
            m_pArray->release();
            // record the array state
            m_tStateStack.push(m_tState);
            m_tArrayStack.push(m_pArray);
        }
        else
        {
            m_tState = SAX_NONE;
        }
    }
    
    void endElement(void *ctx, const char *name)
    {
        CC_UNUSED_PARAM(ctx);
        CSSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            m_tStateStack.pop();
            m_tDictStack.pop();
            if ( !m_tDictStack.empty())
            {
                m_pCurDict = m_tDictStack.top();
            }
        }
        else if (sName == "array")
        {
            m_tStateStack.pop();
            m_tArrayStack.pop();
            if (! m_tArrayStack.empty())
            {
                m_pArray = m_tArrayStack.top();
            }
        }
        else if (sName == "true")
        {
            cocos2d::CCString *str = new cocos2d::CCString("1");
            if (SAX_ARRAY == curState)
            {
                m_pArray->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                m_pCurDict->setObject(str, m_sCurKey.c_str());
            }
            str->release();
        }
        else if (sName == "false")
        {
            cocos2d::CCString *str = new cocos2d::CCString("0");
            if (SAX_ARRAY == curState)
            {
                m_pArray->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                m_pCurDict->setObject(str, m_sCurKey.c_str());
            }
            str->release();
        }
        else if (sName == "string" || sName == "integer" || sName == "real")
        {
            cocos2d::CCString* pStrValue = new cocos2d::CCString(m_sCurValue);
            
            if (SAX_ARRAY == curState)
            {
                m_pArray->addObject(pStrValue);
            }
            else if (SAX_DICT == curState)
            {
                m_pCurDict->setObject(pStrValue, m_sCurKey.c_str());
            }
            
            pStrValue->release();
            m_sCurValue.clear();
        }
        
        m_tState = SAX_NONE;
    }
    
    void textHandler(void *ctx, const char *ch, int len)
    {
        CC_UNUSED_PARAM(ctx);
        if (m_tState == SAX_NONE)
        {
            return;
        }
        
        CSSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
        cocos2d::CCString *pText = new cocos2d::CCString(std::string((char*)ch,0,len));
        
        switch(m_tState)
        {
            case SAX_KEY:
                m_sCurKey = pText->getCString();
                break;
            case SAX_INT:
            case SAX_REAL:
            case SAX_STRING:
            {
                if (curState == SAX_DICT)
                {
                    CCAssert(!m_sCurKey.empty(), "not found key : <integet/real>");
                }
                
                m_sCurValue.append(pText->getCString());
            }
                break;
            default:
                break;
        }
        pText->release();
    }
};

class SpriteFrameCacheHelper
{
public:
    static SpriteFrameCacheHelper *sharedSpriteFrameCacheHelper();
    
	static void purgeSpriteFrameCacheHelper();
public:
    
    /**
     *	@brief	Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     *
     */
    void addSpriteFrameFromFile(const char *_plistPath, const char *_imagePath);
    
    void addSpriteFrameFromPak(const char *_plistPath, const char *_imagePath);
    
    void addSpriteFrameFromDict(cocos2d::CCDictionary* dictionary, cocos2d::CCTexture2D *pobTexture, const char *_imagePath);
    
    /**
     *	@brief	Get this display in which image
     *
     */
    const char *getDisplayImagePath(const char *displayName);
	cocos2d::CCTextureAtlas *getTextureAtlas(const char *displayName);
	
private:
    SpriteFrameCacheHelper();
	~SpriteFrameCacheHelper();

    std::map<std::string, std::string> m_Display2ImageMap;
	cocos2d::CCDictionary *m_pDisplay2TextureAtlas;
    
    static SpriteFrameCacheHelper *s_SpriteFrameCacheHelper;

};

}
