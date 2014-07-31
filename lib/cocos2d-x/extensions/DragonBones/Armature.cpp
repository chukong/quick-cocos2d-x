#include "Armature.h"
#include "animation/Animation.h"
#include "display/IDisplayBridge.h"
#include "objects/Frame.h"
#include "animation/AnimationState.h"
#include "events/ArmatureEvent.h"
#include "events/FrameEvent.h"
#include "events/SoundEvent.h"
#include "events/SoundEventManager.h"
#include <stdexcept>
namespace dragonBones
{
        /**
         * Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Object* Armature::getDisplay()
        {
            return _display;
        }
        /**
         * An Animation instance
         * @see dragonBones.animation.Animation
         */
        Animation* Armature::getAnimation()
        {
            return _animation;
        }

        /**
         * Creates a Armature blank instance.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Armature::Armature(Object *display)
        {
            _display = display;
            
            _animation = new Animation(this);
            _slotsZOrderChanged = false;
                        
            _needUpdate = false;
        }
        
        /**
         * Cleans up any resources used by this DBObject instance.
         */
        void Armature::dispose()
        {
            if(!_animation)
            {
                return;
            }
            
            userData = 0;
            
            _animation->dispose();

			for (size_t i = 0; i < _slotList.size(); i++)
			{
				_slotList[i]->dispose();
			}

			for (size_t i = 0; i < _boneList.size(); i++)
			{
				_boneList[i]->dispose();
			}

			for (size_t i = 0; i < _slotList.size(); i++)
			{
				delete _slotList[i];
			}

			for (size_t i = 0; i < _boneList.size(); i++)
			{
				delete _boneList[i];
			}

            _slotList.clear();
            _boneList.clear();
            for(size_t i = 0 ; i < _eventList.size() ; i ++)
            {
                delete _eventList[i];
            }
            _eventList.clear();
            
            DB_SAFE_DELETE(_animation);
            DB_SAFE_DELETE(_display);
        }
        
        void Armature::invalidUpdate()
        {
            _needUpdate = true;
        }
        
        /**
         * Update the animation using this method typically in an ENTERFRAME Event or with a Timer.
         * @param    The amount of second to move the playhead ahead.
         */
        void Armature::advanceTime(Number passedTime)
        {
            int i;
            Slot* slot;
            Armature* childArmature;
            if(_animation->getIsPlaying() || _needUpdate)
            {    
                _needUpdate = false;
                _animation->advanceTime(passedTime);
                passedTime *= _animation->getTimeScale();
                
                i = _boneList.size();
                while(i --)
                {
                    _boneList[i]->update();
                }
                
                i = _slotList.size();
                while(i --)
                {
                    slot = _slotList[i];
                    slot->update();
                    if(slot->_isDisplayOnStage)
                    {
                        childArmature = slot->getChildArmature();
                        if(childArmature)
                        {
                            childArmature->advanceTime(passedTime);
                        }
                    }
                }
                
                if(_slotsZOrderChanged)
                {
                    updateSlotsZOrder();

                    if(hasEventListener(ArmatureEvent::Z_ORDER_UPDATED))
                    {
                        dispatchEvent(new ArmatureEvent(ArmatureEvent::Z_ORDER_UPDATED));
                    }
                }
                
                if(!_eventList.empty())
                {
                    for(size_t i = 0 ; i < _eventList.size() ; i ++)
                    {
                        dispatchEvent(_eventList[i]);
                    }
                    _eventList.clear();
                }
            }
            else
            {
                passedTime *= _animation->getTimeScale();
                i = _slotList.size();
                while(i --)
                {
                    slot = _slotList[i];
                    if(slot->_isDisplayOnStage)
                    {
                        childArmature = slot->getChildArmature();
                        if(childArmature)
                        {
                            childArmature->advanceTime(passedTime);
                        }
                    }
                }
            }
        }
        
        
        /**
         * Get all Slot instance associated with this armature.
         * @return A Vector.&lt;Slot&gt; instance.
         * @see dragonBones.Slot
         */
        std::vector<Slot*> Armature::getSlotsCopy()
        {
            return _slotList;
        }
        std::vector<Slot*>& Armature::getSlots()
        {
            return _slotList;
        }

        /**
         * Get all Bone instance associated with this armature.
         * @return A Vector.&lt;Bone&gt; instance.
         * @see dragonBones.Bone
         */
        std::vector<Bone*> Armature::getBonesCopy()
        {
            return _boneList;
        }
        std::vector<Bone*>& Armature::getBones()
        {
            return _boneList;
        }
        
        /**
         * Retrieves a Slot by name
         * @param    The name of the Bone to retrieve.
         * @return A Slot instance or null if no Slot with that name exist.
         * @see dragonBones.Slot
         */
        Slot* Armature::getSlot(const String &slotName)
        {
            int i = static_cast<int>(_slotList.size());
            while(i --)
            {
                if(_slotList[i]->name == slotName)
                {
                    return _slotList[i];
                }
            }
            return 0;
        }
        
        /**
         * Gets the Slot associated with this DisplayObject.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         * @return A Slot instance.
         * @see dragonBones.Slot
         */
        Slot* Armature::getSlotByDisplay(Object *display)
        {
            if(display)
            {
                int i = static_cast<int>(_slotList.size());
                while(i --)
                {
                    if(_slotList[i]->getDisplay() == display)
                    {
                        return _slotList[i];
                    }
                }
            }
            return 0;
        }
        
        /**
         * Remove a Slot instance from this Armature instance.
         * @param    The Slot instance to remove.
         * @see dragonBones.Slot
         */
        void Armature::removeSlot(Slot *slot)
        {
            if(!slot)
            {
                throw std::invalid_argument("slot is null");
            }
            
            if(indexOf(_slotList , slot) >= 0)
            {
                slot->parent->removeChild(slot);
            }
            else
            {
                throw std::invalid_argument("slot not found");
            }
        }
        
        /**
         * Remove a Slot instance from this Armature instance.
         * @param    The name of the Slot instance to remove.
         * @see dragonBones.Slot
         */
        void Armature::removeSlotByName(const String &slotName)
        {
            if(slotName.empty())
            {
                return;
            }
            
            Slot* slot = getSlot(slotName);
            if(slot)
            {
                removeSlot(slot);
            }
        }
        
        /**
         * Retrieves a Bone by name
         * @param    The name of the Bone to retrieve.
         * @return A Bone instance or null if no Bone with that name exist.
         * @see dragonBones.Bone
         */
        Bone* Armature::getBone(const String &boneName)
        {
            int i = static_cast<int>(_boneList.size());
            while(i --)
            {
                if(_boneList[i]->name == boneName)
                {
                    return _boneList[i];
                }
            }
            return 0;
        }
        
        /**
         * Gets the Bone associated with this DisplayObject.
         * @param    Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         * @return A Bone instance.
         * @see dragonBones.Bone
         */
        Bone* Armature::getBoneByDisplay(Object *display)
        {
            Slot* slot = getSlotByDisplay(display);
            return slot?slot->parent:0;
        }
        
        /**
         * Remove a Bone instance from this Armature instance.
         * @param    The Bone instance to remove.
         * @see    dragonBones.Bone
         */
        void Armature::removeBone(Bone * bone)
        {
            if(!bone)
            {
                throw std::invalid_argument("bone is null");
            }
            
            if(indexOf(_boneList , bone) >= 0)
            {
                if(bone->parent)
                {
                    bone->parent->removeChild(bone);
                }
                else
                {
                    bone->setArmature(0);
                }
            }
            else
            {
                throw std::invalid_argument("bone not found");
            }
        }
        
        /**
         * Remove a Bone instance from this Armature instance.
         * @param    The name of the Bone instance to remove.
         * @see dragonBones.Bone
         */
        void Armature::removeBoneByName(const String &boneName)
        {
            if(boneName.empty())
            {
                return;
            }
            
            Bone* bone = getBone(boneName);
            if(bone)
            {
                removeBone(bone);
            }
        }
        
        
        /**
         * Add a DBObject instance to this Armature instance.
         * @param    A DBObject instance
         * @param    (optional) The parent's name of this DBObject instance.
         * @see dragonBones.core.DBObject
         */
        void Armature::addChild(DBObject *object, const String &parentName)
        {
            if(!object)
            {
                throw std::invalid_argument("object is null");
            }
            
            if(!parentName.empty())
            {
                Bone* boneParent = getBone(parentName);
                if (boneParent)
                {
                    boneParent->addChild(object);
                }
                else
                {
                    throw std::invalid_argument("parentName bone not found");
                }
            }
            else
            {
                if(object->parent)
                {
                    object->parent->removeChild(object);
                }
                object->setArmature(this);
            }
        }
        
        /**
         * Add a Bone instance to this Armature instance.
         * @param    A Bone instance
         * @param    (optional) The parent's name of this Bone instance.
         * @see dragonBones.Bone
         */
        void Armature::addBone(Bone * bone, const String &parentName)
        {
            addChild(bone, parentName);
        }
        
        /**
         * Update the z-order of the display. 
         */
        void Armature::updateSlotsZOrder()
        {
            std::sort(_slotList.begin() , _slotList.end() , sortSlot);
            int i = _slotList.size();
            Slot* slot;
            while(i --)
            {
                slot = _slotList[i];
                if(slot->_isDisplayOnStage)
                {
                    slot->_displayBridge->addDisplay(getDisplay());
                }
            }
            
            _slotsZOrderChanged = false;
        }
        
        /** @private */
        void Armature::addDBObject(DBObject *object)
        {
            if(dynamic_cast<Slot*>(object))
            {
                Slot* slot = static_cast<Slot*>(object);
                if(indexOf(_slotList , slot) < 0)
                {
                    _slotList.push_back(slot);
                }
            }
            else if(dynamic_cast<Bone*>(object))
            {
                Bone* bone = static_cast<Bone*>(object);
                if(indexOf(_boneList , bone) < 0)
                {
                    _boneList.push_back(bone);
                    sortBoneList();
                }
            }
        }
        
        /** @private */
        void Armature::removeDBObject(DBObject * object)
        {
            if(dynamic_cast<Slot*>(object))
            {
                Slot* slot = static_cast<Slot*>(object);
                int index = indexOf(_slotList , slot);
                if(index >= 0)
                {
                    _slotList.erase(_slotList.begin() + index);
                }
            }
            else if(dynamic_cast<Bone*>(object))
            {
                Bone* bone = static_cast<Bone*>(object);
                int index = indexOf(_boneList , bone);
                if(index >= 0)
                {
                    _boneList.erase(_boneList.begin() + index);
                }
            }
        }
        bool Armature::sortBone(const std::pair<int , Bone*>& a , const std::pair<int , Bone*>& b)
        {
            return a.first > b.first;
        }

        /** @private */
        void Armature::sortBoneList()
        {
            int i = _boneList.size();
            if(i == 0)
            {
                return;
            }
            int level;
            Bone* bone;
            Bone* boneParent;
            std::vector<std::pair<int , Bone*> > helpArray;
            while(i --)
            {
                level = 0;
                bone = _boneList[i];
                boneParent = bone;
                while(boneParent)
                {
                    level ++;
                    boneParent = boneParent->parent;
                }
                helpArray.push_back(std::make_pair(level , bone));
            }
            
            std::sort(helpArray.begin() , helpArray.end() , sortBone);

            i = helpArray.size();
            while(i --)
            {
                _boneList[i] = helpArray[i].second;
            }
        }
        
        /** @private */
        void Armature::arriveAtFrame(Frame * frame, TimelineState *timelineState, AnimationState *animationState, bool isCross)
        {
            if(!frame->event.empty() && hasEventListener(FrameEvent::ANIMATION_FRAME_EVENT))
            {
                FrameEvent* frameEvent = new FrameEvent(FrameEvent::ANIMATION_FRAME_EVENT);
                frameEvent->animationState = animationState;
                frameEvent->frameLabel = frame->event;
                _eventList.push_back(frameEvent);
            }

            if(!frame->sound.empty() && SoundEventManager::getInstance()->hasEventListener(SoundEvent::SOUND))
            {
                SoundEvent* soundEvent = new SoundEvent(SoundEvent::SOUND);
                soundEvent->armature = this;
                soundEvent->animationState = animationState;
                soundEvent->sound = frame->sound;
                SoundEventManager::getInstance()->dispatchEvent(soundEvent);
            }
            
            if(!frame->action.empty())
            {
                if(animationState->getIsPlaying())
                {
                    getAnimation()->gotoAndPlay(frame->action);
                }
            }
        }
        
        bool Armature::sortSlot(Slot *slot1, Slot *slot2)
        {
            return slot1->getZOrder() < slot2->getZOrder();
        }
}
