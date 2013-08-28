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
{
}

CCScene::~CCScene()
{
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


bool CCScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        return excuteScriptTouchHandler(CCTOUCHBEGAN, pTouch) == 0 ? false : true;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    CCAssert(false, "Layer#ccTouchBegan override me");
    return true;
}

void CCScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHCANCELLED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHBEGAN, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHCANCELLED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

NS_CC_END
