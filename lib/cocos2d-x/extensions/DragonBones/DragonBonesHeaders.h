//
//  DragonBonesHeaders.h
//  quickcocos2dx
//
//  Created by Wayne Dimart on 14-4-8.
//  Modified by zrong(zengrong.net) on 2014-04-23
//

#ifndef __DRAGONBONES_HEADERS__
#define __DRAGONBONES_HEADERS__

#include "renderer/CCDragonBones.h"  

#include "renderer/Cocos2dxAtlasNode.h"
#include "renderer/Cocos2dxDisplayBridge.h"
#include "renderer/Cocos2dxFactory.h"
#include "renderer/Cocos2dxTextureAtlas.h"

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

#include "utils/ColorTransform.h"
#include "utils/ConstValues.h"
#include "utils/DBDataUtil.h"
#include "utils/BytesType.h"
#include "utils/Matrix.h"
#include "utils/Point.h"
#include "utils/preDB.h"
#include "utils/Rectangle.h"
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

#endif //__DRAGONBONES_HEADERS__
