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

#include "CSBatchNode.h"
#include "CSArmatureDefine.h"
#include "CSArmature.h"

using namespace cocos2d;

namespace cs {

BatchNode *BatchNode::create()
{
	BatchNode *batchNode = new BatchNode();
	if (batchNode && batchNode->init())
	{
		batchNode->autorelease();
		return batchNode;
	}
	CC_SAFE_DELETE(batchNode);
	return NULL;
}

BatchNode::BatchNode()
	:m_pAtlas(NULL)
{
}

bool BatchNode::init()
{
	bool ret = CCNode::init();
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	return ret;
}

void BatchNode::addChild(CCNode *child, int zOrder, int tag)
{
	CCNode::addChild(child, zOrder, tag);
	Armature *armature = dynamic_cast<Armature*>(child);
	if (armature != NULL)
	{
		armature->setBatchNode(this);
	}
}

void BatchNode::visit()
{
	// quick return if not visible. children won't be drawn.
	if (!m_bVisible)
	{
		return;
	}
	kmGLPushMatrix();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	transform();
	sortAllChildren();
	draw();

	// reset for next frame
	m_uOrderOfArrival = 0;

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

void BatchNode::draw()
{
	CC_NODE_DRAW_SETUP();
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pChildren, object)
	{
		Armature *armature = dynamic_cast<Armature*>(object);
		if (armature)
		{
			armature->visit();
			m_pAtlas = armature->getTextureAtlas();
		}
		else
		{
			((CCNode*)object)->visit();
		}
	}

	if (m_pAtlas)
	{
		m_pAtlas->drawQuads();
		m_pAtlas->removeAllQuads();
	}
}

}