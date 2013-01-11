
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "script_support/CCScriptSupport.h"
#include "support/CCNotificationCenter.h"
#include "CCLuaEngine.h"
#include <string>

// cocos2d-x-entensions
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos2dx_extension_crypto.h"
#include "cocos2dx_extension_network.h"
#include "cocos2dx_extension_native.h"
#include "cocos2dx_extension_store.h"
#include "cocos2dx_extensions_luabinding_ios.h"
#include "CCLuaObjcBridge.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2dx_extension_crypto_android.h"
#include "cocos2dx_extension_network_android.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocos2dx_extension_crypto_win32.h"
#include "cocos2dx_extension_network_win32.h"
#include "cocos2dx_extension_native_win32.h"
#include "cocos2dx_extensions_luabinding_win32.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "cocos2dx_extension_crypto_mac.h"
#include "cocos2dx_extension_network_mac.h"
#include "cocos2dx_extension_native_mac.h"
#include "cocos2dx_extensions_luabinding_mac.h"

#endif

// lua framework
extern "C" {
#include "framework_lua.h"
}

// more lua exts
extern "C" {
#include "lualoadexts.h"
}
#include "LuaCCDrawing.h"

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
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    // register lua engine
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    CCLuaStack *pStack = pEngine->getLuaStack();
    lua_State* L = pStack->getLuaState();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    tolua_cocos2dx_extension_crypto_open(L);
    tolua_cocos2dx_extension_network_open(L);
    tolua_cocos2dx_extension_native_open(L);
    tolua_cocos2dx_extension_store_open(L);
    tolua_cocos2dx_extensions_luabinding_ios_open(L);
    CCLuaObjcBridge::luabindingOpen(L);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    tolua_cocos2dx_extension_crypto_android_open(L);
    tolua_cocos2dx_extension_network_android_open(L);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    tolua_cocos2dx_extension_crypto_win32_open(L);
    tolua_cocos2dx_extension_network_win32_open(L);
	tolua_cocos2dx_extension_native_win32_open(L);
    tolua_cocos2dx_extensions_luabinding_win32_open(L);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    tolua_cocos2dx_extension_crypto_mac_open(L);
    tolua_cocos2dx_extension_network_mac_open(L);
    tolua_cocos2dx_extension_native_mac_open(L);
    tolua_cocos2dx_extensions_luabinding_mac_open(L);
    
#endif

    // lua framework
    luaopen_framework_lua(L);
    
    // more lua exts
    luax_loadexts(L);
    tolua_CCDrawing_open(L);
    
    CCFileUtils::sharedFileUtils()->setPopupNotify(false);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    const string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("scripts/main.lua");
#else
    const string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(getStartupScriptFilename().c_str());
#endif
    size_t p = path.find_last_of("/\\");
    if (p != path.npos)
    {
        const string dir = path.substr(0, p);
        pStack->addSearchPath(dir.c_str());
    }
    
    string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    pEngine->executeString(env.c_str());
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_BACKGROUND");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_FOREGROUND");
}
