#include "BaseFactory.h"
#include "objects/SkeletonData.h"
#include "textures/ITextureAtlas.h"
#include "Armature.h"
#include "animation/Animation.h"
#include <stdexcept>
namespace dragonBones
{    

    BaseFactory::BaseFactory()
    {
		CCLOG("BaseFactory");
    }
    BaseFactory::~BaseFactory()
    {
		CCLOG("~BaseFactory");
        dispose();
    }
    
	bool BaseFactory::existSkeletonDataInDic(const String &name)
	{
		if (_dataDic.find(name) != _dataDic.end())
		{
			return true;
		} 
		else
		{
			return false;
		}
	}
	bool BaseFactory::existTextureDataInDic(const String &name)
	{
		if (_textureAtlasDic.find(name) != _textureAtlasDic.end())
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

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
    SkeletonData* BaseFactory::getSkeletonData(const String &name)
    {
        std::map<String , SkeletonData*>::iterator iter = _dataDic.find(name);
        if(iter != _dataDic.end())
        {
            return iter->second;
        }
        else
        {
            return 0;
        }
    }

    /**
    * Add a SkeletonData instance to this BaseFactory instance.
    * @example 
    * <listing>
    * factory.addSkeletonData(data, 'dragon');
    * </listing>
    * @param    A SkeletonData instance.
    * @param    (optional) A name for this SkeletonData instance.
    */
    void BaseFactory::addSkeletonData(SkeletonData *data, const String &name)
    {
        if(!data)
        {
            throw std::invalid_argument("data is null");
        }
        String newname = name.empty() ? data->name : name;
        if(newname.empty())
        {
            throw std::invalid_argument("Unnamed data!");
        }
        _dataDic[newname] = data;
    }

    /**
    * Remove a SkeletonData instance from this BaseFactory instance.
    * @example 
    * <listing>
    * factory.removeSkeletonData('dragon');
    * </listing>
    * @param    The name for the SkeletonData instance to remove.
    */
    void BaseFactory::removeSkeletonData(const String &name)
    {
        std::map<String , SkeletonData*>::iterator iter = _dataDic.find(name);
        if(iter != _dataDic.end())
        {
            delete iter->second;
            _dataDic.erase(iter);
        }
    }

    /**
    * Return the TextureAtlas by that name.
    * @example 
    * <listing>
    * var atlas:Object = factory.getTextureAtlas('dragon');
    * </listing>
    * @param    The name of the TextureAtlas to return.
    * @return A textureAtlas.
    */
    ITextureAtlas* BaseFactory::getTextureAtlas(const String &name)
    {
        std::map<String , ITextureAtlas*>::iterator iter = _textureAtlasDic.find(name);
        if(iter != _textureAtlasDic.end())
        {
            return iter->second;
        }
        return nullptr;
    }

    /**
    * Add a textureAtlas to this BaseFactory instance.
    * @example 
    * <listing>
    * factory.addTextureAtlas(textureatlas, 'dragon');
    * </listing>
    * @param    A textureAtlas to add to this BaseFactory instance.
    * @param    (optional) A name for this TextureAtlas.
    */
    void BaseFactory::addTextureAtlas(ITextureAtlas *textureAtlas, const String &name)
    {
        if(!textureAtlas)
        {
            throw std::invalid_argument("textureAtlas is null");
        }
        String newname = name;
        if(newname.empty())
        {
            newname = textureAtlas->getName();
        }
        if(newname.empty())
        {
            throw std::invalid_argument("Unnamed data!");
        }
        _textureAtlasDic[newname] = textureAtlas;
    }

    /**
    * Remove a textureAtlas from this baseFactory instance.
    * @example 
    * <listing>
    * factory.removeTextureAtlas('dragon');
    * </listing>
    * @param    The name of the TextureAtlas to remove.
    */
    void BaseFactory::removeTextureAtlas(const String &name)
    {
        std::map<String , ITextureAtlas*>::iterator iter = _textureAtlasDic.find(name);
        if(iter != _textureAtlasDic.end())
        {
            delete iter->second;
            _textureAtlasDic.erase(iter);
        }
    }

    /**
    * Cleans up resources used by this BaseFactory instance.
    * @example 
    * <listing>
    * factory.dispose();
    * </listing>
    * @param    (optional) Destroy all internal references.
    */
    void BaseFactory::dispose(bool disposeData)
    {
        if(disposeData)
        {
            for(std::map<String , SkeletonData*>::iterator iter = _dataDic.begin() ; iter != _dataDic.end() ; iter ++)
            {
                iter->second->dispose();
                delete iter->second;
            }
            for(std::map<String , ITextureAtlas*>::iterator iter = _textureAtlasDic.begin() ; iter != _textureAtlasDic.end() ; iter ++)
            {
                iter->second->dispose();
                delete iter->second;
            }
        }
        _dataDic.clear();
        _textureAtlasDic.clear();
        _textureAtlasLoadingDic.clear();    
        _currentDataName.clear();
        _currentTextureAtlasName.clear();
    }

    /**
    * Build and returns a new Armature instance.
    * @example 
    * <listing>
    * var armature:Armature = factory.buildArmature('dragon');
    * </listing>
    * @param    armatureName The name of this Armature instance.
    * @param    The name of this animation
    * @param    The name of this SkeletonData.
    * @param    The name of this textureAtlas.
    * @param    The name of this skin.
    * @return A Armature instance.
    */
    Armature* BaseFactory::buildArmature(const String &armatureName,
                                         const String &animationName,
                                         const String &skeletonName,
                                         const String &textureAtlasName,
                                         const String &skinName)
    {
        ArmatureData* armatureData = 0;
        SkeletonData *data = 0;
        if(!skeletonName.empty())
        {
            std::map<String , SkeletonData*>::iterator iter = _dataDic.find(skeletonName);
            if(iter != _dataDic.end())
            {
                data = iter->second;
                armatureData = data->getArmatureData(armatureName);
            }
        }
        //else
        //{
        //    for(skeletonName in _dataDic)
        //    {
        //        data = _dataDic[skeletonName];
        //        armatureData = data->getArmatureData(armatureName);
        //        if(armatureData)
        //        {
        //            break;
        //        }
        //    }
        //}

        if(!armatureData)
        {
            return nullptr;
        }

        _currentDataName = skeletonName;
        _currentTextureAtlasName = textureAtlasName.empty() ? skeletonName : textureAtlasName;

        Armature* armature = generateArmature();
        armature->name = armatureName;
        Bone* bone;
        for(size_t i = 0 ; i < armatureData->boneDataList.size() ; i ++)
        {
            BoneData* boneData = armatureData->boneDataList[i];
            bone = new Bone();
            bone->name = boneData->name;
            bone->fixedRotation = boneData->fixedRotation;
            bone->scaleMode = boneData->scaleMode;
            bone->origin = boneData->transform;
            if(armatureData->getBoneData(boneData->parent))
            {
                armature->addBone(bone, boneData->parent);
            }
            else
            {
                armature->addBone(bone);
            }
        }

        ArmatureData* animationArmatureData = 0;
        SkinData *skinDataCopy = 0;
        if(!animationName.empty() && animationName != armatureName)
        {
            //ArmatureData* animationArmatureData = data->getArmatureData(animationName);
            // Get the default animation
            //if(!animationArmatureData)
            //{
            //    for (skeletonName in _dataDic)
            //    {
            //        data = _dataDic[skeletonName];
            //        animationArmatureData = data->getArmatureData(animationName);
            //        if(animationArmatureData)
            //        {
            //            break;
            //        }
            //    }
            //}

            ArmatureData* armatureDataCopy = data->getArmatureData(animationName);
            if(armatureDataCopy)
            {
                skinDataCopy = armatureDataCopy->getSkinData("");
            }
        }

        if(animationArmatureData)
        {
            armature->getAnimation()->setAnimationDataList(animationArmatureData->animationDataList);
        }
        else
        {
            armature->getAnimation()->setAnimationDataList(armatureData->animationDataList);
        }

        SkinData* skinData = armatureData->getSkinData(skinName);
        if(!skinData)
        {
            return nullptr;
            //throw new ArgumentError();
        }

        Slot* slot;
        DisplayData* displayData;
        Armature* childArmature;
        size_t i;
        //var helpArray:Array = [];
        for(size_t j = 0 ; j < skinData->slotDataList.size() ; j ++)
        {
            SlotData* slotData = skinData->slotDataList[j];
            bone = armature->getBone(slotData->parent);
            if(!bone)
            {
                continue;
            }
            slot = generateSlot();
            slot->name = slotData->name;
            slot->setBlendMode(slotData->blendMode);
            slot->_originZOrder = slotData->zOrder;
            slot->_dislayDataList = slotData->displayDataList;

            std::vector<Object*> helpArray;

            i = slotData->displayDataList.size();
            helpArray.resize(i);
            while(i --)
            {
                displayData = slotData->displayDataList[i];

                if(displayData->type == DisplayData::ARMATURE)
                {
                    DisplayData* displayDataCopy = 0;
                    if(skinDataCopy)
                    {
                        SlotData* slotDataCopy = skinDataCopy->getSlotData(slotData->name);
                        if(slotDataCopy)
                        {
                            displayDataCopy = slotDataCopy->displayDataList[i];
                        }
                    }
                    else
                    {
                        displayDataCopy = 0;
                    }

                    childArmature = buildArmature(displayData->name, displayDataCopy?displayDataCopy->name:"", _currentDataName, _currentTextureAtlasName);
                    if(childArmature)
                    {
                        helpArray[i] = childArmature;
                    }
				   //fix by Wayne Dimart:
                   // break; we don't use break here, or will crach the program due to incomplete helpArray.
					continue;
                }
                else
                {
                    helpArray[i] = generateDisplay(getTextureAtlas(_currentTextureAtlasName), displayData->name, displayData->pivot.x, displayData->pivot.y);
                }
            }
            slot->setDisplayList(helpArray);
            slot->changeDisplay(0);
            bone->addChild(slot);
        }

        //
        i = armature->_boneList.size();
        while(i --)
        {
            armature->_boneList[i]->update();
        }

        i = armature->_slotList.size();
        while(i --)
        {
            slot = armature->_slotList[i];
            slot->update();
        }
        armature->updateSlotsZOrder();

        return armature;
    }

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
    Object* BaseFactory::getTextureDisplay(const String &textureName, const String &textureAtlasName, Number pivotX, Number pivotY)
    {
        ITextureAtlas* textureAtlas = 0;
        if(!textureAtlasName.empty())
        {
            std::map<String , ITextureAtlas*>::iterator iter = _textureAtlasDic.find(textureAtlasName);
            if(iter != _textureAtlasDic.end())
            {
                textureAtlas = iter->second;
            }
        }
        //if(!textureAtlas && !textureAtlasName)
        //{
        //    for (textureAtlasName in _textureAtlasDic)
        //    {
        //        textureAtlas = _textureAtlasDic[textureAtlasName];
        //        if(textureAtlas.getRegion(textureName))
        //        {
        //            break;
        //        }
        //        textureAtlas = null;
        //    }
        //}
        if(textureAtlas)
        {
            if(isNaN(pivotX) || isNaN(pivotY))
            {
                SkeletonData* data = _dataDic[textureAtlasName];
                if(data)
                {
                    Point *pivot = data->getSubTexturePivot(textureName);
                    if(pivot)
                    {
                        pivotX = pivot->x;
                        pivotY = pivot->y;
                    }
                }
            }

            return generateDisplay(textureAtlas, textureName, pivotX, pivotY);
        }
        return nullptr;
    }

    /** @private */
    //void loaderCompleteHandler(Event *e)
    //{
    //    e.target.removeEventListener(Event.COMPLETE, loaderCompleteHandler);
    //    var loader:Loader = e.target.loader;
    //    var content:Object = e.target.content;
    //    loader.unloadAndStop();
    //    
    //    String name = loader.name;
    //    Object textureAtlasRawData = _textureAtlasLoadingDic[name];
    //    delete _textureAtlasLoadingDic[name];
    //    if(name && textureAtlasRawData)
    //    {
    //        if (content is Bitmap)
    //        {
    //            content =  (content as Bitmap).bitmapData;
    //        }
    //        else if (content is Sprite)
    //        {
    //            content = (content as Sprite).getChildAt(0) as MovieClip;
    //        }
    //        else
    //        {
    //            //
    //        }
    //        
    //        var textureAtlas:Object = generateTextureAtlas(content, textureAtlasRawData);
    //        addTextureAtlas(textureAtlas, name);
    //        
    //        name = null;
    //        for(name in _textureAtlasLoadingDic)
    //        {
    //            break;
    //        }
    //        //
    //        if(!name && this.hasEventListener(Event.COMPLETE))
    //        {
    //            this.dispatchEvent(new Event(Event.COMPLETE));
    //        }
    //    }
    //}

    /** @private */
    ITextureAtlas* BaseFactory::generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData)
    {
        return nullptr;
    }

    /**
    * Generates an Armature instance.
    * @return Armature An Armature instance.
    */
    Armature* BaseFactory::generateArmature()
    {
        return nullptr;
    }

    /**
    * Generates an Slot instance.
    * @return Slot An Slot instance.
    */
    Slot* BaseFactory::generateSlot()
    {
        return nullptr;
    }

    /**
    * Generates a DisplayObject
    * @param    textureAtlas The TextureAtlas.
    * @param    fullName A qualified name.
    * @param    pivotX A pivot x based value.
    * @param    pivotY A pivot y based value.
    * @return
    */
    Object* BaseFactory::generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY)
    {
        return nullptr;
    }
}
