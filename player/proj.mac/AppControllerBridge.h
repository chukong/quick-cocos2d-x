
#include "cocos2d.h"

using namespace cocos2d;

class AppControllerBridge : public CCObject
{
public:
    AppControllerBridge(void *controller)
    : m_controller(controller)
    {
    }
    
    void onWelcomeNewProject(void);
    void onWelcomeOpen(void);
    void onWelcomeSamples(void);
    void onWelcomeGetStarted(void);

private:
    void *m_controller;
};
