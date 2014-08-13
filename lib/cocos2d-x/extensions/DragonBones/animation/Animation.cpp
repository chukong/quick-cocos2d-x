#include "objects/AnimationData.h"
#include "Animation.h"
#include "AnimationState.h"
#include "Slot.h"
#include "Armature.h"
#include "TimelineState.h"
namespace dragonBones
{    
        const String Animation::NONE = "none";
        const String Animation::SAME_LAYER = "sameLayer";
        const String Animation::SAME_GROUP = "sameGroup";
        const String Animation::SAME_LAYER_AND_GROUP = "sameLayerAndGroup";
        const String Animation::ALL = "all";
        
        
        /**
         * Unrecommended API. Recommend use getAnimationList.
         */
        const std::vector<String> &Animation::getMovementList()
        {
            return getAnimationList();
        }

        /**
         * Unrecommended API. Recommend use getLastAnimationName.
         */
        const String &Animation::getMovementID()
        {
            return getLastAnimationName();
        }
    
        /**
         * The name of the last AnimationData played.
        * @see dragonBones.objects.AnimationData.
         */
        const String &Animation::getLastAnimationName()
        {
            return _lastAnimationState?_lastAnimationState->name:BytesType::BLANK;
        }
    
        /**
         * The last AnimationData this Animation played.
         * @see dragonBones.objects.animationData->
         */
        AnimationState *Animation::getLastAnimationState()
        {
            return _lastAnimationState;
        }
        
        /**
         * An vector containing all AnimationData names the Animation can play.
         * @see dragonBones.objects.animationData->
         */
        const std::vector<String> &Animation::getAnimationList()
        {
            return _animationList;
        }
        
        bool Animation::getIsPlaying()
        {
            return _isPlaying && _isActive;
        }
        
        bool Animation::getIsComplete()
        {
            if(_lastAnimationState)
            {
                if(!_lastAnimationState->getIsComplete())
                {
                    return false;
                }
                int j = _animationLayer.size();
                while(j --)
                {
                    std::vector<AnimationState*> *animationStateList = _animationLayer[j];
                    int i = animationStateList->size();
                    while(i --)
                    {
                        if(!animationStateList->at(i)->getIsComplete())
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
            return false;
        }
        
        /**
         * The AnimationData list associated with this Animation instance.
         * @see dragonBones.objects.animationData->
         */
        const std::vector<AnimationData*>& Animation::getAnimationDataList()
        {
            return _animationDataList;
        }
    
        void Animation::setAnimationDataList(const std::vector<AnimationData*> &value)
        {
            _animationDataList = value;
            _animationList.clear();
            for(size_t i = 0 ; i < _animationDataList.size() ; i ++)
            {
                _animationList.push_back(_animationDataList[i]->name);
            }
        }

        AnimationData* Animation::getAnimationData(std::string &name)
        {
            for (size_t i = 0; i < _animationDataList.size(); i++)
            {
                AnimationData* data = _animationDataList[i];
                if (data->name == name)
                {
                    return data;
                }
            }
            return 0;
        }
       
        /**
         * The amount by which passed time should be scaled. Used to slow down or speed up animations. Defaults to 1.
         */
        Number Animation::getTimeScale()
        {
            return _timeScale;
        }
        void Animation::setTimeScale(Number value)
        {
            if (value < 0)
            {
                value = 0;
            }
            _timeScale = value;
        }
        
        /**
         * Creates a new Animation instance and attaches it to the passed Armature.
         * @param    An Armature to attach this Animation instance to.
         */
        Animation::Animation(Armature *armature)
        {
            _armature = armature;
            _lastAnimationState = 0;
            _isPlaying = false;
            _isActive = false;
            tweenEnabled = true;
            _timeScale = 1;
        }
        
        /**
         * Qualifies all resources used by this Animation instance for garbage collection.
         */
        void Animation::dispose()
        {
            if(!_armature)
            {
                return;
            }
            stop();
            int i = _animationLayer.size();
            while(i --)
            {
                std::vector<AnimationState*> *animationStateList = _animationLayer[i];
                int j = animationStateList->size();
                while(j --)
                {
                    AnimationState::returnObject(animationStateList->at(j));
                }
                animationStateList->clear();
                delete animationStateList;
            }
            _animationLayer.clear();
            _animationList.clear();
            
            _armature = 0;
            _animationDataList.clear();
            _animationList.clear();
        }
        
        /**
         * Move the playhead to that AnimationData
         * @param animationName The name of the AnimationData to play.
         * @param fadeInTime A fade time to apply (> 0)
         * @param duration The duration of that animationData->
         * @param loop Loop(0:loop forever, 1~+OO:loop times, -1~-OO:will fade animation after loop complete).
         * @param layer The layer of the animation.
         * @param group The group of the animation.
         * @param fadeOutMode Fade out mode.
         * @param displayControl Display control.
         * @param pauseFadeOut Pause other animation playing.
         * @param pauseFadeIn Pause this animation playing before fade in complete.
         * @see dragonBones.objects.animationData->
         * @see dragonBones.animation.animationState->
         */
        AnimationState* Animation::gotoAndPlay(
            const String &animationName, 
            Number fadeInTime, 
            Number duration, 
            Number loop, 
            uint layer, 
            const String &group,
            const String &fadeOutMode,
            bool displayControl,
            bool pauseFadeOut,
            bool pauseFadeIn
        )
        {
            if (_animationDataList.empty())
            {
                return 0;
            }
            int i = _animationDataList.size();
            AnimationData* animationData = 0;
            while(i --)
            {
                if(_animationDataList[i]->name == animationName)
                {
                    animationData = _animationDataList[i];
                    break;
                }
            }
            if (!animationData)
            {
                return 0;
            }
            
            _isPlaying = true;
            
            //
            fadeInTime = fadeInTime < 0?(animationData->fadeInTime < 0?0.3f:animationData->fadeInTime):fadeInTime;
            
            Number durationScale;
            if(duration < 0)
            {
                durationScale = animationData->scale < 0?1:animationData->scale;
            }
            else
            {
                durationScale = duration / animationData->duration;
            }
            
            loop = isNaN(loop) ?animationData->loop:loop;
            layer = addLayer(layer);
            
            //autoSync = autoSync && !pauseFadeOut && !pauseFadeIn;
            AnimationState* animationState = 0;

            if(fadeOutMode == NONE)
            {
            }
            else if(fadeOutMode == SAME_LAYER)
            {
                std::vector<AnimationState*> *animationStateList = _animationLayer[layer];
                i = animationStateList->size();
                while(i --)
                {
                    animationState = animationStateList->at(i);
                    animationState->fadeOut(fadeInTime, pauseFadeOut);
                }
            }
            else if(fadeOutMode == SAME_GROUP)
            {
                int j = _animationLayer.size();
                while(j --)
                {
                    std::vector<AnimationState*> *animationStateList = _animationLayer[j];
                    i = animationStateList->size();
                    while(i --)
                    {
                        animationState = animationStateList->at(i);
                        if(animationState->group == group)
                        {
                            animationState->fadeOut(fadeInTime, pauseFadeOut);
                        }
                    }
                }

            }
            else if(fadeOutMode == ALL)
            {
                int j = _animationLayer.size();
                while(j --)
                {
                    std::vector<AnimationState*> *animationStateList = _animationLayer[j];
                    i = animationStateList->size();
                    while(i --)
                    {
                        animationState = animationStateList->at(i);
                        animationState->fadeOut(fadeInTime, pauseFadeOut);
                    }
                }

            }
            else 
            {
                std::vector<AnimationState*> *animationStateList = _animationLayer[layer];
                i = animationStateList->size();
                while(i --)
                {
                    animationState = animationStateList->at(i);
                    if(animationState->group == group)
                    {
                        animationState->fadeOut(fadeInTime, pauseFadeOut);
                    }
                }
            }

            _lastAnimationState = animationState->borrowObject();
            _lastAnimationState->group = group;
            _lastAnimationState->tweenEnabled = tweenEnabled;
            _lastAnimationState->fadeIn(_armature, animationData, fadeInTime, 1 / durationScale, (int)loop, layer, displayControl, pauseFadeIn);
            
            addState(_lastAnimationState);
            
            std::vector<Slot*> &slotList = _armature->_slotList;
            Slot* slot;
            i = slotList.size();
            while(i --)
            {
                slot = slotList[i];
                if(slot->getChildArmature())
                {
                    slot->getChildArmature()->getAnimation()->gotoAndPlay(animationName, fadeInTime);
                }
            }
            
            _lastAnimationState->advanceTime(0);
            
            return _lastAnimationState;
        }
        
        /**
         * Play the animation from the current position.
         */
        void Animation::play()
        {
            if (_animationDataList.size() == 0)
            {
                return;
            }
            if(!_lastAnimationState)
            {
                gotoAndPlay(_animationDataList[0]->name);
            }
            else if (!_isPlaying)
            {
                _isPlaying = true;
            }
            else
            {
                gotoAndPlay(_lastAnimationState->name);
            }
        }
        
        void Animation::stop()
        {
            _isPlaying = false;
        }
        
        /**
         * Returns the AnimationState named name.
         * @return A AnimationState instance.
         * @see dragonBones.animation.animationState->
         */
        AnimationState* Animation::getState(const String &name, uint layer)
        {
            int l = _animationLayer.size();
            if(l == 0)
            {
                return 0;
            }
            else if((int)layer >= l)
            {
                layer = l - 1;
            }
            
            std::vector<AnimationState*> *animationStateList = _animationLayer[layer];
            if(!animationStateList)
            {
                return 0;
            }
            int i = animationStateList->size();
            while(i --)
            {
                if(animationStateList->at(i)->name == name)
                {
                    return animationStateList->at(i);
                }
            }
            
            return 0;
        }
        
        bool Animation::hasAnimation(const String &animationName)
        {
            int i = _animationDataList.size();
            while(i --)
            {
                if(_animationDataList[i]->name == animationName)
                {
                    return true;
                }
            }
            
            return false;
        }
        
        void Animation::advanceTime(Number passedTime)
        {
            /*
            if(!_isPlaying || !_isActive)
            {
                return;
            }
            */
            passedTime *= _timeScale;
            
            int l = _armature->_boneList.size();
            int i;
            int j;
            int k = l;
            uint stateListLength;
            Bone* bone;
            String boneName;
            Number weigthLeft;
            
            Number x;
            Number y;
            Number skewX;
            Number skewY;
            Number scaleX;
            Number scaleY;
            Number pivotX;
            Number pivotY;
            
            Number layerTotalWeight;
            AnimationState* animationState;
            TimelineState* timelineState;
            Number weight;
            DBTransform *transform = 0;
            Point *pivot = 0;
            
            l --;
            while(k --)
            {
                bone = _armature->_boneList[k];
                boneName = bone->name;
                weigthLeft = 1;
                
                x = 0;
                y = 0;
                skewX = 0;
                skewY = 0;
                scaleX = 0;
                scaleY = 0;
                pivotX = 0;
                pivotY = 0;
                
                i = _animationLayer.size();
                while(i --)
                {
                    layerTotalWeight = 0;
                    std::vector<AnimationState*> *animationStateList = _animationLayer[i];
                    stateListLength = animationStateList->size();
                    for(j = 0;j < (int)stateListLength;j ++)
                    {
                        animationState = animationStateList->at(j);
                        if(k == l)
                        {
                            if(animationState->advanceTime(passedTime))
                            {
                                removeState(animationState);
                                j --;
                                stateListLength --;
                                continue;
                            }
                        }
                        
                        timelineState = animationState->_timelineStates[boneName];
                        
                        if(timelineState && timelineState->tweenActive)
                        {
                            weight = animationState->_fadeWeight * animationState->weight * weigthLeft;
                            transform = &timelineState->transform;
                            pivot = &timelineState->pivot;
                            x += transform->x * weight;
                            y += transform->y * weight;
                            skewX += transform->skewX * weight;
                            skewY += transform->skewY * weight;
                            scaleX += transform->scaleX * weight;
                            scaleY += transform->scaleY * weight;
                            pivotX += pivot->x * weight;
                            pivotY += pivot->y * weight;
                            
                            layerTotalWeight += weight;
                        }
                    }
                    
                    if(layerTotalWeight >= weigthLeft)
                    {
                        break;
                    }
                    else
                    {
                        weigthLeft -= layerTotalWeight;
                    }
                }
                transform = &bone->tween;
                pivot = &bone->_tweenPivot;
                
                transform->x = x;
                transform->y = y;
                transform->skewX = skewX;
                transform->skewY = skewY;
                transform->scaleX = scaleX;
                transform->scaleY = scaleY;
                pivot->x = pivotX;
                pivot->y = pivotY;
            }
        }
        
        /** @private */
        void Animation::setActive(AnimationState *animationState, bool active)
        {
            if(active)
            {
                _isActive = true;
            }
            else
            {
                int i = _animationLayer.size();
                int j;
                while(i --)
                {
                    std::vector<AnimationState*> *animationStateList = _animationLayer[i];
                    j = animationStateList->size();
                    while(j --)
                    {
                        if(animationStateList->at(j)->getIsPlaying())
                        {
                            return;
                        }
                    }
                }
                _isActive = false;
            }
        }
        
        uint Animation::addLayer(uint layer)
        {
            if(layer >= _animationLayer.size())
            {
                _animationLayer.push_back(new std::vector<AnimationState*>());
            }
            return layer;
        }
        
        void Animation::addState(AnimationState *animationState)
        {
            std::vector<AnimationState*> *animationStateList = _animationLayer[animationState->getLayer()];
            animationStateList->push_back(animationState);
        }
        
        void Animation::removeState(AnimationState *animationState)
        {
            int layer = animationState->getLayer();
            std::vector<AnimationState*> *animationStateList = _animationLayer[layer];
            animationStateList->erase(animationStateList->begin() + indexOf(*animationStateList , animationState));
            
            animationState->returnObject(animationState);
            
            if(animationStateList->size() == 0 && layer == _animationLayer.size() - 1)
            {
                _animationLayer.pop_back();
            }
        }    
}