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

#include "cocos2d.h"

#include "SPJsonData.h"
using namespace cocos2d;

namespace sp{

/*
 *  @brief  ContourData include a contour vertex information 
 */
class  ContourData : public CCObject, public JsonData
{
public:
    static ContourData *createWithJson(const char *_pszDescription);
	static ContourData *create();
public:
	ContourData();
	~ContourData(void);
    
    virtual bool init();
    
    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();
    
    /*
     *  @brief  add a vertex to this contour, this method will retain this CCPoint, and release it when remove it.
     */
    void addVertex(CCPoint *_vertex);
    
    /*
     *  @brief  insert a vertex to this contour, this method will retain this CCPoint, and release it when remove it.
     */
    void insertVertex(CCPoint *_vertex, int _index);
    
    /*
     *  @brief  remove vertex
     */
    void removeVertex(CCPoint *_vertex);
    
    /*
     *  @brief  get the vertex form given index
     */
    CCPoint *getVertex(int _index);
    
    /*
     *  @brief  get the index of given vertex
     */
    int indexOfVertex(CCPoint *_vertex);
    
    /*
     *  @brief  get the vertex count
     */
    int getVertexCount();
    
    /*
     *  @brief  get the vertex list
     */
    const CCArray *getVertexList();
    
private:
    //! save contour vertex info, vertex saved in a CCPoint
    CCArray *m_pVertexList;
};
		

}
