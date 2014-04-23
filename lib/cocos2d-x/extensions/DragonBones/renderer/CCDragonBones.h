//
//  CCDragonBones.h
//
//
//  Created by Wayne Dimart on 14-4-18.
//  Copyright (c) 2014 . All rights reserved.
//	Modified by zrong(zengrong.net) on 2014-04-22
//

#ifndef __QUICKCOCOS2DX__CCDRAGONBONES__
#define __QUICKCOCOS2DX__CCDRAGONBONES__

#include <iostream>
#include "cocos2d.h"
#include "utils/preDB.h"
#include "animation/Animation.h"
#include "events/Event.h"

namespace dragonBones {
    class Armature;
    class CCDragonBones:public cocos2d::CCNode {
    public:
		// create
        static Armature* buildArmature(	const char* skeletonXMLFile,
                                        const char* textureXMLFile,
                                        const char* dragonBonesName,
                                        const char* armatureName,
                                        const char* animationName = "");

        static CCDragonBones* create(Armature*arm);

        static CCDragonBones* create(	const char* skeletonXMLFile,
										const char* dragonBonesName,
										const char* armatureName); 
															 
        static CCDragonBones* create(	const char* skeletonXMLFile,
                                        const char* textureXMLFile,
                                        const char* dragonBonesName,
                                        const char* armatureName,
                                        const char* animationName = "");

        CCNode* getDisplayNode();
        Armature* getArmature();
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
                                const String &key,
                                cocos2d::CCObject*pObj,
                                cocos2d::SEL_CallFuncND callback); 
		bool hasEventListener(const String &type);
		void removeEventListener(const String &type, const std::string &key);
		void dispatchEvent(Event *event);

		// Methods for cocos2d-x users.
        void setBoneTexture(const char* boneName, const char* textureName, const char* textureAtlasName);

		// Override cocos2d-x method.
		virtual void onExit();

        
    private:
        void initWithArmature(Armature*arm);
        void update(float dt);
        Armature* m_Armature; 
		cocos2d::SEL_CallFuncND	m_Callback;
		cocos2d::CCObject*	m_Caller;
		void eventBridge(Event*e); 
        Animation* getAnimation();
    }; 
}
#endif // __QUICKCOCOS2DX__CCDRAGONBONES__
