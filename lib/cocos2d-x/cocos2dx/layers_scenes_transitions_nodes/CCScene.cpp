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
#include "touch_dispatcher/CCTouchTargetNode.h"
#include "support/CCPointExtension.h"
#include "script_support/CCScriptSupport.h"
#include "CCDirector.h"

NS_CC_BEGIN

CCScene::CCScene()
: m_touchableNodes(NULL)
, m_touchingTargets(NULL)
, m_touchDispatchingEnabled(false)
, m_touchRegistered(false)
{
    m_touchableNodes = CCArray::createWithCapacity(100);
    m_touchableNodes->retain();
    m_touchingTargets = CCArray::createWithCapacity(10);
    m_touchingTargets->retain();

    m_bIgnoreAnchorPointForPosition = true;
    setAnchorPoint(ccp(0.5f, 0.5f));
}

CCScene::~CCScene()
{
    CC_SAFE_RELEASE(m_touchableNodes);
    CC_SAFE_RELEASE(m_touchingTargets);
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
//        CCLOG("ADD TOUCHABLE NODE <%p>", node);
        if (!m_touchDispatchingEnabled)
        {
            enableTouchDispatching();
        }
    }
}

void CCScene::removeTouchableNode(CCNode *node)
{
    m_touchableNodes->removeObject(node);
//    CCLOG("REMOVE TOUCHABLE NODE <%p>", node);
    if (m_touchableNodes->count() == 0 && m_touchDispatchingEnabled)
    {
        disableTouchDispatching();
    }
}

void CCScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (!m_touchDispatchingEnabled) return;

    // save touches id
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        m_touchingIds.insert(((CCTouch*)*it)->getID());
    }

    // check current in touching
    if (m_touchingTargets->count())
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHADDED);
        return;
    }

    // start new touching event
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

                if (touchTarget->getTouchMode() == kCCTouchesOneByOne)
                {
                    touchTarget->setTouchId(touch->getID());
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
                node->ccTouchesCaptureBegan(pTouches, touchTarget->getNode());
            }
            else
            {
                dispatchingContinue = node->ccTouchCaptureBegan(touchTarget->findTouch(pTouches), touchTarget->getNode());
            }
        }

        if (!dispatchingContinue)
        {
            // the target stop dispatching, try to next
            continue;
        }

        // phase: targeting
        node = touchTarget->getNode();
        bool ret = true;
        if (touchMode == kCCTouchesAllAtOnce)
        {
            node->ccTouchesBegan(pTouches, pEvent);
        }
        else
        {
            ret = node->ccTouchBegan(touchTarget->findTouch(pTouches), pEvent);
        }

        if (ret)
        {
            m_touchingTargets->addObject(touchTarget);
//            CCLOG("ADD TOUCH TARGET [%p]", touchTarget);
        }

        if (node->isTouchSwallowEnabled())
        {
            // target swallow touch event, stop dispatching
            break;
        }
        
        // continue dispatching, try to next
    }
}

void CCScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    dispatchingTouchEvent(pTouches, pEvent, CCTOUCHMOVED);
}

void CCScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        m_touchingIds.erase(((CCTouch*)*it)->getID());
    }

    if (m_touchingIds.size())
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHREMOVED);
    }
    else
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHENDED);
        // remove all touching nodes
//        CCLOG("TOUCH ENDED, REMOVE ALL TOUCH TARGETS");
        m_touchingTargets->removeAllObjects();
    }
}

void CCScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    dispatchingTouchEvent(pTouches, pEvent, CCTOUCHCANCELLED);
    // remove all touching nodes
//    CCLOG("TOUCH CANCELLED, REMOVE ALL TOUCH TARGETS");
    m_touchingTargets->removeAllObjects();
}

void CCScene::visit()
{
    g_drawOrder = 0;
    CCLayer::visit();
}

void CCScene::cleanup(void)
{
    m_touchRegistered = false;
    m_touchableNodes->removeAllObjects();
    m_touchingTargets->removeAllObjects();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::cleanup();
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
    if (!m_touchRegistered)
    {
        CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
        m_touchRegistered = true;
    }
    m_touchDispatchingEnabled = true;
}

void CCScene::disableTouchDispatching()
{
    m_touchDispatchingEnabled = false;
}

void CCScene::dispatchingTouchEvent(CCSet *pTouches, CCEvent *pEvent, int event)
{
    CCNode *node = NULL;
    CCTouchTargetNode *touchTarget = NULL;
    CCTouch *touch = NULL;

    unsigned int count = m_touchingTargets->count();
//    CCLOG("TOUCH TARGETS COUNT [%u]", count);
    for (unsigned int i = 0; i < count; ++i)
    {
        touchTarget = dynamic_cast<CCTouchTargetNode*>(m_touchingTargets->objectAtIndex(i));

        if (!touchTarget->getNode()->isRunning())
        {
            // target removed from scene, remove it
//            CCLOG("REMOVE TARGET [%u]", i);
            m_touchingTargets->removeObjectAtIndex(i);
            --count;
            --i;
            continue;
        }

        int touchMode = touchTarget->getTouchMode();
        if (touchMode != kCCTouchesAllAtOnce)
        {
            touch = touchTarget->findTouch(pTouches);
            if (!touch)
            {
                // not found touch id for target, skip this target
                continue;
            }
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
        for (int j = path->count() - 1; j >= 0; --j)
        {
            node = dynamic_cast<CCNode*>(path->objectAtIndex(j));
            if (touchMode == kCCTouchesAllAtOnce)
            {
                switch (event)
                {
                    case CCTOUCHMOVED:
                        node->ccTouchesCaptureMoved(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHENDED:
                        node->ccTouchesCaptureEnded(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHCANCELLED:
                        node->ccTouchesCaptureCancelled(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHADDED:
                        node->ccTouchesCaptureAdded(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHREMOVED:
                        node->ccTouchesCaptureRemoved(pTouches, touchTarget->getNode());
                        break;
                }
            }
            else
            {
                switch (event)
                {
                    case CCTOUCHMOVED:
                        node->ccTouchCaptureMoved(touch, touchTarget->getNode());
                        break;

                    case CCTOUCHENDED:
                        node->ccTouchCaptureEnded(touch, touchTarget->getNode());
                        break;

                    case CCTOUCHCANCELLED:
                        node->ccTouchCaptureCancelled(touch, touchTarget->getNode());
                        break;

                    case CCTOUCHREMOVED:
                        if (touch->getID() == touchTarget->getTouchId())
                        {
                            node->ccTouchCaptureEnded(touch, touchTarget->getNode());
                        }
                        break;
                }
            }
        } // for (int j = path->count() - 1; j >= 0; --j)

        // phase: targeting
        node = touchTarget->getNode();
        if (touchMode == kCCTouchesAllAtOnce)
        {
            switch (event)
            {
                case CCTOUCHMOVED:
                    node->ccTouchesMoved(pTouches, pEvent);
                    break;

                case CCTOUCHENDED:
                    node->ccTouchesEnded(pTouches, pEvent);
                    break;

                case CCTOUCHCANCELLED:
                    node->ccTouchesCancelled(pTouches, pEvent);
                    break;

                case CCTOUCHADDED:
                    node->ccTouchesAdded(pTouches, pEvent);
                    break;

                case CCTOUCHREMOVED:
                    node->ccTouchesRemoved(pTouches, pEvent);
                    break;
            }
        }
        else
        {
            switch (event)
            {
                case CCTOUCHMOVED:
                    node->ccTouchMoved(touch, pEvent);
                    break;

                case CCTOUCHENDED:
                    node->ccTouchEnded(touch, pEvent);
                    break;
                    
                case CCTOUCHCANCELLED:
                    node->ccTouchCancelled(touch, pEvent);
                    break;

                case CCTOUCHREMOVED:
                    if (touch->getID() == touchTarget->getTouchId())
                    {
                        node->ccTouchEnded(touch, pEvent);
                        // target touching ended, remove it
//                        CCLOG("REMOVE TARGET [%u]", i);
                        m_touchingTargets->removeObjectAtIndex(i);
                        --count;
                        --i;
                    }
                    break;
            }
        }
    }
}

NS_CC_END
