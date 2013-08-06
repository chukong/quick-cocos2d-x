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

#include "CCLinkPosition.h"
#include "CCAction.h"
#include "CCActionInterval.h"
#include "base_nodes/CCNode.h"
#include "support/CCPointExtension.h"
#include "CCDirector.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN

//
// Follow
//
CCLinkPosition::~CCLinkPosition()
{
    CC_SAFE_RELEASE(m_pobFollowedNode);
}

CCLinkPosition* CCLinkPosition::create(CCNode *pFollowedNode)
{
    CCLinkPosition *pRet = new CCLinkPosition();
    if (pRet && pRet->initWithTarget(pFollowedNode))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCLinkPosition::initWithTarget(CCNode *pFollowedNode)
{
    CCAssert(pFollowedNode != NULL, "");

    pFollowedNode->retain();
    m_pobFollowedNode = pFollowedNode;

    return true;
}

CCObject *CCLinkPosition::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    CCLinkPosition *pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCLinkPosition*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCLinkPosition();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCAction::copyWithZone(pZone);
    // copy member data
    pRet->m_nTag = m_nTag;
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCLinkPosition::step(float dt)
{
    CC_UNUSED_PARAM(dt);

    m_pTarget->setPosition(m_pobFollowedNode->getPosition());
}

bool CCLinkPosition::isDone()
{
    return ( !m_pobFollowedNode->isRunning() );
}

void CCLinkPosition::stop()
{
    m_pTarget = NULL;
    CCAction::stop();
}

NS_CC_END
