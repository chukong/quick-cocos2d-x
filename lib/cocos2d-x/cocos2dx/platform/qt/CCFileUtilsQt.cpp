/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCFileUtilsQt.h"
#include "platform/CCCommon.h"

// Qt
#include <QApplication>
#include <QFileInfo>
#include <QDir>

using namespace std;

NS_CC_BEGIN

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsWin32();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsWin32::CCFileUtilsWin32()
{
}

bool CCFileUtilsWin32::init()
{
    m_strDefaultResRootPath = qApp->applicationDirPath().append('/').toLocal8Bit().constData();
    return CCFileUtils::init();
}

bool CCFileUtilsWin32::isFileExist(const std::string& strFilePath)
{
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, m_strDefaultResRootPath);
    }
    QFileInfo fileInfo(strPath.c_str());
    return fileInfo.exists();
}

bool CCFileUtilsWin32::isDirectoryExist(const string &strDirPath)
{
    QDir dir(strDirPath.data());
    return dir.exists();
}

bool CCFileUtilsWin32::isAbsolutePath(const std::string& strPath)
{
    QFileInfo fileInfo(strPath.c_str());
    return fileInfo.isAbsolute();
}

string CCFileUtilsWin32::getWritablePath()
{
    std::string ret(qApp->applicationDirPath().toLocal8Bit().constData());
    return ret;
}

NS_CC_END
