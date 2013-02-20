#pragma once

#include <string>
#include <vector>

using namespace std;

typedef struct _ProjectConfig
{
    std::string projectDir;
    std::string scriptFile;
    float frameWidth;
    float frameHeight;
    float frameScale;
    bool showConsole;
    int windowLeft;
    int windowTop;

    _ProjectConfig(void)
    : scriptFile("scripts/main.lua")
    , frameWidth(320)
    , frameHeight(480)
    , frameScale(1.0f)
    , showConsole(true)
    , windowLeft(-1)
    , windowTop(-1)
    {
    }
} ProjectConfig;


typedef struct _ScreenSizeDescription {
    string title;
    int width;
    int height;

    _ScreenSizeDescription(const char *title_, int width_, int height_)
    {
        title = title_;
        width = width_;
        height = height_;
    }
} ScreenSizeDescription;

typedef vector<ScreenSizeDescription> ScreenSizeArray;
typedef ScreenSizeArray::iterator ScreenSizeArrayIterator;

class ProjectConfigDefaults
{
public:
    static ProjectConfigDefaults *sharedDefaults(void);
    
    int getScreenSizeCount(void) {
        return m_screenSizeArray.size();
    }
    ScreenSizeDescription getScreenSize(int index);
    int checkScreenSize(int width, int height);
    bool isLandscape(int width, int height) {
        return width > height;
    }
    
private:
    ProjectConfigDefaults(void);

    static ProjectConfigDefaults *s_sharedInstance;
    ScreenSizeArray m_screenSizeArray;
};

