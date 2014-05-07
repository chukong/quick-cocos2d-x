#ifndef __PROJECT_CONFIG_H_
#define __PROJECT_CONFIG_H_

#include <string>
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

#if defined(_WINDOWS)
#define DIRECTORY_SEPARATOR "\\"
#define DIRECTORY_SEPARATOR_CHAR '\\'
#else
#define DIRECTORY_SEPARATOR "/"
#define DIRECTORY_SEPARATOR_CHAR '/'
#endif

#define kProjectConfigProjectDir                1
#define kProjectConfigScriptFile                2
#define kProjectConfigPackagePath               4
#define kProjectConfigWritablePath              8
#define kProjectConfigFrameSize                 16
#define kProjectConfigFrameScale                32
#define kProjectConfigShowConsole               64
#define kProjectConfigLoadPrecompiledFramework  128
#define kProjectConfigWriteDebugLogToFile       256
#define kProjectConfigWindowOffset              1024

#define kProjectConfigOpenRecent (kProjectConfigProjectDir | kProjectConfigScriptFile | kProjectConfigPackagePath | kProjectConfigWritablePath | kProjectConfigFrameSize | kProjectConfigFrameScale | kProjectConfigShowConsole | kProjectConfigLoadPrecompiledFramework | kProjectConfigWriteDebugLogToFile)

#define kProjectConfigAll (kProjectConfigProjectDir | kProjectConfigScriptFile | kProjectConfigPackagePath | kProjectConfigWritablePath | kProjectConfigFrameSize | kProjectConfigFrameScale | kProjectConfigShowConsole | kProjectConfigLoadPrecompiledFramework | kProjectConfigWriteDebugLogToFile | kProjectConfigWindowOffset)


class ProjectConfig
{
public:
    ProjectConfig(void)
    : m_isWelcome(false)
	, m_scriptFile("$PROJDIR/scripts/main.lua")
    , m_writablePath("")
    , m_packagePath("")
    , m_frameSize(960, 640)
    , m_frameScale(1.0f)
    , m_showConsole(true)
    , m_loadPrecompiledFramework(true)
    , m_writeDebugLogToFile(true)
    , m_windowOffset(0, 0)
    {
        normalize();
    }

	bool isWelcome(void) { return m_isWelcome; };
    void resetToWelcome(void);

    const string getProjectDir(void);
    void setProjectDir(const string projectDir);

    const string getScriptFile(void);
    const string getScriptFileRealPath(void);
    void setScriptFile(const string scriptFile);

    const string getWritablePath(void);
    const string getWritableRealPath(void);
    void setWritablePath(const string writablePath);

    const string getPackagePath(void);
    const string getNormalizedPackagePath(void);
    void setPackagePath(const string packagePath);
    void addPackagePath(const string packagePath);
    const vector<string> getPackagePathArray(void);

    const CCSize getFrameSize(void);
    void setFrameSize(CCSize frameSize);
    bool isLandscapeFrame(void);
    void changeFrameOrientation(void);
    void changeFrameOrientationToPortait(void);
    void changeFrameOrientationToLandscape(void);

    const float getFrameScale(void);
    void setFrameScale(float frameScale);

    const bool isShowConsole(void);
    void setShowConsole(bool showConsole);

    bool isLoadPrecompiledFramework(void);
    void setLoadPrecompiledFramework(bool load);

    const bool isWriteDebugLogToFile(void);
    void setWriteDebugLogToFile(bool writeDebugLogToFile);
    const string getDebugLogFilePath(void);

    const CCPoint getWindowOffset(void);
    void setWindowOffset(CCPoint windowOffset);

    void parseCommandLine(vector<string>& args);
    const string makeCommandLine(unsigned int mask = kProjectConfigAll);

    bool validate(void);
    void dump(void);

private:
	bool    m_isWelcome;
    string	m_projectDir;
    string	m_scriptFile;
    string	m_packagePath;
    string  m_writablePath;
    CCSize	m_frameSize;
    float	m_frameScale;
    bool	m_showConsole;
    bool    m_loadPrecompiledFramework;
    bool    m_writeDebugLogToFile;
    bool    m_restartProcess;
    CCPoint	m_windowOffset;

    void normalize(void);
    const string replaceProjectDirToMacro(const string& path);
    const string replaceProjectDirToFullPath(const string& path);
    bool isAbsolutePath(const string& path);
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

typedef vector<SimulatorScreenSize> ScreenSizeArray;
typedef ScreenSizeArray::iterator ScreenSizeArrayIterator;

class SimulatorConfig
{
public:
    static SimulatorConfig *sharedDefaults(void);

    // predefined screen size
    int getScreenSizeCount(void);
    const SimulatorScreenSize getScreenSize(int index);
    int checkScreenSize(const CCSize& size);

    // set quick-cocos2d-x root path
    void setQuickCocos2dxRootPath(const char *path);
    const string getQuickCocos2dxRootPath(void);

    // get precompiled framework path
    const string getPrecompiledFrameworkPath(void);

    // helper
    static void makeNormalizePath(string *path, const char *directorySeparator = NULL);

private:
    SimulatorConfig(void);

    static SimulatorConfig *s_sharedInstance;

    ScreenSizeArray m_screenSizeArray;
    string m_quickCocos2dxRootPath;
};

#endif /* __PROJECT_CONFIG_H_ */
