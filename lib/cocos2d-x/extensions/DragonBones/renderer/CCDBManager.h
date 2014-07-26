#ifndef __CCDBFACTORY_H__
#define __CCDBFACTORY_H__

#include "utils/preDB.h"
#include "CCDBFactory.h"
#include "Armature.h"
#include "Slot.h"
#include "base_nodes/CCNode.h"
#include "CCDBNode.h"

namespace dragonBones
{
	class CCDBManager : public cocos2d::CCObject
    {
	private:
		CCDBManager();
		~CCDBManager();
	public:

		// get singleton
		static CCDBManager *getInstance();
		static void destroyInstance();

        static void parseXMLByDir(const String& path,String &skeletonXMLFile, String &textureXMLFile);
        
        inline Armature* createArmatureByDir(   const String &path,
                                                const String &armatureName,
                                                const String &animationName = "",
                                                const String &skeletonName = "",
                                                const String &textureAtlasName = "",
                                                const String &skinName = "")
        {
            String skeletonFile(""), textureFile("");
            parseXMLByDir(path, skeletonFile, textureFile);
            return createArmatureByFiles(skeletonFile, textureFile,
                                         armatureName, animationName,
                                         skeletonName, textureAtlasName, skinName);
        };
        
        inline Armature* createArmatureByFiles( const String &skeletonXMLFile,
                                                const String &textureXMLFile,
                                                const String &armatureName,
                                                const String &animationName = "",
                                                const String &skeletonName = "",
                                                const String &textureAtlasName = "",
                                                const String &skinName = "")
        {
            loadData(skeletonXMLFile, textureXMLFile,
                      skeletonName, textureAtlasName);
			return _factory.buildArmature(armatureName, animationName,
                                 skeletonName, textureAtlasName, skinName);
        };
        
        inline void loadDataByDir(const String &path,
                                   const String &skeletonName,
                                   const String &textureAtlasName)
        {
            String skeletonFile(""), textureFile("");
            parseXMLByDir(path, skeletonFile, textureFile);
            loadData(skeletonFile, textureFile, skeletonName, textureAtlasName);
        };
        void loadData(const String &skeletonFile, const String &textureAtlasFile,
                           const String &skeletonName, const String &textureAtlasName);
        
        inline void loadDataByDirAsync(const String &path,
                                            const String &skeletonName,
                                            const String &textureAtlasName,
                                            cocos2d::CCObject* pObj,
                                            cocos2d::SEL_CallFuncO selector)
        {
            String skeletonFile(""), textureFile("");
            parseXMLByDir(path, skeletonFile, textureFile);
            loadDataAsync(skeletonFile, textureFile,
                               skeletonName, textureAtlasName,
                               pObj, selector);
        };
        
        inline void loadDataByDirAsync(const String &path,
                                            const String &skeletonName,
                                            const String &textureAtlasName,
                                            int scriptHandler)
        {
            String skeletonFile(""), textureFile("");
            parseXMLByDir(path, skeletonFile, textureFile);
            loadDataAsync(skeletonFile, textureFile,
                               skeletonName, textureAtlasName,
                               scriptHandler);
        };
        
        inline void loadDataAsync(const String &skeletonFile,
                                const String &textureAtlasFile,
                                const String &skeletonName,
                                const String &textureAtlasName,
                                cocos2d::CCObject* pObj,
                                cocos2d::SEL_CallFuncO selector)
        {
            loadDataAsyncImpl(skeletonFile, textureAtlasFile,
                                   skeletonName, textureAtlasName,
                                   pObj, selector, 0);
        };
        
        inline void loadDataAsync(const String &skeletonFile,
                                const String &textureAtlasFile,
                                const String &skeletonName,
                                const String &textureAtlasName,
                                int scriptHandler)
        {
            loadDataAsyncImpl(skeletonFile, textureAtlasFile,
                                   skeletonName, textureAtlasName,
                                   nullptr, nullptr, scriptHandler);
        };
        
        void unloadData(const String &skeletonName, const String &textureAtlasName="");
		CCDBFactory& getFactory();

    private:
        struct AsyncStruct
        {
            const char* imagePath;
            TextureAtlasData* pData;
            cocos2d::CCObject* pObj;
            cocos2d::SEL_CallFuncO pSelector;
            int scriptHandler;
        };
        void loadDataAsyncImpl(const String &skeletonFile,
                                    const String &textureAtlasFile,
                                    const String &skeletonName,
                                    const String &textureAtlasName,
                                    cocos2d::CCObject* pObj,
                                    cocos2d::SEL_CallFuncO selector,
                                    int scriptHandler=0);
        std::map<String, AsyncStruct*> _asyncList;
		CCDBFactory _factory;
        void loadTextureCallback(cocos2d::CCObject* pObj);
		void printTickCount();
    };
};
#endif // __CCDBFACTORY_H__
