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
    : m_scriptFile("")
    , m_writablePath("")
    , m_packagePath("")
    , m_frameSize(320, 480)
    , m_frameScale(1.0f)
    , m_showConsole(true)
    , m_windowOffset(-1, -1)
    {
        normalize();
    }

    const string getProjectDir(void);
    void setProjectDir(const string projectDir);

    const string getScriptFile(void);
    const string getScriptFilePath(void);
    void setScriptFile(const string scriptFile);

    const string getPackagePath(void);
    const string getNormalizedPackagePath(void);
    void setPackagePath(const string packagePath);
    void addPackagePath(const string packagePath);
    const vector<string> getPackagePathArray(void);

    const string getWritablePath(void);
    void setWritablePath(const string writablePath);

    const CCSize getFrameSize(void);
    void setFrameSize(CCSize frameSize);
    bool isLandscapeFrame(void);

    const float getFrameScale(void);
    void setFrameScale(float frameScale);

    const bool isShowConsole(void);
    void setShowConsole(bool showConsole);

    const CCPoint getWindowOffset(void);
    void setWindowOffset(CCPoint windowOffset);

private:
    string	m_projectDir;
    string	m_scriptFile;
    string	m_packagePath;
    string  m_writablePath;
    CCSize	m_frameSize;
    float	m_frameScale;
    bool	m_showConsole;
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
