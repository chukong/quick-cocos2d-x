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
#include <sstream>
#include "CCLuaEngine.h"
using namespace cocos2d;

namespace dragonBones
{
    
    CCDragonBones::CCDragonBones()
    :m_Armature(nullptr)
    {
        
    }
    
    CCDragonBones::~CCDragonBones()
    {
        removeAllEventListener();
        unregisterAllScriptHandler();
        CC_SAFE_DELETE(m_Armature);
    }
    
    CCDragonBones* CCDragonBones::create(Armature *arm)
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
    
    CCDragonBones* CCDragonBones::createByName(const String &armatureName,
                                               const String &animationName,
                                               const String &skeletonName,
                                               const String &textureAtlasName,
                                               const String &skinName)
    {
        Armature* pArm = CCDBManager::getInstance()
            ->getFactory().buildArmature( armatureName,
                              animationName,
                              skeletonName,
                              textureAtlasName,
                              skinName);
        if(pArm) return CCDragonBones::create(pArm);
        return nullptr;
    }
    
    CCDragonBones*	CCDragonBones::createByDir(const String &path,
                                               const String &armatureName,
                                               const String &animationName,
                                               const String &skeletonName,
                                               const String &textureAtlasName,
                                               const String &skinName)
    {
        Armature* pArm = CCDBManager::getInstance()
            ->createArmatureByDir(  path,
                                    armatureName,
                                    animationName,
                                    skeletonName,
                                    textureAtlasName,
                                    skinName);
        if(pArm) return CCDragonBones::create(pArm);
        return nullptr;
    }

    CCDragonBones*	CCDragonBones::createByFiles(const String &skeletonXMLFile,
                                                 const String &textureXMLFile,
                                                 const String &armatureName,
                                                 const String &animationName,
                                                 const String &skeletonName,
                                                 const String &textureAtlasName,
                                                 const String &skinName)
    {

        Armature* pArm = CCDBManager::getInstance()
            ->createArmatureByFiles(skeletonXMLFile,
                                    textureXMLFile,
                                    armatureName,
                                    animationName,
                                    skeletonName,
                                    textureAtlasName,
                                    skinName);
        if(pArm) return CCDragonBones::create(pArm);
        return nullptr;
    }

    void CCDragonBones::update(float dt)
    {
        if (m_Armature)
            m_Armature->advanceTime(dt);
    }

    CCNode* CCDragonBones::getDisplayNode()
    {
        return static_cast<CCDBNode*>(m_Armature->getDisplay())->getNode();
    }

    Armature* CCDragonBones::getArmature()
    {
        return m_Armature;
    }

    void CCDragonBones::gotoAndPlay(const String &animationName,
                                    Number fadeInTime,
                                    Number duration,
                                    Number loop,
                                    uint layer,
                                    const String &group,
                                    const String &fadeOutMode,
                                    bool displayControl,
                                    bool pauseFadeOut,
                                    bool pauseFadeIn)
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
                                    pauseFadeIn);
    }

    void CCDragonBones::initWithArmature(Armature*arm)
    {
        this->m_Armature = arm;
        this->schedule(schedule_selector(CCDragonBones::update), 0);
        this->addChild(static_cast<CCDBNode*>(m_Armature->getDisplay())->getNode());
    }

    void CCDragonBones::setBoneTexture(const char* boneName, const char* textureName, const char* textureAtlasName)
    {
		Object* clothesObj = CCDBManager::getInstance()->getFactory().getTextureDisplay(textureName, textureAtlasName);

        //CCLOG("CLOSE %d", clothesObj);

        Bone* bone = getArmature()->getBone(boneName);
        //CocosNode* oldClothesObj = static_cast<CocosNode*>(bone->getDisplay());
        bone->setDisplay(clothesObj);
    }

    Animation* CCDragonBones::getAnimation()
    {
        return m_Armature->getAnimation();
    }
    
    CCArray* CCDragonBones::getAnimationList()
    {
         std::vector<String> aniList = getAnimation()->getAnimationList();
        
        CCArray* aniArr = CCArray::createWithCapacity(static_cast<unsigned int>(aniList.size()));
        for (auto aniName : aniList)
        {
            aniArr->addObject(CCString::create(aniName.c_str()));
        }
        return aniArr;
    }

    void CCDragonBones::onExit()
    {
        this->unscheduleAllSelectors();
        CCNode::onExit();
    }
    
    String CCDragonBones::pointerToString(cocos2d::CCObject *pObj)
    {
        stringstream ss;
        ss<<pObj;
        return ss.str();
    }
    
    String CCDragonBones::funToString(int funId)
    {
        stringstream ss;
        ss<<funId;
        return String("db_script_") + ss.str();
    }
    
    void  CCDragonBones::addEventListener(const String &type, cocos2d::CCObject *pObj, SEL_CallFuncND selector)
    {
        auto &callbackList = _eventHandlers[type];
		callbackList.push_back(CocosCallback(pObj, selector));
        EventDispatcher::Function f = std::bind(&CCDragonBones::cocosEventBridge, this, std::placeholders::_1);
        String key = pointerToString(pObj);
        CCLOG("%s pointer value: %s", __FUNCTION__, key.c_str());
        m_Armature->addEventListener(type, f, key);
    }
    
    bool CCDragonBones::hasEventListener(const String &type)
    {
        return m_Armature->hasEventListener(type) &&
            _eventHandlers.find(type) != _eventHandlers.end();
    }
    
    bool CCDragonBones::hasEventListener(const String &type, cocos2d::CCObject *pObj)
    {
        auto iter = _eventHandlers.find(type);
        if(iter == _eventHandlers.end()) return false;
        
        for(auto &iterCallback : iter->second)
        {
            if(iterCallback.first == pObj)
            {
                return m_Armature->hasEventListener(type, pointerToString(pObj));
            }
        }
        return false;
    }
    
    void CCDragonBones::removeEventListener(const String &type, cocos2d::CCObject *pObj)
    {
        m_Armature->removeEventListener(type, pointerToString(pObj));
        
        auto iter = _eventHandlers.find(type);
        if(iter != _eventHandlers.end())
        {
            auto &funList = iter->second;
            for(auto iterCallback = funList.begin() ; iterCallback != funList.end() ; )
            {
				if (iterCallback->first == pObj)
                {
                    iterCallback = funList.erase(iterCallback);
                }
                else
                {
                    iterCallback ++;
                }
            }
        }
    }
    
    void CCDragonBones::removeAllEventListener()
    {
        m_Armature->removeAllEventListener();
        _eventHandlers.clear();
    }
    
    void CCDragonBones::cocosEventBridge(Event *e)
    {
        string evtType = e->getType();
        auto eventIter = _eventHandlers.find(evtType);
        if(eventIter != _eventHandlers.end())
        {
            for(auto eventIterCallback : eventIter->second)
            {
                (eventIterCallback.first->*eventIterCallback.second)(this, e);
            }
        }
        
        //cocos2d::CCLog("dragonBones::EventDispatcher.dispatchEvent %s", event->getType());
        // For script engine
        auto scriptIter = _scriptHandlers.find(evtType);
        
        if (_scriptHandlers.end() != scriptIter)
        {
            cocos2d::CCLuaEngine* luaEngine = dynamic_cast<cocos2d::CCLuaEngine*>(cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine());
            if (luaEngine)
            {
                /* CCArray* __param = CCArray::create();
                 __param->addObject(CCInteger::create(evtType));
                 __param->addObject(CCString::create(movId));
                 __luaEngine->executeEventWithArgs(m_nScriptMovementHandler, __param);*/
                
                cocos2d::CCLuaStack *pStack = luaEngine->getLuaStack();
                int luaHandler = scriptIter->second;
                if (!luaHandler) return;
                pStack->pushCCObject(e, "Event");
                pStack->executeFunctionByHandler(luaHandler, 1);
                pStack->clean();
            }
        }
    }
    
    void CCDragonBones::registerScriptHandler(int funId, String type)
    {
        cocos2d::CCLog("%s %d %s", __FUNCTION__, funId, type.c_str());
        this->unregisterScriptHandler(type);
        
        EventDispatcher::Function f = std::bind(&CCDragonBones::cocosEventBridge, this, std::placeholders::_1);
        String key = funToString(funId);
        
        CCLOG("%s funId value: %s", __FUNCTION__, key.c_str());
        m_Armature->addEventListener(type, f, key);
        _scriptHandlers[type] = funId;
    }
    
    bool CCDragonBones::hasScriptHandler(const String &type)
    {
        return _scriptHandlers.find(type) != _scriptHandlers.end() &&
            m_Armature->hasEventListener(type);
    }
    
    void CCDragonBones::unregisterScriptHandler(String type)
    {
        m_Armature->removeEventListener(type);
        auto iter = _scriptHandlers.find(type);
        if (iter != _scriptHandlers.end())
        {
            _scriptHandlers.erase(iter);
        }
    }
    
    void CCDragonBones::unregisterAllScriptHandler()
    {
        _scriptHandlers.clear();
        m_Armature->removeAllEventListener();
    }
    
    int CCDragonBones::getScriptHandler(String type)
    {
        auto iter = _scriptHandlers.find(type);
        if (_scriptHandlers.end() != iter)
        {
            return iter->second;
        }
        return 0;
    }
}