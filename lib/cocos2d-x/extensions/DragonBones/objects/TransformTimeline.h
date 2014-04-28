#ifndef __TRANSFORM_TIMELINE_H__
#define __TRANSFORM_TIMELINE_H__
#include "utils/preDB.h"
#include "Timeline.h"
#include "DBTransform.h"
namespace dragonBones
{    
    class TransformTimeline : public Timeline
    {
    public:
        static TransformTimeline HIDE_TIMELINE;
        
        bool transformed;
        
        DBTransform originTransform;
        Point originPivot;

        Number offset;
        Number getOffset()
        {
            return offset;
        }
        void setOffset(Number value)
        {
            offset = value - (Number)(int)value;
            if(offset < 0)
            {
                offset += 1;
            }
        }
        
        TransformTimeline()
        {
            offset = 0;
            transformed = false;
        }
        
        virtual void dispose()
        {
            if(this == &HIDE_TIMELINE)
            {
                return;
            }
            Timeline::dispose();
        }
    };
};
#endif // __TRANSFORM_TIMELINE_H__
