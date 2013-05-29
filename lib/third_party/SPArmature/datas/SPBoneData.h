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

#include "SPNode.h"

#include "SPJsonData.h"
#include "SPDisplayData.h"

namespace sp{

/**
 *  @brief  BoneData used to init a Bone.
 *  BoneData keeps a DisplayData list, a Bone can have many display to change.
 *  The display information saved in the DisplayData
 */
class  BoneData : public Node
{
public:
    static BoneData *createWithJson(const char *_pszDescription);
	static BoneData *create();
public:
	BoneData(void);
	~BoneData(void);

    /*
     *  @brief   create CCArray DataList
     */
	virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
    
    
    /*
     *  @brief   depth copy the information from the given data to self
     *
     *  @param  the data you want to copy
     */
	//void copy(BoneData *_data);
    
    
    DisplayData *addDisplayData(DisplayData *_displayData);
    DisplayData *addDisplayData(DisplayType _displayType, const char *_pszDescription = NULL);
    DisplayData *insertDisplayData(DisplayData *_displayData, int _index);
    DisplayData *removeDisplayData(int _index);
    DisplayData *changeDisplayDataAtIndex(int _index, DisplayData *_displayData);
    
    
    DisplayData *getDisplayData(int _index);
    CCArray *getDisplayList();
    int getDisplayCount();

public:
    //! the bone's name
	std::string m_strName;
    //! the bone parent's name
	std::string m_strParent;

private:
    //! save DisplayData informations for the Bone
	CCArray *m_pDisplayDataList;
};



}