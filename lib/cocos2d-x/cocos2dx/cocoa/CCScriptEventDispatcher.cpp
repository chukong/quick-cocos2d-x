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

#include "CCScriptEventDispatcher.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

int CCScriptEventDispatcher::s_nextScriptEventHandleId = 0;
CCScriptEventListenersForEvent CCScriptEventDispatcher::s_emptyListenersForEvent;
CCScriptEventListenersForDispatcher CCScriptEventDispatcher::s_emptyListeners;

CCScriptEventDispatcher::CCScriptEventDispatcher()
{
    m_scriptEventListeners = NULL;
}

CCScriptEventDispatcher::~CCScriptEventDispatcher()
{
    if (m_scriptEventListeners)
    {
        removeAllScriptEventListeners();
        delete m_scriptEventListeners;
    }
}

int CCScriptEventDispatcher::addScriptEventListener(int event, int listener, int tag /* = 0 */)
{
    if (!m_scriptEventListeners)
    {
        m_scriptEventListeners = new CCScriptEventListenersForDispatcher();
    }
    s_nextScriptEventHandleId++;
    CCScriptHandlePair p = {listener, tag};
    (*m_scriptEventListeners)[event][s_nextScriptEventHandleId] = p;
    return s_nextScriptEventHandleId;
}

void CCScriptEventDispatcher::removeScriptEventListener(int handle)
{
    if (!m_scriptEventListeners) return;

    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEventIterator it2 = it->second.begin();
        for (; it2 != it->second.end(); ++it2)
        {
            if (it->first == handle)
            {
                const CCScriptHandlePair &p = it2->second;
                CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(p.listener);
                LUALOG("[LUA] Remove script event listener: %d", p.listener);
                it->second.erase(it2);
                return;
            }
        }
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByEvent(int event)
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->find(event);
    if (it != m_scriptEventListeners->end())
    {
        CCScriptEventListenersForEvent &listeners = it->second;
        for (CCScriptEventListenersForEventIterator it2 = listeners.begin(); it2 != listeners.end(); ++it2)
        {
            const CCScriptHandlePair &p = it2->second;
            engine->removeScriptHandler(p.listener);
            LUALOG("[LUA] Remove script event listener: %d", p.listener);
        }
        m_scriptEventListeners->erase(it);
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByTag(int tag)
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEventIterator it2 = it->second.begin();
        for (; it2 != it->second.end(); ++it2)
        {
            const CCScriptHandlePair &p = it2->second;
            if (p.tag == tag)
            {
                engine->removeScriptHandler(p.listener);
                LUALOG("[LUA] Remove script event listener: %d", callback);
                it->second.erase(it2);
            }
        }
    }
}

void CCScriptEventDispatcher::removeAllScriptEventListeners()
{
    if (!m_scriptEventListeners) return;

    CCScriptEngineProtocol *engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEventIterator it2 = it->second.begin();
        for (; it2 != it->second.end(); ++it2)
        {
            const CCScriptHandlePair &p = it2->second;
            engine->removeScriptHandler(p.listener);
            LUALOG("[LUA] Remove script event listener: %d", callback);
        }
    }
    m_scriptEventListeners->clear();
}

bool CCScriptEventDispatcher::hasScriptEventListener(int event)
{
    return m_scriptEventListeners && m_scriptEventListeners->find(event) != m_scriptEventListeners->end();
}

CCScriptEventListenersForEvent &CCScriptEventDispatcher::getScriptEventListenersByEvent(int event) const
{
    if (!m_scriptEventListeners) return s_emptyListenersForEvent;

    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->find(event);
    return  it != m_scriptEventListeners->end() ? it->second : s_emptyListenersForEvent;
}

CCScriptEventListenersForDispatcher &CCScriptEventDispatcher::getAllScriptEventListeners() const
{
    return m_scriptEventListeners ? *m_scriptEventListeners : s_emptyListeners;
}

NS_CC_END
