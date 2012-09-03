
#include "cocos2d.h"
#include "AppDelegate.h"

#include <string>

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

#include "HostVersion.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
    m_startupScriptFilename = std::string("main.lua");
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
    
    //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320, kResolutionShowAll);

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    //pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // register lua engine
    CCScriptEngineProtocol* pEngine = CCLuaEngine::create();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    tolua_cocos2dx_extension_crypto_win32_open(pEngine->getLuaState());
    tolua_cocos2dx_extension_network_win32_open(pEngine->getLuaState());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    tolua_cocos2dx_extension_crypto_mac_open(pEngine->getLuaState());
    tolua_cocos2dx_extension_network_mac_open(pEngine->getLuaState());
#endif
    
    const string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(getStartupScriptFilename());
    size_t p = path.find_last_of("/\\");
    if (p != path.npos)
    {
        const string dir = path.substr(0, p);
        pEngine->addSearchPath(dir.c_str());
    }

    CCLOG("------------------------------------------------");
    CCLOG(" HOST VERSION: %s", HOST_VERSION);
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s\n", path.c_str());
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
