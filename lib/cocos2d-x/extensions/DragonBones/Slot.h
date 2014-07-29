#ifndef __SLOT_H__
#define __SLOT_H__
#include "utils/preDB.h"
#include "core/DBObject.h"
namespace dragonBones
{    
    class DisplayData;
    class IDisplayBridge;
    class Slot : public DBObject
    {
    public:
        /** @private */
        std::vector<DisplayData*> _dislayDataList;
        /** @private */
        IDisplayBridge* _displayBridge;
        /** @private */
        Number _originZOrder;
        /** @private */
        Number _tweenZorder;
        /** @private */
        bool _isDisplayOnStage;
        
        bool _isHideDisplay;
        Number _offsetZOrder;
        int _displayIndex;
        String _blendMode;
        
        Number getZOrder();
        
        void setZOrder(Number value);
        
        String getBlendMode();
        
        void setBlendMode(const String &value);
        
        /**
         * The DisplayObject belonging to this Bone instance. Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Object *getDisplay();
        void setDisplayValue(Object *value);
        
        /**
         * The sub-armature of this Slot instance.
         */
        Armature *getChildArmature();
        void setChildArmature(Armature *value);
        
        std::vector<Object*> _displayList;
        /**
         * The DisplayObject list belonging to this Slot instance.
         */
        const std::vector<Object*> &getDisplayList();
        void setDisplayList(const std::vector<Object*> &value);
        
        void setDisplay(Object *display);
        
        /** @private */
        void changeDisplay(int displayIndex);
        
        /**
         * @inheritDoc
         */
        void setVisible(bool value);
        
        /** @private */
        void setArmature(Armature *value);
        
        Slot(IDisplayBridge *displayBrideg);

        virtual ~Slot();
        
        /**
         * @inheritDoc
         */
        void dispose();
        
        /** @private */
        void update();
        
        /** @private */
        void updateVisible(bool value);
        
        void updateChildArmatureAnimation();
        
        /**
         * Change all DisplayObject attached to this Bone instance.
         * @param    displayList An array of valid DisplayObject to attach to this Bone.
         */
        void changeDisplayList(const std::vector<Object*> &displayList);
    };
};
#endif // __SLOT_H__
