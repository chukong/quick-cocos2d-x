#ifndef __COCOS2DX_DISPLAY_BRIDGE_H__
#define __COCOS2DX_DISPLAY_BRIDGE_H__
#include "utils/preDB.h"
#include "display/IDisplayBridge.h"
namespace dragonBones
{
    class CCDBNode;
    class DisplayObject;
    /**
     * The StarlingDisplayBridge class is an implementation of the IDisplayBridge interface for starling.display.DisplayObject.
     *
     */
    class CCDBDisplayBridge : public IDisplayBridge
    {
    public:
        CCDBDisplayBridge();;
        virtual ~CCDBDisplayBridge();

        virtual bool getVisible();
        virtual void setVisible(bool value);
        
        /**
         * Indicates the original display object relative to specific display engine.
         */
        virtual Object *getDisplay();

        // 设置需要显示哪个Frame
        virtual void setDisplay(Object *value);
        
        /**
         * Cleans up resources used by this IDisplayBridge instance.
         */
        virtual void dispose();
        
        /**
         * Updates the transform of the display object
         * @param    matrix
         * @param    transform
         */
        virtual void updateTransform(Matrix &matrix, DBTransform &transform);
        
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
        );
        
        /**
         * Update the blend mode of the display object
         * @param blendMode The blend mode to use. 
         */
        virtual void updateBlendMode(const String &blendMode);
        
        /**
         * Adds the original display object to another display object.
         * @param    container
         * @param    index
         */
        // 设置父显示节点
        virtual void addDisplay(Object *container, int index = -1);
        
        /**
         * remove the original display object from its parent.
         */
        virtual void removeDisplay();

    protected:
        Object *mDisplay;
        CCDBNode *mDisplayNode;
        //DisplayObject *mDisplayObject;
    };
}

#endif // __COCOS2DX_DISPLAY_BRIDGE_H__
