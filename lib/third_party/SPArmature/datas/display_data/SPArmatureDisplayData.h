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

#pragma once

#include "SPContourSprite.h"
#include "cocos2d.h"

#include "SPJsonData.h"

#include "SPDisplayData.h"

using namespace cocos2d;

namespace sp{

    
class  ArmatureDisplayData  : public DisplayData{
    
public:
    static ArmatureDisplayData *createWithJson(const char *_pszDescription);
	static ArmatureDisplayData *create();
public:
    ArmatureDisplayData();
    virtual ~ArmatureDisplayData(){};
    
    virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
    
    
    void setParam(const char *_displayName)
    {
        m_strDisplayName = _displayName;
    }
    
    void setDisplayName(const char *str){ m_strDisplayName = str; }
    std::string &getDisplayName(){ return m_strDisplayName; }
    
    void copy(ArmatureDisplayData *_displayData);
    
private:
    
    std::string m_strDisplayName;
    
public:
    
//    CREATE_JS_CLASS(ArmatureDisplayData, DisplayData)
//    JS_NO_RETURN_FUNCTION_1(ArmatureDisplayData, setParamJS, const char*)
//    JS_FUNCTION_0(ArmatureDisplayData, getDisplayName)
    
    
};

}