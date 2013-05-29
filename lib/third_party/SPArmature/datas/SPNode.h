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
#include "reader.h"
#include "SPJsonData.h"

using namespace cocos2d;

namespace sp{

/**
 *  @brief  the base node include a lot of attribute.
 *  
 */
class  Node : public CCObject, public JsonData
{
public:
    static Node *createWithJson(const char *_pszDescription);
	static Node *create();
public:
	Node();
	~Node(void);

    virtual bool initWithJson(const char *_pszDescription);

    /*
     *  @brief   update data's json value
     *
     */
    virtual void updateJson();


    /*
     *  @brief   copy datas from _node
     *
     *  @param  _node   a Node to copy datas
     */
	virtual void copy(Node *_node);

    /*
     *  @brief calculate two Node's between value(_to - _from) and set to self
     *
     *  @param  _from   from Node
     *
     *  @param  _to     to Node
     */
	virtual void subtract(Node *_from, Node *_to);
public:
    //! position x attribute
	float m_fX;
    //! position y attribute
	float m_fY;
    //! zorder attribute, used to order the Bone's depth order
	int	  m_iZOrder;
    
	
    /**
     *  @brief  m_fX m_fY m_fSkewX m_fSkewY m_fScaleX m_fScaleY used to calculate transform matrix
     *  m_fSkewX, m_fSkewY can have rotation effect
     *  To get more matrix information, you can have a look at this pape : http://www.senocular.com/flash/tutorials/transformmatrix/
     */
	float m_fSkewX;
	float m_fSkewY;
	float m_fScaleX;
	float m_fScaleY;
    
    //! m_fSkewX, m_fSkewY, and m_fTweenRotate effect the rotation
	float m_fTweenRotate;
    
    
    //! alpha attribute
	int m_iAlpha;
    //! red color attribute
    int m_iRed;
    //! green color attribute
    int m_iGreen;
    //! blue color attribute
    int m_iBlue;
	
};


}
