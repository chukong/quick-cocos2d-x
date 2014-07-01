/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "Updater.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
#include <curl/curl.h>
#include <curl/easy.h>

#include <stdio.h>
#include <vector>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif

#include "support/zip_support/unzip.h"
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;
using namespace std;

NS_CC_EXT_BEGIN;

#define KEY_OF_VERSION   "current-version-code"
#define KEY_OF_DOWNLOADED_VERSION    "downloaded-version-code"
#define TEMP_PACKAGE_FILE_NAME    "cocos2dx-update-temp-package.zip"
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

// Message type
#define UPDATER_MESSAGE_UPDATE_SUCCEED                0
#define UPDATER_MESSAGE_RECORD_DOWNLOADED_VERSION     1
#define UPDATER_MESSAGE_PROGRESS                      2
#define UPDATER_MESSAGE_ERROR                         3

// Some data struct for sending messages

struct ErrorMessage
{
    Updater::ErrorCode code;
    Updater* manager;
};

struct ProgressMessage
{
    int percent;
    Updater* manager;
};

// Implementation of Updater

Updater::Updater(const char* packageUrl/* =NULL */, const char* versionFileUrl/* =NULL */, const char* storagePath/* =NULL */)
:  _storagePath(storagePath)
, _version("")
, _packageUrl(packageUrl)
, _versionFileUrl(versionFileUrl)
, _downloadedVersion("")
, _curl(NULL)
, _tid(NULL)
, _connectionTimeout(0)
, _delegate(NULL)
, _scriptHandler(0)
, _zipUrl("")
, _zipFile("")
, _unzipTmpDir("")
, _updateInfoString("")
{
    checkStoragePath();
    _schedule = new Helper();
}

Updater::~Updater()
{
    if (_schedule)
    {
        _schedule->release();
    }
    unregisterScriptHandler();
}

void Updater::checkStoragePath()
{
    if (_storagePath.size() > 0 && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.append("/");
    }
}

static size_t getUpdateInfoFun(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *updateInfo = (string*)userdata;
    updateInfo->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}

const char* Updater::getUpdateInfo(const char* url)
{
    CCLOG("Updater::getUpdateInfo(%s)", url);
    _curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return "";
    }
    
    _updateInfoString.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getUpdateInfoFun);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_updateInfoString);
    if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("can not get version file content %s, error code is %d", url, res);
        curl_easy_cleanup(_curl);
        return "";
    }
    
    return _updateInfoString.c_str();
}

void* assetsManagerDownloadAndUncompress(void *data)
{
    Updater* self = (Updater*)data;
    
    do
    {
        if (! self->downLoad(self->_zipUrl.c_str(), self->_zipFile.c_str())) break;
        
        // Uncompress zip file.
        if (! self->uncompress(self->_zipFile.c_str(), self->_unzipTmpDir.c_str()))
        {
            self->sendErrorMessage(Updater::kUncompress);
            break;
        }
        
        // Record updated version and remove downloaded zip file
        Updater::Message *msg2 = new Updater::Message();
        msg2->what = UPDATER_MESSAGE_UPDATE_SUCCEED;
        msg2->obj = self;
        self->_schedule->sendMessage(msg2);
    } while (0);
    
    if (self->_tid)
    {
        delete self->_tid;
        self->_tid = NULL;
    }
    
    return NULL;
}

void Updater::update(const char* zipUrl, const char* zipFile, const char* unzipTmpDir)
{
    if (_tid) return;
    
    _zipUrl.clear();
    _zipUrl.append(zipUrl);
    _zipFile.clear();
    _zipFile.append(zipFile);
    _unzipTmpDir.clear();
    _unzipTmpDir.append(unzipTmpDir);
    
    // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
    if (_zipUrl.size() == 0 ||
        _zipFile.size() == 0 ||
        std::string::npos == _zipUrl.find(".zip"))
    {
        CCLOG("no version file url, or no package url, or the package is not a zip file");
        return;
    }
    
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, assetsManagerDownloadAndUncompress, this);
}

bool Updater::uncompress(const char* zipFilePath, const char* unzipTmpDir)
{
    // Create unzipTmpDir
    if(CCFileUtils::sharedFileUtils()->isFileExist(unzipTmpDir))
    {
        this->removeDirectory(unzipTmpDir);
    }
    this->createDirectory(unzipTmpDir);
    
    // Open the zip file
    string outFileName = std::string(zipFilePath);
    unzFile zipfile = unzOpen(outFileName.c_str());
    if (! zipfile)
    {
        CCLOG("can not open downloaded zip file %s", outFileName.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    
    CCLOG("start uncompressing");
    
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return false;
        }
        
        string fullPath = std::string(unzipTmpDir) + fileName;
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
			// get all dir
			string fileNameStr = string(fileName);
			size_t position = 0;
			while((position=fileNameStr.find_first_of("/",position))!=string::npos)
			{
				string dirPath =unzipTmpDir + fileNameStr.substr(0, position);
				// Entry is a direcotry, so create it.
				// If the directory exists, it will failed scilently.
				if (!createDirectory(dirPath.c_str()))
				{
						CCLOG("can not create directory %s", dirPath.c_str());
						//unzClose(zipfile);
						//return false;
				}
				position++;
			}
        }
        else
        {
            // Entry is a file, so extract it.
            
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not open file %s", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (! out)
            {
                CCLOG("can not open destination file %s", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("can not read zip file %s, error code is %d", fileName, error);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    CCLOG("end uncompressing");
    
    return true;
}

bool Updater::removeDirectory(const char* path)
{
    int succ = -1;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + string(path) + "\"";
    succ = system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + pathToSave + "\"";
    succ = system(command.c_str());
#endif
    if(succ != 0)
    {
        return false;
    }
    return true;
}

/*
 * Create a direcotry is platform depended.
 */
bool Updater::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
    return true;
#endif
}

void Updater::setSearchPath()
{
    vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    vector<string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, _storagePath);
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
}

static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

int assetsManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    Updater* manager = (Updater*)ptr;
    Updater::Message *msg = new Updater::Message();
    msg->what = UPDATER_MESSAGE_PROGRESS;
    
    ProgressMessage *progressData = new ProgressMessage();
    progressData->percent = (int)(nowDownloaded/totalToDownload*100);
    progressData->manager = manager;
    msg->obj = progressData;
    
    manager->_schedule->sendMessage(msg);
    
    CCLOG("downloading... %d%%", (int)(nowDownloaded/totalToDownload*100));
    
    return 0;
}

bool Updater::downLoad(const char* zipUrl, const char* zipFile)
{
    // Create a file to save package.
    string outFileName = string(zipFile);
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (! fp)
    {
        sendErrorMessage(kCreateFile);
        CCLOG("can not create file %s", outFileName.c_str());
        return false;
    }
    
    // Download pacakge
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, zipUrl);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, assetsManagerProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("error when download package");
        fclose(fp);
        return false;
    }
    
    CCLOG("succeed downloading package %s", zipUrl);
    
    fclose(fp);
    return true;
}

const char* Updater::getPackageUrl() const
{
    return _packageUrl.c_str();
}

void Updater::setPackageUrl(const char *packageUrl)
{
    _packageUrl = packageUrl;
}

const char* Updater::getStoragePath() const
{
    return _storagePath.c_str();
}

void Updater::setStoragePath(const char *storagePath)
{
    _storagePath = storagePath;
    checkStoragePath();
}

const char* Updater::getVersionFileUrl() const
{
    return _versionFileUrl.c_str();
}

void Updater::setVersionFileUrl(const char *versionFileUrl)
{
    _versionFileUrl = versionFileUrl;
}

void Updater::deleteVersion()
{
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, "");
}

void Updater::setDelegate(UpdaterDelegateProtocol *delegate)
{
    _delegate = delegate;
}

void Updater::registerScriptHandler(int handler)
{
    unregisterScriptHandler();
    _scriptHandler = handler;
}

void Updater::unregisterScriptHandler(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptHandler);
    _scriptHandler = 0;
}

void Updater::setConnectionTimeout(unsigned int timeout)
{
    _connectionTimeout = timeout;
}

unsigned int Updater::getConnectionTimeout()
{
    return _connectionTimeout;
}

void Updater::sendErrorMessage(Updater::ErrorCode code)
{
    Message *msg = new Message();
    msg->what = UPDATER_MESSAGE_ERROR;
    
    ErrorMessage *errorMessage = new ErrorMessage();
    errorMessage->code = code;
    errorMessage->manager = this;
    msg->obj = errorMessage;
    
    _schedule->sendMessage(msg);
}

// Implementation of UpdaterHelper

Updater::Helper::Helper()
{
    _messageQueue = new list<Message*>();
    pthread_mutex_init(&_messageQueueMutex, NULL);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

Updater::Helper::~Helper()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    delete _messageQueue;
}

void Updater::Helper::sendMessage(Message *msg)
{
    pthread_mutex_lock(&_messageQueueMutex);
    _messageQueue->push_back(msg);
    pthread_mutex_unlock(&_messageQueueMutex);
}

void Updater::Helper::update(float dt)
{
    Message *msg = NULL;
    
    // Returns quickly if no message
    pthread_mutex_lock(&_messageQueueMutex);
    if (0 == _messageQueue->size())
    {
        pthread_mutex_unlock(&_messageQueueMutex);
        return;
    }
    
    // Gets message
    msg = *(_messageQueue->begin());
    _messageQueue->pop_front();
    pthread_mutex_unlock(&_messageQueueMutex);
    
    switch (msg->what) {
        case UPDATER_MESSAGE_UPDATE_SUCCEED:
            handleUpdateSucceed(msg);
            
            break;
        case UPDATER_MESSAGE_PROGRESS:
            if (((ProgressMessage*)msg->obj)->manager->_delegate)
            {
                ((ProgressMessage*)msg->obj)->manager->_delegate->onProgress(((ProgressMessage*)msg->obj)->percent);
            }
            if (((ProgressMessage*)msg->obj)->manager->_scriptHandler)
            {
                char buff[10];
                sprintf(buff, "%d", ((ProgressMessage*)msg->obj)->percent);
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(((ProgressMessage*)msg->obj)->manager->_scriptHandler, buff);
            }
            
            delete (ProgressMessage*)msg->obj;
            
            break;
        case UPDATER_MESSAGE_ERROR:
            // error call back
            if (((ErrorMessage*)msg->obj)->manager->_delegate)
            {
                ((ErrorMessage*)msg->obj)->manager->_delegate->onError(((ErrorMessage*)msg->obj)->code);
            }
            if (((ProgressMessage*)msg->obj)->manager->_scriptHandler)
            {
                std::string errorMessage;
                switch ((int)((ErrorMessage*)msg->obj)->code)
                {
                case kCreateFile:
                    errorMessage = "errorCreateFile";
                    break;
            
                case kNetwork:
                    errorMessage = "errorNetwork";
                    break;

                case kNoNewVersion:
                    errorMessage = "errorNoNewVersion";
                    break;

                case kUncompress:
                    errorMessage = "errorUncompress";
                    break;

                default:
                    errorMessage = "errorUnknown";
                }

                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(((ProgressMessage*)msg->obj)->manager->_scriptHandler, errorMessage.c_str());
            }

            delete ((ErrorMessage*)msg->obj);
            
            break;
        default:
            break;
    }
    
    delete msg;
}

void Updater::Helper::handleUpdateSucceed(Message *msg)
{
    Updater* manager = (Updater*)msg->obj;
    
    // Record new version code.
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, manager->_version.c_str());
    
    // Unrecord downloaded version code.
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, "");
    CCUserDefault::sharedUserDefault()->flush();
    
    // Set resource search path.
    manager->setSearchPath();
    
    // Delete unloaded zip file.
    string zipfileName = manager->_zipFile;
    if (remove(zipfileName.c_str()) != 0)
    {
        CCLOG("can not remove downloaded zip file %s", zipfileName.c_str());
    }
    
    if (manager)
    {
        if (manager->_delegate)
        {
            manager->_delegate->onSuccess();
}
        if (manager->_scriptHandler)
        {
            CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(manager->_scriptHandler, "success");
        }
    }
}

NS_CC_EXT_END;
#endif // CC_PLATFORM_WINRT
