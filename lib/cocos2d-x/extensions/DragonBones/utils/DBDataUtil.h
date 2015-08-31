#ifndef __DB_DATA_UTIL_H__
#define __DB_DATA_UTIL_H__
#include "utils/preDB.h"
#include "objects/DBTransform.h"
#include "utils/TransformUtil.h"
namespace dragonBones
{
    class ArmatureData;
    class TransformTimeline;
    class AnimationData;
    /** @private */
    class DBDataUtil
    {
    private:
        static DBTransform _helpTransform1;
        static DBTransform _helpTransform2;
    public:
        
        static void transformArmatureData(ArmatureData *armatureData);
        
        static void transformArmatureDataAnimations(ArmatureData *armatureData);
        
        static void transformAnimationData(AnimationData *animationData, ArmatureData *armatureData);
        
        static void getTimelineTransform(TransformTimeline *timeline, Number position, DBTransform &retult);
        
        static void addHideTimeline(AnimationData *animationData, ArmatureData *armatureData);
    };
};
#endif // __DB_DATA_UTIL_H__
