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
#include "SPDisplayFactory.h"

using namespace cocos2d;

namespace sp{


class  DisplayData : public CCObject, public JsonData
{
public:
    static DisplayData *createWithJson(const char *_pszDescription);
	static DisplayData *create();
    
    static const char *changeDisplayToTexture(const char *);
public:
//    DisplayData(DEFINE_JS obj){}
    DisplayData();
    virtual ~DisplayData(void);
    
    virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
    
    
    
    void setDisplayType(int _displayType){ m_eDisplayType = (DisplayType)_displayType; }
    int getDisplayType(){ return m_eDisplayType; }
    
protected:
	//! mark which type your display is
    DisplayType m_eDisplayType;
    
public:
//    CREATE_JS_CLASS_ROOT(DisplayData)
//    JS_NO_RETURN_FUNCTION_1(DisplayData, setDisplayType, int)
//    JS_FUNCTION_0(DisplayData, getDisplayType)
    
};


}