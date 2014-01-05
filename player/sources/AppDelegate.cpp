
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "support/CCNotificationCenter.h"
#include "CCLuaEngine.h"
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

void AppDelegate::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
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

    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());
}
