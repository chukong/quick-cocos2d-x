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

#include "CCEventDispatcher.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

int CCEventDispatcher::s_nextid = 0;

int CCEventDispatcher::addScriptEventListener(int event, int callback)
{
    s_nextid++;
    m_map[event][s_nextid] = callback;

    if (event == EVENT_ON_ENTER_FRAME)
    {
        scheduleUpdateForNodeEvent();
    }
    return s_nextid;
}

void CCEventDispatcher::removeScriptEventListener(int event, int handle)
{
    ScriptEventHandlerMapIterator it = m_map.find(event);
    if (it != m_map.end())
    {
        ScriptHandlerMap &handlers = it->second;
        ScriptHandlerMapIterator it2 = handlers.find(handle);
        if (it2 != handlers.end())
        {
            int callback = it2->second;
            CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(callback);
            LUALOG("[LUA] Remove script event listener: %d", callback);
            it->second.erase(it2);
        }
    }
}

void CCEventDispatcher::removeAllScriptEventListenersForEvent(int event)
{
    ScriptEventHandlerMapIterator it = m_map.find(event);
    if (it != m_map.end())
    {
        ScriptHandlerMap &handlers = it->second;
        for (ScriptHandlerMapIterator it2 = handlers.begin(); it2 != handlers.end(); ++it2)
        {
            int callback = it2->second;
            CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(callback);
            LUALOG("[LUA] Remove script event listener: %d", callback);
        }

        m_map.erase(it);
    }
}

void CCEventDispatcher::removeAllScriptEventListeners()
{
    for (ScriptEventHandlerMapIterator it = m_map.begin(); it != m_map.end(); ++it)
    {
        removeAllScriptEventListenersForEvent(it->first);
    }
    m_map.clear();
}

bool CCEventDispatcher::hasScriptEventListener(int event)
{
    return m_map.find(event) != m_map.end();
}

ScriptHandlerMap &CCEventDispatcher::getScriptEventListenerForEvent(int event)
{
    ScriptEventHandlerMapIterator it = m_map.find(event);
    CCAssert(it != m_map.end(), "CCEventDispatcher::getScriptEventListenerForEvent() - invalid event");
    return it->second;
}

ScriptEventHandlerMap &CCEventDispatcher::getAllScriptEventListeners()
{
    return m_map;
}

NS_CC_END
