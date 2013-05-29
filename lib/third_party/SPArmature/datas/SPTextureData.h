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


#include "SPContourData.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace sp{

/*
 *  @brief  TextureData include a texture's information 
 */
class  TextureData : public CCObject, public JsonData
{
public:
    static TextureData *createWithJson(const char *_pszDescription);
	static TextureData *create();
public:
	TextureData();
	~TextureData(void);
    
    virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
public:
    //! the texture's name
	std::string m_strName;
    
    //! the texture's anchor point
	float m_fPivotX;
	float m_fPivotY;
	
    //! the texture's width
    float m_fWidth;
    //! the texture's height
	float m_fHeight;
    
    /*
     *  @brief  add a ContourData to this contour, this method will retain this ContourData, and release it when remove it.
     */
    void addContourData(ContourData *_contourData);
    
    /*
     *  @brief  remove ContourData
     */
    void removeContourData(ContourData *_contourData);
    
    /*
     *  @brief  get the ContourData form given index
     */
    ContourData *getContourData(int _index);
    
    CCArray *getContourDatas();
    
    /*
     *  @brief  get the ContourData count
     */
    int getContourCount();
private:
    CCArray *m_pContourDataList;
    
};
		

}
