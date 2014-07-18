#include "Event.h"
namespace dragonBones
{
	void EventDispatcher::addEventListener(const String &type, Function listener, const String &key)
    {
        Listeners &list = mEventListeners[type];
		list.push_back(Callback(listener, key));
    }

    void EventDispatcher::dispatchEvent(Event *event)
    {
        EventListeners::iterator iter = mEventListeners.find(event->getType());
        if(iter != mEventListeners.end())
        {
            for(auto iterCallback : iter->second)
            {
                iterCallback.first(event);
            }
        }
        delete event;
    }
  
    bool EventDispatcher::hasEventListener(const String &type)const
    {
        return mEventListeners.find(type) != mEventListeners.end();
    }
    
    bool EventDispatcher::hasEventListener(const String &type, const String &key)const
    {
        auto iter = mEventListeners.find(type);
        if(iter == mEventListeners.end()) return false;
        for(auto &iterCallback : iter->second)
        {
            if(iterCallback.second == key)
            {
                return true;
            }
        }
        return false;
    }
    
    void EventDispatcher::removeEventListener(const String &type)
    {
        auto iter = mEventListeners.find(type);
        if(iter != mEventListeners.end())
        {
            mEventListeners.erase(iter);
        }
    }

    void EventDispatcher::removeEventListener(const String &type, const String &key)
    {
        auto iter = mEventListeners.find(type);
        if(iter != mEventListeners.end())
        {
            auto funList = iter->second;
            for(auto iterCallback = funList.begin() ; iterCallback != funList.end() ; )
            {
				if (iterCallback->second == key)
                {
                    iterCallback = funList.erase(iterCallback);
                }
                else
                {
                    iterCallback ++;
                }
            }
        }
    }
    
    void EventDispatcher::removeAllEventListener()
    {
        mEventListeners.clear();
    }
}