/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCScriptEventDispatcher.h"
#include "CCScheduler.h"
#include "cocos-ext.h"

NS_CC_BEGIN

CCLuaEngine* CCLuaEngine::m_defaultEngine = NULL;

CCLuaEngine* CCLuaEngine::defaultEngine(void)
{
    if (!m_defaultEngine)
    {
        m_defaultEngine = new CCLuaEngine();
        m_defaultEngine->init();
    }
    return m_defaultEngine;
}

CCLuaEngine::~CCLuaEngine(void)
{
    CC_SAFE_RELEASE(m_stack);
    m_defaultEngine = NULL;
}

bool CCLuaEngine::init(void)
{
    m_stack = CCLuaStack::create();
    m_stack->retain();
    return true;
}

void CCLuaEngine::addSearchPath(const char* path)
{
    m_stack->addSearchPath(path);
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
    m_stack->addLuaLoader(func);
}

void CCLuaEngine::removeScriptObjectByCCObject(CCObject* pObj)
{
    m_stack->removeScriptObjectByCCObject(pObj);
}

void CCLuaEngine::removeScriptHandler(int nHandler)
{
    m_stack->removeScriptHandler(nHandler);
}

int CCLuaEngine::executeString(const char *codes)
{
    int ret = m_stack->executeString(codes);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
    int ret = m_stack->executeScriptFile(filename);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeGlobalFunction(const char* functionName, int numArgs /* = 0 */)
{
    int ret = m_stack->executeGlobalFunction(functionName, numArgs);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeNodeEvent(CCNode* pNode, int nAction)
{
    CCLuaValueDict event;
    switch (nAction)
    {
        case kCCNodeOnEnter:
            event["name"] = CCLuaValue::stringValue("enter");
            break;

        case kCCNodeOnExit:
            event["name"] = CCLuaValue::stringValue("exit");
            break;

        case kCCNodeOnEnterTransitionDidFinish:
            event["name"] = CCLuaValue::stringValue("enterTransitionFinish");
            break;

        case kCCNodeOnExitTransitionDidStart:
            event["name"] = CCLuaValue::stringValue("exitTransitionStart");
            break;

        case kCCNodeOnCleanup:
            event["name"] = CCLuaValue::stringValue("cleanup");
            break;

        default:
            return 0;
    }

    m_stack->clean();
    m_stack->pushCCLuaValueDict(event);

    CCArray *listeners = pNode->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != NODE_EVENT || p->removed) continue;
        m_stack->copyValue(1);
        m_stack->executeFunctionByHandler(p->listener, 1);
        m_stack->settop(1);
    }

    m_stack->clean();
    return 0;
}

int CCLuaEngine::executeNodeEnterFrameEvent(CCNode* pNode, float dt)
{
    CCArray *listeners = pNode->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != NODE_ENTER_FRAME_EVENT || p->removed) continue;
        m_stack->pushFloat(dt);
        m_stack->executeFunctionByHandler(p->listener, 1);
        m_stack->clean();
    }
    return 0;
}

int CCLuaEngine::executeMenuItemEvent(CCMenuItem* pMenuItem)
{
    CCArray *listeners = pMenuItem->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != MENU_ITEM_CLICKED_EVENT || p->removed) continue;
        m_stack->pushInt(pMenuItem->getTag());
        m_stack->pushCCObject(pMenuItem, "CCMenuItem");
        m_stack->executeFunctionByHandler(p->listener, 2);
        m_stack->clean();
    }
    return 0;
}

int CCLuaEngine::executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName, CCObject *obj /* = NULL */)
{
    int nHandler = pNotificationCenter->getObserverHandlerByName(pszName);
    if (!nHandler) return 0;

    m_stack->pushString(pszName);

    if (obj)
        m_stack->pushCCObject(obj, "CCObject");
    else
        m_stack->pushNil();

    int ret = m_stack->executeFunctionByHandler(nHandler, 2);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget/* = NULL*/)
{
    int nHandler = pAction->getScriptHandler();
    if (!nHandler) return 0;

    if (pTarget)
    {
        m_stack->pushCCObject(pTarget, "CCNode");
    }
    int ret = m_stack->executeFunctionByHandler(nHandler, pTarget ? 1 : 0);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeSchedule(int nHandler, float dt, CCNode* pNode/* = NULL*/)
{
    if (!nHandler) return 0;
    m_stack->pushFloat(dt);
    int ret = m_stack->executeFunctionByHandler(nHandler, 1);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeNodeTouchEvent(CCNode* pNode, int eventType, CCTouch *pTouch, int phase)
{
    m_stack->clean();
    CCLuaValueDict event;
    switch (eventType)
    {
        case CCTOUCHBEGAN:
            event["name"] = CCLuaValue::stringValue("began");
            break;

        case CCTOUCHMOVED:
            event["name"] = CCLuaValue::stringValue("moved");
            break;

        case CCTOUCHENDED:
            event["name"] = CCLuaValue::stringValue("ended");
            break;

        case CCTOUCHCANCELLED:
            event["name"] = CCLuaValue::stringValue("cancelled");
            break;

        default:
            CCAssert(false, "INVALID touch event");
            return 0;
    }

    event["mode"] = CCLuaValue::intValue(kCCTouchesOneByOne);
    switch (phase)
    {
        case NODE_TOUCH_CAPTURING_PHASE:
            event["phase"] = CCLuaValue::stringValue("capturing");
            break;

        case NODE_TOUCH_TARGETING_PHASE:
            event["phase"] = CCLuaValue::stringValue("targeting");
            break;

        default:
            event["phase"] = CCLuaValue::stringValue("unknown");
    }

    const CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    event["x"] = CCLuaValue::floatValue(pt.x);
    event["y"] = CCLuaValue::floatValue(pt.y);
    const CCPoint prev = CCDirector::sharedDirector()->convertToGL(pTouch->getPreviousLocationInView());
    event["prevX"] = CCLuaValue::floatValue(prev.x);
    event["prevY"] = CCLuaValue::floatValue(prev.y);

    m_stack->pushCCLuaValueDict(event);

    int eventInt = (phase == NODE_TOUCH_CAPTURING_PHASE) ? NODE_TOUCH_CAPTURE_EVENT : NODE_TOUCH_EVENT;
    CCArray *listeners = pNode->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    int ret = 1;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != eventInt || p->removed) continue;

        if (eventType == CCTOUCHBEGAN)
        {
            // enable listener when touch began
            p->enabled = true;
        }

        if (p->enabled)
        {
            m_stack->copyValue(1);
            int listenerRet = m_stack->executeFunctionByHandler(p->listener, 1);
            if (listenerRet == 0)
            {
                if (phase == NODE_TOUCH_CAPTURING_PHASE && (eventType == CCTOUCHBEGAN || eventType == CCTOUCHMOVED))
                {
                    ret = 0;
                }
                else if (phase == NODE_TOUCH_TARGETING_PHASE && eventType == CCTOUCHBEGAN)
                {
                    // if listener return false when touch began, disable this listener
                    p->enabled = false;
                    ret = 0;
                }
            }
            m_stack->settop(1);
        }
    }

    //CCLOG("executeNodeTouchEvent %p, ret = %d, event = %d, phase = %d", pNode, ret, eventType, phase);
    m_stack->clean();

    return ret;
}

int CCLuaEngine::executeNodeTouchesEvent(CCNode* pNode, int eventType, CCSet *pTouches, int phase)
{
    m_stack->clean();
    CCLuaValueDict event;
    switch (eventType)
    {
        case CCTOUCHBEGAN:
            event["name"] = CCLuaValue::stringValue("began");
            break;

        case CCTOUCHMOVED:
            event["name"] = CCLuaValue::stringValue("moved");
            break;

        case CCTOUCHENDED:
            event["name"] = CCLuaValue::stringValue("ended");
            break;

        case CCTOUCHCANCELLED:
            event["name"] = CCLuaValue::stringValue("cancelled");
            break;

        case CCTOUCHADDED:
            event["name"] = CCLuaValue::stringValue("added");
            break;

        case CCTOUCHREMOVED:
            event["name"] = CCLuaValue::stringValue("removed");
            break;

        default:
            return 0;
    }

    event["mode"] = CCLuaValue::intValue(kCCTouchesAllAtOnce);
    switch (phase)
    {
        case NODE_TOUCH_CAPTURING_PHASE:
            event["phase"] = CCLuaValue::stringValue("capturing");
            break;

        case NODE_TOUCH_TARGETING_PHASE:
            event["phase"] = CCLuaValue::stringValue("targeting");
            break;

        default:
            event["phase"] = CCLuaValue::stringValue("unknown");
    }

    CCLuaValueDict points;
    CCDirector* pDirector = CCDirector::sharedDirector();
    char touchId[16];
    for (CCSetIterator touchIt = pTouches->begin(); touchIt != pTouches->end(); ++touchIt)
    {
        CCLuaValueDict point;
        CCTouch* pTouch = (CCTouch*)*touchIt;
        sprintf(touchId, "%d", pTouch->getID());
        point["id"] = CCLuaValue::stringValue(touchId);

        const CCPoint pt = pDirector->convertToGL(pTouch->getLocationInView());
        point["x"] = CCLuaValue::floatValue(pt.x);
        point["y"] = CCLuaValue::floatValue(pt.y);
        const CCPoint prev = pDirector->convertToGL(pTouch->getPreviousLocationInView());
        point["prevX"] = CCLuaValue::floatValue(prev.x);
        point["prevY"] = CCLuaValue::floatValue(prev.y);

        points[touchId] = CCLuaValue::dictValue(point);
    }
    event["points"] = CCLuaValue::dictValue(points);
    m_stack->pushCCLuaValueDict(event);

    int eventInt = (phase == NODE_TOUCH_CAPTURING_PHASE) ? NODE_TOUCH_CAPTURE_EVENT : NODE_TOUCH_EVENT;
    CCArray *listeners = pNode->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != eventInt || p->removed) continue;
        m_stack->copyValue(1);
        m_stack->executeFunctionByHandler(p->listener, 1);
        m_stack->settop(1);
    }

    m_stack->clean();
    
    return 1;
}

int CCLuaEngine::executeLayerKeypadEvent(CCLayer* pLayer, int eventType)
{
    m_stack->clean();
    CCLuaValueDict event;
    event["name"] = CCLuaValue::stringValue("clicked");
    switch (eventType)
    {
        case kTypeBackClicked:
            event["key"] = CCLuaValue::stringValue("back");
            break;

        case kTypeMenuClicked:
            event["key"] = CCLuaValue::stringValue("menu");
            break;

        default:
            return 0;
    }

    m_stack->pushCCLuaValueDict(event);

    CCArray *listeners = pLayer->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != KEYPAD_EVENT || p->removed) continue;
        m_stack->copyValue(1);
        m_stack->executeFunctionByHandler(p->listener, 1);
        m_stack->settop(1);
    }
    m_stack->clean();
    return 0;
}

int CCLuaEngine::executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue)
{
    m_stack->clean();
    CCLuaValueDict event;
    event["name"] = CCLuaValue::stringValue("changed");
    event["x"] = CCLuaValue::floatValue(pAccelerationValue->x);
    event["y"] = CCLuaValue::floatValue(pAccelerationValue->y);
    event["z"] = CCLuaValue::floatValue(pAccelerationValue->z);
    event["timestamp"] = CCLuaValue::floatValue(pAccelerationValue->timestamp);

    m_stack->pushCCLuaValueDict(event);

    CCArray *listeners = pLayer->getAllScriptEventListeners();
    CCScriptHandlePair *p;
    for (int i = listeners->count() - 1; i >= 0; --i)
    {
        p = dynamic_cast<CCScriptHandlePair*>(listeners->objectAtIndex(i));
        if (p->event != ACCELERATE_EVENT || p->removed) continue;
        m_stack->copyValue(1);
        m_stack->executeFunctionByHandler(p->listener, 1);
        m_stack->settop(1);
    }
    return 0;
}

int CCLuaEngine::executeEvent(int nHandler, const char* pEventName, CCObject* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
    m_stack->pushString(pEventName);
    if (pEventSource)
    {
        m_stack->pushCCObject(pEventSource, pEventSourceClassName ? pEventSourceClassName : "CCObject");
    }
    int ret = m_stack->executeFunctionByHandler(nHandler, pEventSource ? 2 : 1);
    m_stack->clean();
    return ret;
}

bool CCLuaEngine::handleAssert(const char *msg)
{
    bool ret = m_stack->handleAssert(msg);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::reallocateScriptHandler(int nHandler)
{
    int nRet = m_stack->reallocateScriptHandler(nHandler);
    m_stack->clean();
    return nRet;
}

int CCLuaEngine::executeTableViewEvent(int nEventType,cocos2d::extension::CCTableView* pTableView,void* pValue, CCArray* pResultArray)
{
    if (NULL == pTableView)
        return 0;

    int nHanlder = pTableView->getScriptHandler(nEventType);
    if (0 == nHanlder)
        return 0;

    int nRet = 0;
    switch (nEventType)
    {
        case cocos2d::extension::CCTableView::kTableViewScroll:
        case cocos2d::extension::CCTableView::kTableViewZoom:
        {
            m_stack->pushCCObject(pTableView, "CCTableView");
            nRet = m_stack->executeFunctionByHandler(nHanlder, 1);
        }
            break;
        case cocos2d::extension::CCTableView::kTableCellTouched:
        case cocos2d::extension::CCTableView::kTableCellHighLight:
        case cocos2d::extension::CCTableView::kTableCellUnhighLight:
        case cocos2d::extension::CCTableView::kTableCellWillRecycle:
        {
            m_stack->pushCCObject(pTableView, "CCTableView");
            m_stack->pushCCObject(static_cast<cocos2d::extension::CCTableViewCell*>(pValue), "CCTableViewCell");
            nRet = m_stack->executeFunctionByHandler(nHanlder, 2);
        }
            break;
        case cocos2d::extension::CCTableView::kTableCellSizeForIndex:
        {
            m_stack->pushCCObject(pTableView, "CCTableView");
            m_stack->pushInt(*((int*)pValue));
            nRet = m_stack->executeFunctionReturnArray(nHanlder, 2, 2, pResultArray);
        }
            break;
        case cocos2d::extension::CCTableView::kTableCellSizeAtIndex:
        {
            m_stack->pushCCObject(pTableView, "CCTableView");
            m_stack->pushInt(*((int*)pValue));
            nRet = m_stack->executeFunctionReturnArray(nHanlder, 2, 1, pResultArray);
        }
            break;
        case cocos2d::extension::CCTableView::kNumberOfCellsInTableView:
        {
            m_stack->pushCCObject(pTableView, "CCTableView");
            nRet = m_stack->executeFunctionReturnArray(nHanlder, 1, 1, pResultArray);
        }
            break;
        default:
            break;
    }
    return nRet;
}

int CCLuaEngine::executeEventWithArgs(int nHandler, CCArray* pArgs)
{
    if (NULL == pArgs)
        return 0;

    CCObject*   pObject = NULL;

    CCInteger*  pIntVal = NULL;
    CCString*   pStrVal = NULL;
    CCDouble*   pDoubleVal = NULL;
    CCFloat*    pFloatVal = NULL;
    CCBool*     pBoolVal = NULL;


    int nArgNums = 0;
    for (unsigned int i = 0; i < pArgs->count(); i++)
    {
        pObject = pArgs->objectAtIndex(i);
        if (NULL != (pIntVal = dynamic_cast<CCInteger*>(pObject)))
        {
            m_stack->pushInt(pIntVal->getValue());
            nArgNums++;
        }
        else if (NULL != (pStrVal = dynamic_cast<CCString*>(pObject)))
        {
            m_stack->pushString(pStrVal->getCString());
            nArgNums++;
        }
        else if (NULL != (pDoubleVal = dynamic_cast<CCDouble*>(pObject)))
        {
            m_stack->pushFloat(pDoubleVal->getValue());
            nArgNums++;
        }
        else if (NULL != (pFloatVal = dynamic_cast<CCFloat*>(pObject)))
        {
            m_stack->pushFloat(pFloatVal->getValue());
            nArgNums++;
        }
        else if (NULL != (pBoolVal = dynamic_cast<CCBool*>(pObject)))
        {
            m_stack->pushBoolean(pBoolVal->getValue());
            nArgNums++;
        }
        else if(NULL != pObject)
        {
            m_stack->pushCCObject(pObject, "CCObject");
            nArgNums++;
        }
    }

    return  m_stack->executeFunctionByHandler(nHandler, nArgNums);
}

bool CCLuaEngine::parseConfig(CCScriptEngineProtocol::ConfigType type, const std::string& str)
{
    lua_getglobal(m_stack->getLuaState(), "__onParseConfig");
    if (!lua_isfunction(m_stack->getLuaState(), -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", "__onParseConfig");
        lua_pop(m_stack->getLuaState(), 1);
        return false;
    }
    
    m_stack->pushInt((int)type);
    m_stack->pushString(str.c_str());
    
    return m_stack->executeFunction(2);
}

NS_CC_END
