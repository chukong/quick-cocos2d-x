#include "Cocos2dxFactory.h"
#include "Cocos2dxDisplayBridge.h"
#include "Cocos2dxTextureAtlas.h"
#include "Cocos2dxAtlasNode.h"
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
     * Creates a new Cocos2dxFactory instance.
     */
    Cocos2dxFactory::Cocos2dxFactory()
    {
    }
    void Cocos2dxFactory::loadSkeletonFile(const String &skeletonFile , const String &name)
    {
        if(existSkeletonDataInDic(name))
        {
            //todo
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

    void Cocos2dxFactory::loadTextureAtlasFile(const String &textureAtlasFile , const String &name)
    {
		if (existTextureDataInDic(name))
		{
			//todo
		}
		else
		{
			TextureAtlasData *textureAtlasData = parseTextureAtlasFile(textureAtlasFile);
			addTextureAtlas(new dragonBones::Cocos2dxTextureAtlas(textureAtlasData));
		}
    }
    
    TextureAtlasData* Cocos2dxFactory::parseTextureAtlasFile(const String &textureAtlasFile)
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
    
    void Cocos2dxFactory::loadDataFiles(const String &skeletonFile, const String &textureAtlasFile, const String &dbName)
    {
        loadSkeletonFile(skeletonFile, dbName);
        loadTextureAtlasFile(textureAtlasFile, dbName);
    }
    
    void Cocos2dxFactory::loadDataFilesAsync(const String &skeletonFile,
                                             const String &textureAtlasFile,
                                             const String &dbName,
                                             cocos2d::CCObject* pObj,
                                             cocos2d::SEL_CallFuncO selector)
    {
        loadDataFilesAsyncImpl(skeletonFile, textureAtlasFile, dbName, pObj, selector);
    }
    
    void Cocos2dxFactory::loadDataFilesAsync(const String &skeletonFile,
                                             const String &textureAtlasFile,
                                             const String &dbName,
                                             int scriptHandler)
    {
        loadDataFilesAsyncImpl(skeletonFile, textureAtlasFile, dbName, nullptr, nullptr, scriptHandler);
    }
    
    void Cocos2dxFactory::loadDataFilesAsyncImpl(const String &skeletonFile,
                                                 const String &textureAtlasFile,
                                                 const String &dbName,
                                                 cocos2d::CCObject* pObj,
                                                 cocos2d::SEL_CallFuncO selector,
                                                 int scriptHandler)
    {
        loadSkeletonFile(skeletonFile, dbName);
		if (existTextureDataInDic(dbName))
		{
			loadTextureAtlasFile(textureAtlasFile, dbName);
            doAsyncCallBack(pObj, selector, scriptHandler);
		}
		else
		{
            TextureAtlasData *textureAtlasData = parseTextureAtlasFile(textureAtlasFile);
            
            Cocos2dxFactory::AsyncStruct* asyncObj = new Cocos2dxFactory::AsyncStruct();
            asyncObj->pObj = pObj;
            asyncObj->pData = textureAtlasData;
            asyncObj->pSelector = selector;
            asyncObj->scriptHandler = scriptHandler;
            _asyncList[textureAtlasData->imagePath] = asyncObj;
			
            cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(textureAtlasData->imagePath.c_str(),
                                                                         this,
                                                                         cocos2d::SEL_CallFuncO(&Cocos2dxFactory::loadTextureCallback));
		}
    }
    
    void Cocos2dxFactory::loadTextureCallback(cocos2d::CCObject *pObj)
    {
        cocos2d::CCTexture2D* texture = static_cast<cocos2d::CCTexture2D*>(pObj);
        const char* textureKey = cocos2d::CCTextureCache::sharedTextureCache()->keyForTexture(texture);
        if(textureKey)
        {
            String keyName(textureKey);
            auto iter = _asyncList.find(keyName);
            if(iter != _asyncList.end())
            {
                Cocos2dxFactory::AsyncStruct* asyncObj = iter->second;
                addTextureAtlas(new Cocos2dxTextureAtlas(asyncObj->pData));
                doAsyncCallBack(asyncObj->pObj, asyncObj->pSelector, asyncObj->scriptHandler);
                _asyncList.erase(keyName);
                delete asyncObj;
            }
        }
    }
    
    void Cocos2dxFactory::doAsyncCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO selector, int handler)
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
    ITextureAtlas* Cocos2dxFactory::generateTextureAtlas(Object *content, TextureAtlasData *textureAtlasRawData)
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
    Armature* Cocos2dxFactory::generateArmature()
    {
        cocos2d::CCNodeRGBA *node = cocos2d::CCNodeRGBA::create();
        node->setCascadeOpacityEnabled(true);
        return new Armature(new CocosNode(node));
    }
    
    /** @private */
    Slot* Cocos2dxFactory::generateSlot()
    {
        return new Slot(new Cocos2dxDisplayBridge());
    }
    
    /** @private */
    Object* Cocos2dxFactory::generateDisplay(ITextureAtlas *textureAtlas, const String &fullName, Number pivotX, Number pivotY)
    {
        Cocos2dxTextureAtlas *ccTextureAtlas = dynamic_cast<Cocos2dxTextureAtlas*>(textureAtlas);
        cocos2d::CCRect rect;
        rect.origin.x = 0;
        rect.origin.y = 0;
        Rectangle region = ccTextureAtlas->getRegion(fullName);
        rect.size.width = region.width;
        rect.size.height = region.height;

        cocos2d::Cocos2dxAtlasNode *atlasNode = cocos2d::Cocos2dxAtlasNode::create(ccTextureAtlas->getTextureAtlas() ,
                                                                                   ccTextureAtlas->getQuadIndex(fullName),
                                                                                   rect);
        // cocos2d::ccBlendFunc func;
        // func.src = GL_SRC_ALPHA;
        // func.dst = GL_ONE_MINUS_SRC_ALPHA;
        // atlasNode->setBlendFunc(func);
        atlasNode->setCascadeOpacityEnabled(true);
        atlasNode->setAnchorPoint(cocos2d::CCPoint(pivotX / (Number)region.width , (region.height-pivotY) / (Number)region.height));
        atlasNode->setContentSize(cocos2d::CCSize(region.width , region.height));
        return new CocosNode(atlasNode);
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

	Cocos2dxFactory * Cocos2dxFactory::msCocos2dxFactory = nullptr;

	Cocos2dxFactory * Cocos2dxFactory::getInstance()
	{
		if (msCocos2dxFactory == nullptr)
		{
			msCocos2dxFactory = new Cocos2dxFactory();
		}
		return msCocos2dxFactory;
	}

	void Cocos2dxFactory::destroyInstance()
	{
		if (msCocos2dxFactory)
		{
			msCocos2dxFactory->dispose();
			CC_SAFE_DELETE(msCocos2dxFactory);
		}
	}

};
