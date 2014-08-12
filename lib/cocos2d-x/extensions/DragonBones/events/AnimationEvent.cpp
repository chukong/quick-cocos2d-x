#include "AnimationEvent.h"
#include "animation/AnimationState.h"

namespace dragonBones
{    
    /**
        * Dispatched when the playback of an animation fade in.
        */
    const String AnimationEvent::MOVEMENT_CHANGE = "fadeIn";
        
    /**
        * Dispatched when the playback of an animation fade in.
        */
    const String AnimationEvent::FADE_IN = "fadeIn";
        
    /**
        * Dispatched when the playback of an animation fade out.
        */
    const String AnimationEvent::FADE_OUT = "fadeOut";
        
    /**
        * Dispatched when the playback of an animation starts.
        */
    const String AnimationEvent::START = "start";
        
    /**
        * Dispatched when the playback of a animation stops.
        */
    const String AnimationEvent::COMPLETE = "complete";
        
    /**
        * Dispatched when the playback of a animation completes a loop.
        */
    const String AnimationEvent::LOOP_COMPLETE = "loopComplete";
        
    /**
        * Dispatched when the playback of an animation fade in complete.
        */
    const String AnimationEvent::FADE_IN_COMPLETE = "fadeInComplete";
        
    /**
        * Dispatched when the playback of an animation fade out complete.
        */
    const String AnimationEvent::FADE_OUT_COMPLETE = "fadeOutComplete";
        

    const String & AnimationEvent::getMovementID()
    {
        return animationState->name;
    }

}