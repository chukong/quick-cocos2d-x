#ifndef __ANIMATION_STATE_H__
#define __ANIMATION_STATE_H__
#include "utils/preDB.h"
namespace dragonBones
{
    class Armature;
    class TimelineState;
    class Frame;
    class AnimationData;
    class AnimationState
    {
    private :
        static std::vector<AnimationState*> _pool;
    public:
        
        /** @private */
        static AnimationState* borrowObject();
        
        /** @private */
        static void returnObject(AnimationState * animationState);
        
        /** @private */
        static void clear();
        
        bool tweenEnabled;
        bool blend;
        String group;
        Number weight;
        
        /** @private */
        std::map<String , TimelineState*> _timelineStates;
        /** @private */
        Number _fadeWeight;
        
        Armature* _armature;
        Frame *_currentFrame;
        std::map<String , int> _mixingTransforms;
        int _fadeState;
        Number _fadeInTime;
        Number _fadeOutTime;
        Number _fadeOutBeginTime;
        Number _fadeOutWeight;
        bool _fadeIn;
        bool _fadeOut;
        int _pauseBeforeFadeInCompleteState;

        String name;

        AnimationData* _clip;
        AnimationData *getClip()
        {
            return _clip;
        }
        
        int _loopCount;
        int getLoopCount()
        {
            return _loopCount;
        }
        
        int _loop;
        int getLoop()
        {
            return _loop;
        }
        
        uint _layer;
        uint getLayer()
        {
            return _layer;
        }
        
        bool _isPlaying;
        bool getIsPlaying()
        {
            return _isPlaying && !_isComplete;
        }
        
        bool _isComplete;
        bool getIsComplete()
        {
            return _isComplete; 
        }
        
        Number getFadeInTime()
        {
            return _fadeInTime;
        }
        
        Number _totalTime;
        Number getTotalTime()
        {
            return _totalTime;
        }
        
        Number _currentTime;
        Number getCurrentTime()
        {
            return _currentTime;
        }
        void setCurrentTime(Number value);
        
        Number _timeScale;
        Number getTimeScale()
        {
            return _timeScale;
        }
        void setTimeScale(Number value);
        
    public:
        bool displayControl;
        
        AnimationState();
        
        /** @private */
        void fadeIn(Armature * armature, AnimationData * clip, Number fadeInTime, Number timeScale, int loop, uint layer, bool displayControl, bool pauseBeforeFadeInComplete);
        
        void fadeOut(Number fadeOutTime, bool pause = false);

        void play();
        
        void stop();
        
        int getMixingTransform(const String &timelineName);
        
        void addMixingTransform(const String &timelineName, int type = 2, bool recursive = true);
        
        void removeMixingTransform(const String &timelineName = "", bool recursive = true);
        
        bool advanceTime(Number passedTime);
        
        void updateTimelineStates();
        
        void addTimelineState(const String &timelineName);
        
        void removeTimelineState(const String &timelineName);
        
        void clearAll();
    };
};
#endif // __ANIMATION_STATE_H__
