
#include "SimulatorConfig.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

void ProjectConfig::setProjectDir(const string projectDir)
{
    m_projectDir = projectDir;
    normalize();
}

const string ProjectConfig::getScriptFilePath(void)
{
    string path(m_scriptFile);
    if (path.substr(0, 9).compare("$WORKDIR\\") == 0)
    {
        path = path.substr(9);
    }
    if (path.length() < 2 || path[1] != ':')
    {
        path = m_projectDir + path;
    }
    return path;
}

void ProjectConfig::setScriptFile(const string scriptFile)
{
    m_scriptFile = scriptFile;
    normalize();
}

const string ProjectConfig::getNormalizedPackagePath(void)
{
    // replace $WORKDIR
    string path = m_packagePath;
    int pos = std::string::npos;
    while ((pos = path.find("$WORKDIR")) != std::string::npos)
    {
        path = path.substr(0, pos) + m_projectDir + path.substr(pos + 8);
    }
    size_t len = path.length();
    if (len && path[len - 1] != ';')
    {
        path.append(";");
    }
    path.append(";");
    SimulatorConfig::makeNormalizePath(&path, "/");
    return path;
}

void ProjectConfig::addPackagePath(const string packagePath)
{
    if (packagePath.length())
    {
        if (m_packagePath.length())
        {
            m_packagePath.append(";");
        }
        m_packagePath.append(packagePath);
        normalize();
    }
}

const vector<string> ProjectConfig::getPackagePathArray(void)
{
    vector<string> arr;

    int pos = std::string::npos;
    int prev = 0;
    while ((pos = m_packagePath.find_first_of(";", pos + 1)) != std::string::npos)
    {
        string path = m_packagePath.substr(prev, pos - prev);
        if (path.length() > 0) arr.push_back(path);
        prev = pos + 1;
    }
    string path = m_packagePath.substr(prev);
    if (path.length() > 0) arr.push_back(path);
    return arr;
}

void ProjectConfig::normalize(void)
{
    SimulatorConfig::makeNormalizePath(&m_projectDir);
    SimulatorConfig::makeNormalizePath(&m_scriptFile);
    SimulatorConfig::makeNormalizePath(&m_packagePath);

    int len = m_projectDir.length();
    if (len > 0 && m_projectDir[len - 1] != DIRECTORY_SEPARATOR_CHAR)
    {
        m_projectDir.append(DIRECTORY_SEPARATOR);
    }

    int projectDirLength = m_projectDir.length();
    if (projectDirLength > 0)
    {
        if (strcasecmp(m_scriptFile.substr(0, projectDirLength).c_str(), m_projectDir.c_str()) == 0)
        {
            m_scriptFile = string("$WORKDIR\\").append(m_scriptFile.substr(projectDirLength));
        }

        vector<string> arr = getPackagePathArray();
        m_packagePath = string("");
        for (vector<string>::iterator it = arr.begin(); it != arr.end(); ++it)
        {
            string path = *it;
            if (strcasecmp(path.substr(0, projectDirLength).c_str(), m_projectDir.c_str()) == 0)
            {
                path = string("$WORKDIR\\").append(path.substr(projectDirLength));
            }
            m_packagePath.append(path);
            m_packagePath.append(";");
        }
    }

    if (m_packagePath.length() > 0 && m_packagePath[m_packagePath.length() - 1] == ';')
    {
        m_packagePath = m_packagePath.substr(0, m_packagePath.length() - 1);
    }
}


// SimulatorConfig

SimulatorConfig *SimulatorConfig::s_sharedInstance = NULL;

SimulatorConfig *SimulatorConfig::sharedDefaults(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new SimulatorConfig();
    }
    return s_sharedInstance;
}

SimulatorConfig::SimulatorConfig(void)
{
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (320x480)", 320, 480));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (640x960)", 640, 960));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (640x1136)", 640, 1136));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad (768x1024)", 768, 1024));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (1536x2048)", 1536, 2048));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (480x800)", 480, 800));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (480x854)", 480, 854));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (600x1024)", 600, 1024));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (768x1024)", 768, 1024));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (720x1280)", 720, 1280));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (800x1280)", 800, 1280));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1080x1920)", 1080, 1920));
}

int SimulatorConfig::checkScreenSize(const CCSize& size)
{
    int width = size.width;
    int height = size.height;

    if (width > height)
    {
        int w = width;
        width = height;
        height = w;
    }

    int count = (int)m_screenSizeArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorScreenSize &size = m_screenSizeArray[i];
        if (size.width == width && size.height == height)
        {
            return i;
        }
    }

    return -1;
}


// helper

void SimulatorConfig::makeNormalizePath(string *path, const char *directorySeparator/* = NULL*/)
{
    if (!directorySeparator) directorySeparator = DIRECTORY_SEPARATOR;
    int pos = std::string::npos;
    while ((pos = path->find_first_of("/\\", pos + 1)) != std::string::npos)
    {
        path->replace(pos, 1, directorySeparator);
    }
}
