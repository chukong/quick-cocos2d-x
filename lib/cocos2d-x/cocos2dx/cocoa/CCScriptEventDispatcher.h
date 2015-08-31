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

#ifndef __CCSCRIPT_EVENT_DISPATCHER_H__
#define __CCSCRIPT_EVENT_DISPATCHER_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

#define NODE_EVENT                  0
#define NODE_ENTER_FRAME_EVENT      1
#define NODE_TOUCH_EVENT            2
#define NODE_TOUCH_CAPTURE_EVENT    3
#define MENU_ITEM_CLICKED_EVENT     4
#define ACCELERATE_EVENT            5
#define KEYPAD_EVENT                6

#define NODE_TOUCH_CAPTURING_PHASE  0
#define NODE_TOUCH_TARGETING_PHASE  1

class CC_DLL CCScriptHandlePair : public CCObject
{
public:
    unsigned int handle;
    int event;
    int listener;
    int tag;
    bool enabled;
    bool removed;

    static CCScriptHandlePair *create(unsigned int handle, int event, int listener, int tag)
    {
        CCScriptHandlePair *pair = new CCScriptHandlePair(handle, event, listener, tag);
        pair->autorelease();
        return pair;
    }

    CCScriptHandlePair(unsigned int handle_, int event_, int listener_, int tag_)
    : handle(handle_)
    , event(event_)
    , listener(listener_)
    , tag(tag_)
    , enabled(true)
    , removed(false)
    {
    }
};

class CC_DLL CCScriptEventDispatcher : public CCObject
{
public:
    CCScriptEventDispatcher();
    virtual ~CCScriptEventDispatcher();
    int addScriptEventListener(int event, int listener, int tag = 0);
    void removeScriptEventListener(unsigned int handle);
    void removeScriptEventListenersByEvent(int event);
    void removeScriptEventListenersByTag(int tag);
    void removeAllScriptEventListeners();

    CCArray *getAllScriptEventListeners()
    {
        return m_scriptEventListeners;
    }

protected:
    CCArray *m_scriptEventListeners;

private:
    static unsigned int s_nextScriptEventHandleIndex;
};

NS_CC_END

#endif // __CCSCRIPT_EVENT_DISPATCHER_H__
