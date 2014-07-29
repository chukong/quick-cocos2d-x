#ifndef __I_ANIMATABLE_H__
#define __I_ANIMATABLE_H__
#include "utils/preDB.h"
namespace dragonBones
{
    /**
    * Copyright 2012-2013. DragonBones. All Rights Reserved.
    * @playerversion Flash 10.0
    * @langversion 3.0
    * @version 2.0
    */
    
    /**
     * The IAnimatable interface defines the methods used by all animatable instance type used by the DragonBones system.
     * @see dragonBones.Armature
     * @see dragonBones.animation.WorldClock
     */
    class IAnimatable : public Object
    {
    public:
        /**
         * Update the animation using this method typically in an ENTERFRAME Event or with a Timer.
         * @param    The amount of second to move the playhead ahead.
         */
        virtual void advanceTime(Number passedTime) = 0;
    };
};
#endif // __I_ANIMATABLE_H__
