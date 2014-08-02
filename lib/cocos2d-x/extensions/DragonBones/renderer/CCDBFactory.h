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
	class CCDBFactory : public BaseFactory
    {
    public:
		static TextureAtlasData* parseTextureAtlasFile(const String &textureAtlasFile);
        /** @private */
        ITextureAtlas* generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData);
        
        /** @private */
        virtual Armature* generateArmature();
        
        /** @private */
        Slot* generateSlot();
        
        /** @private */
        virtual Object* generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY);
        
        virtual void loadSkeletonFile(const String &skeletonFile , const String &name  = "");
        virtual void loadTextureAtlasFile(const String &textureAtlasFile , const String &name  = "");
    };
};
#endif // __COCOS2DX_FACTORY_H__
