
#include "SimulatorConfig.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

void ProjectConfig::setProjectDir(const char *projectDir)
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

void ProjectConfig::setScriptFile(const char *scriptFile)
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
	return path;
}

const vector<string> ProjectConfig::getPackagePathArray(void)
{
	vector<string> arr;

	int pos = std::string::npos;
	int prev = 0;
	while ((pos = m_packagePath.find_first_of(";", pos + 1)) != std::string::npos)
	{
		arr.push_back(m_packagePath.substr(prev, pos - prev));
		prev = pos + 1;
	}
	arr.push_back(m_packagePath.substr(prev));
	return arr;
}

void ProjectConfig::normalize(void)
{
    SimulatorConfig::makeNormalizePath(&m_projectDir);
    SimulatorConfig::makeNormalizePath(&m_scriptFile);
	SimulatorConfig::makeNormalizePath(&m_packagePath, "/");

	int len = m_projectDir.length();
	if (len > 0 && m_projectDir[len - 1] != DIRECTORY_SEPARATOR_CHAR)
	{
		m_projectDir.append(DIRECTORY_SEPARATOR);
	}

	if (m_scriptFile.length() >= 1 && m_scriptFile[0] == '$') return;

	int projectDirLength = m_projectDir.length();
	if (strcasecmp(m_scriptFile.substr(0, projectDirLength).c_str(), m_projectDir.c_str()) == 0)
	{
		m_scriptFile = string("$WORKDIR\\").append(m_scriptFile.substr(projectDirLength));
	}
}

void ProjectConfig::normalizeUnixStyle(void)
{
    SimulatorConfig::makeNormalizePath(&m_projectDir, "/");
    SimulatorConfig::makeNormalizePath(&m_scriptFile, "/");
	SimulatorConfig::makeNormalizePath(&m_packagePath, "/");

	int len = m_projectDir.length();
	if (len > 0 && m_projectDir[len - 1] != '/')
	{
		m_projectDir.append("/");
	}
}


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
