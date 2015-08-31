#include "DBDataUtil.h"
#include "animation/TimelineState.h"
#include "objects/ArmatureData.h"
#include "objects/TransformFrame.h"
namespace dragonBones
{

    DBTransform DBDataUtil::_helpTransform1;
    DBTransform DBDataUtil::_helpTransform2;

    void DBDataUtil::transformArmatureData(ArmatureData *armatureData)
    {
        std::vector<BoneData*> &boneDataList = armatureData->boneDataList;
        int i = boneDataList.size();
        BoneData* boneData;
        BoneData* parentBoneData;
        while(i --)
        {
            boneData = boneDataList[i];
            if(!boneData->parent.empty())
            {
                parentBoneData = armatureData->getBoneData(boneData->parent);
                if(parentBoneData)
                {
                    boneData->transform = boneData->global;
                    TransformUtil::transformPointWithParent(boneData->transform, parentBoneData->global);
                }
            }
        }
    }

    void DBDataUtil::transformArmatureDataAnimations(ArmatureData *armatureData)
    {
        std::vector<AnimationData*> &animationDataList = armatureData->animationDataList;
        int i = animationDataList.size();
        while(i --)
        {
            transformAnimationData(animationDataList[i], armatureData);
        }
    }

    void DBDataUtil::transformAnimationData(AnimationData *animationData, ArmatureData *armatureData)
    {
        SkinData *skinData = armatureData->getSkinData("");
        std::vector<BoneData*> & boneDataList = armatureData->boneDataList;
        std::vector<SlotData*> & slotDataList = skinData->slotDataList;
        int i = boneDataList.size();

        BoneData* boneData = 0;
        TransformTimeline* timeline = 0;
        SlotData* slotData = 0;
        DisplayData* displayData = 0;
        TransformTimeline* parentTimeline = 0;
        DBTransform *originTransform = 0;
        Point *originPivot = 0;
        TransformFrame *prevFrame = 0;
        uint frameListLength;
        TransformFrame *frame = 0;

        while(i --)
        {
            boneData = boneDataList[i];
            timeline = animationData->getTimeline(boneData->name);
            if(!timeline)
            {
                continue;
            }

            slotData = 0;
            for(size_t j = 0 ; j < slotDataList.size() ; j ++)
            {
                slotData = slotDataList[j];
                if(slotData->parent == boneData->name)
                {
                    break;
                }
            }

            parentTimeline = !boneData->parent.empty() ? animationData->getTimeline(boneData->parent):0;

            std::vector<Frame*> &frameList = timeline->frameList;

            originTransform = 0;
            prevFrame = 0;
            originPivot = 0;
            frameListLength = frameList.size();
            for(uint j = 0;j < frameListLength;j ++)
            {
                frame = static_cast<TransformFrame*>(frameList[j]);
                if(parentTimeline)
                {
                    //tweenValues to transform.
                    _helpTransform1 = frame->global;

                    //get transform from parent timeline->
                    getTimelineTransform(parentTimeline, frame->position, _helpTransform2);
                    TransformUtil::transformPointWithParent(_helpTransform1, _helpTransform2);

                    //transform to tweenValues.
                    frame->transform = _helpTransform1;
                }
                else
                {
                    frame->transform = frame->global;
                }

                frame->transform.x -= boneData->transform.x;
                frame->transform.y -= boneData->transform.y;
                frame->transform.skewX -= boneData->transform.skewX;
                frame->transform.skewY -= boneData->transform.skewY;
                frame->transform.scaleX -= boneData->transform.scaleX;
                frame->transform.scaleY -= boneData->transform.scaleY;

                if(!timeline->transformed)
                {
                    if(slotData)
                    {
                        frame->zOrder -= slotData->zOrder;
                    }
                }

                if(originTransform == 0)
                {
                    originTransform = &timeline->originTransform;
                    *originTransform = frame->transform;
                    originTransform->skewX = TransformUtil::formatRadian(originTransform->skewX);
                    originTransform->skewY = TransformUtil::formatRadian(originTransform->skewY);
                    originPivot = &timeline->originPivot;
                    originPivot->x = frame->pivot.x;
                    originPivot->y = frame->pivot.y;
                }

                frame->transform.x -= originTransform->x;
                frame->transform.y -= originTransform->y;
                frame->transform.skewX = TransformUtil::formatRadian(frame->transform.skewX - originTransform->skewX);
                frame->transform.skewY = TransformUtil::formatRadian(frame->transform.skewY - originTransform->skewY);
                frame->transform.scaleX -= originTransform->scaleX;
                frame->transform.scaleY -= originTransform->scaleY;

                if(!timeline->transformed)
                {
                    frame->pivot.x -= originPivot->x;
                    frame->pivot.y -= originPivot->y;
                }

                if(prevFrame)
                {
                    Number dLX = frame->transform.skewX - prevFrame->transform.skewX;

                    if(prevFrame->tweenRotate)
                    {

                        if(prevFrame->tweenRotate > 0)
                        {
                            if(dLX < 0)
                            {
                                frame->transform.skewX += TransformUtil::PI * 2;
                                frame->transform.skewY += TransformUtil::PI * 2;
                            }

                            if(prevFrame->tweenRotate > 1)
                            {
                                frame->transform.skewX += TransformUtil::PI * 2 * (prevFrame->tweenRotate - 1);
                                frame->transform.skewY += TransformUtil::PI * 2 * (prevFrame->tweenRotate - 1);
                            }
                        }
                        else
                        {
                            if(dLX > 0)
                            {
                                frame->transform.skewX -= TransformUtil::PI * 2;
                                frame->transform.skewY -= TransformUtil::PI * 2;
                            }

                            if(prevFrame->tweenRotate < 1)
                            {
                                frame->transform.skewX += TransformUtil::PI * 2 * (prevFrame->tweenRotate + 1);
                                frame->transform.skewY += TransformUtil::PI * 2 * (prevFrame->tweenRotate + 1);
                            }
                        }
                    }
                    else
                    {
                        frame->transform.skewX = prevFrame->transform.skewX + TransformUtil::formatRadian(frame->transform.skewX - prevFrame->transform.skewX);
                        frame->transform.skewY = prevFrame->transform.skewY + TransformUtil::formatRadian(frame->transform.skewY - prevFrame->transform.skewY);
                    }
                }

                prevFrame = frame;
            }
            timeline->transformed = true;
        }
    }

    void DBDataUtil::getTimelineTransform(TransformTimeline *timeline, Number position, DBTransform &retult)
    {
        std::vector<Frame*> &frameList = timeline->frameList;
        int i = frameList.size();

        TransformFrame* currentFrame;
        Number tweenEasing;
        Number progress;
        TransformFrame* nextFrame;
        while(i --)
        {
            currentFrame = static_cast<TransformFrame*>(frameList[i]);
            if(currentFrame->position <= position && currentFrame->position + currentFrame->duration > position)
            {
                tweenEasing = currentFrame->tweenEasing;
                if(i == frameList.size() - 1 || isNaN(tweenEasing) || position == currentFrame->position)
                {
                    retult = currentFrame->global;
                }
                else
                {
                    progress = (position - currentFrame->position) / currentFrame->duration;
                    if(tweenEasing)
                    {
                        progress = TimelineState::getEaseValue(progress, tweenEasing);
                    }

                    nextFrame = static_cast<TransformFrame*>(frameList[i + 1]);

                    retult.x = currentFrame->global.x +  (nextFrame->global.x - currentFrame->global.x) * progress;
                    retult.y = currentFrame->global.y +  (nextFrame->global.y - currentFrame->global.y) * progress;
                    retult.skewX = TransformUtil::formatRadian(currentFrame->global.skewX +  (nextFrame->global.skewX - currentFrame->global.skewX) * progress);
                    retult.skewY = TransformUtil::formatRadian(currentFrame->global.skewY +  (nextFrame->global.skewY - currentFrame->global.skewY) * progress);
                    retult.scaleX = currentFrame->global.scaleX +  (nextFrame->global.scaleX - currentFrame->global.scaleX) * progress;
                    retult.scaleY = currentFrame->global.scaleY +  (nextFrame->global.scaleY - currentFrame->global.scaleY) * progress;
                }
                break;
            }
        }
    }

    void DBDataUtil::addHideTimeline(AnimationData *animationData, ArmatureData *armatureData)
    {
        std::vector<BoneData*>& boneDataList = armatureData->boneDataList;
        int i = boneDataList.size();

        BoneData* boneData;
        String boneName;
        while(i --)
        {
            boneData = boneDataList[i];
            boneName = boneData->name;
            if(!animationData->getTimeline(boneName))
            {
                animationData->addTimeline(&TransformTimeline::HIDE_TIMELINE, boneName);
            }
        }
    }
};