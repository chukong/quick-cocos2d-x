#ifndef __BONE_H__
#define __BONE_H__
#include "utils/preDB.h"
#include "core/DBObject.h"
namespace dragonBones
{
    class Frame;
    class TimelineState;
    class AnimationState;
    class Slot;
    class Bone : public DBObject
    {
    public:
        //private static const _soundManager:SoundEventManager = SoundEventManager.getInstance();
        //0/1/2
        int scaleMode;
        
        /** @private */
        Point _tweenPivot;
        
        std::vector<DBObject*> _children;
        
        Slot* _slot;
        
        /**
         * The sub-armature of default Slot of this Bone instance.
         */
        Armature* getChildArmature();
        
        /**
         * The DisplayObject of default Slot of this Bone instance.
         */
        Object* getDisplay();
        void setDisplay(Object *value);
        
        String displayController;
        
        /**
         * @inheritDoc
         */
        virtual void setVisible(bool value);
        
        /** @private */
        void setArmature(Armature *value);
        
        Bone();

        virtual ~Bone();
        
        /**
         * @inheritDoc
         */
        void dispose();
        
        bool contains(DBObject *child);
        
        void addChild(DBObject *child);
        
        void removeChild(DBObject *child);
        
        /**
         * Get all Slot instance associated with this bone.
         * @return A Vector.&lt;Slot&gt; instance.
         * @see dragonBones.Slot
         */
        std::list<Slot*> getSlots();
        
        /** @private */
        void arriveAtFrame(Frame *frame, TimelineState *timelineState, AnimationState *animationState, bool isCross);
        
        /** @private */
        void updateColor(
            Number aOffset, 
            Number rOffset, 
            Number gOffset, 
            Number bOffset, 
            Number aMultiplier, 
            Number rMultiplier, 
            Number gMultiplier, 
            Number bMultiplier,
            bool isColorChanged
        );
    };
};
#endif // __BONE_H__
