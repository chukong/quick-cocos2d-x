//
//  CCDragonBones.h
//
//
//  Created by Wayne Dimart on 14-4-18.
//  Copyright (c) 2014 . All rights reserved.
//	Modified by zrong(zengrong.net) on 2014-04-22
//

#ifndef __CCDRAGONBONES__
#define __CCDRAGONBONES__

#include <iostream>
#include "utils/preDB.h"
#include "animation/Animation.h"
#include "events/Event.h"

namespace dragonBones {
    class Armature;
    class CCDragonBones:public cocos2d::CCNode {
    public:
        CCDragonBones();
        virtual ~CCDragonBones();

        static CCDragonBones* create(Armature*arm);
        static CCDragonBones* createByName( const String &armatureName,
                                            const String &animationName="",
                                            const String &skeletonName="",
                                            const String &textureAtlasName="",
                                            const String &skinName="");

        static CCDragonBones* createByDir(	const String &path,
                                            const String &armatureName,
                                            const String &animationName="",
                                            const String &skeletonName="",
                                            const String &textureAtlasName="",
                                            const String &skinName="");
								
        static CCDragonBones* createByFiles(const String &skeletonXMLFile,
                                            const String &textureXMLFile,
                                            const String &armatureName,
                                            const String &animationName="",
                                            const String &skeletonName="",
                                            const String &textureAtlasName="",
                                            const String &skinName="");

        CCNode* getDisplayNode();
        Armature* getArmature();
        Animation* getAnimation();
        cocos2d::CCArray* getAnimationList();
        void gotoAndPlay(   const String &animationName,
                            Number fadeInTime = -1,
                            Number duration = -1,
                            Number loop = NaN,
                            uint layer = 0,
                            const String &group = "",
                            const String &fadeOutMode = Animation::SAME_LAYER_AND_GROUP,
                            bool displayControl = true,
                            bool pauseFadeOut = true,
                            bool pauseFadeIn = true
			);
 
		void addEventListener(	const String &type,
                                cocos2d::CCObject *pObj,
                                cocos2d::SEL_CallFuncND selector);
        void removeEventListener(const String &type, cocos2d::CCObject *pObj);
        void removeAllEventListener();
   		bool hasEventListener(const String &type);
   		bool hasEventListener(const String &type, cocos2d::CCObject *pObj);
		
        // Methods for cocos2d-x users.
        void setBoneTexture(const char* boneName, const char* textureName, const char* textureAtlasName);
        
		// Override cocos2d-x method.
		virtual void onExit();
        
        // For script engine
        void registerScriptHandler(int funId, String type);
        void unregisterScriptHandler(String type);
        void unregisterAllScriptHandler();
        bool hasScriptHandler(const String &type);
        int  getScriptHandler(String type);
        
    private:
        void initWithArmature(Armature* arm);
        void update(float dt);
        Armature* m_Armature;
        
        String pointerToString(CCObject* pObj);
		void cocosEventBridge(Event* e);
        typedef std::pair<cocos2d::CCObject*, cocos2d::SEL_CallFuncND> CocosCallback;
        
        // For script engine
        String funToString(int funId);
        std::map<String, int> _scriptHandlers;
        std::map<String, std::list<CocosCallback>> _eventHandlers;
    }; 
}
#endif // __CCDRAGONBONES__
