
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "support/CCNotificationCenter.h"
#include "CCLuaEngine.h"
#include <string>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
#include "player.h"
#endif

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
AppDelegate::AppDelegate(int argc, char *argv[])
    : CCApplication(argc, argv)
#else
AppDelegate::AppDelegate()
#endif
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
    // regist my own lua
    Player::registerAllCpp();
#endif

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
