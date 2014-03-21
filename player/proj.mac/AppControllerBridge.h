
#include "cocos2d.h"

using namespace cocos2d;

class AppControllerBridge : public CCObject
{
public:
    AppControllerBridge(void *controller)
    : m_controller(controller)
    {
    }
    
    void onWelcomeNewProject(CCObject *object);
    void onWelcomeOpenProject(CCObject *object);
    void onWelcomeListSamples(CCObject *object);
    void onWelcomeOpenDocuments(CCObject *object);
    void onWelcomeOpenCommunity(CCObject *object);

private:
    void *m_controller;
};
