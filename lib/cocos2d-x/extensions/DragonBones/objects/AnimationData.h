#ifndef __ANIMATION_DATA_H__
#define __ANIMATION_DATA_H__
#include "utils/preDB.h"
#include "Timeline.h"
#include "TransformTimeline.h"
namespace dragonBones
{
    class AnimationData : public Timeline
    {
    public:
        uint frameRate;
        String name;
        int loop;
        Number tweenEasing;
        
        typedef std::map<std::string , Timeline*> Timelines;
        Timelines timelines;
        
        Number fadeInTime;
                
        AnimationData()
        {
            loop = 0;
            tweenEasing = NaN;            
            fadeInTime = 0;
        }
        virtual ~AnimationData()
        {
            dispose();
        }
        void setFadeInTime(Number value)
        {
            if(isNaN(value))
            {
                value = 0;
            }
            fadeInTime = value;
        }

        virtual void dispose()
        {
            Timeline::dispose();
            
            for(Timelines::iterator iter = timelines.begin() ; iter != timelines.end() ; iter ++)
            {
                if(iter->second != &TransformTimeline::HIDE_TIMELINE)
                {
                    iter->second->dispose();
                    delete iter->second;
                }
            }
            timelines.clear();
        }
        
        TransformTimeline *getTimeline(const String &timelineName)
        {
            Timelines::iterator iter = timelines.find(timelineName);
            if(iter != timelines.end())
                return static_cast<TransformTimeline*>(iter->second);
            else
                return 0;
        }
        
        void addTimeline(TransformTimeline *timeline, const String &timelineName)
        {            
            timelines[timelineName] = timeline;
        }
    };
};
#endif // __ANIMATION_DATA_H__
