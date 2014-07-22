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
        
        Armature* createArmatureByDir(const String &path,
                                  const String &armatureName,
                                 const String &animationName = "",
                                 const String &skeletonName = "",
                                 const String &skinName = "");
        
        Armature* createArmatureByFiles(const String &armatureName,
                                 const String &animationName = "",
                                 const String &skeletonName = "",
                                 const String &skeletonXMLFile = "",
                                 const String &textureXMLFile = "",
                                 const String &skinName = "");
        
        Armature* createArmature(const String &armatureName,
                                 const String &animationName = "",
                                 const String &skeletonName = "",
                                 const String &skinName = "");
        
        virtual void loadSkeletonFile(const String &skeletonFile , const String &name  = "");
        virtual void loadTextureAtlasFile(const String &textureAtlasFile , const String &name  = "");
        
        void loadDataFiles(const String &skeletonFile, const String &textureAtlasFile, const String &dbName);
        
        inline void loadDataFilesAsync(const String &skeletonFile,
                                const String &textureAtlasFile,
                                const String &dbName,
                                cocos2d::CCObject* pObj,
                                cocos2d::SEL_CallFuncO selector)
        {
            loadDataFilesAsyncImpl(skeletonFile, textureAtlasFile, dbName, pObj, selector, 0);
        };
        
        inline void loadDataFilesAsync(const String &skeletonFile,
                                const String &textureAtlasFile,
                                const String &dbName,
                                int scriptHandler)
        {
            loadDataFilesAsyncImpl(skeletonFile, textureAtlasFile, dbName, nullptr, nullptr, scriptHandler);
        };

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
        void loadDataFilesAsyncImpl(const String &skeletonFile,
                                    const String &textureAtlasFile,
                                    const String &dbName,
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
