#ifndef __SOUND_EVENT_MANAGER_H__
#define __SOUND_EVENT_MANAGER_H__
#include "utils/preDB.h"
#include "Event.h"
#include <stdexcept>
namespace dragonBones
{
    //[Event(name="sound",type="dragonBones.events.SoundEvent")]
    
    /**
     * @private
     */
    class SoundEventManager : public EventDispatcher
    {
    private :
        static SoundEventManager *_instance;
        
    public :
        static SoundEventManager* getInstance()
        {
            if (!_instance)
            {
                _instance = new SoundEventManager();
            }
            return _instance;
        }
        
        SoundEventManager()
        {
            if (_instance)
            {
                throw std::invalid_argument("Singleton already constructed!");
            }
        }
    };
}
#endif // __SOUND_EVENT_MANAGER_H__
