#include "Event.h"
#include "CCLuaEngine.h"
namespace dragonBones
{

    // 使用 EventDispatcher 对象注册事件侦听器对象，以使侦听器能够接收事件通知。 
	void EventDispatcher::addEventListener(const String &type, Function listener, const std::string &key)
    {
        Listeners &list = mEventListeners[type];
		list.push_back(Callback(listener, key));
    }

    // 将事件调度到事件流中。
    void EventDispatcher::dispatchEvent(Event *event)
    {
        EventListeners::iterator iter = mEventListeners.find(event->getType());
        if(iter != mEventListeners.end())
        {
            for(Listeners::iterator iterCallback = iter->second.begin() ; iterCallback != iter->second.end() ; iterCallback ++)
            {
                iterCallback->first(event);
            }
        }

        //cocos2d::CCLog("dragonBones::EventDispatcher.dispatchEvent %s", event->getType());
        // For script engine
        std::map<String, int>::iterator iter1 = scriptHandlers.find(event->getType());

        if (scriptHandlers.end() != iter1)
        {
            cocos2d::CCLuaEngine* luaEngine = dynamic_cast<cocos2d::CCLuaEngine*>(cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine());
            if (luaEngine)
            {
  /*              CCArray* __param = CCArray::create();
                __param->addObject(CCInteger::create(evtType));
                __param->addObject(CCString::create(movId));
                __luaEngine->executeEventWithArgs(m_nScriptMovementHandler, __param);*/

                cocos2d::CCLuaStack *pStack = luaEngine->getLuaStack();
                int nHandler = iter1->second;
                if (!nHandler) return;
                pStack->pushCCObject(event, "CCObject");
                pStack->executeFunctionByHandler(nHandler, 1);
                pStack->clean();
            }
            
            //cocos2d::CCLuaEngine *pEngine = cocos2d::CCLuaEngine::defaultEngine();
            //cocos2d::CCLuaStack *pStack = pEngine->getLuaStack();
            //int nHandler = iter1->second;
            //if (!nHandler) return;
            //pStack->pushCCObject(event, "CCObject");
            //pStack->executeFunctionByHandler(nHandler, 1);
            //pStack->clean();
        }
        delete event;
    }

    // 检查 EventDispatcher 对象是否为特定事件类型注册了任何侦听器。  
    bool EventDispatcher::hasEventListener(const String &type)const
    {
        return mEventListeners.find(type) != mEventListeners.end() || scriptHandlers.find(type) != scriptHandlers.end();;
    }

    // 从 EventDispatcher 对象中删除侦听器。 
    void EventDispatcher::removeEventListener(const String &type, const std::string &key)
    {
        EventListeners::iterator iter = mEventListeners.find(type);
        if(iter != mEventListeners.end())
        {
            for(Listeners::iterator iterCallback = iter->second.begin() ; iterCallback != iter->second.end() ; )
            {
				if (iterCallback->second == key)
                {
                    iterCallback = iter->second.erase(iterCallback);
                }
                else
                {
                    iterCallback ++;
                }
            }
        }
    }

    // For script engine
    void EventDispatcher::registerScriptHandler(int funId, String type)
    {
        //cocos2d::CCLog("dragonBones::EventDispatcher::registerScriptHandler %d %s", funId, type);
        this->unregisterScriptHandler(type);
        scriptHandlers[type] = funId;
    }
    void EventDispatcher::unregisterScriptHandler(String type)
    {
        std::map<String, int>::iterator iter = scriptHandlers.find(type);

        if (scriptHandlers.end() != iter)
        {
            scriptHandlers.erase(iter);
        }
    }
    int  EventDispatcher::getScriptHandler(String type)
    {
        std::map<String, int>::iterator iter = scriptHandlers.find(type);

        if (scriptHandlers.end() != iter)
            return iter->second;

        return 0;
    }
}