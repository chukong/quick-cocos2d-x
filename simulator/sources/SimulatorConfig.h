#ifndef __PROJECT_CONFIG_H_
#define __PROJECT_CONFIG_H_

#include <string>
#include <vector>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

#if defined(_WINDOWS)
#define DIRECTORY_SEPARATOR "\\"
#define DIRECTORY_SEPARATOR_CHAR '\\'
#else
#define DIRECTORY_SEPARATOR "/"
#define DIRECTORY_SEPARATOR_CHAR '/'
#endif

class ProjectConfig
{
public:
    ProjectConfig(void)
    : m_scriptFile("$WORKDIR/scripts/main.lua")
    , m_packagePath("")
    , m_frameSize(320, 480)
    , m_frameScale(1.0f)
    , m_showConsole(true)
    , m_loadPrecompiledFramework(true)
    , m_windowOffset(-1, -1)
    {
        normalize();
    }

    const string getProjectDir(void) {
        return m_projectDir;
    }
    void setProjectDir(const string projectDir);

    const string getScriptFile(void) {
        return m_scriptFile;
    }
    const string getScriptFilePath(void);
    void setScriptFile(const string scriptFile);

    const string getPackagePath(void) {
        return m_packagePath;
    }
    const string getNormalizedPackagePath(void);
    void setPackagePath(const string packagePath) {
        m_packagePath = packagePath;
    }
    void addPackagePath(const string packagePath);
    const vector<string> getPackagePathArray(void);

    const CCSize getFrameSize(void) {
        return m_frameSize;
    }
    void setFrameSize(CCSize frameSize) {
        CCAssert(frameSize.width > 0 && frameSize.height > 0, "Invalid frameSize");
        m_frameSize = frameSize;
    }
    bool isLandscapeFrame(void) {
        return m_frameSize.width > m_frameSize.height;
    }

    const float getFrameScale(void) {
        return m_frameScale;
    }
    void setFrameScale(float frameScale) {
        CCAssert(frameScale > 0, "Invalid frameScale");
        m_frameScale = frameScale;
    }

    const bool isShowConsole(void) {
        return m_showConsole;
    }
    void setShowConsole(bool showConsole) {
        m_showConsole = showConsole;
    }

    const bool isLoadPrecompiledFramework(void) {
        return m_loadPrecompiledFramework;
    }
    void setLoadPrecompiledFramework(bool loadPrecompiledFramework) {
        m_loadPrecompiledFramework = loadPrecompiledFramework;
    }

    const CCPoint getWindowOffset(void) {
        return m_windowOffset;
    }
    void setWindowOffset(CCPoint windowOffset) {
        m_windowOffset = windowOffset;
    }

private:
    string	m_projectDir;
    string	m_scriptFile;
    string	m_packagePath;
    CCSize	m_frameSize;
    float	m_frameScale;
    bool	m_showConsole;
    bool	m_loadPrecompiledFramework;
    CCPoint	m_windowOffset;

    void normalize(void);
};


// SimulatorConfig

typedef struct _SimulatorScreenSize {
    string title;
    int width;
    int height;

    _SimulatorScreenSize(const string title_, int width_, int height_)
    {
        title  = title_;
        width  = width_;
        height = height_;
    }
} SimulatorScreenSize;

class SimulatorConfig
{
public:
    static SimulatorConfig *sharedDefaults(void);
    
    int numScreenSize(void) {
        return m_screenSizeArray.size();
    }
    const SimulatorScreenSize getScreenSize(int index) {
        return m_screenSizeArray.at(index);
    }
    int checkScreenSize(const CCSize& size);

    // helper
    static void makeNormalizePath(string *path, const char *directorySeparator = NULL);
    
private:
    SimulatorConfig(void);

    static SimulatorConfig *s_sharedInstance;

    typedef vector<SimulatorScreenSize> ScreenSizeArray;
    typedef ScreenSizeArray::iterator ScreenSizeArrayIterator;
    ScreenSizeArray m_screenSizeArray;
};

#endif /* __PROJECT_CONFIG_H_ */
