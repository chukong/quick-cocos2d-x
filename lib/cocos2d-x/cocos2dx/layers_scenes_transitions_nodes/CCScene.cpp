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

CCTouchTargetNode *CCTouchTargetNode::create(CCNode *node)
{
    CCTouchTargetNode *touchableNode = new CCTouchTargetNode(node);
    touchableNode->autorelease();
    return touchableNode;
}

CCTouchTargetNode::CCTouchTargetNode(CCNode *node)
: m_touchId(0)
, m_touch(NULL)
, m_valid(true)
{
    m_node = node;
    m_node->retain();
    m_touchMode = node->getTouchMode();

    m_touches = CCSet::create();
    m_touches->retain();
}

CCTouchTargetNode::~CCTouchTargetNode()
{
    CC_SAFE_RELEASE(m_node);
    CC_SAFE_RELEASE(m_touches);
    CC_SAFE_RELEASE(m_touch);
}

CCNode *CCTouchTargetNode::getNode()
{
    return  m_node;
}

int CCTouchTargetNode::getTouchMode()
{
    return m_touchMode;
}

int CCTouchTargetNode::getTouchId()
{
    CCAssert(m_touchMode == kCCTouchesOneByOne, "");
    return m_touchId;
}

void CCTouchTargetNode::setTouchId(int touchId)
{
    CCAssert(m_touchMode == kCCTouchesOneByOne, "");
    m_touchId = touchId;
}

CCTouch *CCTouchTargetNode::getTouch()
{
    CCAssert(m_touchMode == kCCTouchesOneByOne, "");
    return m_touch;
}

void CCTouchTargetNode::setTouch(CCTouch *touch)
{
    CCAssert(m_touchMode == kCCTouchesOneByOne, "");
    m_touch = touch->copy();
    m_touch->autorelease();
    m_touch->retain();
}

void CCTouchTargetNode::addTouchIdForMultiTouches(int touchId)
{
    CCAssert(m_touchMode == kCCTouchesAllAtOnce, "");
    m_touchIds.push_back(touchId);
}

bool CCTouchTargetNode::hasTouchIdForMultiTouches(int touchId)
{
    CCAssert(m_touchMode == kCCTouchesAllAtOnce, "");
    for (vector<int>::iterator it = m_touchIds.begin(); it != m_touchIds.end(); ++it)
    {
        if (*it == touchId) return true;
    }
    return false;
}

CCSet *CCTouchTargetNode::getTouchesForMultiTouches()
{
    CCAssert(m_touchMode == kCCTouchesAllAtOnce, "");
    return m_touches;
}

void CCTouchTargetNode::addTouchForMultiTouches(CCTouch *touch)
{
    CCAssert(m_touchMode == kCCTouchesAllAtOnce, "");
    CCTouch *copy = touch->copy();
    copy->autorelease();
    m_touches->addObject(copy);
}

void CCTouchTargetNode::cleanupTouchAndTouches()
{
    CC_SAFE_RELEASE_NULL(m_touch);
    CC_SAFE_RELEASE_NULL(m_touches);
}

void CCTouchTargetNode::setInvalid()
{
    m_valid = false;
}

bool CCTouchTargetNode::isValid()
{
    return m_valid;
}

// ----

CCScene::CCScene()
: m_touchableNodes(NULL)
, m_touchingTarget(NULL)
, m_touchDispatchingEnabled(false)
{
    m_touchableNodes = CCArray::createWithCapacity(100);
    m_touchableNodes->retain();
    m_bIgnoreAnchorPointForPosition = true;
    setAnchorPoint(ccp(0.5f, 0.5f));
}

CCScene::~CCScene()
{
    CC_SAFE_RELEASE(m_touchableNodes);
    CC_SAFE_RELEASE(m_touchingTarget);
}

bool CCScene::init()
{
    bool bRet = false;
    do
    {
        CCDirector *pDirector;
        CC_BREAK_IF(!(pDirector = CCDirector::sharedDirector()));
        this->setContentSize(pDirector->getWinSize());
        // success
        bRet = true;
    } while (0);
    return bRet;
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

CCScene *CCScene::getScene()
{
    return this;
}

void CCScene::addTouchableNode(CCNode *node)
{
    if (!m_touchableNodes->containsObject(node))
    {
        m_touchableNodes->addObject(node);
        CCLOG("ADD TOUCHABLE NODE <%p>", node);
        if (!m_touchDispatchingEnabled)
        {
            enableTouchDispatching();
        }
    }
}

void CCScene::removeTouchableNode(CCNode *node)
{
    m_touchableNodes->removeObject(node);
    CCLOG("REMOVE TOUCHABLE NODE <%p>", node);
    if (m_touchableNodes->count() == 0 && m_touchDispatchingEnabled)
    {
        disableTouchDispatching();
    }
}

bool CCScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    // cleanup
    CC_SAFE_RELEASE_NULL(m_touchingTarget);

    // sort touchable nodes
    sortAllTouchableNodes(m_touchableNodes);

    // find touching target
    bool isTouchable = true;
    CCObject *obj = NULL;
    CCNode *node = NULL;
    CCNode *checkTouchableNode = NULL;
    CCTouchTargetNode *touchTarget = NULL;

    CCARRAY_FOREACH(m_touchableNodes, obj)
    {
        checkTouchableNode = node = dynamic_cast<CCNode*>(obj);

        // check node is visible and capturing enabled
        isTouchable = true;
        do
        {
            isTouchable = isTouchable
                    && checkTouchableNode->isRunning()
                    && checkTouchableNode->isVisible()
                    && checkTouchableNode->isTouchCaptureEnabled();
            checkTouchableNode = checkTouchableNode->getParent();
        } while (checkTouchableNode && isTouchable);
        if (!isTouchable) continue;

        // prepare for touch testing
        touchTarget = NULL;
        const CCRect boundingBox = node->getCascadeBoundingBox();

        // set touch target
        CCTouch *touch = NULL;
        for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
        {
            touch = (CCTouch*)*it;
            const CCPoint touchPoint = touch->getLocation();

            if (boundingBox.containsPoint(touchPoint))
            {
                if (!touchTarget)
                {
                    touchTarget = CCTouchTargetNode::create(node);
                }

                if (touchTarget->getTouchMode() == kCCTouchesAllAtOnce)
                {
                    touchTarget->addTouchForMultiTouches(touch);
                }
                else
                {
                    touchTarget->setTouch(touch);
                    break;
                }
            }
        }

        if (!touchTarget)
        {
            // touch points not in current target, try to next
            continue;
        }

        // try to dispatching event
        CCArray *path = CCArray::createWithCapacity(10);
        node = touchTarget->getNode();
        do
        {
            path->addObject(node);
            node = node->getParent();
        } while (node != NULL && node != this);

        // phase: capturing
        // from parent to child
        bool dispatchingContinue = true;
        int touchMode = touchTarget->getTouchMode();
        for (int i = path->count() - 1; dispatchingContinue && i >= 0; --i)
        {
            node = dynamic_cast<CCNode*>(path->objectAtIndex(i));
            if (touchMode == kCCTouchesAllAtOnce)
            {
                dispatchingContinue = node->ccTouchesCaptureBegan(touchTarget->getTouchesForMultiTouches(),
                                                                  touchTarget->getNode());
            }
            else
            {
                dispatchingContinue = node->ccTouchCaptureBegan(touchTarget->getTouch(), touchTarget->getNode());
            }
        }

        if (!dispatchingContinue)
        {
            // the target stop dispatching, try to next
            continue;
        }

        // phase: targeting
        node = touchTarget->getNode();
        if (touchMode == kCCTouchesAllAtOnce)
        {
            dispatchingContinue = node->ccTouchesBegan(touchTarget->getTouchesForMultiTouches(), pEvent);
        }
        else
        {
            dispatchingContinue = node->ccTouchBegan(touchTarget->getTouch(), pEvent);
        }

        if (!dispatchingContinue)
        {
            // the target stop dispatching, try to next
            continue;
        }

        m_touchingTarget = touchTarget;
        m_touchingTarget->retain();
        break;
    }

    return true;
}

void CCScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void CCScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    // remove all touching nodes
    CC_SAFE_RELEASE_NULL(m_touchingTarget);
}

void CCScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    // remove all touching nodes
    CC_SAFE_RELEASE_NULL(m_touchingTarget);
}

//void CCScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCNode *touchNode = NULL;
//    unsigned int count = m_touchingNodes->count();
//    for (unsigned int i = 0; i < count; ++i)
//    {
//        touchNode = dynamic_cast<CCNode*>(m_touchingNodes->objectAtIndex(i));
//        if (touchNode->isRunning())
//        {
//            touchNode->ccTouchMoved(pTouch, pEvent);
//        }
//        else
//        {
//            m_touchingNodes->removeObjectAtIndex(i);
//            count--;
//            i--;
//        }
//    }
//}
//
//void CCScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCObject *node;
//    CCNode *touchNode = NULL;
//    CCARRAY_FOREACH(m_touchingNodes, node)
//    {
//        touchNode = dynamic_cast<CCNode*>(node);
//        if (touchNode->isRunning())
//        {
//            touchNode->ccTouchEnded(pTouch, pEvent);
//        }
//    }
//    m_touchingNodes->removeAllObjects();
//}
//
//void CCScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCObject *node;
//    CCNode *touchNode = NULL;
//    CCARRAY_FOREACH(m_touchingNodes, node)
//    {
//        touchNode = dynamic_cast<CCNode*>(node);
//        if (touchNode->isRunning())
//        {
//            touchNode->ccTouchCancelled(pTouch, pEvent);
//        }
//    }
//    m_touchingNodes->removeAllObjects();
//}

void CCScene::visit()
{
    g_drawOrder = 0;
    CCLayer::visit();
}

CCTouchTargetNode *CCScene::findTouchingNode(CCNode *node)
{
    CCObject *obj;
    CCTouchTargetNode *touchableNode;
    CCARRAY_FOREACH(m_touchableNodes, obj)
    {
        touchableNode = dynamic_cast<CCTouchTargetNode*>(obj);
        if (touchableNode->getNode() == node)
        {
            return touchableNode;
        }
    }
    return NULL;
}

void CCScene::sortAllTouchableNodes(CCArray *nodes)
{
    int i, j, length = nodes->data->num;
    CCNode **x = (CCNode**)nodes->data->arr;
    CCNode *tempItem;

    // insertion sort
    for(i = 1; i < length; i++)
    {
        tempItem = x[i];
        j = i - 1;

        while(j >= 0 && (tempItem->m_drawOrder > x[j]->m_drawOrder))
        {
            x[j + 1] = x[j];
            j = j - 1;
        }
        x[j + 1] = tempItem;
    }

    // debug
    //    CCLOG("----------------------------------------");
    //    for(i=0; i<length; i++)
    //    {
    //        tempItem = x[i];
    //        CCLOG("[%03d] m_drawOrder = %u, w = %0.2f, h = %0.2f", i, tempItem->m_drawOrder, tempItem->getCascadeBoundingBox().size.width, tempItem->getCascadeBoundingBox().size.height);
    //    }
}

void CCScene::enableTouchDispatching()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    m_touchDispatchingEnabled = true;
}

void CCScene::disableTouchDispatching()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    m_touchDispatchingEnabled = false;
}

NS_CC_END
