#include "Bone.h"
#include "Slot.h"
#include "animation/AnimationState.h"
#include "objects/TransformFrame.h"
#include "utils/TransformUtil.h"
#include "Armature.h"
#include "animation/Animation.h"
#include "display/IDisplayBridge.h"
#include "events/FrameEvent.h"
#include "events/SoundEvent.h"
#include "events/SoundEventManager.h"
#include <stdexcept>
namespace dragonBones
{
        /**
         * The sub-armature of default Slot of this Bone instance.
         */
        Armature* Bone::getChildArmature()
        {
            return _slot?_slot->getChildArmature():0; 
        }
        
        /**
         * The DisplayObject of default Slot of this Bone instance.
         */
        Object* Bone::getDisplay()
        {
            return _slot?_slot->getDisplay():0;
        }
        void Bone::setDisplay(Object *value)
        {
            if(_slot)
            {
                _slot->setDisplayValue(value);
            }
        }
        /**
         * @inheritDoc
         */
        void Bone::setVisible(bool value)
        {
            if(_visible != value)
            {
                _visible = value;
                int i = _children.size();
                while(i --)
                {
                    DBObject* child = _children[i];
                    if(dynamic_cast<Slot*>(child))
                    {
                        static_cast<Slot*>(child)->updateVisible(_visible);
                    }
                }
            }
        }
        
        /** @private */
        void Bone::setArmature(Armature *value)
        {
            DBObject::setArmature(value);
            int i = _children.size();
            while(i --)
            {
                _children[i]->setArmature(_armature);
            }
        }
        
        Bone::Bone()
        {
            _scaleType = 2;
            scaleMode = 1;
            _slot = 0;
        }
        
        /**
         * @inheritDoc
         */
        void Bone::dispose()
        {
            DBObject::dispose();
            
            int i = _children.size();
            while(i --)
            {
                _children[i]->dispose();
            }
            _children.clear();
            
            _slot = 0;
            _tweenPivot = Point();
        }
        
        bool Bone::contains(DBObject *child)
        {
            if(!child)
            {
                throw std::invalid_argument("child is null");
            }
            if(child == this)
            {
                return false;
            }
            DBObject* ancestor = child;
            while (!(ancestor == this || ancestor == 0))
            {
                ancestor = ancestor->parent;
            }
            return ancestor == this;
        }
        
        void Bone::addChild(DBObject *child)
        {
            if(!child)
            {
                throw std::invalid_argument("child is null");
            }
            
            if(child == this || (dynamic_cast<Bone*>(child) && static_cast<Bone*>(child)->contains(this)))
            {
                throw std::invalid_argument("An Bone cannot be added as a child to itself or one of its children (or children's children, etc.)");
            }
            
            if(child->parent)
            {
                child->parent->removeChild(child);
            }
            _children.push_back(child);
            child->parent = this;
            child->setArmature(_armature);
            
            if(!_slot && dynamic_cast<Slot*>(child))
            {
                _slot = static_cast<Slot*>(child);
            }
        }
        
        void Bone::removeChild(DBObject *child)
        {
            if(!child)
            {
                throw std::invalid_argument("child is null");
            }
            
            int index = indexOf(_children , child);
            if (index >= 0)
            {
                _children.erase(_children.begin() + index);
                child->parent = 0;
                child->setArmature(0);
                
                if(child == _slot)
                {
                    _slot = 0;
                }
            }
            else
            {
                throw std::invalid_argument("child not found");
            }
        }
        
        /**
         * Get all Slot instance associated with this bone.
         * @return A Vector.&lt;Slot&gt; instance.
         * @see dragonBones.Slot
         */
        std::list<Slot*> Bone::getSlots()
        {
            std::list<Slot*> slotList;
            int i = _children.size();
            while(i --)
            {
                if(dynamic_cast<Slot*>(_children[i]))
                {
                    slotList.push_front(static_cast<Slot*>(_children[i]));
                }
            }
            return slotList;
        }
        
        /** @private */
        void Bone::arriveAtFrame(Frame *frame, TimelineState *timelineState, AnimationState *animationState, bool isCross)
        {
            if(frame)
            {
                int mixingType = animationState->getMixingTransform(name);
                if(animationState->displayControl && (mixingType == 2 || mixingType == -1))
                {
                    if(
                        displayController.empty() || displayController == animationState->name
                    )
                    {
                        TransformFrame* tansformFrame = static_cast<TransformFrame*>(frame);
                        if(_slot)
                        {
                            int displayIndex = tansformFrame->displayIndex;
                            if(displayIndex >= 0)
                            {
                                if(!isNaN(tansformFrame->zOrder) && tansformFrame->zOrder != _slot->_tweenZorder)
                                {
                                    _slot->_tweenZorder = tansformFrame->zOrder;
                                    _armature->_slotsZOrderChanged = true;
                                }
                            }
                            _slot->changeDisplay(displayIndex);
                            _slot->updateVisible(tansformFrame->visible);
                        }
                    }
                }

                if(!frame->event.empty() && _armature->hasEventListener(FrameEvent::BONE_FRAME_EVENT))
                {
                    FrameEvent* frameEvent = new FrameEvent(FrameEvent::BONE_FRAME_EVENT);
                    frameEvent->bone = this;
                    frameEvent->animationState = animationState;
                    frameEvent->frameLabel = frame->event;
                    _armature->_eventList.push_back(frameEvent);
                }
                
                if(!frame->sound.empty() && SoundEventManager::getInstance()->hasEventListener(SoundEvent::SOUND))
                {
                    SoundEvent* soundEvent = new SoundEvent(SoundEvent::SOUND);
                    soundEvent->armature = _armature;
                    soundEvent->animationState = animationState;
                    soundEvent->sound = frame->sound;
                    SoundEventManager::getInstance()->dispatchEvent(soundEvent);
                }
                
                if(!frame->action.empty())
                {
                    for(size_t i = 0 ; i < _children.size() ; i ++)
                    {
                        DBObject* child = _children[i];
                        if(dynamic_cast<Slot*>(child))
                        {
                            Armature* childArmature = static_cast<Slot*>(child)->getChildArmature();
                            if(childArmature)
                            {
                                childArmature->getAnimation()->gotoAndPlay(frame->action);
                            }
                        }
                    }
                }
            }
            else
            {
                if(_slot)
                {
                    _slot->changeDisplay(-1);
                }
            }
        }
        
        /** @private */
        void Bone::updateColor(
            Number aOffset, 
            Number rOffset, 
            Number gOffset, 
            Number bOffset, 
            Number aMultiplier, 
            Number rMultiplier, 
            Number gMultiplier, 
            Number bMultiplier,
            bool isColorChanged
        )
        {
            if(isColorChanged || _isColorChanged)
            {
                _slot->_displayBridge->updateColor(
                    aOffset, 
                    rOffset, 
                    gOffset, 
                    bOffset, 
                    aMultiplier, 
                    rMultiplier, 
                    gMultiplier, 
                    bMultiplier
                );
            }
            _isColorChanged = isColorChanged;
        }

        Bone::~Bone()
        {
            dispose();
        }

}
