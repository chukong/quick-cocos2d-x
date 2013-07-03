/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CSDisplayFactory.h"
#include "CSDatas.h"
#include "CSBone.h"
#include "CSArmature.h"
#include "CSSkin.h"
#include "CSSpriteFrameCacheHelper.h"
#include "CSArmatureDataManager.h"
#include "CSShaderNode.h"
#include "CSTransformHelp.h"

using namespace cocos2d;

namespace cs {

void CS_DISPLAY_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
	switch(displayData->displayType)
	{
	case CS_DISPLAY_SPRITE:
		CS_DISPLAY_SPRITE_ADD(bone, decoDisplay, displayData); break;
	case  CS_DISPLAY_PARTICLE:
		CS_DISPLAY_PARTICLE_ADD(bone, decoDisplay, displayData); break;
	case  CS_DISPLAY_ARMATURE:
		CS_DISPLAY_ARMATURE_ADD(bone, decoDisplay, displayData); break;
	default:
		break;
	}
}

void CS_DISPLAY_CREATE(Bone *bone, DecorativeDisplay *decoDisplay)
{
	switch(decoDisplay->getDisplayData()->displayType)
	{
	case CS_DISPLAY_SPRITE:
		CS_DISPLAY_SPRITE_CREATE(bone, decoDisplay); break;
	case CS_DISPLAY_PARTICLE:
		CS_DISPLAY_PARTICLE_CREATE(bone, decoDisplay); break; 
	case CS_DISPLAY_ARMATURE:
		CS_DISPLAY_ARMATURE_CREATE(bone, decoDisplay); break;
	default:
		break;
	}
}

void CS_DISPLAY_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
	CS_RETURN_IF(!decoDisplay);

#if ENABLE_PHYSICS_DETECT
	if (dirty)
	{
		ColliderDetector *detector = decoDisplay->getColliderDetector();
		if (detector)
		{
			CCAffineTransform t = CCAffineTransformConcat(bone->nodeToArmatureTransform(), bone->getArmature()->nodeToWorldTransform());
			detector->updateTransform(t);
		}
	}
#endif
	
	
	switch(decoDisplay->getDisplayData()->displayType)
	{
	case CS_DISPLAY_SPRITE:
		CS_DISPLAY_SPRITE_UPDATE(bone, decoDisplay, dt, dirty); break;
	case CS_DISPLAY_PARTICLE:
		CS_DISPLAY_PARTICLE_UPDATE(bone, decoDisplay, dt, dirty); break; 
	case CS_DISPLAY_ARMATURE:
		CS_DISPLAY_ARMATURE_UPDATE(bone, decoDisplay, dt, dirty); break;
	default:
		break;
	}
}



void CS_DISPLAY_SPRITE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
	SpriteDisplayData *sdp = SpriteDisplayData::create();
	sdp->copy((SpriteDisplayData*)displayData);
	decoDisplay->setDisplayData(sdp);
	CS_DISPLAY_SPRITE_CREATE(bone, decoDisplay);
}

void CS_DISPLAY_SPRITE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay)
{
	Skin *skin = NULL;

	SpriteDisplayData *displayData = (SpriteDisplayData*)decoDisplay->getDisplayData();

	//! remove .xxx
	std::string textureName = displayData->displayName;
	size_t startPos = textureName.find_last_of(".");

	if(startPos != std::string::npos)
	{
		textureName = textureName.erase(startPos);
	}

	//! create display
	if(textureName.compare("") == 0)
	{
		skin = Skin::create();
	}
	else
	{
		skin = Skin::createWithSpriteFrameName((textureName + ".png").c_str());
	}

	CCTextureAtlas *atlas = SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->getTextureAtlas((textureName + ".png").c_str());
	skin->setTextureAtlas(atlas);

	TextureData *textureData = ArmatureDataManager::sharedArmatureDataManager()->getTextureData(textureName.c_str());
	if(textureData)
	{
		//! Init display anchorPoint£¬ every Texture have a anchor point
		skin->setAnchorPoint(ccp( textureData->pivotX, textureData->pivotY));
	}

	skin->setBone(bone);
	skin->setSkinData(*bone->getBoneData());

	decoDisplay->setDisplay(skin);

#if ENABLE_PHYSICS_DETECT
	if (textureData && textureData->contourDataList.count() > 0)
	{

		//! create ContourSprite
		ColliderDetector *colliderDetector = ColliderDetector::create(bone);
		colliderDetector->addContourDataList(&textureData->contourDataList);

		decoDisplay->setColliderDetector(colliderDetector);
	}
#endif
}

void CS_DISPLAY_SPRITE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
	Skin *skin = (Skin*)decoDisplay->getDisplay();
	skin->updateTransform();
}


void CS_DISPLAY_ARMATURE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
	ArmatureDisplayData *adp = ArmatureDisplayData::create(); ;
	adp->copy((ArmatureDisplayData*)displayData);
	decoDisplay->setDisplayData(adp);

	CS_DISPLAY_ARMATURE_CREATE(bone, decoDisplay);
}
void CS_DISPLAY_ARMATURE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay)
{
	ArmatureDisplayData *displayData = (ArmatureDisplayData*)decoDisplay->getDisplayData();
    
    Armature *armature = Armature::create(displayData->displayName.c_str(), bone);
    
    /*
     *  because this bone have called this name, so armature should change it's name, or it can't add to
     *  Armature's bone children.
     */
    armature->setName((bone->getName() + "_armatureChild").c_str());
    
	decoDisplay->setDisplay(armature);
}
void CS_DISPLAY_ARMATURE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
	CS_RETURN_IF(!dirty);

	Armature *armature = bone->getChildArmature();
	if(armature)
	{
		armature->sortAllChildren();
	 	armature->update(dt);
	}
}



void CS_DISPLAY_PARTICLE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
	ParticleDisplayData *adp = ParticleDisplayData::create(); ;
	adp->copy((ParticleDisplayData*)displayData);
	decoDisplay->setDisplayData(adp);

	CS_DISPLAY_PARTICLE_CREATE(bone, decoDisplay);
}
void CS_DISPLAY_PARTICLE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay)
{
	ParticleDisplayData *displayData = (ParticleDisplayData*)decoDisplay->getDisplayData();
	CCParticleSystem *system = CCParticleSystemQuad::create(displayData->plist.c_str());
	decoDisplay->setDisplay(system);
}
void CS_DISPLAY_PARTICLE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
	CCParticleSystem *system = (CCParticleSystem*)decoDisplay->getDisplay();
	Node node;
	TransformHelp::matrixToNode(bone->nodeToArmatureTransform(), node);
	system->setPosition(node.x, node.y);
	system->setScaleX(node.scaleX);
	system->setScaleY(node.scaleY);
	system->update(dt);
}



void CS_DISPLAY_SHADER_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
	ShaderDisplayData *sdp = ShaderDisplayData::create();
	sdp->copy((ShaderDisplayData*)displayData);
	decoDisplay->setDisplayData(sdp);

	CS_DISPLAY_SHADER_CREATE(bone, decoDisplay);
}
void CS_DISPLAY_SHADER_CREATE(Bone *bone, DecorativeDisplay *decoDisplay)
{
	ShaderDisplayData *displayData = (ShaderDisplayData*)decoDisplay->getDisplayData();
	ShaderNode *sn = ShaderNode::shaderNodeWithVertex(displayData->vert.c_str(), displayData->frag.c_str());
	decoDisplay->setDisplay(sn);
}

}