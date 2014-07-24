#ifndef __COCOS2DX_FACTORY_H__
#define __COCOS2DX_FACTORY_H__

#include "utils/preDB.h"
#include "factories/BaseFactory.h"
#include "Armature.h"
#include "Slot.h"
#include "base_nodes/CCNode.h"
#include "CCDBNode.h"

namespace dragonBones
{

    //class DisplayObject : public Object
    //{
    //public:
    //    DisplayObject()
    //        : textureAtlas(0)
    //        , atlasNode(0)
    //        , pivotX(0)
    //        , pivotY(0)
    //    {

    //    };
    //    virtual ~DisplayObject()
    //    {
    //        CC_SAFE_RELEASE(atlasNode);
    //    }

    //    Cocos2dxTextureAtlas *textureAtlas;
    //    cocos2d::Cocos2dxAtlasNode *atlasNode;

    //    String fullName;
    //    Number pivotX;
    //    Number pivotY;

    //    /**
    //     * Updates the transform of the display object
    //     * @param    matrix
    //     * @param    transform
    //     */
    //    void updateTransform(Matrix &matrix, DBTransform &transform)
    //    {
    //        textureAtlas->updateTransform(this , matrix, transform);
    //    }

    //    void updateColor(
    //        Number aOffset, 
    //        Number rOffset, 
    //        Number gOffset, 
    //        Number bOffset, 
    //        Number aMultiplier, 
    //        Number rMultiplier, 
    //        Number gMultiplier, 
    //        Number bMultiplier
    //        )
    //    {
    //        textureAtlas->updateColor(this , aOffset, 
    //            rOffset, 
    //            gOffset, 
    //            bOffset, 
    //            aMultiplier, 
    //            rMultiplier, 
    //            gMultiplier, 
    //            bMultiplier);
    //    }

    //};


    /**
     * A object managing the set of armature resources for Starling engine. It parses the raw data, stores the armature resources and creates armature instances.
     * @see dragonBones.Armature
     */
    
    /**
     * A StarlingFactory instance manages the set of armature resources for the starling DisplayList. It parses the raw data (ByteArray), stores the armature resources and creates armature instances.
     * <p>Create an instance of the StarlingFactory class that way:</p>
     * <listing>
     * import flash.events.Event; 
     * import dragonBones.factorys.BaseFactory;
     * 
     * [Embed(source = "../assets/Dragon2.png", mimeType = "application/octet-stream")]  
     *    private static const ResourcesData:Class;
     * var factory:StarlingFactory = new StarlingFactory(); 
     * factory.addEventListener(Event.COMPLETE, textureCompleteHandler);
     * factory.parseData(new ResourcesData());
     * </listing>
     * @see dragonBones.Armature
     */
    class CCDBManager : public BaseFactory, public cocos2d::CCObject
    {
    public:
        /**
         * Creates a new StarlingFactory instance.
         */
        CCDBManager();

		// get singleton
		static CCDBManager *getInstance();
		static void destroyInstance();

        static void parseXMLByDir(const String& path,String &skeletonXMLFile, String &textureXMLFile);
        /** @private */
        ITextureAtlas* generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData);
        
        /** @private */
        virtual Armature* generateArmature();
        
        /** @private */
        Slot* generateSlot();
        
        /** @private */
        virtual Object* generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY);
        
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
            return buildArmature(armatureName, animationName,
                                 skeletonName, textureAtlasName, skinName);
        };
        
        virtual void loadSkeletonFile(const String &skeletonFile , const String &name  = "");
        virtual void loadTextureAtlasFile(const String &textureAtlasFile , const String &name  = "");
        
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

	protected:
		static CCDBManager *msCCDBManager;
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
        TextureAtlasData* parseTextureAtlasFile(const String &textureAtlasFile);
        void doAsyncCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO selector, int handler=0);
        void loadTextureCallback(cocos2d::CCObject* pObj);
    };
};
#endif // __COCOS2DX_FACTORY_H__
