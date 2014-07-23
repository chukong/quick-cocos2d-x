#include "CCDBManager.h"
#include "CCDBDisplayBridge.h"
#include "CCDBTextureAtlas.h"
#include "CCDBAtlasNode.h"
#include "utils/ConstValues.h"
#include "objects/XMLDataParser.h"

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "textures/CCTextureCache.h"
#include "cocoa/CCGeometry.h"
#include "base_nodes/CCNode.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "script_support/CCScriptSupport.h"
namespace dragonBones
{

    /**
     * Creates a new CCDBManager instance.
     */
    CCDBManager::CCDBManager()
    {
    }
    
    void CCDBManager::parseXMLByDir(const String& path, String &skeletonXMLFile, String &textureXMLFile)
    {
        String dataDir(path);
        size_t pos;
        while ((pos = dataDir.find_first_of("\\")) != String::npos)
        {
            dataDir.replace(pos, 1, "/");
        }
        size_t slash = dataDir.find_last_of("/");
        if(slash == String::npos)
        {
            dataDir.append("/");
        }
        skeletonXMLFile.append(dataDir + "skeleton.xml");
        textureXMLFile.append(dataDir + "texture.xml");
    }
    
    Armature* CCDBManager::createArmature(const String &armatureName,
                             const String &animationName,
                             const String &skeletonName,
                             const String &skinName)
    {
        return buildArmature(armatureName, animationName, skeletonName, skeletonName, skinName);
    }
    
    void CCDBManager::loadSkeletonFile(const String &skeletonFile , const String &name)
    {
        if(existSkeletonDataInDic(name))
        {
            //todo
            CCLOG("%s, name %s has already been in cache.", __func__, name.c_str());
        }
        else
        {
            dragonBones::XMLDataParser parser;
            unsigned long dummySize;
            
            dragonBones::XMLDocument doc;
            unsigned char* skeleton_data = cocos2d::CCFileUtils::sharedFileUtils()->
                getFileData(skeletonFile.c_str(), "rb", &dummySize);
            doc.Parse(reinterpret_cast<char*>(skeleton_data),dummySize);
            delete[] skeleton_data;
            
            SkeletonData *skeleton = parser.parseSkeletonData(doc.RootElement());
            
            addSkeletonData(skeleton , name);
        }
    }

    void CCDBManager::loadTextureAtlasFile(const String &textureAtlasFile , const String &name)
    {
		if (existTextureDataInDic(name))
		{
			//todo
            CCLOG("%s, name %s has already been in cache.", __func__, name.c_str());
		}
		else
		{
			TextureAtlasData *textureAtlasData = parseTextureAtlasFile(textureAtlasFile);
			addTextureAtlas(new dragonBones::CCDBTextureAtlas(textureAtlasData));
		}
    }
    
    TextureAtlasData* CCDBManager::parseTextureAtlasFile(const String &textureAtlasFile)
    {
        dragonBones::XMLDataParser parser;
        unsigned long dummySize;
        
        dragonBones::XMLDocument doc;
        unsigned char* texture_data = cocos2d::CCFileUtils::sharedFileUtils()->
        getFileData(textureAtlasFile.c_str(), "rb", &dummySize);
        doc.Parse(reinterpret_cast<char*>(texture_data),dummySize);
        delete[] texture_data;
        
        size_t pos = textureAtlasFile.find_last_of("/");
        if (std::string::npos != pos){
            std::string base_path = textureAtlasFile.substr(0, pos + 1);
            
            std::string img_path = doc.RootElement()->Attribute(ConstValues::A_IMAGE_PATH.c_str());
            std::string new_img_path = base_path + img_path;
            
            doc.RootElement()->SetAttribute(ConstValues::A_IMAGE_PATH.c_str(), new_img_path.c_str());
        }
        return parser.parseTextureAtlasData(doc.RootElement());
    }
    
    void CCDBManager::loadDataFiles(const String &skeletonFile, const String &textureAtlasFile, const String &skeletonName)
    {
        if(!skeletonFile.empty())
            loadSkeletonFile(skeletonFile, skeletonName);
        if(!textureAtlasFile.empty())
            loadTextureAtlasFile(textureAtlasFile, skeletonName);
    }

    void CCDBManager::loadDataFilesAsyncImpl(const String &skeletonFile,
                                                 const String &textureAtlasFile,
                                                 const String &skeletonName,
                                                 cocos2d::CCObject* pObj,
                                                 cocos2d::SEL_CallFuncO selector,
                                                 int scriptHandler)
    {
        CCLOG("%s skeletonFile:%s, textureAtlasFile:%s skeletonName:%s pObj:%d selector:%d, handler:%d",
              __func__,
              skeletonFile.c_str(),
              textureAtlasFile.c_str(),
              skeletonName.c_str(),
              pObj,
              selector,
              scriptHandler);
        loadSkeletonFile(skeletonFile, skeletonName);
		if (existTextureDataInDic(skeletonName))
		{
			loadTextureAtlasFile(textureAtlasFile, skeletonName);
            doAsyncCallBack(pObj, selector, scriptHandler);
		}
		else
		{
            TextureAtlasData *textureAtlasData = parseTextureAtlasFile(textureAtlasFile);
            
            CCDBManager::AsyncStruct* asyncObj = new CCDBManager::AsyncStruct();
            asyncObj->pObj = pObj;
            asyncObj->pData = textureAtlasData;
            asyncObj->pSelector = selector;
            asyncObj->scriptHandler = scriptHandler;
            std::string imgPath = cocos2d::CCFileUtils::sharedFileUtils()
                ->fullPathForFilename(textureAtlasData->imagePath.c_str());
            _asyncList[imgPath] = asyncObj;
			
            cocos2d::CCTextureCache::sharedTextureCache()
                ->addImageAsync(imgPath.c_str(),
                                this,
                                cocos2d::SEL_CallFuncO(&CCDBManager::loadTextureCallback));
		}
    }
    
    void CCDBManager::loadTextureCallback(cocos2d::CCObject *pObj)
    {
        cocos2d::CCTexture2D* texture = static_cast<cocos2d::CCTexture2D*>(pObj);
        const char* textureKey = cocos2d::CCTextureCache::sharedTextureCache()->keyForTexture(texture);
        CCLOG("%s textureKey:%s object:%d", __func__, textureKey, pObj);
        for(auto kename : _asyncList)
        {
            CCLOG("first:%s, second:", kename.first.c_str());
        }
        if(textureKey)
        {
            String keyName(textureKey);
            auto iter = _asyncList.find(keyName);
            if(iter != _asyncList.end())
            {
                CCDBManager::AsyncStruct* asyncObj = iter->second;
                addTextureAtlas(new CCDBTextureAtlas(asyncObj->pData));
                doAsyncCallBack(asyncObj->pObj, asyncObj->pSelector, asyncObj->scriptHandler);
                _asyncList.erase(keyName);
                delete asyncObj;
            }
        }
    }
    
    void CCDBManager::doAsyncCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO selector, int handler)
    {
        CCLOG("%s target:%d selector:%d, handler:%d", __func__, target, selector, handler);
        if (target && selector)
        {
            (target->*selector)(target);
        }
        if (handler)
        {
            cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()
                ->executeEvent(handler, "loadDataFilesAsync");
        }
    }
    
    /** @private */
    ITextureAtlas* CCDBManager::generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData)
    {
        return nullptr;
        /*var texture:Texture;
        var bitmapData:BitmapData;
        if (content is BitmapData)
        {
            bitmapData = content as BitmapData;
            texture = Texture.fromBitmapData(bitmapData, generateMipMaps, optimizeForRenderToTexture);
        }
        else if (content is MovieClip)
        {
            var width:int = getNearest2N(content.width) * scaleForTexture;
            var height:int = getNearest2N(content.height) * scaleForTexture;
            
            _helpMatrix.a = 1;
            _helpMatrix.b = 0;
            _helpMatrix.c = 0;
            _helpMatrix.d = 1;
            _helpMatrix.scale(scaleForTexture, scaleForTexture);
            _helpMatrix.tx = 0;
            _helpMatrix.ty = 0;                
            var movieClip:MovieClip = content as MovieClip;
            movieClip.gotoAndStop(1);
            bitmapData = new BitmapData(width, height, true, 0xFF00FF);
            bitmapData.draw(movieClip, _helpMatrix);
            movieClip.gotoAndStop(movieClip.totalFrames);
            texture = Texture.fromBitmapData(bitmapData, generateMipMaps, optimizeForRenderToTexture, scaleForTexture);
        }
        else
        {
            throw new Error();
        }            
        var textureAtlas:StarlingTextureAtlas = new StarlingTextureAtlas(texture, textureAtlasRawData, false);            
        if (Starling.handleLostContext)
        {
            textureAtlas._bitmapData = bitmapData;
        }
        else
        {
            bitmapData.dispose();
        }
        return textureAtlas;*/
    }
    
    /** @private */
    Armature* CCDBManager::generateArmature()
    {
        cocos2d::CCNodeRGBA *node = cocos2d::CCNodeRGBA::create();
        node->setCascadeOpacityEnabled(true);
        return new Armature(new CCDBNode(node));
    }
    
    /** @private */
    Slot* CCDBManager::generateSlot()
    {
        return new Slot(new CCDBDisplayBridge());
    }
    
    /** @private */
    Object* CCDBManager::generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY)
    {
        CCDBTextureAtlas *ccTextureAtlas = dynamic_cast<CCDBTextureAtlas*>(textureAtlas);
        cocos2d::CCRect rect;
        rect.origin.x = 0;
        rect.origin.y = 0;
        Rectangle region = ccTextureAtlas->getRegion(fullName);
        rect.size.width = region.width;
        rect.size.height = region.height;

        cocos2d::CCDBAtlasNode *atlasNode = cocos2d::CCDBAtlasNode::create(ccTextureAtlas->getTextureAtlas() ,
                                                                                   ccTextureAtlas->getQuadIndex(fullName),
                                                                                   rect);
        // cocos2d::ccBlendFunc func;
        // func.src = GL_SRC_ALPHA;
        // func.dst = GL_ONE_MINUS_SRC_ALPHA;
        // atlasNode->setBlendFunc(func);
        atlasNode->setCascadeOpacityEnabled(true);
        atlasNode->setAnchorPoint(cocos2d::CCPoint(pivotX / (Number)region.width , (region.height-pivotY) / (Number)region.height));
        atlasNode->setContentSize(cocos2d::CCSize(region.width , region.height));
        return new CCDBNode(atlasNode);
        //static_cast<cocos2d::CCLayerColor*>(node->node)->initWithColor(cocos2d::ccc4(255,0,0,255) , 100 , 100);
        //return node;
        //DisplayObject *obj = new DisplayObject();
        //obj->textureAtlas = dynamic_cast<Cocos2dxTextureAtlas*>(textureAtlas);
        //obj->atlasNode = cocos2d::Cocos2dxAtlasNode::create(obj->textureAtlas->getTextureAtlas() , obj->textureAtlas->getQuadIndex(fullName));
        //obj->atlasNode->retain();
        //obj->fullName = fullName;
        //obj->pivotX = pivotX;
        //obj->pivotY = pivotY;


        //return obj;
    }

	CCDBManager * CCDBManager::msCCDBManager = nullptr;

	CCDBManager * CCDBManager::getInstance()
	{
		if (msCCDBManager == nullptr)
		{
			msCCDBManager = new CCDBManager();
		}
		return msCCDBManager;
	}

	void CCDBManager::destroyInstance()
	{
		if (msCCDBManager)
		{
			msCCDBManager->dispose();
			CC_SAFE_DELETE(msCCDBManager);
		}
	}

};
