#ifndef __ANIMATION_EVENT_H__
#define __ANIMATION_EVENT_H__
#include "utils/preDB.h"
#include "Event.h"
namespace dragonBones
{    
    class AnimationState;
    class Armature;
    /**
     * The AnimationEvent provides and defines all events dispatched during an animation.
     *
     * @see dragonBones.Armature
     * @see dragonBones.animation.Animation
     */
    class AnimationEvent : public Event
    {
    public:
        /**
         * Dispatched when the playback of an animation fade in.
         */
        static const String MOVEMENT_CHANGE;
        
        /**
         * Dispatched when the playback of an animation fade in.
         */
        static const String FADE_IN;
        
        /**
         * Dispatched when the playback of an animation fade out.
         */
        static const String FADE_OUT;
        
        /**
         * Dispatched when the playback of an animation starts.
         */
        static const String START;
        
        /**
         * Dispatched when the playback of a animation stops.
         */
        static const String COMPLETE;
        
        /**
         * Dispatched when the playback of a animation completes a loop.
         */
        static const String LOOP_COMPLETE;
        
        /**
         * Dispatched when the playback of an animation fade in complete.
         */
        static const String FADE_IN_COMPLETE;
        
        /**
         * Dispatched when the playback of an animation fade out complete.
         */
        static const String FADE_OUT_COMPLETE;
        
        /**
         * The animationState instance.
         */
        AnimationState *animationState;
        
        Armature *armature;

        const String &getMovementID();
        
        /**
         * Creates a new AnimationEvent instance.
         * @param    type
         * @param    cancelable
         */
        AnimationEvent(const String &type)
            : Event(type)
            , armature(0)
            , animationState(0)
        {
            
        }
        
    };
};
#endif // __ANIMATION_EVENT_H__
