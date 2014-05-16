/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

#include "CCScriptSupport.h"
#include "CCScheduler.h"

bool CC_DLL cc_assert_script_compatible(const char *msg)
{
    cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
    if (pEngine && pEngine->handleAssert(msg))
    {
        return true;
    }
    return false;
}

NS_CC_BEGIN

// CCScriptListenerHandle

int CCScriptListenerHandle::s_nextHandleId = 0;

CCScriptListenerHandle* CCScriptListenerHandle::create(int listener)
{
    CCScriptListenerHandle* handle = new CCScriptListenerHandle(listener);
    handle->autorelease();
    return handle;
}

CCScriptListenerHandle::CCScriptListenerHandle(int listener)
: m_listener(listener)
{
    ++s_nextHandleId;
    m_handle = s_nextHandleId;
}

CCScriptListenerHandle::~CCScriptListenerHandle(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
}

int CCScriptListenerHandle::getListener(void)
{
    return m_listener;
}

int CCScriptListenerHandle::getHandle(void)
{
    return m_handle;
}

// CCSchedulerScriptHandle

CCSchedulerScriptHandle* CCSchedulerScriptHandle::create(int listener, float interval, bool paused)
{
    CCSchedulerScriptHandle* handle = new CCSchedulerScriptHandle(listener, interval, paused);
    handle->autorelease();
    return handle;
}

CCSchedulerScriptHandle::CCSchedulerScriptHandle(int listener, float interval, bool paused)
: CCScriptListenerHandle(listener)
, m_paused(paused)
, m_markedForDeletion(false)
{
    m_timer = new CCTimer();
    m_timer->initWithScriptHandler(listener, interval);
    m_timer->autorelease();
    m_timer->retain();
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", listener, m_handle);
}

CCSchedulerScriptHandle::~CCSchedulerScriptHandle(void)
{
    m_timer->release();
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", m_listener, m_handle);
}

CCTimer *CCSchedulerScriptHandle::getTimer(void)
{
    return m_timer;
}

bool CCSchedulerScriptHandle::isPaused(void)
{
    return m_paused;
}

void CCSchedulerScriptHandle::markedForDeletion(void)
{
    m_markedForDeletion = true;
}

bool CCSchedulerScriptHandle::isMarkedForDeletion(void)
{
    return m_markedForDeletion;
}


// CCScriptEngineManager

static CCScriptEngineManager* s_pSharedScriptEngineManager = NULL;


CCScriptEngineManager::~CCScriptEngineManager(void)
{
    removeScriptEngine();
}

void CCScriptEngineManager::setScriptEngine(CCScriptEngineProtocol *pScriptEngine)
{
    removeScriptEngine();
    m_pScriptEngine = pScriptEngine;
}

void CCScriptEngineManager::removeScriptEngine(void)
{
    if (m_pScriptEngine)
    {
        delete m_pScriptEngine;
        m_pScriptEngine = NULL;
    }
}

CCScriptEngineManager* CCScriptEngineManager::sharedManager(void)
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new CCScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}

void CCScriptEngineManager::purgeSharedManager(void)
{
    if (s_pSharedScriptEngineManager)
    {
        delete s_pSharedScriptEngineManager;
        s_pSharedScriptEngineManager = NULL;
    }
}

NS_CC_END
