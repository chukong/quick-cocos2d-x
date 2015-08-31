
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocoa/CCObject.h"
#include "CCApplication.h"
#include "ProjectConfig/SimulatorConfig.h"

class StartupCall;

/**
 @brief    The cocos2d Application.

 The reason for implement as private inheritance is to hide some interface call by CCDirector.
 */
class  AppDelegate : public cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
     @brief    Implement CCDirector and CCScene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();

    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();

    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();

    void setProjectConfig(const ProjectConfig& config);
    void setOpenRecents(const CCLuaValueArray& recents);

private:
    // track event
    void trackEvent(const char *eventName);
    void trackLaunchEvent();
    
private:
    ProjectConfig m_projectConfig;
    CCLuaValueArray m_openRecents;

    friend class StartupCall;
};

class StartupCall : public CCObject
{
public:
    static StartupCall *create(AppDelegate *app);
    void startup();

private:
    AppDelegate *m_app;
};

#endif // _APP_DELEGATE_H_
