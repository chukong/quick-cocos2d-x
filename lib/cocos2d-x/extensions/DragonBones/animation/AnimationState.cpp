#include "AnimationState.h"
#include "TimelineState.h"
#include "objects/AnimationData.h"
#include "Armature.h"
#include "Animation.h"
#include "events/AnimationEvent.h"
#include <stdexcept>
namespace dragonBones
{

    std::vector<AnimationState*> AnimationState::_pool;

        /** @private */
        AnimationState* AnimationState::borrowObject()
        {
            if(_pool.empty())
            {
                return new AnimationState();
            }
            AnimationState *state = _pool.back();
            _pool.pop_back();
            return state;
        }
        
        /** @private */
        void AnimationState::returnObject(AnimationState * animationState)
        {
            animationState->clearAll();
            
            if(indexOf(_pool , animationState) < 0)
            {
                _pool.push_back(animationState);
            }
        }
        
        /** @private */
        void AnimationState::clear()
        {
            int i = _pool.size();
            while(i --)
            {
                _pool[i]->clearAll();
            }
            _pool.clear();
            
            TimelineState::clear();
        }
        void AnimationState::setCurrentTime(Number value)
        {
            if(value < 0 || isNaN(value))
            {
                value = 0;
            }
            //
            _currentTime = value;
        }

        void AnimationState::setTimeScale(Number value)
        {
            if(value < 0)
            {
                value = 0;
            }
            else if(isNaN(value))
            {
                value = 1;
            }
            else if(_timeScale == Infinite)
            {
                //*
                _timeScale = 1;
            }
            _timeScale = value;
        }
        
        AnimationState::AnimationState()
        { 
            tweenEnabled = false;
            blend = false;
            weight = 0;
            _fadeWeight = 0;
            _armature = 0;
            _currentFrame = 0;
            _fadeState = 0;
            _fadeInTime = 0;
            _fadeOutTime = 0;
            _fadeOutBeginTime = 0;
            _fadeOutWeight = 0;
            _fadeIn = false;
            _fadeOut = false;
            _pauseBeforeFadeInCompleteState = 0;
            _clip = 0;
            _loopCount = 0;
            _loop = 0;
            _layer = 0;
            _isPlaying = 0;
            _isComplete = 0;
            _totalTime = 0;
            _currentTime = 0;
            _timeScale = 0;
            displayControl = false;
        }
        
        /** @private */
        void AnimationState::fadeIn(Armature * armature, AnimationData * clip, Number fadeInTime, Number timeScale, int loop, uint layer, bool inDisplayControl, bool pauseBeforeFadeInComplete)
        {
            _armature = armature;
            _clip = clip;
            name = _clip->name;
            _layer = layer;
            
            _totalTime = _clip->duration;
            if(round(_clip->duration * _clip->frameRate) < 2 || timeScale == Infinite)
            {
                _timeScale = 1;
                _currentTime = _totalTime;
                if(_loop >= 0)
                {
                    _loop = 1;
                }
                else
                {
                    _loop = -1;
                }
            }
            else
            {
                _timeScale = timeScale;
                _currentTime = 0;
                _loop = loop;
            }
            
            if(pauseBeforeFadeInComplete)
            {
                _pauseBeforeFadeInCompleteState = -1;
            }
            else
            {
                _pauseBeforeFadeInCompleteState = 1;
            }
            
            _fadeInTime = fadeInTime * _timeScale;
            
            
            _loopCount = -1;
            _fadeState = 1;
            _fadeOutBeginTime = 0;
            _fadeOutWeight = -1;
            _fadeWeight = 0;
            _isPlaying = true;
            _isComplete = false;
            _fadeIn = true;
            _fadeOut = false;
            
            displayControl = inDisplayControl;
            
            weight = 1;
            blend = true;
            tweenEnabled = true;
            
            updateTimelineStates();
        }
        
        void AnimationState::fadeOut(Number fadeOutTime, bool pause)
        {
            if(!_armature || _fadeOutWeight >= 0)
            {
                return;
            }
            _fadeState = -1;
            _fadeOutWeight = _fadeWeight;
            _fadeOutTime = fadeOutTime * _timeScale;
            _fadeOutBeginTime = _currentTime;
            
            _isPlaying = !pause;
            _fadeOut = true;
            displayControl = false;
            
            for(std::map<String , TimelineState*>::iterator iter = _timelineStates.begin() ; iter != _timelineStates.end() ; iter ++)
            {
                iter->second->fadeOut();
            }
        }
        
        void AnimationState::play()
        {
            _isPlaying = true;
        }
        
        void AnimationState::stop()
        {
            _isPlaying = false;
        }
        
        int AnimationState::getMixingTransform(const String &timelineName)
        {
            std::map<String , int>::iterator iter = _mixingTransforms.find(timelineName);
            return iter != _mixingTransforms.end() ? iter->second : -1;
        }
        
        void AnimationState::addMixingTransform(const String &timelineName, int type , bool recursive)
        {
            if(_clip && _clip->getTimeline(timelineName))
            {
                if(recursive)
                {
                    int i = _armature->_boneList.size();
                    Bone* bone;
                    Bone* currentBone;
                    while(i --)
                    {
                        bone = _armature->_boneList[i];
                        if(bone->name == timelineName)
                        {
                            currentBone = bone;
                        }
                        if(currentBone && (currentBone == bone || currentBone->contains(bone)))
                        {
                            _mixingTransforms[bone->name] = type;
                        }
                    }
                }
                else
                {
                    _mixingTransforms[timelineName] = type;
                }
                
                updateTimelineStates();
            }
            else
            {
                // TODO(hejiangzhou): Shall we disable exception?
                throw std::invalid_argument("argument error");
            }
        }
        
        void AnimationState::removeMixingTransform(const String &timelineName , bool recursive)
        {
            if(!timelineName.empty())
            {
                if(recursive)
                {
                    int i = _armature->_boneList.size();
                    Bone* bone;
                    Bone* currentBone;
                    while(i --)
                    {
                        bone = _armature->_boneList[i];
                        if(bone->name == timelineName)
                        {
                            currentBone = bone;
                        }
                        if(currentBone && (currentBone == bone || currentBone->contains(bone)))
                        {
                            std::map<String , int>::iterator iter = _mixingTransforms.find(bone->name);
                            if(iter != _mixingTransforms.end())
                            {
                                _mixingTransforms.erase(iter);
                            }
                        }
                    }
                }
                else
                {
                    std::map<String , int>::iterator iter = _mixingTransforms.find(timelineName);
                    if(iter != _mixingTransforms.end())
                    {
                        _mixingTransforms.erase(iter);
                    }
                }
            }

            
            updateTimelineStates();
        }
        
        bool AnimationState::advanceTime(Number passedTime)
        {
            AnimationEvent *event = 0;
            bool isComplete = false;
            
            if(_fadeIn)
            {    
                _fadeIn = false;
                _armature->getAnimation()->setActive(this, true);
                if(_armature->hasEventListener(AnimationEvent::FADE_IN))
                {
                    event = new AnimationEvent(AnimationEvent::FADE_IN);
                    event->animationState = this;
                    _armature->_eventList.push_back(event);
                }
            }
            
            if(_fadeOut)
            {    
                _fadeOut = false;
                _armature->getAnimation()->setActive(this, true);
                if(_armature->hasEventListener(AnimationEvent::FADE_OUT))
                {
                    event = new AnimationEvent(AnimationEvent::FADE_OUT);
                    event->animationState = this;
                    _armature->_eventList.push_back(event);
                }
            }
            
            _currentTime += passedTime * _timeScale;
            
            if(_isPlaying && !_isComplete && _pauseBeforeFadeInCompleteState)
            {
                Number progress;
                int currentLoopCount;
                if(_pauseBeforeFadeInCompleteState == -1)
                {
                    _pauseBeforeFadeInCompleteState = 0;
                    progress = 0;
                    currentLoopCount = (int)progress;
                }
                else
                {
                    progress = _currentTime / _totalTime;
                    //update loopCount
                    currentLoopCount = (int)progress;
                    if(currentLoopCount != _loopCount)
                    {
                        if(_loopCount == -1)
                        {
                            _armature->getAnimation()->setActive(this, true);
                            if(_armature->hasEventListener(AnimationEvent::START))
                            {
                                event = new AnimationEvent(AnimationEvent::START);
                                event->animationState = this;
                                _armature->_eventList.push_back(event);
                            }
                        }
                        _loopCount = currentLoopCount;
                        if(_loopCount)
                        {
                            if(_loop && _loopCount * _loopCount >= _loop * _loop - 1)
                            {
                                isComplete = true;
                                progress = 1;
                                currentLoopCount = 0;
                                if(_armature->hasEventListener(AnimationEvent::COMPLETE))
                                {
                                    event = new AnimationEvent(AnimationEvent::COMPLETE);
                                    event->animationState = this;
                                    _armature->_eventList.push_back(event);
                                }
                            }
                            else
                            {
                                if(_armature->hasEventListener(AnimationEvent::LOOP_COMPLETE))
                                {
                                    event = new AnimationEvent(AnimationEvent::LOOP_COMPLETE);
                                    event->animationState = this;
                                    _armature->_eventList.push_back(event);
                                }
                            }
                        }
                    }
                }
                
                
                for(std::map<String , TimelineState*>::iterator iter = _timelineStates.begin() ; iter != _timelineStates.end() ; iter ++)
                {
                    iter->second->update(progress);
                }
                
                //
                if(_clip->frameList.size() > 0)
                {
                    Number playedTime = _totalTime * (progress - currentLoopCount);
                    bool isArrivedFrame = false;
                    int frameIndex;
                    while(!_currentFrame || playedTime > _currentFrame->position + _currentFrame->duration || playedTime < _currentFrame->position)
                    {
                        if(isArrivedFrame)
                        {
                            _armature->arriveAtFrame(_currentFrame, 0, this, true);
                        }
                        isArrivedFrame = true;
                        if(_currentFrame)
                        {
                            frameIndex = indexOf(_clip->frameList , _currentFrame);
                            frameIndex ++;
                            if(frameIndex >= (int)_clip->frameList.size())
                            {
                                frameIndex = 0;
                            }
                            _currentFrame = _clip->frameList[frameIndex];
                        }
                        else
                        {
                            _currentFrame = _clip->frameList[0];
                        }
                    }
                    
                    if(isArrivedFrame)
                    {
                        _armature->arriveAtFrame(_currentFrame, 0, this, false);
                    }
                }
            }
            
            //update weight and fadeState
            if(_fadeState > 0)
            {
                if(_fadeInTime == 0)
                {
                    _fadeWeight = 1;
                    _fadeState = 0;
                    _pauseBeforeFadeInCompleteState = 1;
                    _armature->getAnimation()->setActive(this, false);
                    if(_armature->hasEventListener(AnimationEvent::FADE_IN_COMPLETE))
                    {
                        event = new AnimationEvent(AnimationEvent::FADE_IN_COMPLETE);
                        event->animationState = this;
                        _armature->_eventList.push_back(event);
                    }
                }
                else
                {
                    _fadeWeight = _currentTime / _fadeInTime;
                    if(_fadeWeight >= 1)
                    {
                        _fadeWeight = 1;
                        _fadeState = 0;
                        if(_pauseBeforeFadeInCompleteState == 0)
                        {
                            _currentTime -= _fadeInTime;
                        }
                        _pauseBeforeFadeInCompleteState = 1;
                        _armature->getAnimation()->setActive(this, false);
                        if(_armature->hasEventListener(AnimationEvent::FADE_IN_COMPLETE))
                        {
                            event = new AnimationEvent(AnimationEvent::FADE_IN_COMPLETE);
                            event->animationState = this;
                            _armature->_eventList.push_back(event);
                        }
                    }
                }
            }
            else if(_fadeState < 0)
            {
                if(_fadeOutTime == 0)
                {
                    _fadeWeight = 0;
                    _fadeState = 0;
                    _armature->getAnimation()->setActive(this, false);
                    if(_armature->hasEventListener(AnimationEvent::FADE_OUT_COMPLETE))
                    {
                        event = new AnimationEvent(AnimationEvent::FADE_OUT_COMPLETE);
                        event->animationState = this;
                        _armature->_eventList.push_back(event);
                    }
                    return true;
                }
                else
                {
                    _fadeWeight = (1 - (_currentTime - _fadeOutBeginTime) / _fadeOutTime) * _fadeOutWeight;
                    if(_fadeWeight <= 0)
                    {
                        _fadeWeight = 0;
                        _fadeState = 0;
                        _armature->getAnimation()->setActive(this, false);
                        if(_armature->hasEventListener(AnimationEvent::FADE_OUT_COMPLETE))
                        {
                            event = new AnimationEvent(AnimationEvent::FADE_OUT_COMPLETE);
                            event->animationState = this;
                            _armature->_eventList.push_back(event);
                        }
                        return true;
                    }
                }
            }
            
            if(isComplete)
            {
                _isComplete = true;
                if(_loop < 0)
                {
                    fadeOut((_fadeOutWeight ? _fadeOutWeight : _fadeInTime) / _timeScale, true);
                }
                else
                {
                    _armature->getAnimation()->setActive(this, false);
                }
            }
            
            return false;
        }
        
        void AnimationState::updateTimelineStates()
        {
            if(!_mixingTransforms.empty())
            {
                for(std::map<String , TimelineState*>::iterator iter = _timelineStates.begin() ; iter != _timelineStates.end() ; )
                {
                    if(_mixingTransforms.find(iter->first) == _mixingTransforms.end())
                    {
                        if(iter != _timelineStates.end())
                        {
                            TimelineState::returnObject(static_cast<TimelineState*>(iter->second));
                            iter = _timelineStates.erase(iter);
                        }else{
                            iter++;
                        }
                    }
                }
                
                for(std::map<String , int>::iterator iter = _mixingTransforms.begin() ; iter != _mixingTransforms.end() ; iter ++)
                {
                    if(_timelineStates.find(iter->first) == _timelineStates.end())
                    {
                        addTimelineState(iter->first);
                    }
                }
            }
            else
            {
                for(AnimationData::Timelines::iterator iter = _clip->timelines.begin() ; iter != _clip->timelines.end() ; iter ++)
                {
                    if(_timelineStates.find(iter->first) == _timelineStates.end())
                    {
                        addTimelineState(iter->first);
                    }
                }
            }
        }
        
        void AnimationState::addTimelineState(const String &timelineName)
        {
            Bone* bone = _armature->getBone(timelineName);
            if(bone)
            {
                TimelineState* timelineState = TimelineState::borrowObject();
                TransformTimeline* timeline = _clip->getTimeline(timelineName);
                timelineState->fadeIn(bone, this, timeline);
                _timelineStates[timelineName] = timelineState;
            }
        }
        
        void AnimationState::removeTimelineState(const String &timelineName)
        {
            std::map<String , TimelineState*>::iterator iter = _timelineStates.find(timelineName);
            if(iter != _timelineStates.end())
            {
                TimelineState::returnObject(static_cast<TimelineState*>(iter->second));
                _timelineStates.erase(iter);
            }
        }
        
        void AnimationState::clearAll()
        {
            _armature = 0;
            _currentFrame = 0;
            _clip = 0;
            _mixingTransforms.clear();
            
            for(std::map<String , TimelineState*>::iterator iter = _timelineStates.begin() ; iter != _timelineStates.end() ; )
            {
                if(iter != _timelineStates.end())
                {
                    TimelineState::returnObject(static_cast<TimelineState*>(iter->second));
                    iter = _timelineStates.erase(iter);
                }else{
                    iter++;
                }
            }
        }
}
