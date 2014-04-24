#ifndef __TIMELINE_STATE_H__
#define __TIMELINE_STATE_H__

#include "utils/preDB.h"
#include "AnimationState.h"
#include "objects/DBTransform.h"
#include "utils//TransformUtil.h"
#include <cmath>

namespace dragonBones
{
    class Bone;
    class TransformTimeline;
    class TransformFrame;
    /** @private */
    class TimelineState
    {
    private:
        static std::vector<TimelineState*> _pool;
    public:
        /** @private */
        static TimelineState* borrowObject();
        
        /** @private */
        static void returnObject(TimelineState *timeline);
        
        /** @private */
        void static clear();
        
        static Number getEaseValue(Number value, Number easing)
        {
            Number valueEase;
            if (easing > 1)
            {
                valueEase = 0.5f * (1 - cos(value * TransformUtil::PI )) - value;
                easing -= 1;
            }
            else if (easing > 0)
            {
                valueEase = sin(value * TransformUtil::HALF_PI) - value;
            }
            else if (easing < 0)
            {
                valueEase = 1 - cos(value * TransformUtil::HALF_PI) - value;
                easing *= -1;
            }
            return valueEase * easing + value;
        }

        TimelineState();

        void fadeIn(Bone *bone, AnimationState *animationState, TransformTimeline *timeline);

        void fadeOut();

        void update(Number progress);

        void clearAll();
        DBTransform transform;
        Point pivot;
        bool tweenActive;
        
    private:
        int _updateState;
        
        AnimationState *_animationState;
        Bone *_bone;
        TransformTimeline *_timeline;
        TransformFrame *_currentFrame;
        Number _currentFramePosition;
        Number _currentFrameDuration;
        DBTransform _durationTransform;
        Point _durationPivot;
        ColorTransform _durationColor;
        DBTransform _originTransform;
        Point _originPivot;
        
        Number _tweenEasing;
        bool _tweenTransform;
        bool _tweenColor;
        
        Number _totalTime;
        
    };
};
#endif // __TIMELINE_STATE_H__
