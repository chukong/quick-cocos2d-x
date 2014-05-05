#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCDirector.h"
#include <algorithm>
#include "platform/CCFileUtils.h"

#include <QApplication>
#include <QLocale>
#include <QObject>
#include <QDir>

class Cocos2DQt5MainloopIntegration : public QObject {
    public:
        Cocos2DQt5MainloopIntegration()
            : QObject()
            , m_timer(0)
        {
        }

        void setInterval(int interval_ms)
        {
            if (m_timer != 0) {
                killTimer(m_timer);
            }

            m_timer = startTimer(interval_ms);
        }

    protected:
        virtual void timerEvent(QTimerEvent */*event*/)
        {
//            cocos2d::CCDirector::sharedDirector()->mainLoop();
        }

    private:
        int m_timer;
};

/**
@brief    This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/
static void PVRFrameEnableControlWindow(bool bEnable);

NS_CC_BEGIN


// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication(int argc, char *argv[])
    : m_application(NULL)
    , m_mainloop(new Cocos2DQt5MainloopIntegration)
{
    m_nAnimationInterval = 1.0f / 60.0f * 1000.0f;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;

    m_application = new QApplication(argc, argv);
}

CCApplication::~CCApplication()
{
    delete m_mainloop;
    delete m_application;

    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
//    // Initialize instance and cocos2d.
//    if (! applicationDidFinishLaunching())
//    {
//        return 0;
//    }

//    m_mainloop->setInterval(m_nAnimationInterval);

    return m_application->exec();
}

void CCApplication::setAnimationInterval(double interval)
{
    m_nAnimationInterval = interval * 1000.0f;
    m_mainloop->setInterval(m_nAnimationInterval);

    CCEGLView::sharedOpenGLView()->setInterval(m_nAnimationInterval);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

cocos2d::ccLanguageType CCApplication::getCurrentLanguage()
{
    switch (QLocale::system().language())
    {
    case QLocale::Chinese: return cocos2d::kLanguageChinese;
    case QLocale::French:  return cocos2d::kLanguageFrench;
    case QLocale::Italian: return cocos2d::kLanguageItalian;
    case QLocale::German:  return cocos2d::kLanguageGerman;
    case QLocale::Spanish: return cocos2d::kLanguageSpanish;
    case QLocale::Russian: return cocos2d::kLanguageRussian;

    return cocos2d::kLanguageEnglish;
    }
}

cocos2d::TargetPlatform CCApplication::getTargetPlatform()
{
    cocos2d::TargetPlatform platform = cocos2d::kTargetWindows;
#if defined(Q_OS_MAC) || defined(Q_OS_OSX)
    platform = cocos2d::kTargetMacOS;
#elif defined(Q_OS_UNIX)
    platform = cocos2d::kTargetLinux;
#endif
    return platform;
}

void CCApplication::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    int pos;
    while ((pos = m_startupScriptFilename.find_first_of("\\")) != std::string::npos)
    {
        m_startupScriptFilename.replace(pos, 1, "/");
    }
}

//#include "CCApplication.moc"
NS_CC_END

