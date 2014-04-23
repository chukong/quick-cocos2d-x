//
//  CCDragonBones.cpp
//  quickcocos2dx
//
//  Created by Wayne Dimart on 14-4-18.
//  Copyright (c) 2014 . All rights reserved.
//  Modified by zrong(zengrong.net) on 2014-04-22
//

#include "CCDragonBones.h"
#include "cocos2d.h"
#include "DragonBonesHeaders.h"
using namespace cocos2d;

namespace dragonBones
{
    Armature* CCDragonBones::buildArmature(const char* skeletonXMLFile,
        const char* textureXMLFile,
        const char* dragonBonesName,
        const char* armatureName,
        const char* animationName)
    {
        Cocos2dxFactory *fac = Cocos2dxFactory::getInstance();
        fac->loadSkeletonFile(skeletonXMLFile);
        fac->loadTextureAtlasFile(textureXMLFile);
        return fac->buildArmature(armatureName, animationName, dragonBonesName);
    }

    CCDragonBones*	CCDragonBones::create(const char* skeletonXMLFile,
        const char* dragonBonesName,
        const char* armatureName)
    {
        return CCDragonBones::create(skeletonXMLFile,
            "texture.xml",
            dragonBonesName,
            armatureName,
            "");
    }

    CCDragonBones*	CCDragonBones::create(const char* skeletonXMLFile,
        const char* textureXMLFile,
        const char* dragonBonesName,
        const char* armatureName,
        const char* animationName)
    {
        CCDragonBones* pNew = new CCDragonBones();
        if (pNew && pNew->init())
        {
            Armature*arm = CCDragonBones::buildArmature(skeletonXMLFile,
                textureXMLFile,
                dragonBonesName,
                armatureName,
                animationName);
            pNew->initWithArmature(arm);
            pNew->autorelease();
            return pNew;
        }
        CC_SAFE_DELETE(pNew);
        return NULL;
    }

    CCDragonBones* CCDragonBones::create(Armature*arm)
    {
        CCDragonBones* pNew = new CCDragonBones();
        if (pNew && pNew->init())
        {
            pNew->initWithArmature(arm);
            pNew->autorelease();
            return pNew;
        }
        CC_SAFE_DELETE(pNew);
        return NULL;
    }

    void CCDragonBones::update(float dt)
    {
        if (m_Armature)
            m_Armature->advanceTime(dt);
    }

    CCNode* CCDragonBones::getDisplayNode()
    {
        return static_cast<CocosNode*>(m_Armature->getDisplay())->getNode();
    }

    Armature* CCDragonBones::getArmature()
    {
        return m_Armature;
    }

    void  CCDragonBones::addEventListener(const String &type, const String &key, cocos2d::CCObject*pObj, SEL_CallFuncND callback)
    {
        m_Caller = pObj;
        m_Callback = callback;
        std::function<void(Event*)> f = std::bind(&CCDragonBones::eventBridge, this, std::placeholders::_1);
        m_Armature->addEventListener(type, f, key);
    }

    bool CCDragonBones::hasEventListener(const String &type)
    {
        return m_Armature->hasEventListener(type);
    }
    void CCDragonBones::removeEventListener(const String &type, const std::string &key)
    {
        m_Armature->removeEventListener(type, key);
    }
    void CCDragonBones::dispatchEvent(Event *event)
    {
        m_Armature->dispatchEvent(event);
    }

    void CCDragonBones::eventBridge(Event*e){
        (m_Caller->*m_Callback)(this, e);
    }

    void CCDragonBones::gotoAndPlay(
        const String &animationName,
        Number fadeInTime,
        Number duration,
        Number loop,
        uint layer,
        const String &group,
        const String &fadeOutMode,
        bool displayControl,
        bool pauseFadeOut,
        bool pauseFadeIn
        )
    {
        getAnimation()->gotoAndPlay(animationName,
            fadeInTime,
            duration,
            loop,
            layer,
            group,
            fadeOutMode,
            displayControl,
            pauseFadeOut,
            pauseFadeIn
            );
    }

    void CCDragonBones::initWithArmature(Armature*arm)
    {
        this->m_Armature = arm;
        this->schedule(schedule_selector(CCDragonBones::update), 0);
        this->addChild(static_cast<CocosNode*>(m_Armature->getDisplay())->node);
    }

    void CCDragonBones::setBoneTexture(const char* boneName, const char* textureName, const char* textureAtlasName)
    {

        Cocos2dxFactory* fac = Cocos2dxFactory::getInstance();
        Object* clothesObj = fac->getTextureDisplay(textureName, textureAtlasName);

        //CCLOG("CLOSE %d", clothesObj);

        Bone* bone = getArmature()->getBone(boneName);
        CocosNode* oldClothesObj = static_cast<CocosNode*>(bone->getDisplay());
        bone->setDisplay(clothesObj);
    }

    Animation* CCDragonBones::getAnimation()
    {
        return m_Armature->getAnimation();
    }

    void CCDragonBones::onExit()
    {
        this->unscheduleAllSelectors();
    }
}