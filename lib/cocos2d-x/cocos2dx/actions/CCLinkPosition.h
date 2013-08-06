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

#ifndef __ACTIONS_CCLINKPOSITION_H__
#define __ACTIONS_CCLINKPOSITION_H__

#include "actions/CCAction.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 @brief CCLinkPosition is an action that "follows" a node.

 Eg:
 layer->runAction(CCLinkPosition::actionWithTarget(hero));

 Instead of using CCCamera as a "follower", use this action instead.
 @since v0.99.2
 */
class CC_DLL CCLinkPosition : public CCAction
{
public:
    CCLinkPosition()
    : m_pobFollowedNode(NULL)
    {}
    virtual ~CCLinkPosition(void);

    bool initWithTarget(CCNode *pFollowedNode);

    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual void stop(void);

public:
    /** creates the action with a set boundary,
     It will work with no boundary if @param rect is equal to CCRectZero.
     */
    static CCLinkPosition* create(CCNode *pFollowedNode);
protected:
    // node to follow
    CCNode *m_pobFollowedNode;
};

NS_CC_END

#endif /* defined(__ACTIONS_CCLINKPOSITION_H__) */
