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

USING_NS_CC;
using namespace std;

NS_CC_EXT_BEGIN;

#define KEY_OF_VERSION   "current-version-code"
#define KEY_OF_DOWNLOADED_VERSION    "downloaded-version-code"
#define TEMP_PACKAGE_FILE_NAME    "cocos2dx-update-temp-package.zip"
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

// Message type
#define UPDATER_MESSAGE_UPDATE_SUCCEED                0
#define UPDATER_MESSAGE_STATE                         1
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

struct StateMessage
{
    Updater::StateCode code;
    Updater* manager;
};

// Implementation of Updater

Updater::Updater()
: _curl(NULL)
, _tid(NULL)
, _connectionTimeout(0)
, _delegate(NULL)
, _scriptHandler(0)
, _fileUrl("")
, _filePath("")
, _unzipTmpDir("")
, _updateInfoString("")
, _resetBeforeUnZIP(true)
, _updateType(kUpdateUndefined)
{
    //CCLOG("Updater::Updater()");
    _schedule = new Helper();
    CCDirector::sharedDirector()->getScheduler()
        ->scheduleUpdateForTarget(_schedule, 0, false);
}

Updater::~Updater()
{
    //CCLOG("Updater::~Updater()");
    if (_schedule)
    {
        CCDirector::sharedDirector()->getScheduler()
            ->unscheduleAllForTarget(_schedule);
        _schedule->release();
    }
    unregisterScriptHandler();
}

void Updater::checkUnZIPTmpDir()
{
    if (_unzipTmpDir.size() > 0 && _unzipTmpDir[_unzipTmpDir.size() - 1] != '/')
    {
        _unzipTmpDir.append("/");
    }
}

void Updater::clearOnSuccess()
{
    if(_updateType == kUpdateZIP)
    {
        // Delete unloaded zip file.
        if (remove(_filePath.c_str()) != 0)
        {
            CCLOG("Updater::clearOnSuccess Can not remove downloaded zip file %s", _filePath.c_str());
        }
    }
}

static size_t getUpdateInfoWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *updateInfo = (string*)userdata;
	CCLOG("getUpdateInfoWriteFunc %s", updateInfo->c_str());
    updateInfo->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}

static size_t downloadWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

const char* Updater::getUpdateInfo(const char* url)
{
    CCLOG("Updater::getUpdateInfo(%s)", url);
    _curl = curl_easy_init();
    if (! _curl)
    {
        sendErrorMessage(kNetwork);
        CCLOG("Updater::getUpdateInfo(%s) Can not init curl", url);
        return "";
    }
    
    _updateInfoString.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getUpdateInfoWriteFunc);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_updateInfoString);
    if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("Can not get update info content %s, error code is %d", url, res);
        return "";
    }
    
    return _updateInfoString.c_str();
}

void* updateThreadFunc(void *data)
{
    Updater* self = (Updater*)data;
    do
    {
        if (! self->download(self->_fileUrl.c_str(), self->_filePath.c_str())) break;
        if(self->_updateType == Updater::kUpdateZIP)
        {
            // Uncompress zip file.
            if (! self->uncompress(self->_filePath.c_str(), self->_unzipTmpDir.c_str(),self->_resetBeforeUnZIP))
            {
                self->sendErrorMessage(Updater::kUncompress);
                break;
            }
        }
        self->sendSuccMessage();
    } while (0);
    self->clearTid();
    return NULL;
}

void Updater::update(const char* zipUrl, const char* zipFile, const char* unzipTmpDir, bool resetBeforeUnZIP)
{
    if(!isAvailable()) return;
    
    _updateType = kUpdateZIP;
    
    _fileUrl.clear();
    _fileUrl.append(zipUrl);
    _filePath.clear();
    _filePath.append(zipFile);
    _unzipTmpDir.clear();
    _unzipTmpDir.append(unzipTmpDir);
    _resetBeforeUnZIP = resetBeforeUnZIP;
    
    checkUnZIPTmpDir();
    
    // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
    if (_fileUrl.size() == 0 ||
        _filePath.size() == 0 ||
        std::string::npos == _fileUrl.find(".zip"))
    {
        CCLOG("No version file url, or no package url, or the package is not a zip file");
        return;
    }
    
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, updateThreadFunc, this);
}

void Updater::update(cocos2d::CCArray *list)
{
    return;
    if(!isAvailable()) return;
    _updateType = kUpdateFiles;

    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, updateThreadFunc, this);
}

void Updater::update(const char* fileUrl)
{
    return;
    if(!isAvailable()) return;
    _updateType = kUpdateFileAsync;
    
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, updateThreadFunc, this);
}

void Updater::update(const char* fileUrl, const char* filePath)
{
    if(!isAvailable()) return;
    _updateType = kUpdateFile;
    _fileUrl.clear();
    _fileUrl.append(fileUrl);
    _filePath.clear();
    _filePath.append(filePath);
    
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, updateThreadFunc, this);
}

bool Updater::uncompress(const char* zipFilePath, const char* unzipTmpDir, bool resetBeforeUnZIP)
{
    if(resetBeforeUnZIP)
    {
        // Create unzipTmpDir
        if(CCFileUtils::sharedFileUtils()->isFileExist(unzipTmpDir))
        {
            this->removeDirectory(unzipTmpDir);
        }
    }
    
    this->createDirectory(unzipTmpDir);
    
    // Open the zip file
    string outFileName = std::string(zipFilePath);
    unzFile zipfile = unzOpen(outFileName.c_str());
    if (! zipfile)
    {
        CCLOG("Can not open downloaded zip file %s", outFileName.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("Can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    
    CCLOG("Start uncompressing");
    
    this->sendStateMessage(kUncompressStart);
    
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
            CCLOG("Can not read file info");
            unzClose(zipfile);
            return false;
        }
        
        //CCLOG("fullName:%s", fileName);
        string fullPath = std::string(unzipTmpDir) + fileName;
        
        //CCLOG("fullPath:%s", fullPath.c_str());
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
						CCLOG("Can not create directory %s", dirPath.c_str());
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
                CCLOG("Can not open file %s", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (! out)
            {
                CCLOG("Can not open destination file %s", fullPath.c_str());
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
                    CCLOG("Can not read zip file %s, error code is %d", fileName, error);
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
                CCLOG("Can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    CCLOG("End uncompressing");
    this->sendStateMessage(kUncompressDone);
    
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
    command += "\"" + string(path) + "\"";
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

int downloadProgressFunc(void *ptr, double totalToDownload, double nowDownloaded,
                              double totalToUpLoad, double nowUpLoaded)
{
    Updater* manager = (Updater*)ptr;
    Updater::Message *msg = new Updater::Message();
    msg->what = UPDATER_MESSAGE_PROGRESS;
    
    ProgressMessage *progressData = new ProgressMessage();

    progressData->percent = totalToDownload > 0 ?
        (int)(nowDownloaded/totalToDownload*100) :
        0;
    progressData->manager = manager;
    msg->obj = progressData;
    
    manager->_schedule->sendMessage(msg);
    
    //CCLOG("downloading... %d%%", progressData->percent);
    return 0;
}

bool Updater::download(const char* fileUrl, const char* filePath)
{
    // Create a file to save package.
    string outFileName = string(filePath);
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (! fp)
    {
        sendErrorMessage(kCreateFile);
        CCLOG("can not create file %s", outFileName.c_str());
        return false;
    }
    
    _curl = curl_easy_init();
    if (! _curl)
    {
        sendErrorMessage(kNetwork);
        CCLOG("Updater::download(%s, %s) Can not init curl!", fileUrl, filePath);
        return false;
    }
    
    this->sendStateMessage(kDownStart);
    
    // Download pacakge
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, fileUrl);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downloadWriteFunc);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    curl_easy_setopt(_curl, CURLOPT_FRESH_CONNECT, 1);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("Error when download package");
        fclose(fp);
        return false;
    }
    
    CCLOG("Succeed downloading file %s", fileUrl);
    
    fclose(fp);
    this->sendStateMessage(kDownDone);
    return true;
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
    CCScriptEngineManager::sharedManager()->getScriptEngine()->
        removeScriptHandler(_scriptHandler);
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

void Updater::sendSuccMessage()
{
    // Record updated version and remove downloaded zip file
    Message *msg = new Message();
    msg->what = UPDATER_MESSAGE_UPDATE_SUCCEED;
    msg->obj = this;
    
    _schedule->sendMessage(msg);
    _updateType = kUpdateUndefined;
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

void Updater::sendStateMessage(Updater::StateCode code)
{
    Message *msg = new Message();
    msg->what = UPDATER_MESSAGE_STATE;
    
    StateMessage *stateMessage = new StateMessage();
    stateMessage->code = code;
    stateMessage->manager = this;
    msg->obj = stateMessage;
    
    _schedule->sendMessage(msg);
}

void Updater::clearTid()
{
    if(_tid)
    {
        delete _tid;
        _tid = NULL;
    }
}

bool Updater::isAvailable()
{
    if(_tid) return false;
    if(_updateType!=kUpdateUndefined)
    {
 
        CCLOG("Update is running!");
        return false;
    }
    return true;
}

// Implementation of UpdaterHelper

Updater::Helper::Helper()
{
    //CCLOG("Updater::Helper::Helper()");
    _messageQueue = new list<Message*>();
    pthread_mutex_init(&_messageQueueMutex, NULL);
}

Updater::Helper::~Helper()
{
    //TODO 2014-08-19 zrong
    // The Helper::update lost the lastest message in MacOS.
    // But in XCode debug mode, the message is correct.
    // Add the CCLOG in here can fix it .
    // It's a stonger bug. Perhaps about multi-thread or lua.
    CCLOG("Updater::Helper::~Helper()");
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
    //CCLOG("_messageQueue:%d", _messageQueue->size());
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
        case UPDATER_MESSAGE_STATE:
            handlerState(msg);
            break;
        case UPDATER_MESSAGE_PROGRESS:
            handlerProgress(msg);
            break;
        case UPDATER_MESSAGE_ERROR:
            handlerError(msg);
            break;
        default:
            break;
    }
    
    delete msg;
}

void Updater::Helper::handleUpdateSucceed(Message *msg)
{
    Updater* manager = (Updater*)msg->obj;
    CCLOG("Updater::helper::handlerUpdateSuccessed pointer %u handler %u", manager, manager->_scriptHandler);
    if (manager)
    {
        manager->clearOnSuccess();

        if (manager->_delegate)
        {
            manager->_delegate->onSuccess();
        }
        if (manager->_scriptHandler)
        {
            CCScriptEngineManager::sharedManager()
                ->getScriptEngine()
                ->executeEvent(
                               manager->_scriptHandler,
                               "success",
                               CCString::create("success"),
                               "CCString"
                               );
        }
    }
    else
    {
        CCLOG("Updater::Helper::handlerUpdateSuccessed Can not get the Update instance!");
    }
}

void Updater::Helper::handlerState(Message *msg)
{
    StateMessage* stateMsg = (StateMessage*)msg->obj;
    if(stateMsg->manager->_delegate)
    {
        stateMsg->manager->_delegate->onState(stateMsg->code);
    }
    if (stateMsg->manager->_scriptHandler)
    {
        std::string stateMessage;
        switch ((StateCode)stateMsg->code)
        {
            case kDownStart:
                stateMessage = "downloadStart";
                break;
                
            case kDownDone:
                stateMessage = "downloadDone";
                break;
                
            case kUncompressStart:
                stateMessage = "uncompressStart";
                break;
            case kUncompressDone:
                stateMessage = "uncompressDone";
                break;
                
            default:
                stateMessage = "stateUnknown";
        }
        
        CCScriptEngineManager::sharedManager()
            ->getScriptEngine()
            ->executeEvent(
                           stateMsg->manager->_scriptHandler,
                           "state",
                           CCString::create(stateMessage.c_str()),
                           "CCString");
    }
    
    delete ((StateMessage*)msg->obj);
}

void Updater::Helper::handlerError(Message* msg)
{
    ErrorMessage* errorMsg = (ErrorMessage*)msg->obj;
    if (errorMsg->manager->_delegate)
    {
        errorMsg->manager->_delegate
            ->onError(errorMsg->code);
    }
    if (errorMsg->manager->_scriptHandler)
    {
        std::string errorMessage;
        switch (errorMsg->code)
        {
            case kCreateFile:
                errorMessage = "errorCreateFile";
                break;
                
            case kNetwork:
                errorMessage = "errorNetwork";
                break;
                
            case kUncompress:
                errorMessage = "errorUncompress";
                break;
                
            default:
                errorMessage = "errorUnknown";
        }
        
        CCScriptEngineManager::sharedManager()
            ->getScriptEngine()
            ->executeEvent(
                           errorMsg->manager->_scriptHandler,
                           "error",
                           CCString::create(errorMessage.c_str()),
                           "CCString"
                           );
    }
    
    delete ((ErrorMessage*)msg->obj);
}

void Updater::Helper::handlerProgress(Message* msg)
{
    ProgressMessage* progMsg = (ProgressMessage*)msg->obj;
    if (progMsg->manager->_delegate)
    {
        progMsg->manager->_delegate
            ->onProgress(progMsg->percent);
    }
    if (progMsg->manager->_scriptHandler)
    {
        //char buff[10];
        //sprintf(buff, "%d", ((ProgressMessage*)msg->obj)->percent);
        CCScriptEngineManager::sharedManager()
            ->getScriptEngine()
            ->executeEvent(
                       progMsg->manager->_scriptHandler,
                       "progress",
                       CCInteger::create(progMsg->percent),
                       "CCInteger"
                       );
    }
    
    delete (ProgressMessage*)msg->obj;
}

NS_CC_EXT_END;
#endif // CC_PLATFORM_WINRT
