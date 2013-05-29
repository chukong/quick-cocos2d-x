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

using namespace cocos2d;

namespace sp{
    
    
enum RENDER_TYPE
{
    SIMPLE_ZORDER,          //! use a single png and cocos2dx zorder to order
    BATCHNODE_ZORDER,       //! use CCSpriteBatchNode and cocos2dx zorder to order
    BATCHNODE_VERTEXZ,      //! use CCSpriteBatchNode and cocos2dx vertexz to order. The batch node will open depth test and alpha test, the advantage is we can order between two different CCSpriteBatchNode, the disadvantage is it can't have      translucence effect.
    
    RENDER_MAX
};


class BatchNode : public CCSpriteBatchNode
{
public:
	static BatchNode *create(const char *_fileName);
public:
    BatchNode();
    
    
	void draw();
    
    /*
     *  @brief   set this BatchNode's render type
     *
     *  @@param _renderType    RENDER_TYPE you want to set
     */
    void setRenderType(RENDER_TYPE _renderType);
    
    /*
     *  @brief   get this BatchNode's render type
     *
     *  @return    RENDER_TYPE you want to set
     */
    RENDER_TYPE getRenderType();
    
private:
    RENDER_TYPE m_eRenderType;
};


}