/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCScene.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "support/CCPointExtension.h"
#include "script_support/CCScriptSupport.h"
#include "CCDirector.h"

NS_CC_BEGIN

CCScene::CCScene()
: m_touchableNodes(NULL)
, m_touchNode(NULL)
{
    m_touchableNodes = CCArray::createWithCapacity(100);
    m_touchableNodes->retain();
}

CCScene::~CCScene()
{
    CC_SAFE_RELEASE(m_touchableNodes);
}

CCScene *CCScene::create()
{
    CCScene *pRet = new CCScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void CCScene::addTouchableNode(CCNode *node)
{
    if (!m_touchableNodes->containsObject(node))
    {
        m_touchableNodes->addObject(node);
//        CCLOG("ADD TOUCHABLE NODE: %p", node);
        if (!isTouchEnabled())
        {
            setTouchEnabled(true);
        }
    }
}

void CCScene::removeTouchableNode(CCNode *node)
{
    m_touchableNodes->removeObject(node);
//    CCLOG("REMOVE TOUCHABLE NODE: %p", node);
    if (m_touchableNodes->count() == 0 && isTouchEnabled())
    {
        setTouchEnabled(false);
    }
}

bool CCScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_SAFE_RELEASE_NULL(m_touchNode);
    const CCPoint p = pTouch->getLocation();
    CCObject *node;
    CCNode *touchNode = NULL;
    sortAllTouchableNodes();
    CCARRAY_FOREACH(m_touchableNodes, node)
    {
        touchNode = dynamic_cast<CCNode*>(node);
        if (!touchNode->isVisible()) continue;
        const CCRect boundingBox = touchNode->getCascadeBoundingBox();
        if (boundingBox.containsPoint(p))
        {
            touchNode->retain();
            bool ret = touchNode->ccTouchBegan(pTouch, pEvent);
            if (ret && touchNode->isRunning())
            {
                m_touchNode = touchNode;
                m_touchNode->retain();
            }
            touchNode->release();
            if (ret) return true;
        }
    }

    return false;
}

void CCScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_touchNode)
    {
        if (m_touchNode->isRunning())
        {
            m_touchNode->ccTouchMoved(pTouch, pEvent);
        }
        else
        {
            CC_SAFE_RELEASE_NULL(m_touchNode);
        }
    }
}

void CCScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_touchNode)
    {
        m_touchNode->ccTouchEnded(pTouch, pEvent);
        m_touchNode->release();
        m_touchNode = NULL;
    }
}

void CCScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_touchNode)
    {
        m_touchNode->ccTouchCancelled(pTouch, pEvent);
        m_touchNode->release();
        m_touchNode = NULL;
    }
}

void CCScene::visit()
{
    g_drawOrder = 0;
    CCLayer::visit();
}

void CCScene::sortAllTouchableNodes()
{
    int i,j,length = m_touchableNodes->data->num;
    CCNode ** x = (CCNode**)m_touchableNodes->data->arr;
    CCNode *tempItem;

    // insertion sort
    for(i=1; i<length; i++)
    {
        tempItem = x[i];
        j = i-1;

        while(j>=0 && (tempItem->m_drawOrder > x[j]->m_drawOrder))
//        while(j>=0 && (tempItem->m_drawDepth > x[j]->m_drawDepth
//                       || (tempItem->m_drawDepth == x[j]->m_drawDepth && tempItem->m_nZOrder > x[j]->m_nZOrder)
//                       || (tempItem->m_drawDepth == x[j]->m_drawDepth && tempItem->m_nZOrder == x[j]->m_nZOrder &&  tempItem->m_drawOrder > x[j]->m_drawOrder)))
        {
            x[j+1] = x[j];
            j = j-1;
        }
        x[j+1] = tempItem;
    }

    // debug
//    CCLOG("----------------------------------------");
//    for(i=0; i<length; i++)
//    {
//        tempItem = x[i];
//        CCLOG("[%03d] m_drawDepth = %d, m_nZOrder = %d, m_drawOrder = %u, w = %0.2f, h = %0.2f", i, tempItem->m_drawDepth, tempItem->m_nZOrder, tempItem->m_drawOrder, tempItem->getCascadeBoundingBox().size.width, tempItem->getCascadeBoundingBox().size.height);
//    }
}

NS_CC_END
