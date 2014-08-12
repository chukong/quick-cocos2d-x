#ifndef __EVENT_H__
#define __EVENT_H__

#include "utils/preDB.h"
#include "cocos2d.h"
#include <functional>

namespace dragonBones
{
    class Event : public cocos2d::CCObject
    {
        String _type;
    public:
        Event(const String &type)
        : _type(type)
        {};
        virtual ~Event(){};

        const String &getType()const
        {
            return _type;
        }
    };

    class EventDispatcher
    {
    public:
		typedef std::function<void(Event*)> Function;
        // 使用 EventDispatcher 对象注册事件侦听器对象，以使侦听器能够接收事件通知，key是这个回调的唯一标示，用来removeEventListener反注册用的
        void addEventListener(const String &type, Function listener , const String &key);

        // 将事件调度到事件流中。
        void dispatchEvent(Event *event);

        // 检查 EventDispatcher 对象是否为特定事件类型注册了侦听器。
        bool hasEventListener(const String &type)const;
        // 检查 EventDispatcher 对象是否为特定的事件注册了特定key的侦听器。
        bool hasEventListener(const String &type, const String &key)const;

        // 删除当前类型的所有侦听器
        void removeEventListener(const String &type);
        // 删除指定类型指定key的侦听器
        void removeEventListener(const String &type, const String &key);
        
        void removeAllEventListener();

    protected:
        typedef std::pair<Function , String> Callback;
        typedef std::list<Callback> Listeners;
        typedef std::map<String , Listeners> EventListeners;
        // 保存所有侦听器列表
        EventListeners mEventListeners;
    };
}
#endif // __EVENT_H__
