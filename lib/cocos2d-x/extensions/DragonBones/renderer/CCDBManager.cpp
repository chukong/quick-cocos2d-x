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
	static unsigned int _tickCount;

	static void doAsyncCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO selector, int handler)
	{
		//CCLOG("%s target:%d selector:%d, handler:%d", __FUNCTION__, target, selector, handler);
		if (target && selector)
		{
			(target->*selector)(target);
			target->release();
		}
		if (handler)
		{
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()
				->executeEvent(handler, "loadDataFilesAsync");
		}
	}

	static CCDBManager *msCCDBManager = nullptr;

	CCDBManager * CCDBManager::getInstance()
	{
		if (!msCCDBManager)
		{
			msCCDBManager = new CCDBManager();
		}
		return msCCDBManager;
	}

	/**
	* Creates a new CCDBManager instance.
	*/
	CCDBManager::CCDBManager()
	{
		printTickCount();
	}
	CCDBManager::~CCDBManager()
	{
		CCLOG("~CCDBMAnager");
		for (auto iter = _asyncList.begin(); iter != _asyncList.end(); iter++)
		{
			delete iter->second;
		}
		_asyncList.clear();
		_factory.dispose(true);
	}

	void CCDBManager::destroyInstance()
	{
		CCLOG("CCDBMAnager::destroyInstance");
		if (msCCDBManager)
		{
			CC_SAFE_DELETE(msCCDBManager);
		}
	}

	void CCDBManager::printTickCount()
	{
		++_tickCount;
		CCLOG("%s tickcount:%d thisptr:%d msCCDBManager:%d, sizeof(%d) %d, %d", __FUNCTION__, _tickCount, this, msCCDBManager, sizeof(CCDBManager), sizeof(BaseFactory), sizeof(CCObject));
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
        if(slash == String::npos || slash != dataDir.size()-1)
        {
            dataDir.append("/");
        }
        skeletonXMLFile.append(dataDir + "skeleton.xml");
        textureXMLFile.append(dataDir + "texture.xml");
    }
      
    void CCDBManager::loadData(const String &skeletonFile,
                                    const String &textureAtlasFile,
                                    const String &skeletonName,
                                    const String &textureAtlasName)
    {
        if(!skeletonFile.empty())
			_factory.loadSkeletonFile(skeletonFile, skeletonName);
        if(!textureAtlasFile.empty())
			_factory.loadTextureAtlasFile(textureAtlasFile, textureAtlasName);
    }

    void CCDBManager::loadDataAsyncImpl(   const String &skeletonFile,
                                                const String &textureAtlasFile,
                                                const String &skeletonName,
                                                const String &textureAtlasName,
                                                cocos2d::CCObject* pObj,
                                                cocos2d::SEL_CallFuncO selector,
                                                int scriptHandler)
    {
        /*
        CCLOG("%s skeletonFile:%s, textureAtlasFile:%s skeletonName:%s pObj:%d selector:%d, handler:%d",
              __FUNCTION__,
              skeletonFile.c_str(),
              textureAtlasFile.c_str(),
              skeletonName.c_str(),
              pObj,
              selector,
              scriptHandler);
         //*/
		_factory.loadSkeletonFile(skeletonFile, skeletonName);
		//if (!_asyncList)
		//	_asyncList = new std::map<String, AsyncStruct*>();
		if (_factory.existTextureDataInDic(skeletonName))
		{
			_factory.loadTextureAtlasFile(textureAtlasFile, textureAtlasName);
            doAsyncCallBack(pObj, selector, scriptHandler);
		}
		else
		{
            TextureAtlasData *textureAtlasData = CCDBFactory::parseTextureAtlasFile(textureAtlasFile);
            
            CCDBManager::AsyncStruct* asyncObj = new CCDBManager::AsyncStruct();
			//auto asyncObj = new AsyncStruct();
            asyncObj->pObj = pObj;
            asyncObj->pData = textureAtlasData;
            asyncObj->pSelector = selector;
            asyncObj->scriptHandler = scriptHandler;
            std::string imgPath = cocos2d::CCFileUtils::sharedFileUtils()
                ->fullPathForFilename(textureAtlasData->imagePath.c_str());
            (_asyncList)[imgPath] = asyncObj;
			CCLOG("loadDataAsyncImpl,size:%d", _asyncList.size());
			if (pObj) pObj->retain();
			printTickCount();
            cocos2d::CCTextureCache::sharedTextureCache()
                ->addImageAsync(imgPath.c_str(),
                                (cocos2d::CCObject*)msCCDBManager,
                                cocos2d::SEL_CallFuncO(&CCDBManager::loadTextureCallback));
		}
    }

    void CCDBManager::loadTextureCallback(cocos2d::CCObject *pObj)
    {
        cocos2d::CCTexture2D* texture = static_cast<cocos2d::CCTexture2D*>(pObj);
        const char* textureKey = cocos2d::CCTextureCache::sharedTextureCache()->keyForTexture(texture);
        //CCLOG("%s textureKey:%s object:%d", __FUNCTION__, textureKey, pObj);
        //for(auto kename : _asynclist)
        //{
        //    cclog("first:%s, second:", kename.first.c_str());
        //}
		CCLOG("CCDBManager::loadTextureCallback size %d", _asyncList.size());
		CCLOG("CCDBManager::loadTextureCallback empty %d", _asyncList.empty());
		printTickCount();
		if (_asyncList.empty())
			CCLOG("asyncList is empty");
        if(textureKey)
        {
            String keyName(textureKey);
            auto iter = _asyncList.find(keyName);
            if(iter != _asyncList.end())
            {
                auto asyncObj = iter->second;
				_factory.addTextureAtlas(new CCDBTextureAtlas(asyncObj->pData));
                doAsyncCallBack(asyncObj->pObj, asyncObj->pSelector, asyncObj->scriptHandler);
                delete asyncObj;
                _asyncList.erase(keyName);
            }
        }
    }
    
    void CCDBManager::unloadData(const String &skeletonName, const String &textureAtlasName)
    {
        _factory.removeSkeletonData(skeletonName);
        String texName(textureAtlasName.empty()?skeletonName:textureAtlasName);
        CCDBTextureAtlas *texture = static_cast<CCDBTextureAtlas*>(_factory.getTextureAtlas(textureAtlasName));
        if(texture)
        {
            String imagePath = texture->getImagePath();
            cocos2d::CCTextureCache::sharedTextureCache()
                ->removeTextureForKey(imagePath.c_str());
        }
        _factory.removeTextureAtlas(texName);
        //CCLOG("Dragon in skeleton cache:%d", existSkeletonDataInDic("Dragon"));
        //CCLOG("Dragon in texture cache:%d", existTextureDataInDic("Dragon"));
    }

	CCDBFactory& CCDBManager::getFactory()
	{
		return _factory;
	}
};