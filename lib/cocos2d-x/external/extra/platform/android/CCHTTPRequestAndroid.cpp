#include "network/CCHTTPRequest.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include "platform/android/jni/jniHelper.h"

#if CC_LUA_ENGINE_ENABLED > 0
extern "C" {
#include "lua.h"
}
#include "CCLuaEngine.h"
#endif
#include <sstream>


NS_CC_EXTRA_BEGIN

unsigned int CCHTTPRequest::s_id = 0;

static jclass      s_classHttp = NULL;
static pthread_key_t s_threadKey;

static bool getEnv(JNIEnv **env)
{
    bool bRet = false;
    JavaVM* jvm = JniHelper::getJavaVM();

    switch(jvm->GetEnv((void**)env, JNI_VERSION_1_4))
    {
    case JNI_OK:
        bRet = true;
            break;
    case JNI_EDETACHED:
        pthread_key_create (&s_threadKey, NULL);
        if (jvm->AttachCurrentThread(env, 0) < 0)
        {
            CCLOG("Failed to get the environment using AttachCurrentThread()");
            break;
        }
        if (pthread_getspecific(s_threadKey) == NULL)
            pthread_setspecific(s_threadKey, env); 
        bRet = true;
        break;
    default:
        CCLOG("Failed to get the environment using GetEnv()");
        break;
    }      

    return bRet;
}

static jclass getClassID_(const char *className, JNIEnv *env)
{
    JNIEnv *pEnv = env;
    jclass ret = 0;

    do 
    {
        if (! pEnv)
        {
            if (! getEnv(&pEnv))
            {
                break;
            }
        }
        
        if (NULL == s_classHttp) {
            ret = pEnv->FindClass(className);
            s_classHttp = (jclass)pEnv->NewGlobalRef(ret);
        }
        ret = (jclass)pEnv->NewLocalRef(s_classHttp);
        
        if (! ret)
        {
            CCLOG("Failed to find class of %s", className);
            break;
        }
    } while (0);

    return ret;
}

static bool getStaticMethodInfo(
    JniMethodInfo &methodinfo,
    const char *className,
    const char *methodName,
    const char *paramCode) {
    jmethodID methodID = 0;
    JNIEnv *pEnv = 0;
    bool bRet = false;

    do 
    {
        if (! getEnv(&pEnv))
        {
            break;
        }

        jclass classID = getClassID_(className, pEnv);

        methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
        if (! methodID)
        {
            CCLOG("Failed to find static method id of %s", methodName);
            break;
        }

        methodinfo.classID = classID;
        methodinfo.env = pEnv;
        methodinfo.methodID = methodID;

        bRet = true;
    } while (0);

    return bRet;
}

// jni helper function
jobject getInstance(JNIEnv* env, jclass obj_class)
{  
    jmethodID construction_id = env->GetMethodID(obj_class, "<init>", "()V");  
    jobject obj = env->NewObject(obj_class, construction_id);  
    return obj;  
} 

CCHTTPRequest *CCHTTPRequest::createWithUrl(CCHTTPRequestDelegate *delegate,
                                            const char *url,
                                            int method)
{
    CCHTTPRequest *request = new CCHTTPRequest();
    request->initWithDelegate(delegate, url, method);
    request->autorelease();
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCHTTPRequest *CCHTTPRequest::createWithUrlLua(LUA_FUNCTION listener,
                                               const char *url,
                                               int method)
{
    CCHTTPRequest *request = new CCHTTPRequest();
    request->initWithListener(listener, url, method);
    request->autorelease();
    return request;
}
#endif

bool CCHTTPRequest::initWithDelegate(CCHTTPRequestDelegate *delegate, const char *url, int method)
{
    m_delegate = delegate;
    return initWithUrl(url, method);
}

#if CC_LUA_ENGINE_ENABLED > 0
bool CCHTTPRequest::initWithListener(LUA_FUNCTION listener, const char *url, int method)
{
    m_listener = listener;
    return initWithUrl(url, method);
}
#endif

bool CCHTTPRequest::initWithUrl(const char *url, int method)
{
    CCAssert(url, "CCHTTPRequest::initWithUrl() - invalid url");

    m_url = url;

    if (method == kCCHTTPRequestMethodPOST) {
        m_httpMethod = "POST";
    } else {
        m_httpMethod = "GET";
    }

    ++s_id;
    // CCLOG("HTTPRequest[0x%04x] - create request with url: %s", s_id, url);
    return true;
}

CCHTTPRequest::~CCHTTPRequest(void)
{
    cleanup();
    if (m_listener)
    {
        CCLuaEngine::defaultEngine()->removeScriptHandler(m_listener);
    }
    // CCLOG("CCHTTPRequest[0x%04x] - request removed", s_id);
}

void CCHTTPRequest::setRequestUrl(const char *url)
{
    CCAssert(url, "CCHTTPRequest::setRequestUrl() - invalid url");
    m_url = url;
}

const string CCHTTPRequest::getRequestUrl(void)
{
    return m_url;
}

void CCHTTPRequest::addRequestHeader(const char *header)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::addRequestHeader() - request not idle");
    CCAssert(header, "CCHTTPRequest::addRequestHeader() - invalid header");
    m_headers.push_back(string(header));
}

void CCHTTPRequest::addPOSTValue(const char *key, const char *value)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::addPOSTValue() - request not idle");
    CCAssert(key, "CCHTTPRequest::addPOSTValue() - invalid key");
    m_postFields[string(key)] = string(value ? value : "");
}

void CCHTTPRequest::setPOSTData(const char *data, size_t len)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::setPOSTData() - request not idle");
    CCAssert(data, "CCHTTPRequest::setPOSTData() - invalid post data");
    m_postFields.clear();
    if (0 == len) {
        len = strlen(data);
    }
    if (0 == len) {
        return;
    }
    if (m_postData)
    {
        free(m_postData);
        m_postDataLen = 0;
        m_postData = NULL;
    }
    m_postData = malloc(len + 1);
    memset(m_postData, 0, len + 1);
    if (NULL == m_postData)
    {
        return;
    }
    memcpy(m_postData, data, len);
    m_postDataLen = len;
}

void CCHTTPRequest::addFormFile(const char *name, const char *filePath, const char *contentType)
{
    m_postFile[string(name)] = string(filePath);
    string str = string("Content-Type:");
    str = str.append(contentType);
    m_headers.push_back(str);
}

void CCHTTPRequest::addFormContents(const char *name, const char *value)
{
    m_postContent[string(name)] = string(value);
    string str = string("Content-Type:multipart/form-data");
    m_headers.push_back(str);
    CCLOG("addFormContents:%d", m_headers.size());
}

void CCHTTPRequest::setCookieString(const char *cookie)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::setAcceptEncoding() - request not idle");
    m_cookies = cookie ? cookie : "";
}

const string CCHTTPRequest::getCookieString(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::getResponseData() - request not completed");
    return m_responseCookies;
}

void CCHTTPRequest::setAcceptEncoding(int acceptEncoding)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::setAcceptEncoding() - request not idle");
    //TODO
}

void CCHTTPRequest::setTimeout(int timeout)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::setTimeout() - request not idle");
    m_nTimeOut = timeout;
}

bool CCHTTPRequest::start(void)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "CCHTTPRequest::start() - request not idle");

    m_state = kCCHTTPRequestStateInProgress;
    m_curlState = kCCHTTPRequestCURLStateBusy;
    retain();

    createURLConnectJava();
    setRequestMethodJava();
    setTimeoutJava(m_nTimeOut*1000);

    bool bBoundary = isNeedBoundary();
    for (CCHTTPRequestHeadersIterator it = m_headers.begin(); it != m_headers.end(); ++it)
    {
        string val = *it;
        int len = val.length();
        int pos = val.find(':');
        if (-1 == pos || pos >= len) {
            continue;
        }
        string str1 = val.substr(0, pos);
        string str2 = val.substr(pos + 1, len - pos - 1);

        addRequestHeaderJava(str1.c_str(), str2.c_str(), bBoundary);
    }

    if (m_cookies && 0 != strlen(m_cookies)) {
        addRequestHeaderJava("Cookie", m_cookies, bBoundary);
    }

    // memset(&m_thread, 0, sizeof(pthread_t));
    // memset(&m_threadAttr, 0, sizeof(pthread_attr_t));
    // pthread_attr_init (&m_threadAttr);
    // pthread_attr_setdetachstate (&m_threadAttr,PTHREAD_CREATE_DETACHED);
    // pthread_create(&m_thread, &m_threadAttr, requestCURL, this);
    pthread_create(&m_thread, NULL, requestCURL, this);
    // pthread_detach(m_thread);
    // onRequest();

    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);

    return true;
}

void CCHTTPRequest::cancel(void)
{
    m_delegate = NULL;
    if (m_state == kCCHTTPRequestStateIdle || m_state == kCCHTTPRequestStateInProgress)
    {
        m_state = kCCHTTPRequestStateCancelled;
    }
}

int CCHTTPRequest::getState(void)
{
    return m_state;
}

int CCHTTPRequest::getResponseStatusCode(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return m_responseCode;
}

const CCHTTPRequestHeaders &CCHTTPRequest::getResponseHeaders(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::getResponseHeaders() - request not completed");
    return m_responseHeaders;
}

const string CCHTTPRequest::getResponseHeadersString()
{
    string buf;
    for (CCHTTPRequestHeadersIterator it = m_responseHeaders.begin(); it != m_responseHeaders.end(); ++it)
    {
        buf.append(*it);
    }
    return buf;
}

const string CCHTTPRequest::getResponseString(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::getResponseString() - request not completed");
    return string(m_responseBuffer ? static_cast<char*>(m_responseBuffer) : "");
}

void *CCHTTPRequest::getResponseData(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::getResponseData() - request not completed");
    void *buff = malloc(m_responseDataLength);
    memcpy(buff, m_responseBuffer, m_responseDataLength);
    return buff;
}

#if CC_LUA_ENGINE_ENABLED > 0
LUA_STRING CCHTTPRequest::getResponseDataLua(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::getResponseDataLua() - request not completed");
    CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->clean();
    stack->pushString(static_cast<char*>(m_responseBuffer), (int)m_responseDataLength);
    return 1;
}
#endif

int CCHTTPRequest::getResponseDataLength(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return (int)m_responseDataLength;
}

size_t CCHTTPRequest::saveResponseData(const char *filename)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "CCHTTPRequest::saveResponseData() - request not completed");
    
    FILE *fp = fopen(filename, "wb");
    CCAssert(fp, "CCHTTPRequest::saveResponseData() - open file failure");
    
    size_t writedBytes = m_responseDataLength;
    if (writedBytes > 0)
    {
        fwrite(m_responseBuffer, m_responseDataLength, 1, fp);
    }
    fclose(fp);
    return writedBytes;
}

int CCHTTPRequest::getErrorCode(void)
{
    return m_errorCode;
}

const string CCHTTPRequest::getErrorMessage(void)
{
    return m_errorMessage;
}

CCHTTPRequestDelegate* CCHTTPRequest::getDelegate(void)
{
    return m_delegate;
}

void CCHTTPRequest::checkCURLState(float dt)
{
    CC_UNUSED_PARAM(dt);
    if (m_curlState != kCCHTTPRequestCURLStateBusy)
    {
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
        release();
    }
}

void CCHTTPRequest::update(float dt)
{
    if (m_state == kCCHTTPRequestStateInProgress)
    {
#if CC_LUA_ENGINE_ENABLED > 0
        if (m_listener)
        {
            CCLuaValueDict dict;

            dict["name"] = CCLuaValue::stringValue("inprogress");
            dict["total"] = CCLuaValue::intValue(m_ultotal);
            dict["dltotal"] = CCLuaValue::intValue(m_dltotal);
            dict["request"] = CCLuaValue::ccobjectValue(this, "CCHTTPRequest");

            CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
            stack->clean();
            stack->pushCCLuaValueDict(dict);
            stack->executeFunctionByHandler(m_listener, 1);
        }
#endif
        return;
    }

    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    if (m_curlState != kCCHTTPRequestCURLStateIdle)
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCHTTPRequest::checkCURLState), this, 0, false);
    }

    if (m_state == kCCHTTPRequestStateCompleted)
    {
        // CCLOG("CCHTTPRequest[0x%04x] - request completed", s_id);
        if (m_delegate) m_delegate->requestFinished(this);
    }
    else
    {
        // CCLOG("CCHTTPRequest[0x%04x] - request failed", s_id);
        if (m_delegate) m_delegate->requestFailed(this);
    }

#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        CCLuaValueDict dict;

        switch (m_state)
        {
            case kCCHTTPRequestStateCompleted:
                dict["name"] = CCLuaValue::stringValue("completed");
                break;
                
            case kCCHTTPRequestStateCancelled:
                dict["name"] = CCLuaValue::stringValue("cancelled");
                break;
                
            case kCCHTTPRequestStateFailed:
                dict["name"] = CCLuaValue::stringValue("failed");
                break;
                
            default:
                dict["name"] = CCLuaValue::stringValue("unknown");
        }
        dict["request"] = CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->clean();
        stack->pushCCLuaValueDict(dict);
        stack->executeFunctionByHandler(m_listener, 1);
    }
#endif
}

// instance callback

void CCHTTPRequest::onRequest(void)
{
    CCLOG("CCHTTPRequest - onRequest entry");
    int nSuc = connectJava();
    int code = 0;

    CCLOG("CCHTTPRequest - onRequest connect:%d", nSuc);

    if (0 == nSuc) {
        if (m_postFields.size() > 0)
        {
            bool bNeedConnectSym = false;
            for (Fields::iterator it = m_postFields.begin(); it != m_postFields.end(); ++it)
            {
                postContentJava(it->first.c_str(), it->second.c_str(), bNeedConnectSym);
                bNeedConnectSym = true;
            }
        }

        if (m_postDataLen > 0)
        {
            postContentByteArrayJava(m_postData, m_postDataLen);
        }

        if (m_postContent.size() > 0)
        {
            for (Fields::iterator it = m_postContent.begin(); it != m_postContent.end(); ++it)
            {
                postFromContentJava(it->first.c_str(), it->second.c_str());
            }
        }
        if (m_postFile.size() > 0)
        {
            for (Fields::iterator it = m_postFile.begin(); it != m_postFile.end(); ++it)
            {
                postFromFileJava(it->first.c_str(), it->second.c_str());
            }
        }

        if (NULL != m_httpMethod && 0 == strcmp(m_httpMethod, "POST")) {
            postFormEndJava(isNeedBoundary());
        }

        //set cookie TODO

        code = getResponedCodeJava();

        CCLOG("CCHTTPRequest responed code:%d", code);

        char* header = NULL;

        int nCounter = 0;
        while(true) {
            header = getResponedHeaderByIdxJava(nCounter);
            if (NULL == header) {
                break;
            }
            onWriteHeader(header, strlen(header));
            free(header);
            header = NULL;
            nCounter++;
        }

        //get cookies
        char* strCookies = getResponedHeaderByKeyJava("set-cookie");
        if (NULL != strCookies) {
            m_responseCookies = strCookies;
            free(strCookies);
        }

        //content len
        int nContentLen = getResponedHeaderByKeyIntJava("Content-Length");

        while (true) {
            char* recvData = NULL;
            int nRecv = 0;
            nRecv = getResponedStringJava(&recvData);
            if (NULL == recvData) {
                code = 0;
                CCLOG("CCHTTPRequest - onRequest, get null responed string");
                break;
            } else {
                if (1 == (char)(*recvData)) {
                    nRecv -= 1;
                    onWriteData(recvData + 1, nRecv);

                    //here m_responseDataLength have add nRecv value
                    onProgress(m_responseDataLength, nRecv, nContentLen, nRecv);

                    free(recvData);
                } else {
                    // CCLOG("CCHTTPRequest - onRequest, responed string completed");
                    free(recvData);
                    break;
                }
            }
        }
    }

    m_errorCode = code;
    m_responseCode = code;
    m_errorMessage = (code >= 200 && code < 300) ? "" : getResponedErrJava();
    m_state = (code >= 200 && code < 600) ? kCCHTTPRequestStateCompleted : kCCHTTPRequestStateFailed;
    m_curlState = kCCHTTPRequestCURLStateClosed;
}

size_t CCHTTPRequest::onWriteData(void *buffer, size_t bytes)
{
    if (m_responseDataLength + bytes + 1 > m_responseBufferLength)
    {
        m_responseBufferLength += BUFFER_CHUNK_SIZE;
        m_responseBuffer = realloc(m_responseBuffer, m_responseBufferLength);
    }

    memcpy(static_cast<char*>(m_responseBuffer) + m_responseDataLength, buffer, bytes);
    m_responseDataLength += bytes;
    static_cast<char*>(m_responseBuffer)[m_responseDataLength] = 0;
    return bytes;
}

size_t CCHTTPRequest::onWriteHeader(void *buffer, size_t bytes)
{
    char *headerBuffer = new char[bytes + 1];
    headerBuffer[bytes] = 0;
    memcpy(headerBuffer, buffer, bytes);    
    m_responseHeaders.push_back(string(headerBuffer));
    delete []headerBuffer;
    return bytes;
}

int CCHTTPRequest::onProgress(double dltotal, double dlnow, double ultotal, double ulnow)
{
    m_dltotal = dltotal;
    m_dlnow = dlnow;
    m_ultotal = ultotal;
    m_ulnow = ulnow;

    return m_state == kCCHTTPRequestStateCancelled ? 1: 0;
}

void CCHTTPRequest::cleanup(void)
{
    m_state = kCCHTTPRequestStateCleared;
    m_responseBufferLength = 0;
    m_responseDataLength = 0;
    m_postDataLen = 0;
    if (m_postData)
    {
        free(m_postData);
        m_postData = NULL;
    }
    if (m_responseBuffer)
    {
        free(m_responseBuffer);
        m_responseBuffer = NULL;
    }
    if (m_httpConnect)
    {
        closeJava();
        JNIEnv* env;
        getEnv(&env);
        env->DeleteGlobalRef(m_httpConnect);
        m_httpConnect = NULL;
    }
}

// curl callback

void *CCHTTPRequest::requestCURL(void *userdata)
{
    CCLOG("CCHTTPRequest - requestCURL entry");
    int nRet = 0;
    CCHTTPRequest* httpRequest = static_cast<CCHTTPRequest*>(userdata);
    JavaVM* jvm = JniHelper::getJavaVM();
    // JNIEnv *env = NULL;
    // getEnv(&env);
    // nRet = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    // if (nRet >= 0) {
    //     CCLOG("ERROR, get JNIEnv fail:%d", nRet);
    //     return NULL;
    // }

    //Attach Thread
    // CCLOG("CCHTTPRequest - requestCURL attach");
    // nRet = jvm->AttachCurrentThread(&env, NULL);
    // if (JNI_OK != nRet) {
    //     CCLOG("ERROR, attach thread fail:%d", nRet);
    //     return NULL;
    // }
    // CCLOG("CCHTTPRequest - requestCURL attach finish");

    httpRequest->onRequest();

    //Detach Thread
    nRet = jvm->DetachCurrentThread();
    if( JNI_OK != nRet) {
        CCLOG("ERROR, detach thread fail:%d", nRet);
    }

    // pthread_detach(pthread_self());
    pthread_exit((void *)0);
    return NULL;
}

size_t CCHTTPRequest::writeDataCURL(void *buffer, size_t size, size_t nmemb, void *userdata)
{
    return static_cast<CCHTTPRequest*>(userdata)->onWriteData(buffer, size *nmemb);
}

size_t CCHTTPRequest::writeHeaderCURL(void *buffer, size_t size, size_t nmemb, void *userdata)
{
    return static_cast<CCHTTPRequest*>(userdata)->onWriteHeader(buffer, size *nmemb);
}

int CCHTTPRequest::progressCURL(void *userdata, double dltotal, double dlnow, double ultotal, double ulnow)
{
    return static_cast<CCHTTPRequest*>(userdata)->onProgress(dltotal, dlnow, ultotal, ulnow);
}



bool CCHTTPRequest::isNeedBoundary() {
    if (0 == m_postFile.size() && 0 == m_postContent.size()) {
        return false;
    } else {
        return true;
    }
}

void CCHTTPRequest::createURLConnectJava() {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "createURLConnect",
        "(Ljava/lang/String;)Ljava/net/HttpURLConnection;"))
    {
        jstring jurl = methodInfo.env->NewStringUTF(m_url.c_str());
        jobject jObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, jurl);
        m_httpConnect = methodInfo.env->NewGlobalRef(jObj);
        methodInfo.env->DeleteLocalRef(jurl);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::setRequestMethodJava() {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "setRequestMethod",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;)V"))
    {
        jstring jstr = methodInfo.env->NewStringUTF(m_httpMethod);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstr);
        methodInfo.env->DeleteLocalRef(jstr);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::addRequestHeaderJava(const char* key, const char* value, bool bBoundary) {
    CCLOG("CCHTTPRequest - addRequestHeaderJava:key = %s, val = %s", key, value);
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "addRequestHeader",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        jstring jstrKey = methodInfo.env->NewStringUTF(key);
        jstring jstrVal = methodInfo.env->NewStringUTF(value);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrKey, jstrVal, bBoundary);
        methodInfo.env->DeleteLocalRef(jstrKey);
        methodInfo.env->DeleteLocalRef(jstrVal);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::setTimeoutJava(int msTime) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "setTimeout",
        "(Ljava/net/HttpURLConnection;I)V"))
    {
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, msTime);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

int CCHTTPRequest::connectJava() {
    CCLOG("CCHTTPRequest - connectJava entry");
    int nSuc = 0;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "connect",
        "(Ljava/net/HttpURLConnection;)I"))
    {
        CCLOG("CCHTTPRequest - connectJava 1");
        nSuc = methodInfo.env->CallStaticIntMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    CCLOG("CCHTTPRequest - connectJava exit");

    return nSuc;
}

void CCHTTPRequest::postContentJava(const char* key, const char* value, bool bConnectSym) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "postContent",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;Ljava/lang/String;Z)V"))
    {
        jstring jstrKey = methodInfo.env->NewStringUTF(key);
        jstring jstrVal = methodInfo.env->NewStringUTF(value);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrKey, jstrVal, bConnectSym);
        methodInfo.env->DeleteLocalRef(jstrKey);
        methodInfo.env->DeleteLocalRef(jstrVal);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::postContentByteArrayJava(void* val, size_t len) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "postContentByteArray",
        "(Ljava/net/HttpURLConnection;[B)V"))
    {
        jbyteArray bytearray;
        bytearray = methodInfo.env->NewByteArray(len);
        methodInfo.env->SetByteArrayRegion(bytearray, 0, len, (const jbyte*)val);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, bytearray);
        methodInfo.env->DeleteLocalRef(bytearray);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::postFromContentJava(const char* key, const char* value) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "postFormContent",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring jstrKey = methodInfo.env->NewStringUTF(key);
        jstring jstrVal = methodInfo.env->NewStringUTF(value);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrKey, jstrVal);
        methodInfo.env->DeleteLocalRef(jstrKey);
        methodInfo.env->DeleteLocalRef(jstrVal);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::postFromFileJava(const char* fileName, const char* filePath) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "postFormFile",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring jstrFile = methodInfo.env->NewStringUTF(fileName);
        jstring jstrPath = methodInfo.env->NewStringUTF(filePath);
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrFile, jstrPath);
        methodInfo.env->DeleteLocalRef(jstrFile);
        methodInfo.env->DeleteLocalRef(jstrPath);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void CCHTTPRequest::postFormEndJava(bool bBoundary) {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "postFormEnd",
        "(Ljava/net/HttpURLConnection;Z)V"))
    {
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, bBoundary);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

int CCHTTPRequest::getResponedCodeJava() {
    int nResponed = 0;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedCode",
        "(Ljava/net/HttpURLConnection;)I"))
    {
        nResponed = methodInfo.env->CallStaticIntMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return nResponed;
}

char* CCHTTPRequest::getResponedErrJava() {
    char* error = nullptr;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedErr",
        "(Ljava/net/HttpURLConnection;)Ljava/lang/String;"))
    {
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        error = getCStrFromJString((jstring)jObj, methodInfo.env);
        if (NULL != jObj) {
            methodInfo.env->DeleteLocalRef(jObj);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return error;
}

char* CCHTTPRequest::getResponedHeaderJava() {
    char* header = nullptr;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedHeader",
        "(Ljava/net/HttpURLConnection;)Ljava/lang/String;"))
    {
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        header = getCStrFromJString((jstring)jObj, methodInfo.env);
        if (NULL != jObj) {
            methodInfo.env->DeleteLocalRef(jObj);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return header;
}

char* CCHTTPRequest::getResponedHeaderByIdxJava(int idx) {
    char* header = nullptr;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedHeaderByIdx",
        "(Ljava/net/HttpURLConnection;I)Ljava/lang/String;"))
    {
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, idx);
        header = getCStrFromJString((jstring)jObj, methodInfo.env);
        if (NULL != jObj) {
            methodInfo.env->DeleteLocalRef(jObj);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return header;
}

char* CCHTTPRequest::getResponedHeaderByKeyJava(const char* key) {
    char* value = NULL;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedHeaderByKey",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;)Ljava/lang/String;"))
    {
        jstring jstrKey = methodInfo.env->NewStringUTF(key);
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrKey);
        value = getCStrFromJString((jstring)jObj, methodInfo.env);
        methodInfo.env->DeleteLocalRef(jstrKey);
        if (NULL != jObj) {
            methodInfo.env->DeleteLocalRef(jObj);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return value;
}

int CCHTTPRequest::getResponedHeaderByKeyIntJava(const char* key) {
    int nContentLen = 0;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedHeaderByKeyInt",
        "(Ljava/net/HttpURLConnection;Ljava/lang/String;)I"))
    {
        jstring jstrKey = methodInfo.env->NewStringUTF(key);
        nContentLen = methodInfo.env->CallStaticIntMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect, jstrKey);
        methodInfo.env->DeleteLocalRef(jstrKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return nContentLen;
}

int CCHTTPRequest::getResponedStringJava(char** ppData) {
    int nDataLen = 0;
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "getResponedString",
        "(Ljava/net/HttpURLConnection;)[B"))
    {
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        nDataLen = getCStrFromJByteArray((jbyteArray)jObj, methodInfo.env, ppData);
        if (NULL != jObj) {
            methodInfo.env->DeleteLocalRef(jObj);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return nDataLen;
}

void CCHTTPRequest::closeJava() {
    JniMethodInfo methodInfo;
    if (getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/QuickHTTPInterface",
        "close",
        "(Ljava/net/HttpURLConnection;)V"))
    {
        methodInfo.env->CallStaticVoidMethod(
            methodInfo.classID, methodInfo.methodID, m_httpConnect);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

char* CCHTTPRequest::getCStrFromJString(jstring jstr, JNIEnv* env) {
    if (NULL == jstr) {
        return NULL;
    }

    const char* str = NULL;
    char* strRet = NULL;
    str = env->GetStringUTFChars(jstr, NULL);
    if (NULL != str) {
        strRet = strdup(str);
    }
    env->ReleaseStringUTFChars(jstr, str);

    return strRet;
}

int CCHTTPRequest::getCStrFromJByteArray(jbyteArray jba, JNIEnv* env, char** ppData) {
    if (NULL == jba) {
        *ppData = NULL;
        return 0;
    }

    char* str = NULL;

    int len  = env->GetArrayLength(jba);
    str = (char*)malloc(sizeof(char)*len);
    env->GetByteArrayRegion(jba, 0, len, (jbyte*)str);

    *ppData = str;
    return len;
}



NS_CC_EXTRA_END
