#ifndef __XML_DATA_PARSER_H__
#define __XML_DATA_PARSER_H__
#include "core/DragonBones.h"

#include "utils/preDB.h"
#include "objects/dbtinyxml2.h"

#include "objects/SkeletonData.h"
#include "objects/TransformFrame.h"

#include "objects/TextureAtlasData.h"

namespace dragonBones
{
    /**
     * The XMLDataParser class parses xml data from dragonBones generated maps.
     */
    class XMLDataParser
    {
    public:
        
        TextureAtlasData* parseTextureAtlasData(const dragonBones::XMLElement *rootElement, Number scale = 1);
        
        /**
         * Parse the SkeletonData.
         * @param    xml The SkeletonData xml to parse.
         * @return A SkeletonData instance.
         */
        SkeletonData *parseSkeletonData(const dragonBones::XMLElement *rootElement);
    private:
        
        ArmatureData *parseArmatureData(const dragonBones::XMLElement *armatureXML, SkeletonData *data, uint frameRate);
        
        BoneData *parseBoneData(const dragonBones::XMLElement *boneXML);
        
        SkinData *parseSkinData(const dragonBones::XMLElement *skinXML, SkeletonData *data);
        
        SlotData *parseSlotData(const dragonBones::XMLElement *slotXML, SkeletonData *data);
        
        DisplayData *parseDisplayData(const dragonBones::XMLElement *displayXML, SkeletonData *data);
        
        /** @private */
        static AnimationData *parseAnimationData(const dragonBones::XMLElement *animationXML, ArmatureData *armatureData, uint frameRate);
        
        typedef Frame* (*FrameParser)(const dragonBones::XMLElement *,uint);


        static void parseTimeline(const dragonBones::XMLElement *timelineXML, Timeline *timeline, FrameParser frameParser, uint frameRate);
        
        static TransformTimeline *parseTransformTimeline(const dragonBones::XMLElement *timelineXML, Number duration, uint frameRate);
        
        static void parseFrame(const dragonBones::XMLElement *frameXML, Frame *frame, uint frameRate);
        
        static Frame *parseMainFrame(const dragonBones::XMLElement *frameXML, uint frameRate);
        
        static Frame *parseTransformFrame(const dragonBones::XMLElement *frameXML, uint frameRate);
        
        static void parseTransform(const dragonBones::XMLElement *transformXML, DBTransform *transform, Point *pivot = 0);
    };
};
#endif // __XML_DATA_PARSER_H__
