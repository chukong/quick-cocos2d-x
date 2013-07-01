
#include "AppControllerBridge.h"
#import "AppController.h"

void AppControllerBridge::onWelcomeNewProject(void)
{
    [(AppController*)m_controller welcomeNewProject];
}

void AppControllerBridge::onWelcomeOpen(void)
{
    [(AppController*)m_controller welcomeOpen];
}

void AppControllerBridge::onWelcomeSamples(void)
{
    [(AppController*)m_controller welcomeSamples];
}

void AppControllerBridge::onWelcomeGetStarted(void)
{
    [(AppController*)m_controller welcomeGetStarted];
}
