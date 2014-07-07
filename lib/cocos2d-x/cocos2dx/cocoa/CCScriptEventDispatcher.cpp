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

#include <algorithm>

#include "CCScriptEventDispatcher.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

unsigned int CCScriptEventDispatcher::s_nextScriptEventHandleIndex = 0;

CCScriptEventDispatcher::CCScriptEventDispatcher()
: m_scriptEventListeners(NULL)
{
}

CCScriptEventDispatcher::~CCScriptEventDispatcher()
{
    if (m_scriptEventListeners)
    {
        removeAllScriptEventListeners();
        m_scriptEventListeners->release();
    }
}

int CCScriptEventDispatcher::addScriptEventListener(int event, int listener, int tag /* = 0 */)
{
    if (!m_scriptEventListeners)
    {
        m_scriptEventListeners = CCArray::createWithCapacity(10);
        m_scriptEventListeners->retain();
    }

    s_nextScriptEventHandleIndex++;
    m_scriptEventListeners->addObject(CCScriptHandlePair::create(s_nextScriptEventHandleIndex, event, listener, tag));

    return s_nextScriptEventHandleIndex;
}

void CCScriptEventDispatcher::removeScriptEventListener(unsigned int handle)
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    unsigned int c = m_scriptEventListeners->count();
    CCScriptHandlePair *p;
    for (unsigned int i = 0; i < c; ++i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(m_scriptEventListeners->objectAtIndex(i));
        if (p->handle != handle) continue;
        if (!p->removed)
        {
            p->removed = true;
            engine->removeScriptHandler(p->listener);
            break;
        }
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByEvent(int event)
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    unsigned int c = m_scriptEventListeners->count();
    CCScriptHandlePair *p;
    for (unsigned int i = 0; i < c; ++i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(m_scriptEventListeners->objectAtIndex(i));
        if (!p->removed && p->event == event)
        {
            p->removed = true;
            engine->removeScriptHandler(p->listener);
        }
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByTag(int tag)
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    unsigned int c = m_scriptEventListeners->count();
    CCScriptHandlePair *p;
    for (unsigned int i = 0; i < c; ++i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(m_scriptEventListeners->objectAtIndex(i));
        if (!p->removed && p->tag == tag)
        {
            p->removed = true;
            engine->removeScriptHandler(p->listener);
        }
    }
}

void CCScriptEventDispatcher::removeAllScriptEventListeners()
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    unsigned int c = m_scriptEventListeners->count();
    CCScriptHandlePair *p;
    for (unsigned int i = 0; i < c; ++i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(m_scriptEventListeners->objectAtIndex(i));
        if (!p->removed)
        {
            p->removed = true;
            engine->removeScriptHandler(p->listener);
        }
    }
}

NS_CC_END
