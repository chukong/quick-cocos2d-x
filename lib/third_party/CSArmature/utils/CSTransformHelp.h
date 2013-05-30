/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
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

#ifndef COCOSTUDIO_CSTRANSFORMHELP_H
#define COCOSTUDIO_CSTRANSFORMHELP_H

#include "cocos2d.h"
#include "CSDatas.h"

namespace cs {

    
/*
 *  @brief   use to calculate the matrix of node from parent node
 */
class TransformHelp
{
public:
	TransformHelp();

	static void transformFromParent(Node &node, const Node &parentNode);
	static void transformToParent(Node &node, const Node &parentNode);

	static void transformFromParentWithoutScale(Node &node, const Node &parentNode);
	static void transformToParentWithoutScale(Node &node, const Node &parentNode);

	static void nodeToMatrix(const Node &_node, cocos2d::CCAffineTransform &_matrix);
	static void matrixToNode(const cocos2d::CCAffineTransform &_matrix, Node &_node);

	static void nodeConcat(Node &target, Node &source);
public:
	static cocos2d::CCAffineTransform helpMatrix1;
	static cocos2d::CCAffineTransform helpMatrix2;

	static cocos2d::CCPoint helpPoint1;
	static cocos2d::CCPoint helpPoint2;
};

}

#endif
