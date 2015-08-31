
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "support/CCNotificationCenter.h"
#include "CCLuaEngine.h"
#include "cocos2dx_extra.h"
#include "network/CCHTTPRequest.h"
#include "native/CCNative.h"
#include <string>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC_EXTRA;

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

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // register lua engine
    CCScriptEngineManager::sharedManager()->setScriptEngine(CCLuaEngine::defaultEngine());
    StartupCall *call = StartupCall::create(this);
    if (m_projectConfig.getDebuggerType() != kCCLuaDebuggerNone)
    {
        CCScene *scene = CCScene::create();
        CCLabelTTF *label = CCLabelTTF::create("WAITING FOR CONNECT TO DEBUGGER...", "Arial", 32);
        const CCSize winSize = pDirector->getWinSize();
        label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        scene->addChild(label);
        pDirector->runWithScene(scene);
        scene->runAction(CCCallFunc::create(call, callfunc_selector(StartupCall::startup)));
    }
    else
    {
        call->startup();
    }

	// track launch event
    trackLaunchEvent();
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_BACKGROUND_EVENT");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_FOREGROUND_EVENT");
}

void AppDelegate::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
}

void AppDelegate::setOpenRecents(const CCLuaValueArray& recents)
{
    m_openRecents = recents;
}

void AppDelegate::trackEvent(const char *eventName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	const char *platform = "win";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	const char *platform = "mac";
#else
	const char *platform = "UNKNOWN";
#endif

    CCHTTPRequest *request = CCHTTPRequest::createWithUrl(NULL,
                                                          "http://www.google-analytics.com/collect",
                                                          kCCHTTPRequestMethodPOST);
    request->addPOSTValue("v", "1");
    request->addPOSTValue("tid", "UA-54146057-1");
    request->addPOSTValue("cid", CCNative::getOpenUDID().c_str());
    request->addPOSTValue("t", "event");
    
    request->addPOSTValue("an", "player");
    request->addPOSTValue("av", cocos2dVersion());

	request->addPOSTValue("ec", platform);
    request->addPOSTValue("ea", eventName);
    
    request->start();
}

void AppDelegate::trackLaunchEvent()
{
    trackEvent("launch");
    
    const char *trackUrl = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    trackUrl = "http://c.kp747.com/k.js?id=c19010907080b2d7";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    trackUrl = "http://c.kp747.com/k.js?id=c1e060d0a0e0e207";
#endif
    
    if (trackUrl)
    {
        CCHTTPRequest *request = CCHTTPRequest::createWithUrl(NULL,
                                                              trackUrl,
                                                              kCCHTTPRequestMethodGET);
        request->start();
    }
}
// ----------------------------------------

StartupCall *StartupCall::create(AppDelegate *app)
{
    StartupCall *call = new StartupCall();
    call->m_app = app;
    call->autorelease();
    return call;
}

void StartupCall::startup()
{
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    CCLuaStack *pStack = pEngine->getLuaStack();

    ProjectConfig &projectConfig = m_app->m_projectConfig;

    // set search path
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(projectConfig.getScriptFileRealPath().c_str());
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
        pStack->addSearchPath(workdir.c_str());
    }

    // connect debugger
    if (projectConfig.getDebuggerType() != kCCLuaDebuggerNone)
    {
        pStack->connectDebugger(projectConfig.getDebuggerType(), NULL, 0, NULL, workdir.c_str());
    }

    // load framework
    if (projectConfig.isLoadPrecompiledFramework())
    {
        const string precompiledFrameworkPath = SimulatorConfig::sharedDefaults()->getPrecompiledFrameworkPath();
        pStack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
    }

    // set default scene
    CCScene *scene = CCScene::create();
    if (CCDirector::sharedDirector()->getRunningScene())
    {
        CCDirector::sharedDirector()->replaceScene(scene);
    }
    else
    {
        CCDirector::sharedDirector()->runWithScene(scene);
    }

    // load script
    string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    pEngine->executeString(env.c_str());
    
    // set open recents
    lua_State *L = pEngine->getLuaStack()->getLuaState();
    lua_newtable(L);
    int i = 1;
    for (CCLuaValueArrayIterator it = m_app->m_openRecents.begin(); it != m_app->m_openRecents.end(); ++it)
    {
        lua_pushstring(L, it->stringValue().c_str());
        lua_rawseti(L, -2, i);
        ++i;
    }
    lua_setglobal(L, "__G__OPEN_RECENTS__");

    // set quick-cocos2d-x root path
    std::string quickPath = SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
    lua_pushstring(L, quickPath.c_str());
    lua_setglobal(L, "__G__QUICK_PATH__");
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());
}
