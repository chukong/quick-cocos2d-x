
#include "ProjectConfig.h"

#if defined(_WINDOWS)
#define DIRECTORY_SEPARATOR "\\"
#else
#define DIRECTORY_SEPARATOR "/"
#endif

void normalizePath(string &path, const char *directorySeparator = NULL)
{
    if (!directorySeparator) directorySeparator = DIRECTORY_SEPARATOR;
    int pos = -1;
    while ((pos = path.find_first_of("/\\", pos + 1)) != std::string::npos)
    {
        path.replace(pos, 1, directorySeparator);
    }
}

void ProjectConfig::normalize(void)
{
    normalizePath(projectDir);
    normalizePath(scriptFile);
}

void ProjectConfig::normalizeUnixStyle(void)
{
    normalizePath(projectDir, "/");
    normalizePath(scriptFile, "/");
}

ProjectConfigDefaults *ProjectConfigDefaults::s_sharedInstance = NULL;

ProjectConfigDefaults *ProjectConfigDefaults::sharedDefaults(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new ProjectConfigDefaults();
    }
    return s_sharedInstance;
}

ProjectConfigDefaults::ProjectConfigDefaults(void)
{
    m_screenSizeArray.push_back(ScreenSizeDescription("iPhone 3Gs (320x480)", 320, 480));
    m_screenSizeArray.push_back(ScreenSizeDescription("iPhone 4 (640x960)", 640, 960));
    m_screenSizeArray.push_back(ScreenSizeDescription("iPhone 5 (640x1136)", 640, 1136));
    m_screenSizeArray.push_back(ScreenSizeDescription("iPad (768x1024)", 768, 1024));
    m_screenSizeArray.push_back(ScreenSizeDescription("iPad Retina (1536x2048)", 1536, 2048));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (480x800)", 480, 800));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (480x854)", 480, 854));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (600x1024)", 600, 1024));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (768x1024)", 768, 1024));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (720x1280)", 720, 1280));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (800x1280)", 800, 1280));
    m_screenSizeArray.push_back(ScreenSizeDescription("Android (1080x1920)", 1080, 1920));
}

ScreenSizeDescription ProjectConfigDefaults::getScreenSize(int index)
{
    return m_screenSizeArray.at(index);
}

int ProjectConfigDefaults::checkScreenSize(int width, int height)
{
    if (width > height)
    {
        int w = width;
        width = height;
        height = w;
    }

    for (int i = 0; i < m_screenSizeArray.size(); ++i)
    {
        const ScreenSizeDescription &size = m_screenSizeArray[i];
        if (size.width == width && size.height == height)
        {
            return i;
        }
    }

    return -1;
}
