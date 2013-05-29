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

#include "SPTransformHelp.h"
#include "SPUtilMath.h"

namespace sp{

CCAffineTransform TransformHelp::helpMatrix1;
CCAffineTransform TransformHelp::helpMatrix2;

CCPoint TransformHelp::helpPoint1;
CCPoint TransformHelp::helpPoint2;

TransformHelp::TransformHelp()
{
}

void TransformHelp::transformFromParent(Node &_boneData, const Node &_parentData)
{
	nodeToMatrix(_boneData, helpMatrix1);
	nodeToMatrix(_parentData, helpMatrix2);

	helpMatrix2 = CCAffineTransformInvert(helpMatrix2);
	helpMatrix1 = CCAffineTransformConcat(helpMatrix1, helpMatrix2);

	matrixToNode(helpMatrix1, _boneData);
}

void TransformHelp::nodeToMatrix(const Node &_node, CCAffineTransform &_matrix)
{
	_matrix.a = _node.m_fScaleX * cos(_node.m_fSkewY);
	_matrix.b = _node.m_fScaleX * sin(_node.m_fSkewY);
	_matrix.c = _node.m_fScaleY * sin(_node.m_fSkewX);
	_matrix.d = _node.m_fScaleY * cos(_node.m_fSkewX);

	_matrix.tx = _node.m_fX;
	_matrix.ty = _node.m_fY;
}

void TransformHelp::matrixToNode(const CCAffineTransform &_matrix, Node &_node)
{
    /*
     *  In as3 language, there is a function called "deltaTransformPoint", it calculate a point used give Transform
     *  but not used the tx, ty value. we simulate the function here
     */
	helpPoint1.x = 0;
	helpPoint1.y = 1;
	helpPoint1 = CCPointApplyAffineTransform(helpPoint1, _matrix);
	helpPoint1.x -= _matrix.tx;
	helpPoint1.y -= _matrix.ty;

	helpPoint2.x = 1;
	helpPoint2.y = 0;
	helpPoint2 = CCPointApplyAffineTransform(helpPoint2, _matrix);
	helpPoint2.x -= _matrix.tx;
	helpPoint2.y -= _matrix.ty;



	_node.m_fSkewX = -(atan2f(helpPoint1.y, helpPoint1.x) - 1.5707964f);
	_node.m_fSkewY = atan2f(helpPoint2.y, helpPoint2.x);
	_node.m_fScaleX = sqrt(_matrix.a * _matrix.a + _matrix.b * _matrix.b);
	_node.m_fScaleY = sqrt(_matrix.c * _matrix.c + _matrix.d * _matrix.d);
	_node.m_fX = _matrix.tx;
	_node.m_fY = _matrix.ty;
}

}