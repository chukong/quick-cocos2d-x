//
//  DragonBonesHeaders.h
//  quickcocos2dx
//
//  Created by Wayne Dimart on 14-4-8.
//  Modified by zrong(zengrong.net) on 2014-04-23
//

#ifndef __DRAGONBONES_HEADERS_H__
#define __DRAGONBONES_HEADERS_H__

#include "renderer/CCDragonBones.h"  

#include "renderer/CCDBNode.h"
#include "renderer/CCDBFactory.h"
#include "renderer/CCDBAtlasNode.h"
#include "renderer/CCDBDisplayBridge.h"
#include "renderer/CCDBManager.h"
#include "renderer/CCDBTextureAtlas.h"

#include "Armature.h"
#include "Bone.h"
#include "Slot.h"

#include "factories/BaseFactory.h"
#include "display/IDisplayBridge.h"
#include "textures/ITextureAtlas.h"

#include "core/DBObject.h"
#include "core/DragonBones.h"

#include "animation/Animation.h"
#include "animation/AnimationState.h"
#include "animation/IAnimatable.h"
#include "animation/TimelineState.h"

#include "events/Event.h"
#include "events/AnimationEvent.h"
#include "events/ArmatureEvent.h"
#include "events/FrameEvent.h"
#include "events/SoundEvent.h"
#include "events/SoundEventManager.h"

#include "utils/DBGeometry.h"
#include "utils/ConstValues.h"
#include "utils/DBDataUtil.h"
#include "utils/BytesType.h"
#include "utils/preDB.h"
#include "utils/TransformUtil.h"

#include "objects/DBTransform.h"
#include "objects//dbtinyxml2.h"
#include "objects/DisplayData.h"
#include "objects/SlotData.h"
#include "objects/SkeletonData.h"
#include "objects/TransformFrame.h"
#include "objects/TransformTimeline.h"
#include "objects/SkinData.h"
#include "objects/XMLDataParser.h" 
#include "objects/TextureAtlasData.h"
#include "objects/Timeline.h"
#include "objects/AnimationData.h"
#include "objects/ArmatureData.h"
#include "objects/BoneData.h"
#include "objects/Frame.h"

#endif //__DRAGONBONES_HEADERS_H__
