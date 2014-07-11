#include "XMLDataParser.h"
#include "utils/ConstValues.h"
#include "core/DragonBones.h"
#include "utils/DBDataUtil.h"
#include <stdexcept>
namespace dragonBones
{    

    TextureAtlasData* XMLDataParser::parseTextureAtlasData(const dragonBones::XMLElement *rootElement, Number scale)
    {
        TextureAtlasData* textureAtlasData = new TextureAtlasData();
        textureAtlasData->name = rootElement->Attribute(ConstValues::A_NAME.c_str());
        textureAtlasData->imagePath = rootElement->Attribute(ConstValues::A_IMAGE_PATH.c_str());
        for(const dragonBones::XMLElement* subTextureXML = rootElement->FirstChildElement(ConstValues::SUB_TEXTURE.c_str()) ; subTextureXML ; subTextureXML = subTextureXML->NextSiblingElement(ConstValues::SUB_TEXTURE.c_str()))
        {
            String subTextureName = subTextureXML->Attribute(ConstValues::A_NAME.c_str());
            Rectangle subTextureData;
            subTextureData.x = int(subTextureXML->IntAttribute(ConstValues::A_X.c_str()) / scale);
            subTextureData.y = int(subTextureXML->IntAttribute(ConstValues::A_Y.c_str()) / scale);
            subTextureData.width = int(subTextureXML->IntAttribute(ConstValues::A_WIDTH.c_str()) / scale);
            subTextureData.height = int(subTextureXML->IntAttribute(ConstValues::A_HEIGHT.c_str()) / scale);

            textureAtlasData->addRect(subTextureName , subTextureData);
        }

        return textureAtlasData;
    }

    /**
    * Parse the SkeletonData.
    * @param    xml The SkeletonData xml to parse.
    * @return A SkeletonData instance.
    */
    SkeletonData *XMLDataParser::parseSkeletonData(const dragonBones::XMLElement *rootElement)
    {
        String version = rootElement->Attribute(ConstValues::A_VERSION.c_str());
        if(version != DragonBones::DATA_VERSION)
        {
            throw std::invalid_argument("Nonsupport version!");
        }

        uint frameRate = rootElement->IntAttribute(ConstValues::A_FRAME_RATE.c_str());

        SkeletonData *data = new SkeletonData();
        data->name = rootElement->Attribute(ConstValues::A_NAME.c_str());
        for(const dragonBones::XMLElement* armatureXML = rootElement->FirstChildElement(ConstValues::ARMATURE.c_str()) ; armatureXML ; armatureXML = armatureXML->NextSiblingElement(ConstValues::ARMATURE.c_str()))
        {
            data->addArmatureData(parseArmatureData(armatureXML, data, frameRate));
        }

        return data;
    }

    ArmatureData *XMLDataParser::parseArmatureData(const dragonBones::XMLElement *armatureXML, SkeletonData *data, uint frameRate)
    {
        ArmatureData *armatureData = new ArmatureData();
        armatureData->name = armatureXML->Attribute(ConstValues::A_NAME.c_str());

        for(const dragonBones::XMLElement* boneXML = armatureXML->FirstChildElement(ConstValues::BONE.c_str()) ; boneXML ; boneXML = boneXML->NextSiblingElement(ConstValues::BONE.c_str()))
        {
            armatureData->addBoneData(parseBoneData(boneXML));
        }

        for(const dragonBones::XMLElement* skinXML = armatureXML->FirstChildElement(ConstValues::SKIN.c_str()) ; skinXML ; skinXML = skinXML->NextSiblingElement(ConstValues::SKIN.c_str()))
        {
            armatureData->addSkinData(parseSkinData(skinXML, data));
        }

        DBDataUtil::transformArmatureData(armatureData);
        armatureData->sortBoneDataList();

        for(const dragonBones::XMLElement* animationXML = armatureXML->FirstChildElement(ConstValues::ANIMATION.c_str()) ; animationXML ; animationXML = animationXML->NextSiblingElement(ConstValues::ANIMATION.c_str()))
        {
            armatureData->addAnimationData(parseAnimationData(animationXML, armatureData, frameRate));
        }

        return armatureData;
    }

    BoneData *XMLDataParser::parseBoneData(const dragonBones::XMLElement *boneXML)
    {
        BoneData *boneData = new BoneData();
        boneData->name = boneXML->Attribute(ConstValues::A_NAME.c_str());
        const char *parent = boneXML->Attribute(ConstValues::A_PARENT.c_str());
        if(parent)
        {
            boneData->parent = parent;
        }
        boneData->length = Number(boneXML->DoubleAttribute(ConstValues::A_LENGTH.c_str()));
        const char *inheritScale = boneXML->Attribute(ConstValues::A_SCALE_MODE.c_str());
        if (inheritScale)
        {
            boneData->scaleMode = atoi(inheritScale);
        }

        const char* fixedRotation = boneXML->Attribute(ConstValues::A_FIXED_ROTATION.c_str());
        if(fixedRotation)
        {
            if(strcmp(fixedRotation , "0") == 0
                || strcmp(fixedRotation , "false") == 0
                || strcmp(fixedRotation , "no") == 0
                || strcmp(fixedRotation , "") == 0
                )
            {
                boneData->fixedRotation = false;
            }
            else
            {
                boneData->fixedRotation = true;
            }
        }
        else
        {
            boneData->fixedRotation = false;
        }

        parseTransform(boneXML->FirstChildElement(ConstValues::TRANSFORM.c_str()), &boneData->global);
        boneData->transform = boneData->global;

        return boneData;
    }

    SkinData *XMLDataParser::parseSkinData(const dragonBones::XMLElement *skinXML, SkeletonData *data)
    {
        SkinData *skinData = new SkinData();
        skinData->name = skinXML->Attribute(ConstValues::A_NAME.c_str());

        for(const dragonBones::XMLElement* slotXML = skinXML->FirstChildElement(ConstValues::SLOT.c_str()) ; slotXML ; slotXML = slotXML->NextSiblingElement(ConstValues::SLOT.c_str()))
        {
            skinData->addSlotData(parseSlotData(slotXML, data));
        }

        return skinData;
    }

    SlotData* XMLDataParser::parseSlotData(const dragonBones::XMLElement *slotXML, SkeletonData *data)
    {
        SlotData *slotData = new SlotData();
        slotData->name = slotXML->Attribute(ConstValues::A_NAME.c_str());
        slotData->parent = slotXML->Attribute(ConstValues::A_PARENT.c_str());
        slotData->zOrder = Number(slotXML->DoubleAttribute(ConstValues::A_Z_ORDER.c_str()));
        const char *blendMode = slotXML->Attribute(ConstValues::A_BLENDMODE.c_str());
        if(blendMode)
        {
            slotData->blendMode = blendMode;
        }
        else
        {
            slotData->blendMode = "normal";
        }
        for(const dragonBones::XMLElement* displayXML = slotXML->FirstChildElement(ConstValues::DISPLAY.c_str()) ; displayXML ; displayXML = displayXML->NextSiblingElement(ConstValues::DISPLAY.c_str()))
        {
            slotData->addDisplayData(parseDisplayData(displayXML, data));
        }

        return slotData;
    }

    DisplayData *XMLDataParser::parseDisplayData(const dragonBones::XMLElement *displayXML, SkeletonData *data)
    {
        DisplayData *displayData = new DisplayData();
        displayData->name = displayXML->Attribute(ConstValues::A_NAME.c_str());
        displayData->type = displayXML->Attribute(ConstValues::A_TYPE.c_str());

        displayData->pivot = data->addSubTexturePivot(
            0, 
            0, 
            displayData->name
            );

        parseTransform(displayXML->FirstChildElement(ConstValues::TRANSFORM.c_str()), &displayData->transform, &displayData->pivot);

        return displayData;
    }

    /** @private */
    AnimationData *XMLDataParser::parseAnimationData(const dragonBones::XMLElement *animationXML, ArmatureData *armatureData, uint frameRate)
    {
        AnimationData *animationData = new AnimationData();
        animationData->name = animationXML->Attribute(ConstValues::A_NAME.c_str());
        animationData->frameRate = frameRate;
        animationData->loop = int(animationXML->IntAttribute(ConstValues::A_LOOP.c_str()));
        animationData->setFadeInTime(Number(animationXML->DoubleAttribute(ConstValues::A_FADE_IN_TIME.c_str())));
        animationData->duration = Number(animationXML->DoubleAttribute(ConstValues::A_DURATION.c_str())) / (Number)frameRate;
        animationData->scale = Number(animationXML->DoubleAttribute(ConstValues::A_SCALE.c_str()));
        if(strcmp(animationXML->Attribute(ConstValues::A_TWEEN_EASING.c_str()) , "NaN") == 0)
        {
            animationData->tweenEasing = NaN;
        }
        else
        {
            animationData->tweenEasing = Number(animationXML->DoubleAttribute(ConstValues::A_TWEEN_EASING.c_str()));
        }

        parseTimeline(animationXML, animationData, parseMainFrame, frameRate);

        TransformTimeline *timeline = 0;
        String timelineName;
        for(const dragonBones::XMLElement* timelineXML = animationXML->FirstChildElement(ConstValues::TIMELINE.c_str()) ; timelineXML ; timelineXML = timelineXML->NextSiblingElement(ConstValues::TIMELINE.c_str()))
        {
            timeline = parseTransformTimeline(timelineXML, animationData->duration, frameRate);
            timelineName = timelineXML->Attribute(ConstValues::A_NAME.c_str());
            animationData->addTimeline(timeline, timelineName);
        }

        DBDataUtil::addHideTimeline(animationData, armatureData);
        DBDataUtil::transformAnimationData(animationData, armatureData);

        return animationData;
    }

    void XMLDataParser::parseTimeline(const dragonBones::XMLElement *timelineXML, Timeline *timeline, FrameParser frameParser, uint frameRate)
    {
        Number position = 0;
        Frame *frame = 0;
        for(const dragonBones::XMLElement* frameXML = timelineXML->FirstChildElement(ConstValues::FRAME.c_str()) ; frameXML ; frameXML = frameXML->NextSiblingElement(ConstValues::FRAME.c_str()))
        {
            frame = frameParser(frameXML, frameRate);
            frame->position = position;
            timeline->addFrame(frame);
            position += frame->duration;
        }
        if(frame)
        {
            frame->duration = timeline->duration - frame->position;
        }
    }

    TransformTimeline *XMLDataParser::parseTransformTimeline(const dragonBones::XMLElement *timelineXML, Number duration, uint frameRate)
    {
        TransformTimeline *timeline = new TransformTimeline();
        timeline->duration = duration;

        parseTimeline(timelineXML, timeline, parseTransformFrame, frameRate);

        timeline->scale = Number(timelineXML->DoubleAttribute(ConstValues::A_SCALE.c_str()));
        timeline->offset = Number(timelineXML->DoubleAttribute(ConstValues::A_OFFSET.c_str()));

        return timeline;
    }

    void XMLDataParser::parseFrame(const dragonBones::XMLElement *frameXML, Frame *frame, uint frameRate)
    {
        frame->duration = Number(frameXML->DoubleAttribute(ConstValues::A_DURATION.c_str())) / frameRate;
        const char *action = frameXML->Attribute(ConstValues::A_ACTION.c_str());
        if(action)
        {
            frame->action = action;
        }
        const char *event = frameXML->Attribute(ConstValues::A_EVENT.c_str());
        if(event)
        {
            frame->event = event;
        }
        const char *sound = frameXML->Attribute(ConstValues::A_SOUND.c_str());
        if(sound)
        {
            frame->sound = sound;
        }
    }

    Frame *XMLDataParser::parseMainFrame(const dragonBones::XMLElement *frameXML, uint frameRate)
    {
        Frame *frame = new Frame();
        parseFrame(frameXML, frame, frameRate);
        return frame;
    }

    Frame *XMLDataParser::parseTransformFrame(const dragonBones::XMLElement *frameXML, uint frameRate)
    {
        TransformFrame *frame = new TransformFrame();
        parseFrame(frameXML, frame, frameRate);

        frame->visible = uint(frameXML->IntAttribute(ConstValues::A_HIDE.c_str())) != 1;

        //frame->tweenEasing = Number(frameXML->DoubleAttribute(ConstValues::A_TWEEN_EASING.c_str()));
	const char * tweenEasing = frameXML->Attribute(ConstValues::A_TWEEN_EASING.c_str());
	if(tweenEasing  && strcmp( tweenEasing , "NaN" ) == 0)
        {
            frame->tweenEasing = NaN;
        }
        else
        {
            frame->tweenEasing = Number(frameXML->DoubleAttribute(ConstValues::A_TWEEN_EASING.c_str()));
        }

        frame->tweenRotate = int(frameXML->DoubleAttribute(ConstValues::A_TWEEN_ROTATE.c_str()));
        frame->displayIndex = int(frameXML->DoubleAttribute(ConstValues::A_DISPLAY_INDEX.c_str()));
        //
        frame->zOrder = Number(frameXML->DoubleAttribute(ConstValues::A_Z_ORDER.c_str()));

        parseTransform(frameXML->FirstChildElement(ConstValues::TRANSFORM.c_str()), &frame->global, &frame->pivot);
        frame->transform = frame->global;

        const dragonBones::XMLElement * colorTransformXML = frameXML->FirstChildElement(ConstValues::COLOR_TRANSFORM.c_str());
        if(colorTransformXML)
        {
            frame->color = new ColorTransform();
            frame->color->alphaOffset = Number(colorTransformXML->DoubleAttribute(ConstValues::A_ALPHA_OFFSET.c_str()));
            frame->color->redOffset = Number(colorTransformXML->DoubleAttribute(ConstValues::A_RED_OFFSET.c_str()));
            frame->color->greenOffset = Number(colorTransformXML->DoubleAttribute(ConstValues::A_GREEN_OFFSET.c_str()));
            frame->color->blueOffset = Number(colorTransformXML->DoubleAttribute(ConstValues::A_BLUE_OFFSET.c_str()));

            frame->color->alphaMultiplier = Number(colorTransformXML->DoubleAttribute(ConstValues::A_ALPHA_MULTIPLIER.c_str())) * 0.01f;
            frame->color->redMultiplier = Number(colorTransformXML->DoubleAttribute(ConstValues::A_RED_MULTIPLIER.c_str())) * 0.01f;
            frame->color->greenMultiplier = Number(colorTransformXML->DoubleAttribute(ConstValues::A_GREEN_MULTIPLIER.c_str())) * 0.01f;
            frame->color->blueMultiplier = Number(colorTransformXML->DoubleAttribute(ConstValues::A_BLUE_MULTIPLIER.c_str())) * 0.01f;
        }

        return frame;
    }

    void XMLDataParser::parseTransform(const dragonBones::XMLElement *transformXML, DBTransform *transform, Point *pivot)
    {
        if(transformXML)
        {
            if(transform)
            {
                transform->x = Number(transformXML->DoubleAttribute(ConstValues::A_X.c_str()));
                transform->y = Number(transformXML->DoubleAttribute(ConstValues::A_Y.c_str()));
                transform->skewX = Number(transformXML->DoubleAttribute(ConstValues::A_SKEW_X.c_str())) * ConstValues::ANGLE_TO_RADIAN;
                transform->skewY = Number(transformXML->DoubleAttribute(ConstValues::A_SKEW_Y.c_str())) * ConstValues::ANGLE_TO_RADIAN;
                transform->scaleX = Number(transformXML->DoubleAttribute(ConstValues::A_SCALE_X.c_str()));
                transform->scaleY = Number(transformXML->DoubleAttribute(ConstValues::A_SCALE_Y.c_str()));
            }
            if(pivot)
            {
                pivot->x = Number(transformXML->DoubleAttribute(ConstValues::A_PIVOT_X.c_str()));
                pivot->y = Number(transformXML->DoubleAttribute(ConstValues::A_PIVOT_Y.c_str()));
            }
        }
    }
}
