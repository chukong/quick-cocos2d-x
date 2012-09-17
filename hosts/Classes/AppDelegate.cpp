
#include "AppDelegate.h"
#include "HostVersion.h"
#include "SimpleAudioEngine.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocos2dx_extension_crypto_win32.h"
#include "cocos2dx_extension_network_win32.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "cocos2dx_extension_crypto_mac.h"
#include "cocos2dx_extension_network_mac.h"
#endif
// more lua exts
#include "LuaCCDrawing.h"

#include <string>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end();
    //CCScriptEngineManager::purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    pDirector->enableRetinaDisplay(true);
#endif
    
    pDirector->setProjection(kCCDirectorProjection2D);
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // turn on display FPS
    pDirector->setDisplayStats(true);
//#endif
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    
    lua_State* L = pEngine->getLuaState();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    tolua_cocos2dx_extension_crypto_win32_open(L);
    tolua_cocos2dx_extension_network_win32_open(L);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    tolua_cocos2dx_extension_crypto_mac_open(L);
    tolua_cocos2dx_extension_network_mac_open(L);
#endif
    
    // more lua exts
    tolua_CCDrawing_open(L);
    
    CCFileUtils::sharedFileUtils()->setPopupNotify(false);
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    const string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(getStartupScriptFilename().c_str());
#else
    const string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("client_scripts/main_new.lua");
#endif
    size_t p = path.find_last_of("/\\");
    if (p != path.npos)
    {
        const string dir = path.substr(0, p);
        pEngine->addSearchPath(dir.c_str());
    }
    
    CCLOG("------------------------------------------------");
    CCLOG("HOST VERSION: %s", HOST_VERSION);
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
