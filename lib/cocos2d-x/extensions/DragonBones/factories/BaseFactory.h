#ifndef __BASE_FACTORY_H__
#define __BASE_FACTORY_H__
#include "utils/preDB.h"
namespace dragonBones
{
    class SkeletonData;
    class ITextureAtlas;
    class TextureAtlasData;
    class Armature;
    class Slot;
    class Object;
    // TODO : complete event
    ///** Dispatched after a sucessful call to parseData(). */
    //[Event(name="complete", type="flash.events.Event")]
    
    class BaseFactory
    {

        /** @private */
        std::map<String , SkeletonData*> _dataDic;
        /** @private */
        std::map<String , ITextureAtlas*> _textureAtlasDic;
        /** @private */
        std::map<String , TextureAtlasData*> _textureAtlasLoadingDic;
        /** @private */
        String _currentDataName;
        /** @private */
        String _currentTextureAtlasName;
    public:
        BaseFactory();
        virtual ~BaseFactory();
        
        //add load function for SkeletonFile and TextureAtlasFile
        virtual void loadSkeletonFile(const String &skeletonFile , const String &name  = "") = 0;
        virtual void loadTextureAtlasFile(const String &textureAtlasFile , const String &name = "") = 0;

		bool existSkeletonDataInDic(const String &name);
		bool existTextureDataInDic(const String &name);
        /**
         * Parses the raw data and returns a SkeletonData instance.    
         * @example 
         * <listing>
         * import flash.events.Event; 
         * import dragonBones.factorys.BaseFactory;
         * 
         * [Embed(source = "../assets/Dragon1.swf", mimeType = "application/octet-stream")]
         *    private static const ResourcesData:Class;
         * var factory:BaseFactory = new BaseFactory(); 
         * factory.addEventListener(Event.COMPLETE, textureCompleteHandler);
         * factory.parseData(new ResourcesData());
         * </listing>
         * @param    ByteArray. Represents the raw data for the whole DragonBones system.
         * @param    String. (optional) The SkeletonData instance name.
         * @return A SkeletonData instance.
         */
        //public function parseData(bytes:ByteArray, dataName:String = null):SkeletonData
        //{
        //    if(!bytes)
        //    {
        //        throw new ArgumentError();
        //    }
        //    var decompressedData:DecompressedData = DataParser.decompressData(bytes);
        //        
        //    var data:SkeletonData = DataParser.parseData(decompressedData.dragonBonesData);
        //    
        //    dataName = dataName || data->name;
        //    addSkeletonData(data, dataName);
        //    var loader:Loader = new Loader();
        //    loader.name = dataName;
        //    _textureAtlasLoadingDic[dataName] = decompressedData.textureAtlasData;
        //    loader.contentLoaderInfo.addEventListener(Event.COMPLETE, loaderCompleteHandler);
        //    loader.loadBytes(decompressedData.textureBytes, _loaderContext);
        //    decompressedData.dispose();
        //    return data;
        //}
        
        
        /**
         * Returns a SkeletonData instance.
         * @example 
         * <listing>
         * var data:SkeletonData = factory.getSkeletonData('dragon');
         * </listing>
         * @param    The name of an existing SkeletonData instance.
         * @return A SkeletonData instance with given name (if exist).
         */
        SkeletonData* getSkeletonData(const String &name);
        
        /**
         * Add a SkeletonData instance to this BaseFactory instance.
         * @example 
         * <listing>
         * factory.addSkeletonData(data, 'dragon');
         * </listing>
         * @param    A SkeletonData instance.
         * @param    (optional) A name for this SkeletonData instance.
         */
        void addSkeletonData(SkeletonData *data, const String &name = "");
        
        /**
         * Remove a SkeletonData instance from this BaseFactory instance.
         * @example 
         * <listing>
         * factory.removeSkeletonData('dragon');
         * </listing>
         * @param    The name for the SkeletonData instance to remove.
         */
        void removeSkeletonData(const String &name);
        
        /**
         * Return the TextureAtlas by that name.
         * @example 
         * <listing>
         * var atlas:Object = factory.getTextureAtlas('dragon');
         * </listing>
         * @param    The name of the TextureAtlas to return.
         * @return A textureAtlas.
         */
        ITextureAtlas* getTextureAtlas(const String &name);
        
        /**
         * Add a textureAtlas to this BaseFactory instance.
         * @example 
         * <listing>
         * factory.addTextureAtlas(textureatlas, 'dragon');
         * </listing>
         * @param    A textureAtlas to add to this BaseFactory instance.
         * @param    (optional) A name for this TextureAtlas.
         */
        void addTextureAtlas(ITextureAtlas *textureAtlas, const String &name = "");
        
        /**
         * Remove a textureAtlas from this baseFactory instance.
         * @example 
         * <listing>
         * factory.removeTextureAtlas('dragon');
         * </listing>
         * @param    The name of the TextureAtlas to remove.
         */
        void removeTextureAtlas(const String &name);
        /**
         * Cleans up resources used by this BaseFactory instance.
         * @example 
         * <listing>
         * factory.dispose();
         * </listing>
         * @param    (optional) Destroy all internal references.
         */
        virtual void dispose(bool disposeData = true);
        
        /**
         * Build and returns a new Armature instance.
         * @example 
         * <listing>
         * var armature:Armature = factory.buildArmature('dragon');
         * </listing>
         * @param    armatureName The name of this Armature instance.
         * @param    The name of this animation->
         * @param    The name of this SkeletonData.
         * @param    The name of this textureAtlas.
         * @param    The name of this skin.
         * @return A Armature instance.
         */
        Armature* buildArmature(const String &armatureName, const String &animationName = "",
                                const String &skeletonName = "", const String &textureAtlasName = "",
                                const String &skinName = "");
        /**
         * Return the TextureDisplay.
         * @example 
         * <listing>
         * var texturedisplay:Object = factory.getTextureDisplay('dragon');
         * </listing>
         * @param    The name of this Texture.
         * @param    The name of the TextureAtlas.
         * @param    The registration pivotX position.
         * @param    The registration pivotY position.
         * @return An Object.
         */
        Object* getTextureDisplay(const String &textureName, const String &textureAtlasName = "", Number pivotX = NaN, Number pivotY = NaN);
        
        /** @private */
        //void loaderCompleteHandler(Event *e);
        
        /** @private */
        virtual ITextureAtlas* generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData);
        
        /**
         * Generates an Armature instance.
         * @return Armature An Armature instance.
         */
        virtual Armature* generateArmature();
        
        /**
         * Generates an Slot instance.
         * @return Slot An Slot instance.
         */
        virtual Slot* generateSlot();
        
        /**
         * Generates a DisplayObject
         * @param    textureAtlas The TextureAtlas.
         * @param    fullName A qualified name.
         * @param    pivotX A pivot x based value.
         * @param    pivotY A pivot y based value.
         * @return
         */
        virtual Object* generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY);
    };
};
#endif // __BASE_FACTORY_H__
