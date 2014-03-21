
#include "AppControllerBridge.h"
#import "AppController.h"

void AppControllerBridge::onWelcomeNewProject(CCObject *object)
{
    [(AppController*)m_controller welcomeNewProject];
}

void AppControllerBridge::onWelcomeOpenProject(CCObject *object)
{
    [(AppController*)m_controller welcomeOpenProject];
}

void AppControllerBridge::onWelcomeListSamples(CCObject *object)
{
    [(AppController*)m_controller welcomeListSamples];
}

void AppControllerBridge::onWelcomeOpenDocuments(CCObject *object)
{
    [(AppController*)m_controller welcomeOpenDocuments];
}

void AppControllerBridge::onWelcomeOpenCommunity(CCObject *object)
{
    [(AppController*)m_controller welcomeOpenCommunity];
}
