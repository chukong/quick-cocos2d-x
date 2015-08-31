#ifndef __ARMATURE_EVENT_H__
#define __ARMATURE_EVENT_H__
#include "utils/preDB.h"
#include "Event.h"
namespace dragonBones
{
    /**
     * The ArmatureEvent provides and defines all events dispatched directly by an Armature instance.
     *
     * 
     * @see dragonBones.animation.Animation
     */
    class ArmatureEvent : public Event
    {
    public:
        /**
         * Dispatched after a successful z order update.
         */
        static const String Z_ORDER_UPDATED;
        
        ArmatureEvent(const String &type)
            : Event(type)
        {

        }
        
    };
}

#endif // __ARMATURE_EVENT_H__
