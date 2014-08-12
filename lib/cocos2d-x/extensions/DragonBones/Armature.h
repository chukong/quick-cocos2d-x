#ifndef __ARMATURE_H__
#define __ARMATURE_H__
#include "utils/preDB.h"
#include "animation/IAnimatable.h"
#include "animation/Animation.h"
#include "events/Event.h"
#include "Slot.h"
#include "Bone.h"

namespace dragonBones
{
    class Animation;
    // TODO : dragon bone event
    ///**
    // * Dispatched when a bone of the armature enters a frame.
    // */
    //[Event(name="zOrderUpdated", type="dragonBones.events.ArmatureEvent")]
    ///**
    // * Dispatched when an animation state of the animation begins fade in.
    // */
    //[Event(name="fadeIn", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation begins fade out.
    // */
    //[Event(name="fadeOut", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation starts.
    // */
    //[Event(name="start", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation completes.
    // */
    //[Event(name="complete", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation completes a loop.
    // */
    //[Event(name="loopComplete", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation completes fade in.
    // */
    //[Event(name="fadeInComplete", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation completes fade out.
    // */
    //[Event(name="fadeOutComplete", type="dragonBones.events.AnimationEvent")]
    //
    ///**
    // * Dispatched when an animation state of the animation enters a frame.
    // */
    //[Event(name="animationFrameEvent", type="dragonBones.events.FrameEvent")]
    //
    ///**
    // * Dispatched when a bone of the armature enters a frame.
    // */
    //[Event(name="boneFrameEvent", type="dragonBones.events.FrameEvent")]

    class Armature : public IAnimatable , public EventDispatcher
    {
    public:
        //private static const _soundManager:SoundEventManager = SoundEventManager.getInstance();
        
        //private const _helpArray:Array = [];
        
        /**
         * The name of this DBObject instance's Armature instance.
         */
        String name;
        
        /**
         * An object that can contain any user extra data.
         */
        Object* userData;
        
        /** @private */
        bool _slotsZOrderChanged;
        /** @private */
        std::vector<Slot*> _slotList;
        /** @private */
        std::vector<Bone*> _boneList;
        /** @private */
        std::vector<Event*> _eventList;
        
        /** @private */
        bool _needUpdate;
        
        /** @private */
        Object* _display;
        /**
         * Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Object* getDisplay();
        
        /** @private */
        Animation* _animation;
        /**
         * An Animation instance
         * @see dragonBones.animation.Animation
         */
        Animation* getAnimation();
        /**
         * Creates a Armature blank instance.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Armature(Object *display);

        virtual ~Armature()
        {
            dispose();
        }
        /**
         * Cleans up any resources used by this DBObject instance.
         */
        void dispose();
        
        void invalidUpdate();
        
        /**
         * Update the animation using this method typically in an ENTERFRAME Event or with a Timer.
         * @param    The amount of second to move the playhead ahead.
         */
        void advanceTime(Number passedTime);
        
        /**
         * Get all Slot instance associated with this armature.
         * @return A Vector.&lt;Slot&gt; instance.
         * @see dragonBones.Slot
         */
        std::vector<Slot*> getSlotsCopy();
        std::vector<Slot*>& getSlots();
        /**
         * Get all Bone instance associated with this armature.
         * @return A Vector.&lt;Bone&gt; instance.
         * @see dragonBones.Bone
         */
        std::vector<Bone*> getBonesCopy();
        std::vector<Bone*>& getBones();
        
        /**
         * Retrieves a Slot by name
         * @param    The name of the Bone to retrieve.
         * @return A Slot instance or null if no Slot with that name exist.
         * @see dragonBones.Slot
         */
        Slot* getSlot(const String &slotName);
        
        /**
         * Gets the Slot associated with this DisplayObject.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         * @return A Slot instance.
         * @see dragonBones.Slot
         */
        Slot* getSlotByDisplay(Object *display);
        /**
         * Remove a Slot instance from this Armature instance.
         * @param    The Slot instance to remove.
         * @see dragonBones.Slot
         */
        void removeSlot(Slot *slot);
        
        /**
         * Remove a Slot instance from this Armature instance.
         * @param    The name of the Slot instance to remove.
         * @see dragonBones.Slot
         */
        void removeSlotByName(const String &slotName);
        
        /**
         * Retrieves a Bone by name
         * @param    The name of the Bone to retrieve.
         * @return A Bone instance or null if no Bone with that name exist.
         * @see dragonBones.Bone
         */
        Bone* getBone(const String &boneName);
        /**
         * Gets the Bone associated with this DisplayObject.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         * @return A Bone instance.
         * @see dragonBones.Bone
         */
        Bone* getBoneByDisplay(Object *display);
        
        /**
         * Remove a Bone instance from this Armature instance.
         * @param    The Bone instance to remove.
         * @see    dragonBones.Bone
         */
        void removeBone(Bone * bone);
        
        /**
         * Remove a Bone instance from this Armature instance.
         * @param    The name of the Bone instance to remove.
         * @see dragonBones.Bone
         */
        void removeBoneByName(const String &boneName);
        
        /**
         * Add a DBObject instance to this Armature instance.
         * @param    A DBObject instance
         * @param    (optional) The parent's name of this DBObject instance.
         * @see dragonBones.core.DBObject
         */
        void addChild(DBObject *object, const String &parentName = "");
        
        /**
         * Add a Bone instance to this Armature instance.
         * @param    A Bone instance
         * @param    (optional) The parent's name of this Bone instance.
         * @see dragonBones.Bone
         */
        void addBone(Bone * bone, const String &parentName = "");
        
        /**
         * Update the z-order of the display. 
         */
        void updateSlotsZOrder();
        
        /** @private */
        void addDBObject(DBObject *object);
        
        /** @private */
        void removeDBObject(DBObject * object);
        static bool sortBone(const std::pair<int , Bone*>& a , const std::pair<int , Bone*>& b);

        /** @private */
        void sortBoneList();
        
        /** @private */
        void arriveAtFrame(Frame * frame, TimelineState *timelineState, AnimationState *animationState, bool isCross);
        
        static bool sortSlot(Slot *slot1, Slot *slot2);
        
    };
};
#endif // __ARMATURE_H__
