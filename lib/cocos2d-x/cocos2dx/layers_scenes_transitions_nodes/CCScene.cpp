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
, m_touchTargets(NULL)
{
    m_touchableNodes = CCArray::createWithCapacity(100);
    m_touchableNodes->retain();
    m_touchTargets = CCArray::createWithCapacity(10);
    m_touchTargets->retain();
    m_bIgnoreAnchorPointForPosition = true;
    setAnchorPoint(ccp(0.5f, 0.5f));
}

CCScene::~CCScene()
{
    CC_SAFE_RELEASE(m_touchableNodes);
    CC_SAFE_RELEASE(m_touchTargets);
}

bool CCScene::init()
{
    bool bRet = false;
     do
     {
         CCDirector * pDirector;
         CC_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
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

void CCScene::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

int CCScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    // remove all touch targets
    m_touchTargets->removeAllObjects();

    // check touch targets
    const CCPoint p = pTouch->getLocation();
    CCObject *node;
    CCNode *touchNode = NULL;
    CCNode *checkVisibleNode = NULL;
    bool visible = true;
    sortAllTouchableNodes(m_touchableNodes);
    CCARRAY_FOREACH(m_touchableNodes, node)
    {
        checkVisibleNode = touchNode = dynamic_cast<CCNode*>(node);

        // check node is visible
        visible = true;
        do
        {
            visible = visible && checkVisibleNode->isVisible();
            checkVisibleNode = checkVisibleNode->getParent();
        } while (checkVisibleNode && visible);
        if (!visible) continue;

        const CCRect boundingBox = touchNode->getCascadeBoundingBox();
        if (touchNode->isRunning() && boundingBox.containsPoint(p))
        {
            touchNode->retain();
            int ret = touchNode->ccTouchBegan(pTouch, pEvent);
            if (ret == kCCTouchBegan || ret == kCCTouchBeganNoSwallows)
            {
                m_touchTargets->addObject(touchNode);
                if (ret == kCCTouchBegan)
                {
                    touchNode->release();
                    break;
                }
            }
            touchNode->release();
        }
    }

    sortAllTouchableNodes(m_touchTargets);
    return kCCTouchBegan;
}

int CCScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCNode *touchNode = NULL;
    unsigned int count = m_touchTargets->count();
    for (unsigned int i = 0; i < count; ++i)
    {
        touchNode = dynamic_cast<CCNode*>(m_touchTargets->objectAtIndex(i));
        if (touchNode->isRunning())
        {
            int ret = touchNode->ccTouchMoved(pTouch, pEvent);
            if (ret == kCCTouchMovedSwallows) break;
            if (ret == kCCTouchMovedReleaseOthers)
            {
                for (int j = count - 1; j >= 0; --j)
                {
                    if (j != i)
                    {
                        touchNode = dynamic_cast<CCNode*>(m_touchTargets->objectAtIndex(j));
                        touchNode->ccTouchCancelled(pTouch, pEvent);
                        m_touchTargets->removeObjectAtIndex(j);
                    }
                }
                break;
            }
        }
        else
        {
            m_touchTargets->removeObjectAtIndex(i);
            count--;
            i--;
        }
    }
    return kCCTouchMoved;
}

void CCScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCObject *node;
    CCNode *touchNode = NULL;
    CCARRAY_FOREACH(m_touchTargets, node)
    {
        touchNode = dynamic_cast<CCNode*>(node);
        if (touchNode->isRunning())
        {
            touchNode->ccTouchEnded(pTouch, pEvent);
        }
    }
    m_touchTargets->removeAllObjects();
}

void CCScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCObject *node;
    CCNode *touchNode = NULL;
    CCARRAY_FOREACH(m_touchTargets, node)
    {
        touchNode = dynamic_cast<CCNode*>(node);
        if (touchNode->isRunning())
        {
            touchNode->ccTouchCancelled(pTouch, pEvent);
        }
    }
    m_touchTargets->removeAllObjects();
}

void CCScene::visit()
{
    g_drawOrder = 0;
    CCLayer::visit();
}

void CCScene::sortAllTouchableNodes(CCArray *nodes)
{
    int i,j,length = nodes->data->num;
    CCNode ** x = (CCNode**)nodes->data->arr;
    CCNode *tempItem;

    // insertion sort
    for(i=1; i<length; i++)
    {
        tempItem = x[i];
        j = i-1;

        while(j>=0 && (tempItem->m_drawOrder > x[j]->m_drawOrder))
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
//        CCLOG("[%03d] m_drawOrder = %u, w = %0.2f, h = %0.2f", i, tempItem->m_drawOrder, tempItem->getCascadeBoundingBox().size.width, tempItem->getCascadeBoundingBox().size.height);
//    }
}

NS_CC_END
