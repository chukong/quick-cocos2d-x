#ifndef __I_DISPLAY_BRIDGE_H__
#define __I_DISPLAY_BRIDGE_H__
#include "utils/preDB.h"
#include "objects/DBTransform.h"

namespace dragonBones
{
    /**
     * Provides an interface for display classes that can be used in this DragonBones animation system.
     *
     */
    class IDisplayBridge
    {
    public:
        IDisplayBridge(){};
        virtual ~IDisplayBridge(){};
        virtual bool getVisible() = 0;
        virtual void setVisible(bool value) = 0;
        
        /**
         * Indicates the original display object relative to specific display engine.
         */
        virtual Object *getDisplay() = 0;
        virtual void setDisplay(Object *value) = 0;
        
        /**
         * Cleans up resources used by this IDisplayBridge instance.
         */
        virtual void dispose() = 0;
        
        /**
         * Updates the transform of the display object
         * @param    matrix
         * @param    transform
         */
        virtual void updateTransform(Matrix &matrix, DBTransform &transform) = 0;
        
        /**
         * Updates the color of the display object
         * @param    a
         * @param    r
         * @param    g
         * @param    b
         * @param    aM
         * @param    rM
         * @param    gM
         * @param    bM
         */
        virtual void updateColor(
            Number aOffset, 
            Number rOffset, 
            Number gOffset, 
            Number bOffset, 
            Number aMultiplier, 
            Number rMultiplier, 
            Number gMultiplier, 
            Number bMultiplier
        ) = 0;
        
        /**
         * Update the blend mode of the display object
         * @param blendMode The blend mode to use. 
         */
        virtual void updateBlendMode(const String &blendMode) = 0;
        
        /**
         * Adds the original display object to another display object.
         * @param    container
         * @param    index
         */
        virtual void addDisplay(Object *container, int index = -1) = 0;
        
        /**
         * remove the original display object from its parent.
         */
        virtual void removeDisplay() = 0;
    };
};
#endif // __I_DISPLAY_BRIDGE_H__
