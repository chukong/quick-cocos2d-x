#ifndef __SOUND_EVENT_H__
#define __SOUND_EVENT_H__
#include "utils/preDB.h"
#include "Event.h"
namespace dragonBones
{
    class Armature;
    class AnimationState;
    /**
     * The SoundEvent provides and defines all sound related events dispatched during an animation.
     *
     * @see dragonBones.Armature
     * @see dragonBones.animation.Animation
     */
    class SoundEvent : public Event
    {
    public:
        /**
         * Dispatched when the animation of the animation enter a frame containing sound labels.
         */
        static const String SOUND;
        
        /**
         * The armature that is the target of this event.
         */
        Armature* armature;
        
        AnimationState* animationState;
        
        String sound;
        
        /**
         * Creates a new SoundEvent instance.
         * @param    type
         * @param    cancelable
         */
        SoundEvent(const String &type)
            : Event(type)
            , armature(0)
            , animationState(0)
        {

        }
        
    };
};
#endif // __SOUND_EVENT_H__
